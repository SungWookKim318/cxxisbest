#include "InputPort.hpp"

#include <iostream>
#include <thread>

#include "stream.hpp"
#include "node.hpp"

InputPort::InputPort(const std::string& label) 
: label_("InputPort("+ label+')'), active_(true), dataQueue_(), mtx_(), cv_()
{
    printLog(this->label_, "Created");
}

void InputPort::put(int data) {
    std::unique_lock<std::mutex> lock(mtx_);
    dataQueue_.push(data);
    cv_.notify_one();
}

int InputPort::get() {
    std::unique_lock<std::mutex> lock(mtx_);
    while (dataQueue_.empty() && active_) {
        cv_.wait(lock);
    }
    if (!dataQueue_.empty()) {
        int data = dataQueue_.front();
        dataQueue_.pop();
        return data;
    }
    return 0;
}

void InputPort::close() {
    std::lock_guard<std::mutex> lock(mtx_);
    active_ = false;
    cv_.notify_all();
}

const std::string InputPort::getLabel() const
{
    return this->label_;
}
