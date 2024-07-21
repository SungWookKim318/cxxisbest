#include "node.hpp"

#include <iostream>

#include "common.hpp"
#include "port.hpp"
#include "stream.hpp"

Node::Node(std::string label, FunctorType functor) : label_(label), functor_(functor), outputPort_(std::make_shared<OutputPort>(label))
{
    std::cout << "Node"<< '[' << this->label_ << ']' << "is Created" << std::endl;
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
    std::cout << "Node[" << this->label_ << "] output_port()" << this->outputPort_ << std::endl;
    return this->outputPort_;
}

void Node::process()
{
    std::vector<int> values;
    for (const auto& inputPort : inputPorts_)
    {
        if (inputPort && inputPort->isReady())
        {
            values.push_back(inputPort->getValue());
        } else { 
            return;
        }
    }
    int result = this->functor_(values);
    std::cout << "Node[" << this->label_ << "] processed result: " << result << std::endl;
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
    std::cout << "Node[" << this->label_ << "] is Deleted" << std::endl;
}
