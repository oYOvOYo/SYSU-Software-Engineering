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
  time_str: string;
  isCounting: Boolean;
  getDate = Timer.getDate;
  getElapsedTime = Timer.getElapsedTime;

  constructor(private userService: UserService,
    private dataService: DataService) {
      setInterval(function () {
        this.update_time_str();
      }.bind(this), 1000);
  }

  ngOnInit(): void {
    this.fresh();
  }

  update_time_str(): void {
    if (this.isCounting) {
      const now = new Date().getTime();
      // Find the distance between now an the count down date
      const distance = now - this.timer.begin.getTime();
      // Time calculations for days, hours, minutes and seconds
      const days = Math.floor(distance / (1000 * 60 * 60 * 24));
      const hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
      const minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
      const seconds = Math.floor((distance % (1000 * 60)) / 1000);
      this.time_str = days + 'd ' + hours + 'h '
        + minutes + 'm ' + seconds + 's ';
    }
  }

  fresh() {
    this.dataService.getTimers()
      .then(all_timers => this.timers = all_timers.reverse());
  }

  start(): void {
    this.isCounting = true;
    this.timer = new Timer;
    this.timer.begin = new Date();
  }

  end(): void {
    this.isCounting = false;
    this.timer.end = new Date();
    this.dataService.addTimer(this.timer).then(obj => {
      if (this.timers === undefined) {
        this.timers = [this.timer];
      } else {
        this.timers.push(this.timer);
      }
      this.fresh();
    });
  }

}
