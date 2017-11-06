import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})

export class AppComponent {
  title = 'Work-Better';
  hero: Hero = {
    id: 1,
    name: 'hero1'
  };
}

export class Hero {
  id: number;
  name: string;
}
