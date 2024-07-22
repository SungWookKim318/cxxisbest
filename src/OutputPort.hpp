#include <vector>
#include <string>

#include "common.hpp"

class OutputPort {
public:
    OutputPort(std::string label);
    void connect(std::shared_ptr<InputPort> port);
    void send(int data);
    
private:
    std::vector<std::shared_ptr<InputPort>> connectedPorts;
    const std::string label_;
};
