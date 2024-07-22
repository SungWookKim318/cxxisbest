#pragma once
//
//  common.hpp
//  ExampleTest
//
//  Created by 김성욱 on 7/20/24.
//

#include <memory>
#include <optional>
#include <thread>

class Node;
class InputPort;
class OutputPort;


void printLogging(const std::string& prefix, const std::string& message);

extern std::thread::id mainThreadId;
