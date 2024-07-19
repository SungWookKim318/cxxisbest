#include "node.hpp"

Node::Node(const std::string label): label(label) {}

bool Node::connect(Node* child)
{
    return false;
}

bool Node::disconnect(Node* child)
{
    return false;
}


std::string Node::getLabel()
{
    return this->label;
}

