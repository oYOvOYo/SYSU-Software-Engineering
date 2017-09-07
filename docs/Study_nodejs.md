# Node.js


## URL

1. details each of the components of a parsed URL
```
   ┌─────────────────────────────────────────────────────────────────────────────┐
   │                                    href                                     │
   ├──────────┬┬───────────┬─────────────────┬───────────────────────────┬───────┤
   │ protocol ││   auth    │      host       │           path            │ hash  │
   │          ││           ├──────────┬──────┼──────────┬────────────────┤       │
   │          ││           │ hostname │ port │ pathname │     search     │       │
   │          ││           │          │      │          ├─┬──────────────┤       │
   │          ││           │          │      │          │ │    query     │       │
   "  http:   // user:pass @ host.com : 8080   /p/a/t/h  ?  query=string   #hash "
   │          ││           │          │      │          │ │              │       │
   └──────────┴┴───────────┴──────────┴──────┴──────────┴─┴──────────────┴───────┘
   (all spaces in the "" line should be ignored -- they are purely for formatting)
```

2. The `url.format()` method returns a formatted URL string derived from`urlObject`.

```
url.format(urlObject)
```

3. The `url.parse()` method takes a URL string, parses it, and returns a URL object.

```
url.parse(urlString[, parseQueryString[, slashesDenoteHost]])c
```

4. The `url.resolve()` method resolves a target URL relative to a base URL in a manner similar to that of a Web browser resolving an anchor tag HREF.

```
url.resolve(from, to)
```

## Query String

1. The `querystring.parse()` method parses a URL query string (`str`) into a collection of key and value pairs.

   ```
   querystring.parse(str[, sep[, eq[, options]]])#
   Added in: v0.1.25
   str <String> The URL query string to parse
   sep <String> The substring used to delimit key and value pairs in the query string. Defaults to '&'.
   eq <String>. The substring used to delimit keys and values in the query string. Defaults to '='.
   options <Object>
   decodeURIComponent <Function> The function to use when decoding percent-encoded characters in the query string. Defaults to querystring.unescape().
   maxKeys <number> Specifies the maximum number of keys to parse. Defaults to 1000. Specify 0 to remove key counting limitations.
   ```

2. The `querystring.stringify()` method produces a URL query string from a given `obj` by iterating through the object's "own properties".

   ```
   querystring.stringify(obj[, sep[, eq[, options]]])#
   Added in: v0.1.25
   obj <Object> The object to serialize into a URL query string
   sep <String> The substring used to delimit key and value pairs in the query string. Defaults to '&'.
   eq <String>. The substring used to delimit keys and values in the query string. Defaults to '='.
   options
   encodeURIComponent <Function> The function to use when converting URL-unsafe characters to percent-encoding in the query string. Defaults to querystring.escape().
   ```

## simple example
```javascript
// var http = require('http');
// var url = require('url');
// var fs = require('fs');
// var querystring = require('querystring');

// http.createServer(function (request, response) {
//     response.writeHead(200, { 'Content-Type': 'text/plain' });
//     response.write('Hello ' + 'World'+ '!\n');
//     console.log(url.parse(request.url).href);
//     console.log(url.parse(request.url).query);
//     response.write(url.format(request.url));
//     response.end(index.html);
// }).listen(8010);

// console.log('Server running at http://127.0.0.1:8010/');
var http = require('http');
var fs = require('fs');
var url = require('url');


// 创建服务器
http.createServer( function (request, response) {  
   // 解析请求，包括文件名
   var pathname = url.parse(request.url).pathname;
   
   // 输出请求的文件名
   console.log("Request for " + pathname + " received.");
   
   // 从文件系统中读取请求的文件内容
   fs.readFile(pathname.substr(1), function (err, data) {
      if (err) {
         console.log(err);
         // HTTP 状态码: 404 : NOT FOUND
         // Content Type: text/plain
         response.writeHead(404, {'Content-Type': 'text/html'});
      }else{	         
         // HTTP 状态码: 200 : OK
         // Content Type: text/plain
         response.writeHead(200, {'Content-Type': 'text/html'});	
         
         // 响应文件内容
         response.write(data.toString());		
      }
      //  发送响应数据
      response.end();
   });   
}).listen(8010);

// 控制台会输出以下信息
console.log('Server running at http://127.0.0.1:8010/');
```