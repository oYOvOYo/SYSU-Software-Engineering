"use strict"
window.onload = function(){
  var head = document.getElementsByTagName("head")[0];
  var body = document.getElementsByTagName("body")[0];
  var createElementByTagName = function(tagName) {
    return document.createElement(tagName);
  }
  // appendAllChild in childList 
  HTMLElement.prototype.appendAllChild = function(childList) {
    for (var i = 0; i < childList.length; i++) {
      this.appendChild(childList[i]);
    }
  }
  // link common.css 
  var commonStyle = createElementByTagName("link");
  commonStyle.href="https://jskyzero.github.io/Web/projects/OWN/css/common.css";
  commonStyle.rel="stylesheet";
  commonStyle.type="text/css";
  head.appendChild(commonStyle);

  // add header
  var header = createElementByTagName("Header");
  header.classList.add("Header");
  // header p
  var headerTitle = createElementByTagName("p");
  headerTitle.textContent = "jskyzero";
  // header nav
  var nav = createElementByTagName("nav");

  var twitter = createElementByTagName("a");
  twitter.href="https://twitter.com/jskyzero";
  twitter.textContent="twitter";
  var Github = createElementByTagName("a");
  Github.href="https://github.com/jskyzero";
  Github.textContent = "Github";
  nav.appendAllChild([headerTitle, Github, twitter]);
  header.appendChild(nav);
  body.insertBefore(header, body.children[0]);

  // add footer
  var footer = createElementByTagName("footer");
  footer.appendChild(createElementByTagName("br"));
  footer.insertBefore(document.createTextNode("By jskyzero"), footer.children[0]);
  footer.appendChild(document.createTextNode("2017/02/04"));
  body.appendChild(footer);
}
