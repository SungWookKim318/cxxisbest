#include <string>
#include <mutex>
#include <queue>
#include <atomic>
#include <condition_variable>

#include "common.hpp"

// 하나의 노드에 여러개의 인풋 포트
class InputPort
{
public:
    InputPort(const std::string& label = "unknown input port");

    std::string getLabel() const;

    void put(int data);
    int get();
    void close();
private:
    std::queue<int> dataQueue_;
    std::mutex mtx_;
    std::condition_variable cv_;
    std::atomic<bool> active_;

    const std::string label_;
};

//void make_edge(std::shared_ptr<OutputPort> outputPort, std::shared_ptr<InputPort> inputPort);
