//#include "stream.hpp"
//
//#include <iostream>
//#include <future>
//
//#include "port.hpp"
//
//Stream::Stream(std::shared_ptr<InputPort> inputPort) : inputPort_(inputPort)
//{
//    printLogging("Stream["+inputPort->getLabel()+']', "is Created");
//    prepareFuture();
//}
//
//void Stream::transferValue(int value)
//{
//    this->promise_.set_value(value);
//    
//}
//
//void Stream::prepareFuture()
//{
//    std::promise<int> promise;
//    future_ = promise.get_future().share();
//    inputPort_->setFuture(future_);
//    promise_ = std::move(promise);
//    
//}
//
//std::string Stream::getLabel()
//{
//    return "Stream";
//}
