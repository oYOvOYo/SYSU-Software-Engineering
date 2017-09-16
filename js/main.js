$(document).ready(function () {
  console.log("Welcome to Color-of-Mood");

  // $(".alert").alert('close');


  bootstrap_alert = function () { }
  bootstrap_alert.warning = function (message) {
    $('#alert_box').append('\
      <div class="alert alert-warning alert-dismissible fade show" role="alert">\
        <button type="button" class="close" data-dismiss="alert" aria-label="Close">\
          <span aria-hidden="true">&times;</span>\
        </button>\
        <strong>请注意</strong> 开始游戏前需要在设置绑定对方的IP地址\
       </div>');
  }
  bootstrap_alert.warning('Your text goes here');
  bootstrap_alert.warning('Your text goes here');

function httpGet(theUrl) {
  var xmlHttp = new XMLHttpRequest();
  xmlHttp.open("GET", theUrl, false); // false for synchronous request
  xmlHttp.send(null);
  return xmlHttp.responseText;
}

url = "https://api.ipify.org/?format=json";
console.log(JSON.parse(httpGet(url)).ip);
})



