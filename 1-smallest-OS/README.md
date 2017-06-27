# 最小的操作系统
现在开始动手写自己的最小的操作系统吧。

## 准备阶段
这里再次重申一下，可能完成一件事情主要的障碍会是一开始的环境配置。

另外本项目的主要作用是提供现有平台的解决方法，因而不会每一步像书本上步骤那么详细，每一步的目标应该是简单而清晰的，如果出现问题可以自行查阅参考或者自己寻找帮助。

### 工具配置
1. 虚拟机这里选用`VMware Workstation 12 Player`，请下载后安装完成。
2. 接下来大部分时间我们将使用Linux来编译（汇编）代码，这里选用的Linux发行版为`Ubuntu12.04 LTS`，请下载后使用上文的虚拟机软件创建一个虚拟机。
3. 汇编器方面，该书选用的是[NASM](http://www.nasm.us/)，`Wikipedia：The Netwide Assembler (NASM) is an assembler and disassembler for the Intel x86 architecture`，安装就`sudo apt-get install nasm`就好。

### 前置知识储备

您可能需要：
1. 一个安静不被打断的环境，一台拥有管理员权限的电脑，网络连接，和一颗愿意学习的心。
2. 会Windows/Linux系统下的基本操作。
3. 了解`Intel x86 architecture`及NASM编写。
4. 熟悉C语言编写。
如果你需要补充对应知识的话请求助于互联网。

### nasm 初步

> 请参考0.helloworld.asm

## 动手
1. 创建Linux虚拟机，设置共享文件夹。
2. 在windows下编写好代码
3. 在linux下汇编
4. 使用作者提供的软盘读写工具写成软盘
5. 使用虚拟机模拟运行。

会出问题的最后一步，新建一个MS dos虚拟机，设置软盘为我们上一部生成的文件即可。

