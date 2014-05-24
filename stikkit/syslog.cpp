//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include <iostream>
#include <QDateTime>
#include "syslog.hpp"
#include "configuration.hpp"

using namespace Stikkit;

void Syslog::Log(QString Message, StikkitLogType Type)
{
    QString d = QDateTime::currentDateTime().toString();
    QString message = d + "   " + Message;
    if (Type == StikkitLogType_Error)
    {
        std::cerr << message.toStdString() << std::endl;
    } else
    {
        std::cout << message.toStdString() << std::endl;
    }
}

void Syslog::ErrorLog(QString Message)
{
    Syslog::Log("ERROR: " + Message, StikkitLogType_Error);
}

void Syslog::WarningLog(QString Message)
{
    Syslog::Log("WARNING: " + Message, StikkitLogType_Warn);
}

void Syslog::DebugLog(QString Message, unsigned int Verbosity)
{
    if (Configuration::Verbosity >= Verbosity)
    {
        Syslog::Log("DEBUG[" + QString::number(Verbosity) + "]: " + Message, StikkitLogType_Debug);
    }
}
