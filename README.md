# Simple-calculator
## 要求

- 基于命令行实现一个能对32位有符号整数(-2147483648 ~ 2147483647)进行四则运算('+', '-', '*', '/')的计算器。
- 能使用括号进行表达式嵌套('(', ')')，不同词法单元间（ 数字及运算符）可以有任意空格（包括制表符及换行符）。
- 表达式输入的行中应当有对应的提示符(prompt)，如">>"。
- 当表达式输入正确后键入回车，程序就进行相应的运算并在下 一行显示结果。
- 当表达式输入错误时则显示错误信息。
- 当结果溢出时则显示溢出错误。
- 当出现除零时则显示除零错误。
- 无论输入错误与否，计算成功与否，皆在输出相应信息后另起 一行继续下一次的输入。
- 输入Ctrl+C则立即结束程序(shutdown)。
- 若直接输入EOF则退出程序(exit)。

## Backus–Naur Form

```
<Expression>          ::=  <AdditiveExpression>
<AdditiveExpression>  ::=  <AdditiveExpression> "+" <MultipleExpression>  	    
                         |  <AdditiveExpression> "-" <MultipleExpression> 
                         |  <MultipleExpression>
<MultipleExpression>  ::= <MultipleExpression> "*" <PrimaryExpression>
                         | <MultipleExpression> "/" <PrimaryExpression> 
                         | <PrimaryExpression>
<PrimaryExpression>   ::= "(" <Expression> ")" 
                         | <Integer>
<Integer>             ::= "-" <Number>
                         | "+" <number>
                         | <number>
<number>              ::= <digit> <number>
                          | <digit>
<digit>   ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```

## Project Structure

```
.
├── bin
│   └── SimpleCalculator
├── build
│   └── *.o
├── include
│   ├── arithmetic.h	// basic arithmetic using only int
│   ├── calculate.h		// the main part of the calculate	
│   ├── error.h 		// define some errors and some func about error
│   ├── shellUI.h		// a shell UI read message and use the message
│   └── test.h			// some tests 
├── LICENSE
├── makefile
├── README.md
└── src
    ├── arithmetic.c
    ├── calculate.c
    ├── error.c 
    ├── shellUI.c
    ├── SimpleCalculator.c
    └── test.c
```

## References

[Elementary arithmetic](https://en.wikipedia.org/wiki/Elementary_arithmetic)
