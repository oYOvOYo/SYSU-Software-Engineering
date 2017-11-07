import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { RootComponent } from './root.component';
import { LoginInComponent } from './login-in.component';


const routes: Routes = [
  { path: '', redirectTo: '/#', pathMatch: 'full' },
  { path: '#', component: RootComponent },
  { path: 'login-in', component: LoginInComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
