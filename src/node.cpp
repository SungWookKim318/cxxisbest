#include "node.hpp"

#include <iostream>
#include <thread>

#include "common.hpp"
#include "InputPort.hpp"
#include "OutputPort.hpp"
#include "stream.hpp"

Node::Node(std::string label, FunctorType functor) 
: label_(label), functor_(functor), inputPorts_({}), running_(true)
{
    printLogging("Node[" + this->label_ + ']', "is Created");
    const auto outputPortLabel = label + "-OutputPort";
    outputPort_ = std::make_shared<OutputPort>(outputPortLabel);
    
    workerThread_ = std::thread(&Node::threadProcess, this);
}

std::shared_ptr<InputPort> Node::getInputPort(size_t index) {
    if (index >= inputPorts_.size()) {
        inputPorts_.resize(index + 1, nullptr);
    }
    if (!inputPorts_[index]) {
        const std::string label = this->label_ + "-InputPort[" + std::to_string(index) + "]";
        inputPorts_[index] = std::make_unique<InputPort>(label);
    }
    return inputPorts_.at(index);
}


std::shared_ptr<OutputPort> Node::getOutputPort() {
    return outputPort_;
}

void Node::stop() {
    running_ = false;
    for (auto& port : inputPorts_) {
        port->close();
    }
}

const std::string& Node::getLabel() const
{
    return this->label_;
}


Node::~Node() { 
    printLogging("Node[" + this->label_ + "]", "is Delete");
}



void Node::threadProcess() {
    while (running_) {
        std::vector<int> inputs;
        for (auto& port : inputPorts_) {
            int input = port->get();
            if (!running_)
                return; // Check running state after potentially blocking operation
            inputs.push_back(input);
        }
        int result = functor_(inputs);
        outputPort_->send(result);
    }
}
