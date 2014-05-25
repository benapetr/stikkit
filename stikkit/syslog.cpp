//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include <iostream>
#include "syslog.hpp"
#include "configuration.hpp"

using namespace Stikkit;

void Syslog::Log(string Message, StikkitLogType Type)
{
    if (Type == StikkitLogType_Error)
    {
        std::cerr << Message << std::endl;
    } else
    {
        std::cout << Message << std::endl;
    }
}

void Syslog::ErrorLog(string Message)
{
    Syslog::Log("ERROR: " + Message, StikkitLogType_Error);
}

void Syslog::WarningLog(string Message)
{
    Syslog::Log("WARNING: " + Message, StikkitLogType_Warn);
}

void Syslog::DebugLog(string Message, unsigned int Verbosity)
{
    if (Configuration::Verbosity >= Verbosity)
    {
        Syslog::Log("DEBUG: " + Message, StikkitLogType_Debug);
    }
}
