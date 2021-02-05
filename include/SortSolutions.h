//
// Created by LaiChao on 2020/11/1.
//

#ifndef THEROADTOADVANCEMENT_SORTSOLUTIONS_H
#define THEROADTOADVANCEMENT_SORTSOLUTIONS_H

#include "./__OSJudge.h"
#include <vector>

using namespace std;

class SortSolution {
public:
    // 非线性时间比较类排序 ==============================================
    static void bubleSort(vector<int> &nums);           // 冒泡排序
    static void quickSort(vector<int> &nums);           // 快速排序
    static void insertionSort(vector<int> &nums);       // 插入排序
    static void selectionSort(vector<int> &nums);       // 选择排序
    static void shellSort(vector<int> &nums);           // 希尔排序
    static void mergeSort(vector<int> &nums);           // 归并排序
    static void heapSort(vector<int> &nums);            // *** 堆排序 ***

    // 线性时间比较类排序 ================================================
    static void countingSort(vector<int> &nums);        // 计数排序
    static void bucketSort(vector<int> &nums);          // 桶排序
    static void radixSort(vector<int> &nums);           // 基数排序
};


#endif //THEROADTOADVANCEMENT_SORTSOLUTIONS_H
