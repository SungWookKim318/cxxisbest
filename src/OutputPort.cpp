#include "OutputPort.hpp"
#include "InputPort.hpp"

OutputPort::OutputPort(std::string label) 
: label_("OutputPort("+ label + ')'), connectedPorts({})
{
    printLog(label_, "created");
}

void OutputPort::connect(std::shared_ptr<InputPort> port) {
    connectedPorts.push_back(port);
}

void OutputPort::send(int data) {
    for (const auto& port : connectedPorts) {
        if (port) {
            port->put(data);
        }
    }
}
