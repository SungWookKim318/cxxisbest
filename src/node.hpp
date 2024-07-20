#pragma once

//
// Creator: SungWook Kim
// Date: 2024-07-19
//

#include <vector>
#include <string>
#include <functional>
#include <memory>

#include "common.hpp"

class Node {
public:
    Node() = default;

    bool addChild(const NodeWeakPtr* child);
    bool removeChild(const NodeWeakPtr* child);
    
    void processStream();

    std::string getLabel();

    std::function<std::optional<int>(std::vector<int>)> functor_;
    
private:
    std::string label_;
    // intput streams -> Stream을 가져서 처리하도록 수정
    std::vector<OptionalStream> inputStreams_;
    // output stream
    std::vector<std::shared_ptr<Stream>> outputStreams_;
};

