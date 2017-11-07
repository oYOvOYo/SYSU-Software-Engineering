import { Component } from '@angular/core';

const html = `
<h1>Work Hard</h1>
<app-login-in></app-login-in>
`;
// <router-outlet></router-outlet>

@Component({
  selector: 'app-root',
  template: html
})
export class RootComponent {

}

