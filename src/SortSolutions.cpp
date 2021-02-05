//
// Created by LaiChao on 2020/11/1.
//

#include "../include/SortSolutions.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//                                          HELP FUNC
// ============================================================================================
void help_quickSort(int left, int right, vector<int> &arr) {
    if (left >= right) {    //递归边界条件
        return;
    }
    if (left < 0 || right >= arr.size()) {
        std::cout << "error args! array bound." << endl;
        return;
    }                       // 非法输入判断,防止数组越界
    int i, j, base, temp;
    i = left, j = right;
    base = arr[left];       // 取最左边的数为基准数
    while (i < j) {
        while (arr[j] <= base && i < j)
            j--;
        while (arr[i] >= base && i < j)
            i++;
        if (i < j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // 基准数归位
    arr[left] = arr[i];
    arr[i] = base;
    help_quickSort(left, i - 1, arr);   // 递归左边
    help_quickSort(i + 1, right, arr);   // 递归右边
}

void merge(vector<int> &nums, int left, int mid, int right) {
    int left_size = mid - left; // 左边数组的大小
    int right_size = right - mid + 1;   // 右边数组的大小（左闭右开）
    vector<int> left_nums(left_size);
    vector<int> right_nums(right_size);
    // 左右数组分别赋值
    for (int i = left; i < mid; i++) left_nums[i - left] = nums[i];
    for (int i = mid; i <= right; i++) right_nums[i - mid] = nums[i];
    int i = 0, j = 0, k = left;
    while (i < left_size && j < right_size) {   // 归并
        if (left_nums[i] < right_nums[j]) nums[k++] = left_nums[i++];
        else nums[k++] = right_nums[j++];
    }
    while (i < left_size) nums[k++] = left_nums[i++];
    while (j < right_size) nums[k++] = right_nums[j++];
}

void merge_sort(vector<int> &nums, int left, int right) {   // 分治
    if (left == right) return;
    int mid = (left + right) / 2;
    merge_sort(nums, left, mid);
    merge_sort(nums, mid + 1, right);
    merge(nums, left, mid + 1, right);
}

void heapify(vector<int> &nums, int n, int m) {
    if (m >= n) return;   // 递归出口
    int c1 = 2 * m + 1;
    int c2 = 2 * m + 2;
    int max = m;
    if (c1 < n && nums[c1] > nums[max]) max = c1;   // 比较左子节点与父节点
    if (c2 < n && nums[c2] > nums[max]) max = c2;   // 比较右子节点与刚刚比较完之后的父节点进行比较
    if (max != m) {
        swap(nums[max], nums[m]);
        heapify(nums, n, max);
    }
}

void build_heap(vector<int> &nums) {
    int n = nums.size();
    int last_node = n - 1;    // 堆的最后一个节点
    int last_heapify_node = (n - 1) / 2;  // 最后一个节点的父节点
    for (int i = last_heapify_node; i >= 0; i--) heapify(nums, n, i);  // 开始堆化
}

//                                          CLASS FUNC
// ============================================================================================
void SortSolution::bubleSort(vector<int> &nums) {
    if (nums.size() < 2) {
        return;
    }
    for (int i = 0; i < nums.size(); i++) {     // 外层循环控制总趟数
        bool flag = false;
        for (int j = 1; j < nums.size() - i; j++) {
            if (nums[j - 1] > nums[j]) {
                swap(nums[j - 1], nums[j]);
                flag = true;
            }
        }
        if (!flag) {    // 说明已经排序完成，避免无用计算
            return;
        }
    }
}

void SortSolution::quickSort(vector<int> &nums) {
    help_quickSort(0, nums.size() - 1, nums);
}

void SortSolution::insertionSort(vector<int> &nums) {
    int j, tmp;
    for (int i = 1; i < nums.size(); i++) { // 从第2个元素开始，逐一比较
        tmp = nums[i];
        for (j = i - 1; j >= 0 && nums[j] > tmp; j--) {
            nums[j + 1] = nums[j];
        }
        nums[j + 1] = tmp;
    }
}

void SortSolution::selectionSort(vector<int> &nums) {
    if (nums.size() < 2) {
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        // 寻找 [i, n) 区间里的最小值
        int minIndex = i;
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }
        swap(nums[minIndex], nums[i]);
    }
}

void SortSolution::radixSort(vector<int> &nums) {
    if (nums.size() < 2) {
        return;
    }
    int exp = 1;
    vector<int> buff(nums.size());
    int maxVal = *max_element(nums.begin(), nums.end());
    while (maxVal >= exp) {
        vector<int> cnt(10);
        for (int i = 0; i < nums.size(); i++) {
            int digit = (nums[i] / exp) % 10;
            cnt[digit]++;
        }
        for (int i = 1; i < 10; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = nums.size() - 1; i >= 0; i--) {
            int digit = (nums[i] / exp) % 10;
            buff[cnt[digit] - 1] = nums[i];
            cnt[digit]--;
        }
        copy(buff.begin(), buff.end(), nums.begin());
        exp *= 10;
    }
}

void SortSolution::shellSort(vector<int> &nums) {
    int n = nums.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int key = nums[i], j;
            for (j = i; j >= gap && key < nums[j - gap]; j -= gap) {
                nums[j] = nums[j - gap];
            }
            nums[j] = key;
        }
    }
}

void SortSolution::mergeSort(vector<int> &nums) {
    merge_sort(nums, 0, nums.size() - 1);
}

void SortSolution::heapSort(vector<int> &nums) {
    build_heap(nums);
    for (int i = nums.size() - 1; i >= 0; i--) {
        swap(nums[0], nums[i]);
        heapify(nums, i, 0);
    }
}
