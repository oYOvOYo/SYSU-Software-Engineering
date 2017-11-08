import { Component, OnInit } from '@angular/core';

import { User } from './user';
import { Timer } from './timer';
import { UserService } from './user.service';
import { DataService } from './data.service';


@Component({
  selector: 'app-timer',
  templateUrl: './timer.component.html',
})

export class TimerComponent implements OnInit {

  timers: Timer[];
  timer: Timer;

  constructor(private userService: UserService,
    private dataService: DataService) {
  }

  ngOnInit(): void {
    this.dataService.getTimers()
      .then(all_timers => this.timers = all_timers.slice(-3));
  }

  start(): void {
    this.timer = new Timer;
    this.timer.begin =  new Date();
  }

  end(): void {
    this.timer.end = new Date();
    this.dataService.addTimer(this.timer);
  }
}
