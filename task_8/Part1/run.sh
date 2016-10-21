#!/bin/bash
# run.sh

# 先后台运行py
python find_reversed_words.py &

# 编译并运行C
gcc find_reversed_words.c -o find_reversed_words
./find_reversed_words
#移除可执行文件
rm find_reversed_words