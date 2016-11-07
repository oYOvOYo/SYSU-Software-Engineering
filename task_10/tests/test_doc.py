#!/usr/bin/env python
# -*- coding:utf-8 -*-


def square(x):
    """Square x.

    >>> square(2)
    4
    >>> square(-2)
    8
    """

    return x * x


def print_line(self, operation_char, operation_help):
    """print_line

    >>> print_line('1', '2')
    "1     - 2                                                 "
    """
    print "{operation_char:<5}- {operation_help:<48}".format(**vars())


import doctest
doctest.testmod()
