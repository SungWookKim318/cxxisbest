#pragma once

//
// Creator: SungWook Kim
// Date: 2024-07-19
//

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <memory>

#include "stream.hpp"

class Node {
public:
    Node(const std::string label);

    bool connect(Node* child);
    bool disconnect(Node* child);
    

    std::string getLabel();

private:
    std::string label;

    std::vector<Stream> inputs;
    Stream output;
};
