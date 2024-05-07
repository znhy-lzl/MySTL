#include <iostream>
#include <sstream>
#include <string>
#include "List.h"

int main()
{
    /* 创建一个 Vector 对象 */
    List<int> myList;

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
            myList.push_back(value);
        } else if (command == "push_front") {
            iss >> value;
            myList.push_front(value);
        } else if (command == "pop_back") {
            myList.pop_back();
        } else if (command == "pop_front") {
            myList.pop_front();
        } else if (command == "remove") {
            iss >> value;
            myList.remove(value);
        } else if (command == "print") {
            if (myList.size() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            printElements(myList);
        } else if (command == "size") {
            std::cout << myList.size() << std::endl;
        } else if (command == "clear") {
            myList.clear();
        }
    }

    return 0;
}


/* 测试用例 */
/* 
输入：
    16
    push_back 10
    push_back 20
    print 
    push_front 30
    print
    push_front 40
    print
    size
    pop_back
    print 
    remove 10
    print 
    size
    clear
    print
    size

输出：
    10 20
    30 10 20 
    40 30 10 20 
    4
    40 30 10
    40 30
    2
    empty
    0
*/
