# Task 11 #
`2016-11-21/16:30`

## Requirement ##
- 计算机网络相关书籍阅读部分
  + 略读谢希仁著的《计算机网络》第五版（第六版纸质版亦可），重点部分为打'\*'的章节
    或小节。精读第一章（梗概）及第四、五章（即TCP/UDP协议以及IP协议）。
  + 精读《计算机网络·自顶向下方法（第六版）》的第一章。
  + 可结合《TCP/IP详解（卷一）》来阅读（这个的确有点难度）。
- 网上资源阅读部分（需先完成上一部分）
  + [知乎用户车小胖专栏](https://zhuanlan.zhihu.com/p/22516664)（这个看不懂很正常）
  + [看这个知乎问题的Raynor的回答](https://www.zhihu.com/question/22017267)
- 使用Linux系统的telnet命令进行初步实践部分
  + 利用telnet访问并获取中山大学官方网站主页( http://www.sysu.edu.cn/ )的html代码内容。
    （利用好chrome浏览器的F12的开发人员工具，注意Network部分的内容，来弄清楚浏览器的请
    求行为细节）
  + 利用telnet的GET指令访问 [http://owtotwo.top:8080/](http://owtotwo.top:8080/)
    网站的主页及获取其HTML内容并保存下来，然后利用telnet的POST指令对 [/login](/login)
    进行模拟登陆此网站(用户名和密码皆为 _testing_ )，然后通过服务器返回的Session以及
    重定向页面（注意观察状态码）的URL，来再一次进行GET此网站的主页，确保与前一个保存的
    主页html代码内容不同（即已登陆状态下的主页）。
- 使用python2.7的urllib2再次实践部分
  + 通过[python官方文档urllib2部分](https://docs.python.org/2/library/urllib2.html)
    来了解urllib2的使用方法，以及进行Example部分的代码实践。
  + 使用urllib2来对上一部分的内容再一次进行实验。
  + 使用python2.7编写脚本对网站[http://owtotwo.top:8080/](http://owtotwo.top:8080/)
    自动注册账号，脚本运行参数有用户名(-u)和密码(-p)。
  + 请不要把服务器给炸了。

## Deadline ##
`2016-11-28/23:00`
