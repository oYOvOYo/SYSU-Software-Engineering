import { Injectable } from '@angular/core';

export class Alert {

  constructor() {
    // add many types
    // const alert_types = ['primary', 'secondary', 'success', 'danger',
    //   'warning', 'info', 'light', 'dark'];

    // alert_types.forEach(function (type) {
    //   this[type] = (strong, message) => {
    //     this.alert(type, strong, message);
    //   };
    // }, this);
  }

  alert(type, strong, message): void {
    const div = document.createElement('div');
    div.className = 'alert alert-' + type + ' alert-dismissible fade show';
    const strong_text = document.createElement('strong');
    strong_text.innerText = strong;
    const common_text = document.createElement('span');
    common_text.innerText = message;
    const button = document.createElement('button');
    button.className = 'close';
    button.setAttribute('data-dismiss', 'alert');
    const span = document.createElement('span');
    span.innerText = '×';
    button.appendChild(span);
    div.appendChild(strong_text);
    div.appendChild(common_text);
    div.appendChild(button);
    document.getElementById('alert_box').appendChild(div);
  }
}
