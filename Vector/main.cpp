#include <iostream>
#include <sstream>
#include <string>
#include "Vector.h"

int main()
{
    /* 创建一个 Vector 对象 */
    Vector<int> myVector;

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

        if (command == "push") {
            int value;
            iss >> value;
            myVector.push_back(value);
        } else if (command == "print") {
            if (myVector.size() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            printElements(myVector);
        } else if (command == "size") {
            std::cout << myVector.size() << std::endl;
        } else if (command == "get") {
            int idx;
            iss >> idx;
            std::cout << myVector[idx] << std::endl;
        } else if (command == "insert") {
            int idx;
            int value;
            iss >> idx >> value;
            myVector.insert(idx, value);
        } else if (command == "pop") {
            myVector.pop_back();
        } else if (command == "iterator") {
            if (myVector.size() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }

            for (auto it = myVector.begin(); it != myVector.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;

        } else if (command == "foreach") {
            if (myVector.size() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }

            for (const auto &element : myVector) {
                std::cout << element << " ";
            }
            std::cout << std::endl;

        } else if (command == "clear") {
            myVector.clear();
        }
    }

    return 0;
}

/* 测试输入及输出: */
/*
输入：
15
push 20
push 30
push 40
print
insert 0 10
size
print
get 1
pop
print
iterator
foreach
clear
size
print

输出：
20 30 40 
4
10 20 30 40 
20
10 20 30 
10 20 30 
10 20 30 
0
empty
*/
