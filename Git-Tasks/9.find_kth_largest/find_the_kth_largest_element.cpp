#include <algorithm>

// return the Kth largest number in the array "num" which contains "size" numbers.
int iLoveYukiNagato(int *num, const int size, const int K);

int iLoveYukiNagato(int *num, const int size, const int K) {
	std::nth_element(num, num + size - K, num + size);
	return num[size - K];
}