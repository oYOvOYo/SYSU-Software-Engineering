#!/usr/bin/env python
# -*- coding: utf-8 -*-


from content import *
import unittest


class NoteTest(unittest.TestCase):

    def test_Note(self):
        note = Note("1", "orz")
        self.assertEqual(note.title, "1")
        self.assertEqual(note.data, "orz")

    def test_read_note(self):
        note = Note("1", "orz")
        str = json.dumps(note, default=lambda note: note.__dict__)
        note2 = json.loads(str, object_hook=lambda dic: read_Note(dic))
        self.assertEqual(note.title, "1")
        self.assertEqual(note.data, note2.data)


if __name__ == "__main__":
    TestModel = unittest.TestLoader().loadTestsFromTestCase(NoteTest)
    unittest.TextTestRunner(verbosity=3).run(TestModel)
