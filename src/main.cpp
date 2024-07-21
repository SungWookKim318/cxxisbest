#include <iostream>

#include "node.hpp"
#include "port.hpp"

int main() {
    using namespace std;
    // 예제 계산 함수 (모든 입력의 합을 계산)
    auto sumFunc = [](std::vector<int> values) -> int {
        int sum = 0;
        for (int value : values) {
            sum += value;
        }
        return sum;
    };

    // 노드 초기화 (합을 계산하는 functor를 사용)
    auto A = std::make_shared<Node>("A", sumFunc);
    auto B = std::make_shared<Node>("B", sumFunc);
    auto C = std::make_shared<Node>("C", sumFunc);
    auto D = std::make_shared<Node>("D", sumFunc);
    auto E = std::make_shared<Node>("E", sumFunc);
    auto F = std::make_shared<Node>("F", sumFunc);

    // Edge 연결
    std::cout << "Edge Connecting" << std::endl;
    make_edge(A->getOutputPort(), C->getInputPort(0)); // A → C
    make_edge(B->getOutputPort(), C->getInputPort(1)); // B → C
    make_edge(B->getOutputPort(), F->getInputPort(0)); // B → F
    make_edge(C->getOutputPort(), D->getInputPort(0)); // C → D
    make_edge(C->getOutputPort(), E->getInputPort(0)); // C → E
    make_edge(C->getOutputPort(), F->getInputPort(1)); // C → F

    // 값 입력
    std::cout << "Put values" << std::endl;
    A->getOutputPort()->send(5); // A의 입력 포트에 값 5 입력
    B->getOutputPort()->send(3); // B의 입력 포트에 값 3 입력

    // 메인 스레드에서 잠시 대기하여 비동기 작업이 완료될 시간을 줌
    std::cout << "Wait mainThread for a while" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    
    D->getOutputPort()->send(2); // D의 입력 포트에 값 2 입력
    
    std::cout<<"end of main\n";
    return 0;
}
