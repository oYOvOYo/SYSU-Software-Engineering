import { Component, OnInit } from '@angular/core';

import { User } from './user';
import { Alert } from './alert.service';
import { UserService } from './user.service';



@Component({
  selector: 'app-login-in',
  templateUrl: './login-in.component.html',
})

export class LoginInComponent implements OnInit {
  user: User;
  img_url: string;

  constructor(
    public userService: UserService,
    private alert: Alert) {
  }

  ngOnInit(): void {
    this.user = new User;
  }

  login_in(): void {
    this.userService.setUser(this.user);
    console.log('login');
    this.userService.getImageUrl().then(url => {
      this.img_url = url;
      this.alert.alert('primary', 'Welcome', this.user.name);
    }).catch(error => {
      this.alert.alert('danger', 'login failed', this.user.name);
    });

  }

  login_out(): void {
    this.userService.setUser(undefined);
    this.img_url = undefined;
    this.alert.alert('warning', 'logout', this.user.name);
  }
}
