#include "node.hpp"

#include <iostream>
#include <thread>

#include "common.hpp"
#include "InputPort.hpp"
#include "OutputPort.hpp"
#include "stream.hpp"

Node::Node(const std::string& label, const size_t inputCount, FunctorType functor)
: label_("Node(" + label + ')'), functor_(functor), inputPorts_({}), running_(true)
{
    printLog(this->label_, "is Created");
    for (size_t i = 0; i < inputCount; ++i) {
        const auto inputPortLabel = label + ':' + std::to_string(i);
        inputPorts_.push_back(std::make_shared<InputPort>(inputPortLabel));
    }
    const auto outputPortLabel = label + ":0";
    outputPort_ = std::make_shared<OutputPort>(outputPortLabel);
    workerThread_ = std::thread(&Node::threadProcess, this);
    workerThread_.detach();
}


Node::~Node() {
    running_ = false;
    if (workerThread_.joinable()) {
        this->stop();
        workerThread_.join();
    }
    printLog(this->label_, "is Delete");
}

void Node::threadProcess() {
    while (running_) {
        std::vector<int> inputs;
        if (inputPorts_.empty() == true) {
//            printLogging("Node(" + this->label_ + ')', "has no input port");
            continue;
        }
        for (auto& port : inputPorts_) {
            int input = port->get();
            if (!running_)
                return;
            inputs.push_back(input);
        }
        if (running_ == false) {
            printLog(this->label_, "is stopped");
            return;
        }
        int result = functor_(inputs);
        printLog(this->label_, "value is :" + std::to_string(result));
        outputPort_->send(result);
    }
}

void Node::stop() {
    running_ = false;
    for (auto& port : inputPorts_) {
        port->close();
    }
}

std::shared_ptr<InputPort> Node::getInputPort(size_t index) {
    if (index >= inputPorts_.size()) {
        printLog(this->label_, "has no input port");
        return nullptr;
    }
    return inputPorts_[index];
}


std::shared_ptr<OutputPort> Node::getOutputPort() {
    return outputPort_;
}

const std::string& Node::getLabel() const
{
    return this->label_;
}
