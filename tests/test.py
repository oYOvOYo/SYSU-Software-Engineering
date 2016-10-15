#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __init__ import *


TestModel = unittest.TestLoader().loadTestsFromTestCase(TestModelFunctions)
unittest.TextTestRunner(verbosity=2).run(TestModel)

TestController = unittest.TestLoader().loadTestsFromTestCase(TestControllerFunctions)
unittest.TextTestRunner(verbosity=2).run(TestController)