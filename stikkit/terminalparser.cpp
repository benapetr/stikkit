//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "terminalparser.hpp"
#include <iostream>
#include "configuration.hpp"
using namespace Stikkit;
using namespace std;

TerminalParser::TerminalParser(int argc, char *argv[])
{
    this->argc = argc;
    this->argv = argv;
}

bool TerminalParser::Parse()
{
    int x = 1;
    while (x < this->argc)
    {
        bool valid = false;
        string text = string(this->argv[x]);
        if (text == "-h" || text == "--help")
        {
            DisplayHelp();
            return true;
        }
        if (text.length() > 1 && text[0] == ('-') && text[1] != ('-'))
        {
            text = text.substr(1);
            while (text.length())
            {
                if (this->ParseChar(text.at(0)))
                {
                    return true;
                } else if (text.at(0) == 'a')
                {
                    if (this->argc > x + 1 && !this->argv[x + 1][0] != '-')
                    {
                        x++;
                        Configuration::Author = this->argv[x];
                    } else
                    {
                        cerr << "Parameter -a requires an argument for it to work!" << endl;
                        return true;
                    }
                } else if (text.at(0) == 'b')
                {
                    if (this->argc > x + 1 && !this->argv[x + 1][0] != '-')
                    {
                        x++;
                        Configuration::URL = this->argv[x];
                    } else
                    {
                        cerr << "Parameter -b requires an argument for it to work!" << endl;
                        return true;
                    }
                }
                text = text.substr(1);
            }
            valid = true;
        }
        if (text == "--version")
        {
            cout << "Stikkit " << Configuration::Version << endl;
            return true;
        }
        if (!valid)
        {
            if (!this->Silent)
            {
                cerr << "This parameter isn't valid: " << text << endl;
            }
            return true;
        }
        x++;
    }
    return false;
}

bool TerminalParser::ParseChar(char x)
{
    switch (x)
    {
        case 'v':
            Configuration::Verbosity++;
            return false;
        case 'h':
            this->DisplayHelp();
            return true;
    }
    return false;
}

void TerminalParser::DisplayHelp()
{
    if (this->Silent)
        return;

    cout << "Stikkit - open source pastebin uploader for Stikked\n\n"\
            "Parameters:\n"\
            "  -a <name>:       Specify author name\n"\
            "  -b <url>:        Specify URL of Stikked server\n"\
            "  -v:              Increases verbosity\n"\
            "  --version:       Display a version\n"\
            "  -h | --help:     Display this help\n\n"\
            "Note: every argument in [brackets] is optional\n"\
            "      but argument in <brackets> is required\n\n"\
            "Stikkit is open source, contribute at https://github.com/benapetr/stikkit" << endl;
}
