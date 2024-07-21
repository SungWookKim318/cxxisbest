#include "port.hpp"

#include <iostream>
#include "stream.hpp"
#include "node.hpp"

void InputPort::setFuture(std::shared_future<int> future)
{
    this->future_ = future;
}

std::shared_future<int> InputPort::getFuture() const
{
    return this->future_;
}

InputPort::InputPort(std::weak_ptr<Node> node, std::string label) : node_(node), label_(label)
{
    std::cout << "InputPort Create - [" << label_ << "]" << std::endl;
}

std::string InputPort::getLabel() const
{
    return this->label_;
}

OutputPort::OutputPort(std::string label) : label_(label), streams_({})
{
    std::cout << "OutputPort create [" << label << "]" << std::endl;
}

std::string OutputPort::getLabel() const
{
    return this->label_;
}

void OutputPort::addStream(std::shared_ptr<Stream> stream)
{
    streams_.push_back(stream);
}

void OutputPort::send(int data)
{
    std::cout << "OutputPort[" << label_ << "] ready to send data: " << data << std::endl;
    for (const auto& stream : streams_)
    {
        std::cout << "OutputPort[" << label_ << "] -> [" <<  stream->getLabel()  << "] send data: " << data << std::endl;
        stream->transferValue(data);
    }
}

void make_edge(std::shared_ptr<OutputPort> outputPort, std::shared_ptr<InputPort> inputPort) {
    auto stream = std::make_shared<Stream>(inputPort);
    outputPort->addStream(stream);
}
