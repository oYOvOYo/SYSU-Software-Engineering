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
  }

  ngOnInit(): void {
    this.user = new User;
  }

  login_in(): void {
    this.userService.setUser(this.user);
    console.log('login');
    this.userService.getImageUrl().then(url => this.img_url = url);
  }

  login_out(): void {
    this.userService.setUser(undefined);
    this.img_url = undefined;
  }
}
