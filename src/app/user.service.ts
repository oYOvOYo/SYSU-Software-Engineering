import { Injectable } from '@angular/core';

import { User } from './user';

@Injectable()
export class UserService {
  private user: User;

  constructor() { }

  getUser(): User {
    return this.user;
  }

  setUser(user): void {
    this.user = user;
  }

  isLoginIn(): Boolean {
    return this.user !== undefined;
  }
}
