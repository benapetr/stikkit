//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include "configuration.hpp"
using namespace Stikkit;
using namespace std;

unsigned int Configuration::Verbosity = 0;
string Configuration::Source = "";
string Configuration::URL = "";
string Configuration::Expiry = "0";
bool Configuration::Private = false;
string Configuration::Author = "";
string Configuration::Version = "1.0.6";
string Configuration::Title = "";
string Configuration::Home = "";
bool Configuration::NoExtras = false;
string Configuration::Input = "";
string Configuration::DefaultURL = "";
string Configuration::Apikey = "";

void Configuration::Init()
{
    struct stat st;
    struct passwd *pw = getpwuid(getuid());
    string homedir = pw->pw_dir;
    Configuration::Home = homedir;
    if (stat("/etc/stikkit/url", &st) != -1)
    {
        ifstream f;
        f.open("/etc/stikkit/url");
        string line;
        if (getline(f, line))
        {
            Configuration::DefaultURL = line;
        }
        f.close();
    }
    if (stat(string(homedir + "/.stikkit").c_str(), &st) == -1)
    {
        mkdir(string(homedir + "/.stikkit").c_str(), 0750);
    } else
    {
        ifstream f;
        f.open(string(homedir + "/.stikkit/url").c_str());
        string line;
        if(getline(f, line))
        {
            Configuration::DefaultURL = line;
        }
        f.close();

        //Apikey
        ifstream fapi;
        fapi.open(string(homedir + "/.stikkit/apikey").c_str());
        string lineapi;
        if(getline(fapi, lineapi))
        {
            Configuration::Apikey = lineapi;
        }
        fapi.close();

        //expiry
        ifstream fexp;
        fexp.open(string(homedir + "/.stikkit/expiry").c_str());
        string lineexp;
        if(getline(fexp, lineexp))
        {
            Configuration::Expiry = lineexp;
        }
        fexp.close();

        //author
        ifstream fauth;
        fauth.open(string(homedir + "/.stikkit/author").c_str());
        string lineauth;
        if(getline(fauth, lineauth))
        {
            Configuration::Author = lineauth;
        }
        fauth.close();
    }
    if (Configuration::Author.length() < 1)
    {
        // we don't have any author here! let's get it from passwd
        Configuration::Author = pw->pw_name;
    }
}

void Configuration::Store()
{
    ofstream myfile (string(Configuration::Home + "/.stikkit/url").c_str());
    if (myfile.is_open())
    {
        myfile << Configuration::URL << "\n";
        myfile.close();
    }
}
