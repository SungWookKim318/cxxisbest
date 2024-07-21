#pragma once

//
// Creator: SungWook Kim
// Date: 2024-07-19
//

#include <vector>
#include <string>
#include <future>
#include <memory>
#include <queue>
#include <optional>

#include "common.hpp"
#include "node.hpp"

//typedef std::unique_ptr<Stream> StreamPointer;

class Stream {

public:
    explicit Stream(std::shared_ptr<InputPort> inputPort);
    void prepareFuture();
    void transferValue(int value);
    
    std::string getLabel();
private:
    std::shared_ptr<InputPort> inputPort_;
    std::promise<int> promise_;
    std::shared_future<int> future_;
};

