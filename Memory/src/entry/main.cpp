//
// Created by Igor Obradovic.
//
#include <entry/Memory.hpp>
#include <sstream>

int main()
{
    int rv = 0;

    try
    {
        std::unique_ptr<game::Memory> Memory = std::make_unique<game::Memory>(  //
                "Memory");

        rv = Memory->run();
    }
    catch (const std::exception& except)
    {
        std::ofstream     errorLog{ "ErrorLog.txt", std::ios::out };
        std::stringstream ss;
        ss << except.what() << std::endl;
        errorLog << ss.str() << std::endl;
        rv = -1;
    }
    return rv;
}
