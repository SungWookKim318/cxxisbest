#include "node.hpp"

#include <iostream>
#include <thread>

#include "common.hpp"
#include "port.hpp"
#include "stream.hpp"

Node::Node(std::string label, FunctorType functor) : label_(label), functor_(functor), outputPort_(std::make_shared<OutputPort>(label))
{
    printLogging("Node[" + this->label_ + ']', "is Created");
}

std::shared_ptr<InputPort> Node::getInputPort(size_t index)
{
    if (index >= inputPorts_.size())
    {
        inputPorts_.resize(index + 1);
    }
    if (!inputPorts_[index])
    {
        std::string label = this->label_ + "-IntputPort[" + std::to_string(index) + "]";
        inputPorts_[index] = std::make_shared<InputPort>(shared_from_this(), label);
        
    }
    return inputPorts_[index];
}

std::shared_ptr<OutputPort> Node::getOutputPort()
{
    printLogging("Node[" + this->label_ + "]", "getOutputPort()");
    return this->outputPort_;
}

void Node::process()
{
    std::vector<std::shared_future<int>> inputFutures;
    printLogging("Node[" + this->label_ + "]", "start process()");
    for (const auto& inputPort : inputPorts_)
    {
        if (inputPort)
        {
            inputFutures.push_back(inputPort->getFuture());
        } else {
            std::cout << "Node[" << this->label_ << "] inputPort is not ready, is nullptr!" << std::endl;
            return;
        }
    }
    
    for (auto& inputFuture : inputFutures)
    {
        inputFuture.wait();
    }
    
    std::vector<int> values = {};
    for (auto& inputFuture : inputFutures)
    {
        values.push_back(inputFuture.get());
    }
    
    int result = this->functor_(values);
    printLogging("Node[" + this->label_ + "]", "processed result: " + std::to_string(result));
    
    this->outputPort_->send(result);
}

void Node::scheduleProcessing()
{
    std::vector<std::shared_future<int>> futures;
    for (const auto& inputPort : inputPorts_) {
        if (inputPort) {
            futures.push_back(inputPort->getFuture());
        }
    }

    std::thread([self = shared_from_this(), futures]() {
        for (const auto& future : futures) {
            future.wait(); // 모든 future가 준비될 때까지 대기
        }
        self->process();
    }).detach();
}

std::string Node::getLabel()
{
    return this->label_;
}


Node::~Node() { 
    printLogging("Node[" + this->label_ + "]", "is Delete");
}
