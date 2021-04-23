#include "ModuleSolutions.h"
#include <iostream>
#include <pthread.h>
#include <vector>
#include <algorithm>
#include <functional>

#define  THREAD_NUMS  5

using namespace std;

void *sayHello(void *args) {
    cout << "hello...\n";
}   // 函数返回函数指针

int main() {
//    pthread_t tids[THREAD_NUMS];    // 线程id
//    for (int i = 0; i < THREAD_NUMS; i++) {
//        // 参数：创建的线程id，线程参数，线程运行函数的起始地址，运行函数的参数
//        int ret = pthread_create(&tids[i], nullptr, sayHello, nullptr);
//        if (ret) cout << "pthread_create error: error_code = " << ret << " .\n";// 线程创建成功返回0
//    }
//    pthread_exit(nullptr);  // 等待各个线程退出，进程结束，否则进程强制结束，线程处于未终止状态
    vector<vector<int>> points{{1, 2},
                               {3, 1},
                               {2, 4},
                               {2, 3},
                               {4, 4}};
    cout << EasySolutions::nearestValidPoint(3, 4, points) << endl;
    return 0;
}