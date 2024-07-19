#pragma once

//
// Creator: SungWook Kim
// Date: 2024-07-19
//

#include <iostream>
#include <vector>
#include <string>
#include <future>
#include <memory>
#include <queue>

//typedef std::unique_ptr<Stream> StreamPointer;

class Stream {

public:
    Stream() = default;

    std::future<int> addInput(int input);
    std::future<int> getOutput();
private:
    std::queue<std::future<int>> inputs_;
    std::vector<std::promise<int>> promises_;
    std::promise<int> output_;
    std::mutex mutex_;
};