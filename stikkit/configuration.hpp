//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>

using namespace std;

namespace Stikkit
{
    class Configuration
    {
        public:
            static unsigned int Verbosity;
            static string URL;
            static string Source;
            static string Input;
            static string Author;
            static string Version;
    };
}

#endif // CONFIGURATION_HPP
