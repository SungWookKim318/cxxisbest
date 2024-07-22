#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>

class InputPort;
class OutputPort;

class Stream {
public:
    void connect(std::shared_ptr<OutputPort> out, std::shared_ptr<InputPort> in);
};

class InputPort {
private:
    std::queue<int> dataQueue;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> active{true};

public:
    void put(int data) {
        std::unique_lock<std::mutex> lock(mtx);
        dataQueue.push(data);
        cv.notify_one();
    }

    int get() {
        std::unique_lock<std::mutex> lock(mtx);
        while (dataQueue.empty() && active) {
            cv.wait(lock);
        }
        if (!dataQueue.empty()) {
            int data = dataQueue.front();
            dataQueue.pop();
            return data;
        }
        return 0; // Returning zero could signify no more data (or a default value).
    }

    void close() {
        std::lock_guard<std::mutex> lock(mtx);
        active = false;
        cv.notify_all();
    }
};

class OutputPort {
private:
    std::vector<std::shared_ptr<InputPort>> connectedPorts;

public:
    void connect(std::shared_ptr<InputPort> port) {
        connectedPorts.push_back(port);
    }

    void send(int data) {
        for (auto& port : connectedPorts) {
            port->put(data);
        }
    }
};

void Stream::connect(std::shared_ptr<OutputPort> out, std::shared_ptr<InputPort> in) {
    out->connect(in);
}

class Node {
private:
    std::vector<std::shared_ptr<InputPort>> inputPorts;
    std::shared_ptr<OutputPort> outputPort;
    std::function<int(std::vector<int>)> computeFunction;
    std::thread workerThread;
    std::atomic<bool> running{true};

    void process() {
        while (running) {
            std::vector<int> inputs;
            for (auto& port : inputPorts) {
                int input = port->get();
                if (!running) return; // Check running state after potentially blocking operation
                inputs.push_back(input);
            }
            int result = computeFunction(inputs);
            outputPort->send(result);
        }
    }

public:
    Node(int inputCount, std::function<int(std::vector<int>)> func) : computeFunction(func) {
        for (int i = 0; i < inputCount; ++i) {
            inputPorts.emplace_back(std::make_shared<InputPort>());
        }
        outputPort = std::make_shared<OutputPort>();
        workerThread = std::thread(&Node::process, this);
        workerThread.detach();
    }

    ~Node() {
        if (workerThread.joinable()) {
            stop();
            workerThread.join();
        }
    }

    void stop() {
        running = false;
        for (auto& port : inputPorts) {
            port->close();
        }
    }

    std::shared_ptr<InputPort> input_port(int index) {
        return inputPorts.at(index);
    }

    std::shared_ptr<OutputPort> output_port() {
        return outputPort;
    }
};

void make_edge(std::shared_ptr<OutputPort> out, std::shared_ptr<InputPort> in) {
    Stream().connect(out, in);
}

int main() {
    Node A(1, [](std::vector<int> in) { return in[0] + 1; });
    Node B(1, [](std::vector<int> in) { return in[0] * 2; });
    Node C(2, [](std::vector<int> in) { return in[0] + in[1]; });
    Node D(1, [](std::vector<int> in) { return in[0] - 1; });
    Node E(1, [](std::vector<int> in) { return in[0] * 3; });
    Node F(2, [](std::vector<int> in) { return in[0] - in[1]; });

    make_edge(A.output_port(), C.input_port(0));
    make_edge(B.output_port(), C.input_port(1));
    make_edge(B.output_port(), F.input_port(0));
    make_edge(C.output_port(), D.input_port(0));
    make_edge(C.output_port(), E.input_port(0));
    make_edge(C.output_port(), F.input_port(1));

    A.input_port(0)->put(10);
    B.input_port(0)->put(20);

    // Simulate processing
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Stop all processing
    A.stop();
    B.stop();
    C.stop();
    D.stop();
    E.stop();
    F.stop();

    return 0;
}
