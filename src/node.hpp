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

typedef std::function<int(std::vector<int>)> FunctorType;
class Node : public std::enable_shared_from_this<Node> {
public:
    Node(std::string label, FunctorType functor);
    virtual ~Node();
    
    std::shared_ptr<InputPort> getInputPort(size_t index);
    std::shared_ptr<OutputPort> getOutputPort();
    
    virtual void process();
    
    void scheduleProcessing();

    std::string getLabel();
    
private:
    std::string label_;

    std::vector<std::shared_ptr<InputPort>> inputPorts_;
    std::shared_ptr<OutputPort> outputPort_;

    FunctorType functor_;
};

