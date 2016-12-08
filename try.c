#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>


int int_add(int num1, int num2) {
  int ans = num1 + num2;
  if ((ans ^ num1) >= 0 || (ans ^ num2) >= 0) {
    return ans;
  } else {
    return 1;
  }
}



int main() {
    char cal_str[] = "0123+4567";
    int size = strlen(cal_str);
    char * char_ptr = strchr(cal_str, '+');
    assert(4 == (char_ptr - cal_str));
    assert(0 == strncmp("0123", cal_str, char_ptr - cal_str));
    assert(4 == (size- (char_ptr - cal_str) -1));
    assert(0 == strncmp(char_ptr + 1, "4567", 4));
    if (NULL) {
        printf("ORZ");
    }
    assert(int_add(INT_MAX, 1) == 1);   
}