import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { LoginInComponent } from './login-in.component';


const routes: Routes = [
  { path: '', redirectTo: '/login-in', pathMatch: 'full' },
  { path: 'login-in', component: LoginInComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
