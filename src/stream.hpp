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
    Stream() = default;
    
    bool put(int value);
    std::optional<int> getCurrentStreamValue();
    
    
private:
    NodeWeakPtr inputNode_;
    NodeWeakPtr outputNode_;
    
    std::optional<int> value_;
};

