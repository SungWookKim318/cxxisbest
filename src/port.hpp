#include <memory>
#include <string>
#include <future>
#include "common.hpp"

#include "stream.hpp"

// 하나의 노드에 여러개의 인풋 포트
class InputPort
{
public:
    explicit InputPort(std::weak_ptr<Node> node, std::string label = "unknown input port");

    std::string getLabel() const;

    void setFuture(std::shared_future<int> future);
    std::shared_future<int> getFuture() const;
private:
    std::shared_future<int> future_;
    std::weak_ptr<Node> node_;

    std::string label_;
};

// 하나의 노드에 하나의 아웃풋 포트
class OutputPort
{
public:
    OutputPort() = delete;
    OutputPort(std::string label);

    std::string getLabel() const;

    void addStream(std::shared_ptr<Stream> stream);
    void send(int newValue);

private:
    std::string label_;
    // 하나의 포트에 여러개의 스트림(연결)
    std::vector<std::shared_ptr<Stream>> streams_;
};


void make_edge(std::shared_ptr<OutputPort> outputPort, std::shared_ptr<InputPort> inputPort);
