$(document).ready( function() {
  console.log("Welcome to Color-of-Mood");

  // $(".alert").alert('close');


  // bootstrap_alert = function() {}
  // bootstrap_alert.warning = function(message) {
  //             $('#alert_placeholder').html('<div class="alert"><a class="close" data-dismiss="alert">×</a><span>'+message+'</span></div>')
  //         }
  // bootstrap_alert.warning('Your text goes here');
  // });

  function httpGet(theUrl) {
      var xmlHttp = new XMLHttpRequest();
      xmlHttp.open( "GET", theUrl, false ); // false for synchronous request
      xmlHttp.send( null );
      return xmlHttp.responseText;
  }

  url="https://api.ipify.org/?format=json";
  console.log(JSON.parse(httpGet(url)).ip);
})



