$(document).ready(function () {
  'use strict';

  var alert = new Alert();
  var db = new CouchDB();
  var me_ip, ta_ip;
  var ip_url = "https://api.ipify.org?format=json";

  console.log("Welcome to Color-of-Mood");
  alert.warning('注意','开始游戏前请在设置里面绑定对方IP');
  
  db.test_connection(()=>{
    alert.danger('错误','无法连接服务器');
  }, ()=> {
    alert.primary('恭喜','连接服务器成功，可以绑定对方IP');
    $('#settingsModal button.btn.btn-primary.bindding')[0].disabled = false;
  });

  $.get(ip_url,responseText => {
    console.log("Your ip is ", responseText.ip);
    alert.primary('恭喜', '更新IP成功，可以点击设置查看当前IP');

    $('#settingsModal .input-group input.me').val(responseText.ip);
    $('#menu .settings')[0].disabled = false;
  });

  $('#settingsModal button.btn.btn-primary.bindding').on( "click", ()=>{
     me_ip = $('#settingsModal .input-group input.me')[0].value;
     ta_ip = $('#settingsModal .input-group input.ta')[0].value;
  })
})



