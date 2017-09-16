$(document).ready(function () {
  'use strict';

  var alert = new bootstrap_alert();
  var ip_url = "http://ip-api.com/json";

  console.log("Welcome to Color-of-Mood");

  httpGetAsync(ip_url, responseText => {
    $('#settingsModal .input-group input.me').val(JSON.parse(responseText).query);
    console.log(JSON.parse(responseText).query);
  })

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
  

  function httpGet(theUrl) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", theUrl, false); // false for synchronous request
    xmlHttp.send(null);
    return xmlHttp.responseText;
  }

  function httpGetAsync(theUrl, callback) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function () {
      if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
        callback(xmlHttp.responseText);
    }
    xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    xmlHttp.send(null);
  }
})



