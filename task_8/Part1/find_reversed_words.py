#!/usr/bin/env python
# -*- coding: utf-8 -*-


if __name__ == "__main__":
    with open('words', 'rt') as f:
        words_list = f.read().split()
        with open('result_py', 'wt') as result:
            for word in words_list:
                if word[::-1] in words_list:
                    print word
                    result.write(word)
                    result.write('\n')
