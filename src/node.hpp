#pragma once

//
// Creator: SungWook Kim
// Date: 2024-07-19
//

#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <atomic>

#include "common.hpp"

typedef std::function<int(std::vector<int>)> FunctorType;

class Node {
public:
    Node(std::string label, FunctorType functor);
    virtual ~Node();
    
    std::shared_ptr<InputPort> getInputPort(size_t index);
    std::shared_ptr<OutputPort> getOutputPort();
    void stop();
    
    const std::string& getLabel() const;
protected:
//    virtual void process(); //protect
private:
    std::vector<std::shared_ptr<InputPort>> inputPorts_;
    std::shared_ptr<OutputPort> outputPort_;
    std::function<int(std::vector<int>)> functor_;
    std::thread workerThread_;
    std::atomic<bool> running_;
    
    const std::string label_;
    
    void threadProcess();
};

