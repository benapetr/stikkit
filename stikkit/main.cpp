//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include <iostream>
#include <string>
#include <unistd.h>
#include <curl/curl.h>
#include "configuration.hpp"
#include "terminalparser.hpp"
#include "syslog.hpp"

static std::string readBuffer;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb)
{
    size_t realsize = size * nmemb;
    readBuffer.append((const char*)contents, realsize);
    return realsize;
}

int main(int argc, char *argv[])
{
    Stikkit::Configuration::Init();
    Stikkit::TerminalParser *t = new Stikkit::TerminalParser(argc, argv);
    if (t->Parse())
    {
        delete t;
        return 0;
    }
    delete t;
    if (!Stikkit::Configuration::Author.length())
    {
        char buffer[200];
        if (getlogin_r(buffer, 200))
        {
            Stikkit::Configuration::Author = buffer;
        }
    }
    if (!Stikkit::Configuration::URL.length())
    {
        if (Stikkit::Configuration::DefaultURL.length() > 0)
        {
            Stikkit::Configuration::URL = Stikkit::Configuration::DefaultURL;
        } else
        {
            Stikkit::Syslog::ErrorLog("No URL to stikked server provided, use stikkit -b <URL>");
            return 20;
        }
    }
    if (!Stikkit::Configuration::DefaultURL.length())
    {
        std::cout << "There is no default URL stored in configuration files, do you want to set " <<
                     Stikkit::Configuration::URL << " as a default URL? (y/n)";
        string response;
        std::cin >> response;
        if (response == "y" || response == "n")
        {
            if (response[0] == 'y')
            {
                Stikkit::Configuration::Store();
            }
        } else
        {
            Stikkit::Syslog::ErrorLog("Invalid option!");
            return 2;
        }
    }
    Stikkit::Configuration::URL += "/api/create";
    std::string line;
    while (std::cin >> line)
        Stikkit::Configuration::Source += line;
    if (Stikkit::Configuration::Source.size() < 1)
    {
        Stikkit::Syslog::Log("Refusing to upload empty string");
        return 60;
    }
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl)
    {
        readBuffer.clear();
        string post = "text=";
        post += curl_easy_escape(curl, Stikkit::Configuration::Source.c_str(), Stikkit::Configuration::Source.length());
        if (Stikkit::Configuration::Author.length() > 0)
        {
            post += "&name=";
            post += curl_easy_escape(curl, Stikkit::Configuration::Author.c_str(), Stikkit::Configuration::Author.length());
        }
        if (Stikkit::Configuration::Title.length() > 0)
        {
            post += "&title=";
            post += curl_easy_escape(curl, Stikkit::Configuration::Title.c_str(), Stikkit::Configuration::Title.length());
        }
        if (Stikkit::Configuration::Private)
            post += "&private=1";
        if (Stikkit::Configuration::Expiry != "0")
            post += "&expire=" + Stikkit::Configuration::Expiry;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_URL, Stikkit::Configuration::URL.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        cout << "Successfully pastebined to: " << readBuffer;
        curl_easy_cleanup(curl);
    } else
    {
        Stikkit::Syslog::ErrorLog("Unable to init curl");
    }
    return 0;
}
