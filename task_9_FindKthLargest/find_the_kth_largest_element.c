#include "find_the_kth_largest_element.h"

void swap(int *x, int *y) {
	int t = *x;
	*x = *y;
	*y = t;
}

int find_the_kth_largest_elements(int *num, const int size, const int k) {
    int x = num[size / 2]; // 设定特值
    int left = 0, right = size-1; // 左右起始
    do { // 交换
        while (num[left] > x)
            left++;
        while (num[right] < x)
            right--;
        if (left <= right) {
            swap(num+right, num+left);
            left++;
            right--;
        }
    } while (left <= right);
    if (right+1 < k && k <= left) {
        return num[k-1]; // 如果最底层排序好了
    }
    if (right+1 >= k) // 递归到下一层
        return find_the_kth_largest_elements(num, right+1, k);
    else // 递归到下一层
        return find_the_kth_largest_elements(num+left, size-left, k-left);
}
