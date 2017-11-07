import { Injectable } from '@angular/core';
import { Headers, Http } from '@angular/http';

import 'rxjs/add/operator/toPromise';

import { Todo } from './todo';
import { Timer } from './timer';
import { Config } from './config';
import { UserService } from './user.service';

@Injectable()
export class TodoService {
  private gists_description = 'work-better config file';
  private config_filename = 'work-better';

  constructor(private http: Http,
    private userService: UserService) {

    this.getRowFile().then(id => console.log(id));
  }

  getTodos(): Promise<Todo[]> {
    return this.getRowFile()
      .then(obj => obj.todos as Todo[])
      .catch(this.handleError);
  }

  getRowFile(): Promise<Config> {
    return this.getGistId()
      .then(id =>
        this.http.get(this.userService.getGistsUrl() + '/' + id,
          { headers: this.userService.getHeaders() })
          .toPromise()
          .then(response => response.json().files[this.config_filename].raw_url)
      )
      .then(raw_url =>
        this.http.get(raw_url)
          .toPromise()
          .then(response => response.json())
      )
      .catch(this.handleError);
  }

  getGistId(): Promise<String> {
    return this.http.get(this.userService.getUserGistsUrl(),
      { headers: this.userService.getHeaders() })
      .toPromise()
      .then(response => response.json().filter(
        each_gists => each_gists.description === this.gists_description
      ))
      .then(response =>
        !(response[0] === undefined) ? response[0].id : this.createNewGist()
      )
      .catch(this.handleError);
  }

  createNewGist(): Promise<String> {
    console.log('create new config file');

    const templateFile = `
    {
      "description": "` + this.gists_description + `",
      "public": false,
      "files": {
        "` + this.config_filename + `": {
          "content": "` + JSON.stringify(new Config) + `"
        }
      }
    }`;
    return this.http.post(this.userService.getGistsUrl(), templateFile,
      { headers: this.userService.getHeaders() })
      .toPromise()
      .then(response => response.json().id);
  }

  private handleError(error: any): Promise<any> {
    console.error('An error occurred', error); // for demo purposes only
    return Promise.reject(error.message || error);
  }
}
