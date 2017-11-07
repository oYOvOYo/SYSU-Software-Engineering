import { Component } from '@angular/core';

import { UserService } from './user.service';
// <router-outlet></router-outlet>

@Component({
  selector: 'app-root',
  templateUrl: './root.component.html'
})
export class RootComponent {
  constructor(private userService: UserService) {
  }
}

