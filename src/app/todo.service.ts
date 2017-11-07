import { Injectable } from '@angular/core';
import { Headers, Http } from '@angular/http';

import 'rxjs/add/operator/toPromise';

import { User } from './user';
import { Todo } from './todo';
import { UserService } from './user.service';

@Injectable()
export class TodoService {
  private Todos: Todo[];

  constructor(private http: Http,
    private userService: UserService) {
    // this.http.get(userService.getGistsUrl(),
    //             {headers: this.userService.getHeaders()})
    //   .toPromise()
    //   .then(response => console.log(response.json()));
    const str = `{
      "description": "the description for this gist",
      "public": true,
      "files": {
        "file1.txt": {
          "content": "String file contents"
        }
      }
    }`;
    this.http.post(userService.getGistsUrl(), str,
      { headers: this.userService.getHeaders() })
      .toPromise()
      .then(response => console.log(response.json()));
  }

  getAllTodo(): Todo[] {
    return this.Todos;
  }

  addTodo(todo): void {
    this.Todos.push(todo);
  }

  getTodoByTitle(title): Todo[] {
    return this.Todos.filter(todo => todo.title === title);
  }
}
