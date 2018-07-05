#!/usr/bin/env python
# -*- coding:utf-8 -*-


from content import *


def NoteServiceTest():
    service = NoteService()
    data = service.list_all_note()
    service.delete_all_note()

    assert service.create_note("1", "helloworld")
    assert service.model.note_list[0].title == "1"
    assert service.model.note_list[0].data == "helloworld"

    assert service.create_note("2", "hi= = = = ")
    assert not service.create_note("2", "")

    assert len(service.querry_note_by_title("1")) == 1
    assert len(service.querry_note_by_keyword("h")) == 2

    assert service.update_note_title("1", "11") == 1
    assert service.model.note_list[0].title == "11"
    assert service.update_note_data("11", "hi- - - - ") == 1
    assert len(service.querry_note_by_keyword("hi")) == 2

    assert service.delete_note("2") == 1
    assert len(service.model.note_list) == 1

    service.write_data()
    return data


def NoteServiceTest2(data):
    service = NoteService()
    assert len(service.model.note_list) == 1
    service.delete_all_note()

    service.model.note_list = data
    service.write_data()

data = NoteServiceTest()
NoteServiceTest2(data)
