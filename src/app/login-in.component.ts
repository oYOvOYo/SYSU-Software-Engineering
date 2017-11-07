import { Component, OnInit } from '@angular/core';

import { User } from './user';
import { UserService } from './user.service';



@Component({
  selector: 'app-login-in',
  templateUrl: './login-in.component.html',
})

export class LoginInComponent implements OnInit {
  user: User;

  constructor(private userService: UserService) {
    this.user = new User;
  }

  ngOnInit(): void {
  }

  login_in(): void {
    this.userService.setUser(User);
  }

  login_out(): void {
    this.userService.setUser(undefined);
  }
}
