$(document).ready(function () {
  'use strict';

  var alert = new bootstrap_alert();
  var ip_url = "http://ip-api.com/json";

  console.log("Welcome to Color-of-Mood");
  $.get(ip_url,responseText => {
    $('#settingsModal .input-group input.me').val(responseText.query);
    console.log("Your ip is ", responseText.query);
  });

  $('#settingsModal button.btn.btn-primary.bindding').on( "click", ()=>{
    alert.warning('请注意','开始游戏前请在设置里面绑定对方IP');
  })
  
  $('#menu .begin')[0].disabled = false;

  // $(".alert").alert('close');
  function bootstrap_alert() { 
    this.alert = (type, strong, message) => {
      $('#alert_box').append('\
      <div class="alert alert-'+ type + ' alert-dismissible fade show" role="alert">\
        <button type="button" class="close" data-dismiss="alert" aria-label="Close">\
          <span aria-hidden="true">&times;</span></button>\
        <strong>'+ strong + '</strong>' + message + '</div>');
    }
    this.warning = (strong, message) => {
      this.alert('warning', strong, message);
    }
  }
})



