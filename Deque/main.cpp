#include <iostream>
#include <sstream>
#include <string>
#include "Deque.h"

int main()
{
    /* 创建一个 Vector 对象 */
    Deque<int> myDeque;

    int N;
    std::cin >> N;
    /* 读走回车 */
    getchar();

    std::string line;
    for (int i = 0; i < N; ++i) {
        /* 读取整行 */
        std::getline(std::cin, line);
        std::istringstream iss(line);

        std::string command;
        iss >> command;

        int value;

        if (command == "push_back") {     
            iss >> value;
            myDeque.push_back(value);
        } else if (command == "push_front") {
            iss >> value;
            myDeque.push_front(value);
        } else if (command == "pop_back") {
            if (myDeque.size() == 0) {
                continue;
            }
            myDeque.pop_back();
        } else if (command == "pop_front") {
            if (myDeque.size() == 0) {
                continue;
            }
            myDeque.pop_front();
        } else if (command == "get") {
            iss >> value;
            std::cout << myDeque[value] << std::endl;
        } else if (command == "print") {
            if (myDeque.size() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            printElements(myDeque);
        } else if (command == "size") {
            std::cout << myDeque.size() << std::endl;
        } else if (command == "clear") {
            myDeque.clear();
        }
    }

    return 0;
}


/* 测试用例 */
/* 
输入：
    15
    push_back 20
    push_back 10
    push_front 30
    push_front 40
    size
    print
    pop_back
    print
    pop_front
    print
    size
    get 1
    clear
    print
    size

输出：
    4
    40 30 20 10 
    40 30 20 
    30 20 
    2
    20
    empty
    0
*/
