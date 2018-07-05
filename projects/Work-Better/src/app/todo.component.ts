import { Component, OnInit } from '@angular/core';

import { User } from './user';
import { Todo } from './todo';
import { UserService } from './user.service';
import { DataService } from './data.service';


@Component({
  selector: 'app-todo',
  templateUrl: './todo.component.html',
})

export class TodoComponent implements OnInit {

  todos: Todo[];
  new_todo: Todo;
  update_title: string;
  select_todo: Todo;

  constructor(private userService: UserService,
    private dataService: DataService) {
  }

  ngOnInit() {
    this.fresh();
  }

  fresh() {
    this.dataService.getTodos()
      .then(all_todos => {
        this.todos = all_todos.reverse();
        // console.log(all_todos);
      });
  }

  onSelect(todo: Todo) {
    this.update_title = todo.title;
    this.select_todo = todo;
  }

  finished(todo: Todo) {
    todo.isFinished = true;
    this.dataService
    .updateTodo(todo.title, todo)
    .then(obj => {
      this.fresh();
    });
  }

  update(todo: Todo) {
    this.dataService
      .updateTodo(this.update_title, todo)
      .then(obj => {
        // this.fresh();
      });
  }

  create() {
    this.new_todo = new Todo;
  }

  add(todo: Todo) {
    this.dataService.addTodo(todo).then(obj => {
      if (this.todos === undefined) {
        this.todos = [todo];
      } else {
        this.todos.push(todo);
      }
      this.fresh();
    });
  }
}
