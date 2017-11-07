import { Component, OnInit } from '@angular/core';

import { User } from './user';
import { Todo } from './todo';
import { UserService } from './user.service';
import { TodoService } from './todo.service';


@Component({
  selector: 'app-todo',
  templateUrl: './todo.component.html',
})

export class TodoComponent implements OnInit {

  constructor(private userService: UserService,
              private todoService: TodoService) {
  }

  ngOnInit(): void {
  }
}
