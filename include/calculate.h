//
// calculate.h
// Copyright (C)  2016 jskyzero
//
// the main part of the calculate
//

#include "arithmetic.h"

int calculate(const char * str);

int expr(const char* cal_str, int size, int* have_error);
int term(const char* cal_str, int size, int* have_error);
int factor(const char* cal_str, int size, int* have_error);
int integer(const char* cal_str, int size, int* have_error);
int number(const char* cal_str, int size, int* have_error);
int digit(char ch, int* have_error);