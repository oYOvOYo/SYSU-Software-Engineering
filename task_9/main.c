#include <stdio.h> // for printf
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC
#include <stdlib.h> // for srand, rand, malloc, free
#include "find_the_kth_largest_element.h"
#include "find_the_kth_largest_element.cpp"


// 最大规模
#define MAX_SIZE 10000000


void test(int i) {
    srand(i);
    // 赋初值
    int size = rand() % MAX_SIZE;
    int K = rand() % size;
    int * num = (int*)malloc(sizeof(int) * size);
    int * num2 = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        num[i] = rand();
        num2[i] = num[i];
    }
    // C 
    clock_t begin = clock();    
    int ans = find_the_kth_largest_elements(num, size, K);    
    clock_t end = clock();
    printf("size = %8d K = %8d ans = %12d time = %8f\n", 
        size, K, ans, (double)(end - begin) / CLOCKS_PER_SEC);
    
    for (int i = 0; i < size; i++) {
        num[i] = rand();
    }
    // C++
    clock_t begin2 = clock();    
    int ans2 = iLoveYukiNagato(num2, size, K);    
    clock_t end2 = clock();
    printf("size = %8d K = %8d ans = %12d time = %8f\n", 
        size, K, ans, (double)(end - begin) / CLOCKS_PER_SEC);
    printf("Uing time C:C++ %f\n\n", (double)(end - begin)/(end2 - begin2));
    // Free
    free(num);
    free(num2);
} 

int main() {
    int test_size = 30; // test size
    while(test_size--)
        test(test_size);
    return 0;
}