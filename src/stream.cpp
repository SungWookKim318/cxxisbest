#include "stream.hpp"

#include <iostream>

bool Stream::put(int value)
{
    if (this->outputNode_.expired()) {
        std::cout << "Output node is deleted." << std::endl;
        return false;
    }
    
    auto output = this->outputNode_.lock();
    if (output == nullptr) {
        std::cout << "Output node is deleted." << std::endl;
        return false;
    }
    
    std::cout << "Put value " << value << " to " << output->getLabel() << std::endl;
    output->processStream();
    return true;
}

std::optional<int> Stream::getCurrentStreamValue() {
    return this->value_;
}
