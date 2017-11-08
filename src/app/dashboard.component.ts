import { Component, OnInit } from '@angular/core';

import { User } from './user';
import { Todo } from './todo';
import { UserService } from './user.service';
import { TodoService } from './todo.service';


@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
})

export class DashBoardComponent implements OnInit {

  todos: Todo[];

  constructor(private userService: UserService,
    private todoService: TodoService) {
  }

  ngOnInit(): void {
    this.todoService.getTodos()
      .then(all_todos => this.todos = all_todos.slice(-3));
  }
}
