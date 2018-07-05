import { Component, OnInit } from '@angular/core';

import { User } from './user';
import { Todo } from './todo';
import { Timer } from './timer';
import { UserService } from './user.service';
import { DataService } from './data.service';


@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
})

export class DashBoardComponent implements OnInit {

  todos: Todo[];
  timers: Timer[];
  getDate = Timer.getDate;
  getElapsedTime = Timer.getElapsedTime;

  constructor(private userService: UserService,
    private dataService: DataService) {
  }

  ngOnInit(): void {
    this.fresh();
  }

  fresh() {
    this.dataService.getRowFile()
    .then(config => {
      this.timers = config.timers.slice(-5).reverse();
      this.todos = config.todos.slice(-5).reverse();
    });
  }
}
