# Work-Better
`jskzero` `2017/11/07`

## Overview

+ work-better contails a todilist and a timer which designed to help you work better.
+ work-better use github account and gits to store data, so you can get your data evevry where.
+ work-better is implemented by angularJS v5.0.0

![preview](/src/assets/img/1.png)

## Install & Run

+ firstly you should hava `nodejs` envirment, and `npm` package manager. use npm to install `angularJS` first.
  ```
  nodejs -v
  npm -v
  npm install -g @angular/cli
  ```

+ install
  ```
  git clone https://github.com/jskyzero/Work-Better.git
  cd Work-Better
  npm install
  ```
+ run
  ```
  npm run
  ```
  then open your browser to open the site

## More UI
![preview](/src/assets/img/3.png)
![preview](/src/assets/img/2.png)
![preview](/src/assets/img/4.png)

## ISSUE

because of the broswer CORS secure issue, I can't set request header to disable cache, the OPTIONS pre-request cause Access-Control-Allow-Headers error, so the update will not show in time, you can **use browser debug mode and set disable cache** by hand to solve it.

## Thanks

Thanks to someone who maybe will not want his(her) name show here.
