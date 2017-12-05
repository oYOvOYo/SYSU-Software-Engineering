var http = require("http");
var url = require("url");
var path = require("path");
var fs = require('fs');
var qs = require('querystring');

var port = 3000;

"use strict"
var tweet = [];

http.createServer(function(req, res) {
  var pathname = url.parse(req.url).pathname;
  var mimeType = getMimeType(pathname);
  if (!!mimeType) {
    handlePage(req, res, pathname);
  } else {
    handleAjax(req, res);
  }
}).listen(port, function(){
  console.log('server listen on ', port);
});

function getMimeType(pathname) {
  var validExtensions = {
    ".html" : "text/html",
    ".js"   : "application/javascript",
    ".css"  : "text/css",
    ".jpg"  : "image/jpeg",
    ".gif"  : "image/gif",
    ".png"  : "image/png"  };
  var ext = path.extname(pathname);
  var type = validExtensions[ext];
  return type;
}

function handlePage(req, res, pathname) {
  var filePath = __dirname + pathname;
  var mimeType = getMimeType(pathname);

  if (fs.existsSync(filePath)) {
    fs.readFile(filePath, function(err, data) {
      if (err) {
        res.writeHead(500);
        res.end();
      } else {
        res.setHeader("Content-Length", data.length);
        res.setHeader("Content-Type", mimeType);
        res.statusCode = 200;
        res.end(data);
      }
    });
  } else {
    res.writeHead(500);
    res.end();
  }
}

function handleAjax(req, res) {
  console.log(req.url);

  if (req.url == "/post" && req.method == "POST" ) {
    handlePostAjax(req, res);
  } else
  if (req.url == "/get" && req.method == "GET") {
    handleGetAjax(req, res);
  } else {
    res.writeHead(500);
    res.end();
  }
  // res.writeHead(200, {'Content-Type': 'text/plain'});
  // res.end("123");
  // res.end("" + JSON.stringify);
}

function handlePostAjax(req, res) {
  var postData = "";
  req.on('data', function(data) {
    postData += data;
    if (postData.length > 1e6)
      req.connection.destroy();
  })

  req.on('end', function() {
    if (postData.length) {
      console.log("Get message", postData);
      addNewTweet(JSON.parse(postData));
    }
  })

  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end("Success");
}

function handleGetAjax(req, res) {
  var getData = JSON.stringify(tweet);
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end(getData);
}

function addNewTweet(postData) {
  postData.time = new Date();
  tweet.push(postData);
  console.log(tweet);
}
