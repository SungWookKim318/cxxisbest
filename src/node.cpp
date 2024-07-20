#include "node.hpp"

#include <iostream>

#include "stream.hpp"
bool Node::addChild(const NodeWeakPtr* child)
{
    return true;
}

bool Node::removeChild(const NodeWeakPtr* child)
{
    return true;
}

void Node::processStream()
{
    std::cout << '[' << this->label_ << ']' << "Processing stream" << std::endl;
    
    
    // 1. input stream을 확인하고 값을 받아오기
    std::vector<int> inputValues;
    for (const auto& stream : this->inputStreams_) {
        if(!stream) {
            std::cout << "Stream is empty" << std::endl;
            return;
        }
        
        if(stream->get()->getCurrentStreamValue() ; const auto value = stream->get()->getCurrentStreamValue().value()) {
            inputValues.push_back(value);
        } else {
            std::cout << "Stream is update next time" << std::endl;
            return;
        }
    }
    
    // 2. Functor에게 전달하고 결과 요청
    const auto result = this->functor_(inputValues);
    
    if(result.has_value()) {
        // 3. output stream에 전달
        for (const auto& stream : this->outputStreams_) {
            if(!stream) {
                std::cout << "Stream is empty" << std::endl;
                return;
            }
            stream->put(result.value());
        }
    } else {
        std::cout << "No result from functor" << std::endl;
    }
}


std::string Node::getLabel()
{
    return this->label_;
}

