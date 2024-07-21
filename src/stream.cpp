#include "stream.hpp"

#include <iostream>
#include <future>

#include "port.hpp"

Stream::Stream(std::shared_ptr<InputPort> inputPort) : inputPort_(inputPort)
{
    std::cout << "Stream[" << inputPort->getLabel() << "] is Created" << std::endl;
} 

void Stream::transferValue(int value)
{
    this->promise_.set_value(value);
}

std::shared_future<int> Stream::createFuture()
{
    std::promise<int> promise;
    auto future = promise.get_future().share();
    this->promise_ = std::move(promise);
    this->inputPort_->setFuture(future);
    return future;
}

std::string Stream::getLabel()
{
    return "Stream";
}
