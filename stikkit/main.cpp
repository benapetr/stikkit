//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include <cstring>
#include <iostream>
#include <errno.h>
#include <string>
#include <curl/curl.h>
#include <fstream>
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
        // we need to provide some author name otherwise stikked will not display anything or some random characters there
        Stikkit::Configuration::Author = "Unknown";
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
    if (Stikkit::Configuration::Input.length())
    {
        // user wants to upload some file
        std::ifstream infile(Stikkit::Configuration::Input.c_str());
        if (!infile)
        {
            cerr << "File could not be opened!" << endl;
            cerr << "Error code: " << strerror(errno) << endl;
            return 61;
        }
        while (std::getline(infile, line))
            Stikkit::Configuration::Source += line + "\n";
    } else
    {
        while (getline(std::cin, line))
            Stikkit::Configuration::Source += line + "\n";
    }
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
        if (Stikkit::Configuration::Apikey.length() > 0)
        {
            Stikkit::Configuration::URL += "?apikey=";
            Stikkit::Configuration::URL += curl_easy_escape(curl, Stikkit::Configuration::Apikey.c_str(), Stikkit::Configuration::Apikey.length());
        }

        if (Stikkit::Configuration::Lang.length() > 0)
        {
            post += "&lang=";
            post += curl_easy_escape(curl, Stikkit::Configuration::Lang.c_str(), Stikkit::Configuration::Lang.length());
        }

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
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "stikkit");

        /* Perform the request, res will get the return HTTP code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        cerr << "\n";
        if(res != CURLE_OK)
        {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return 12;
        }
        if (!Stikkit::Configuration::NoExtras)
            cout << "Successfully pastebined to: " << readBuffer;
        else
            cout << readBuffer;
        curl_easy_cleanup(curl);
    } else
    {
        Stikkit::Syslog::ErrorLog("Unable to init curl");
    }
    return 0;
}
