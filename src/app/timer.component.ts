import { Component, OnInit } from '@angular/core';

import { User } from './user';
import { Timer } from './timer';
import { UserService } from './user.service';
import { TodoService } from './todo.service';


@Component({
  selector: 'app-timer',
  templateUrl: './timer.component.html',
})

export class TimerComponent implements OnInit {

  timers: Timer[];

  constructor(private userService: UserService,
    private todoService: TodoService) {
  }

  ngOnInit(): void {
    // this.todoService.getTodos()
    //   .then(all_todos => this.todos = all_todos.slice(-3));
  }
}
