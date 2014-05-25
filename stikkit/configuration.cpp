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
string Configuration::Expiry = "60";
bool Configuration::Private = false;
string Configuration::Author = "";
string Configuration::Version = "1.0.1";
string Configuration::Title = "";
string Configuration::Home = "";
string Configuration::DefaultURL = "";

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
