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

  todos: Todo[];
  select_todo: Todo;

  constructor(private userService: UserService,
    private todoService: TodoService) {
  }

  ngOnInit(): void {
    this.todoService.getTodos()
      .then(all_todos => this.todos = all_todos);
  }

  onSelect(todo: Todo) {
    this.select_todo = todo;
  }

  finished(todo: Todo) {
    todo.isFinished = true;
    this.update(todo);
  }

  update(todo: Todo) {
    this.todoService.updateTodo(todo);
  }
}
