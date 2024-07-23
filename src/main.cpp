#include <iostream>

#include "common.hpp"
#include "node.hpp"
#include "InputPort.hpp"
#include "OutputPort.hpp"

void make_edge(std::shared_ptr<OutputPort> out, std::shared_ptr<InputPort> in) {
    out->connect(in);
}

int main() {
    mainThreadId = std::this_thread::get_id();
    
    Node A("A", 1, [](std::vector<int> in) { return in[0] + 1; });
    Node B("B", 1, [](std::vector<int> in) { return in[0] * 2; });
    Node C("C", 2, [](std::vector<int> in) { return in[0] + in[1]; });
    Node D("D", 1, [](std::vector<int> in) { return in[0] - 1; });
    Node E("E", 1, [](std::vector<int> in) { return in[0] * 3; });
    Node F("F", 2, [](std::vector<int> in) { return in[0] - in[1]; });

    make_edge(A.getOutputPort(), C.getInputPort(0));
    make_edge(B.getOutputPort(), C.getInputPort(1));
    make_edge(B.getOutputPort(), F.getInputPort(0));
    make_edge(C.getOutputPort(), D.getInputPort(0));
    make_edge(C.getOutputPort(), E.getInputPort(0));
    make_edge(C.getOutputPort(), F.getInputPort(1));

    A.getInputPort(0)->put(10);
    B.getInputPort(0)->put(20);

    // Simulate processing
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Stop all processing
    A.stop();
    B.stop();
    C.stop();
    D.stop();
    E.stop();
    F.stop();

    return 0;
}
