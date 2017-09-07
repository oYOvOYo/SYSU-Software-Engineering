$(document).ready( function() {
  
  console.log("Welcome to use tweet");

  $("#postButton").click(function() {
    var postData = { data: getPostContent()};
    console.log(JSON.stringify(postData));

    $.ajax({
      method: "POST",
      url: "/post",
      data: JSON.stringify(postData)
    }).done(function(meg) {
      finishedPost(meg);
    });
  })

  $("#getButton").click(function() {
    $.ajax({
      method: "GET",
      url: "/get",
    }).done(function(meg) {
      finishedGet(meg);
    })
  })

  $("#getButton").click();
  
  function getPostContent() {
    return $("#postContent").text();
  }

  function finishedPost(meg) {
    $("#postContent")[0].innerHTML = meg;
  }

  function finishedGet(meg) {
    var totalTweet = JSON.parse(meg);

    $("#totalTweet").empty();

    for (var i = 0; i < totalTweet.length; i++) {
      addTweet(totalTweet[i]);
    }
  }
})

function addTweet(eachTweet) {
  var newTweet = document.createElement("div");
  newTweet.className = "eachTweet";

  var newTime = document.createElement("div");
  newTime.className = "eachTime";
  newTime.innerHTML = getDateTime(eachTweet.time);
  
  var newContent = document.createElement("p");
  newContent.className = "eachContent";
  newContent.innerHTML = eachTweet.data;
  
  newTweet.appendChild(newTime);
  newTweet.appendChild(newContent);
  
  $("#totalTweet")[0].append(newTweet);
}

function getDateTime(time) {
    var date = new Date(time);

    var hour = date.getHours();
    hour = (hour < 10 ? "0" : "") + hour;

    var min  = date.getMinutes();
    min = (min < 10 ? "0" : "") + min;

    // var sec  = date.getSeconds();
    // sec = (sec < 10 ? "0" : "") + sec;

    var year = date.getFullYear();

    var month = date.getMonth() + 1;
    month = (month < 10 ? "0" : "") + month;

    var day  = date.getDate();
    day = (day < 10 ? "0" : "") + day;

    return year + ":" + month + ":" + day + ":" + hour + ":" + min ;
}
