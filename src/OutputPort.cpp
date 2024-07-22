#include "OutputPort.hpp"
#include "InputPort.hpp"

OutputPort::OutputPort(std::string label) : label_(label), connectedPorts({})
{
    printLogging("OutputPort["+label+']', "created");
}

void OutputPort::connect(std::shared_ptr<InputPort> port) {
    connectedPorts.push_back(port);
}

void OutputPort::send(int data) {
    for (const auto& port : connectedPorts) {
        port->put(data);
    }
}
