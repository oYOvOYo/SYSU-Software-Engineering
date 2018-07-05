import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { RootComponent } from './root.component';
import { LoginInComponent } from './login-in.component';
import { DashBoardComponent } from './dashboard.component';
import { TodoComponent } from './todo.component';
import { TimerComponent } from './timer.component';


const routes: Routes = [
  { path: '', redirectTo: '/dashboard', pathMatch: 'full'},
  { path: 'dashboard', component: DashBoardComponent },
  { path: 'login-in', component: LoginInComponent },
  { path: 'todo', component: TodoComponent },
  { path: 'timer', component: TimerComponent },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
