import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-root',
  template: `
  <h1>work hard</h1>`
})
export class LoginInComponent implements OnInit {
  // constructor(private heroService: HeroService) { }

      ngOnInit(): void {
        // this.heroService.getHeroes()
        //   .then(heroes =>
        //     this.heroes = heroes.slice(1, 5));
      }
}
