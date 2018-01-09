# lexical_analysis
`jskyzero` `2017/01/10`

## Overview

设一语言的关键词、运算符、分界符的个数与单词如下： 
```cpp
struct { int number; string str[10]; } keywords={3,"int","main","return"} ; //关键词
struct { int number; string str[10]; } operators ={5,"+","*","=","+=","*="}; //运算符
struct { int number; string str[10]; } boundaries ={6,"(",")","{","}",",",";"} ; //分界符
struct { int number; string str[100];} identifieres={0}; //标识符
struct { int number; string str[100];} Unsigned_integer={0}; //无符号整数
```
以上类号分别为1~5，序号从0开始；
标识符是字母开头的字母数字串；常量为无符号整数；
用C++设计一程序实现词法分析。

输入一程序，结束符用”#”；

输出单词数对：<类号，序号>。 输出标识符表，用空格分隔； 输出无符号整数表，用空格分隔；

## Install & Run

```
chmod a+x run
./run
```