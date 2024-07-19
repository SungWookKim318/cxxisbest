#include "stream.hpp"

/*
class Stream {
public:
    Stream() = default;

    std::future<int> addInput(int input) {
        std::promise<int> promise;
        std::future<int> future = promise.get_future();
        {
            std::lock_guard<std::mutex> lock(mutex_);
            inputs_.push(std::move(future));
        }
        promises_.emplace_back(std::move(promise));
        return promises_.back().get_future();
    }

    void setInputValues(const std::vector<int>& values) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (size_t i = 0; i < values.size(); ++i) {
            if (i < promises_.size()) {
                promises_[i].set_value(values[i]);
            }
        }
    }

    std::vector<std::future<int>> getInputs() {
        std::lock_guard<std::mutex> lock(mutex_);
        std::vector<std::future<int>> inputs;
        while (!inputs_.empty()) {
            inputs.push_back(std::move(inputs_.front()));
            inputs_.pop();
        }
        return inputs;
    }

    std::future<int> getOutput() {
        std::lock_guard<std::mutex> lock(mutex_);
        return std::move(output_.get_future());
    }

    void setOutput(int value) {
        std::lock_guard<std::mutex> lock(mutex_);
        output_.set_value(value);
    }

private:
    std::queue<std::future<int>> inputs_;
    std::vector<std::promise<int>> promises_;
    std::promise<int> output_;
    std::mutex mutex_;
};
*/

std::future<int> Stream::addInput(int input)
{
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    {
        std::lock_guard<std::mutex> lock(mutex_);
        inputs_.push(std::move(future));
    }
    promises_.emplace_back(std::move(promise));
    return promises_.back().get_future();
}

std::future<int> Stream::getOutput()
{
    return std::future<int>();
}
