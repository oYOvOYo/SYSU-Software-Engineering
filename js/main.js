$(document).ready(function () {
  'use strict';

  var ip_url = "http://ip-api.com/json";

  console.log("Welcome to Color-of-Mood");

  httpGetAsync(ip_url, responseText => {
    $('#settingsModal .input-group input.me').val(JSON.parse(responseText).query);
    console.log(JSON.parse(responseText).query);
  })

  $('#menu .begin')[0].disabled = false;

  // $(".alert").alert('close');
  var bootstrap_alert = function () { }
  bootstrap_alert.alert = (type, strong, message) => {
    $('#alert_box').append('\
    <div class="alert alert-'+ type + ' alert-dismissible fade show" role="alert">\
      <button type="button" class="close" data-dismiss="alert" aria-label="Close">\
        <span aria-hidden="true">&times;</span></button>\
      <strong>'+ strong + '</strong>' + message + '</div>');
  }
  bootstrap_alert.warning = (strong, message) => {
    bootstrap_alert.alert('warning', strong, message);
  }
  bootstrap_alert.warning('Your text goes here','orz');

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



