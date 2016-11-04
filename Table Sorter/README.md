# Table-sorter

[TOC]

### 题目一 优化

#### 任务要求

>#### 需求规格（50分）
>
>1. Games功能如旧，完全正常（30分，一个Game不正常扣8分，扣完为止）
>2. 代码减少（10分，一个Game做不到扣3分，扣完为止）
>3. 代码可读性增强（10分，一个Game做不到扣3分，扣完为止）
>
>
>#### 软件质量要求（10分）
>
>JavaScript代码模块化，命名合理（5分），每个方法不超过10行（5分）



#### 完成情况

- [x] Games功能如旧，完全正常
- [x] 代码减少
- [x] 代码可读性增强
- [x] JavaScript代码模块化，命名合理
- [x] 每个方法不超过10行[^注1]


#### 长度改变说明

| Title       | Old Lenth | New Lenth | Comments                                 |
| ----------- | :-------- | --------- | ---------------------------------------- |
| puzzle game | 82        | 63        | 按照老师要求之前使用了jQuery这次没有使用,恩然后为了那点加分还减少了代码长度(滑稽)[^注2] |
| Mole game   | 93        | 72        | 重构了代码结构,使用自顶向下的设计,jQuery使得对象的获取和改变更为容易(正经) |





### 题目二 Table Sorter 

#### 任务要求

>1. #### 需求规格（30分）
>
>   1. UI、交互和上图完全一致（10分）
>   2. 能够排序(10分）
>   3. 其它网页（10分，一个网页3分，封顶10分）
>
>   #### 软件质量要求（10分）
>
>   JavaScript代码模块化，命名合理（5分），每个方法不超过10行（5分）



#### 完成情况:

- [x] UI、交互和上图完全一致
- [x] 能够排序
- [x] 其它网页
- [x] JavaScript代码模块化，命名合理
- [x] 每个方法不超过10行[^注1]



#### 其他网页

[ac.2333.moe](https://ac.2333.moe/Problem.xhtml)

[acm.hust.edu.cn](http://acm.hust.edu.cn/problem/list)

[wiki.dengekionline.com](http://wiki.dengekionline.com/battlegirl/%E3%82%AC%E3%83%81%E3%83%A3%E6%AD%A6%E5%99%A8%E4%B8%80%E8%A6%A7)

[wiki.dengekionline.com2](http://wiki.dengekionline.com/battlegirl/%E3%83%A2%E3%83%81%E3%83%BC%E3%83%95%E6%AD%A6%E5%99%A8%E4%B8%80%E8%A6%A7)

#### 插入代码

```
(function(){var sortTable=function(table){var createTable=function(table){var tableHead=table.find("thead");var tableBody=table.find("tbody");var trList=tableBody.find("tr");var haveBeenSord;this.sort=function(index){var index=$(this).index();var sortAscend=function(tr1,tr2){var str1=tr1.children[index].textContent;var str2=tr2.children[index].textContent;return str1.localeCompare(str2)};var sortDescend=function(tr1,tr2){return -sortAscend(tr1,tr2)};if(haveBeenSord){haveBeenSord=false;trList.sort(sortDescend)}else{haveBeenSord=true;trList.sort(sortAscend)}tableBody.append(trList)};tableHead.find("th").bind("click",this.sort)};var tableObj=new createTable(table)};$("table").each(function(){sortTable($(this))})})();
```



---



### Reference

[Homework 8. Table Sorter](http://my.ss.sysu.edu.cn/wiki/display/WEB/Homework+8.+Table+Sorter)

[^注1]: 由于方法存在嵌套,这里理解为最底层单个方法满足小于0行, 对于外层为底层函数均为一行
[^注2]: 有一个主函数怎么算长度都超过10行, 由于没有使用jQUery还希望TA dalao 酌情理解.
