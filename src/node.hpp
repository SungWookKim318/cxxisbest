#include <iostream>
#include <vector>
#include <functional>

class Node {
public:
    Node();
    
    bool connect(Node* child);
    bool disconnect(Node* child);
    
    bool isLeaf();
    
    
private:
    ~Node();
    
    std::vector<Node*> children;
}
