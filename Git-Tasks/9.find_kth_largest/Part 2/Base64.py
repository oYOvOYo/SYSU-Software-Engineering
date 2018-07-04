#!/usr/bin/env python
# -*- coding: utf-8 -*-


import base64


if __name__ == "__main__":
    str = 'TWlkdGVybSBFeGFtIEZpZ2h0aW5nIQ=='
    print "Initial String"
    print str
    print "Encode"
    print base64.standard_b64encode(str)
    print "Decode"
    print base64.standard_b64decode(str)