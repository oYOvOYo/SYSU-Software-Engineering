# Task 3 #
`Release: 2016-09-14/12:16`

---
## 仿照hexdump(Unix)改进十六进制文件查看器（hex_viewer）##
* 具体功能为对 __任意文件__ 以 __十六进制__ 的方式进行查看，并显示在控制台(console)上。
* 其行为需与Unix下的hexdump程序在`-C`选项下的显示结果一致(具体请自行在Linux系统下进行分析)。
* 每行显示 __十六个字节__ 的内容，并且在每行的开头需要显示的 __当前行首字节__ 位置（_base-0,
start from 0, width 8 by default_），每个字节后跟一个空格。
* 并在每行行末输出空格后用两条竖线中间的位置输出当前行的字节对应的字符内容，如果为控制字符则输出'.'。
* 如果命令行输入参数有误，则显示具体参数用法 ``Usage: ./hex_viewer <file> [<num>]``；如果读取文件失败，
则显示``Cannot open the file 'filename' .``。（'filename'为具体文件路径, num为行首字节显示的width）
* 请自行在Linux系统下的diff（或使用git的diff）来测试你的程序`./hex_viewer <file>`
和`hexdump -C <file>`输出结果是否一致。

---
## Sample ##
* Data File:

	[hexdump.txt](./sample/hexdump.txt)
* Data Content:  

	![data content](./sample/data_content.png)

* Output Sample:  

	![output sample](./sample/output_sample.png)

---
##  Reference ##
* https://en.wikipedia.org/wiki/Hex_dump
* http://lxr.free-electrons.com/source/lib/hexdump.c
* https://www.freebsd.org/cgi/man.cgi?query=hexdump&sektion=1

---
## Deadline ##
	 2016-09-15/15:00
