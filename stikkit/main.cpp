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
#include <curl/curl.h>
#include "configuration.hpp"
#include "terminalparser.hpp"
#include "syslog.hpp"

int main(int argc, char *argv[])
{
    Stikkit::TerminalParser *t = new Stikkit::TerminalParser(argc, argv);
    if (t->Parse())
    {
        delete t;
        return 0;
    }
    delete t;
    if (!Stikkit::Configuration::URL.length())
    {
        Stikkit::Syslog::ErrorLog("No URL to stikked server provided, use stikkit -b <URL>");
        return 20;
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
        string post = "text=";
        post += curl_easy_escape(curl, Stikkit::Configuration::Source.c_str(), Stikkit::Configuration::Source.length());
        post += "&name=";
        post += curl_easy_escape(curl, Stikkit::Configuration::Author.c_str(), Stikkit::Configuration::Author.length());
        curl_easy_setopt(curl, CURLOPT_URL, Stikkit::Configuration::URL.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
          cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;

        curl_easy_cleanup(curl);
    } else
    {
        Stikkit::Syslog::ErrorLog("Unable to init curl");
    }
    return 0;
}
