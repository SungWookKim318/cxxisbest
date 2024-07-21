#include "common.hpp"

#include <iostream>
#include <thread>

std::thread::id mainThreadId;

void printLogging(const std::string &prefix, const std::string &message)
{
    auto mainThreadFlag = std::this_thread::get_id() == mainThreadId ? "[Main]" : "[Sub]";
    
    std::cout << mainThreadFlag << " THREAD[" << std::this_thread::get_id() << "],"
    << prefix << " " << message << std::endl;
}
