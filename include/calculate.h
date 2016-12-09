#include "error.h"


int calculate(const char * str);

int int_add(int num1, int num2, int* have_error);
int int_sub(int num1, int num2, int* have_error);
int int_mul(int num1, int num2, int* have_error);
int int_div(int num1, int num2, int* have_error);

int expr(const char* cal_str, int size, int* have_error);
int term(const char* cal_str, int size, int* have_error);
int factor(const char* cal_str, int size, int* have_error);
int integer(const char* cal_str, int size, int* have_error);
int number(const char* cal_str, int size, int* have_error);
int digit(char ch, int* have_error);