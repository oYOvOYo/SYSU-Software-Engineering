import { Component, OnInit } from '@angular/core';

import { User } from './user';
import { UserService } from './user.service';



@Component({
  selector: 'app-login-in',
  templateUrl: './login-in.component.html',
})

export class LoginInComponent implements OnInit {
  user: User;
  img_url: string;

  constructor(private userService: UserService) {
    this.user = new User;
    this.user.name = 'jskyzero';
    this.user.token = 'a79df060d395f0b31fdb6089c5e71e105274a6f2';
  }

  ngOnInit(): void {
    this.login_in();
    console.log('login');
  }

  login_in(): void {
    this.userService.setUser(this.user);
    this.userService.getImageUrl().then(url => this.img_url = url);
  }

  login_out(): void {
    this.userService.setUser(undefined);
    this.img_url = undefined;
  }
}
