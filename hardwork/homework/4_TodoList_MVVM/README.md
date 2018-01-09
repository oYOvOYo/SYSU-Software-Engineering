# 现代操作系统应用开发实验报告

## 一．参考资料

[Windows 10 通用 Windows 平台 (UWP) 应用生命周期](https://docs.microsoft.com/zh-cn/windows/uwp/launch-resume/app-lifecycle#a-nameapp-launcha应用启动)

[Background activity with the Single Process Model](https://blogs.windows.com/buildingapps/2016/06/07/background-activity-with-the-single-process-model/#PC0rf34HdLavkEhG.97)

[App Lifecycle - Keep Apps Alive with Background Tasks and Extended Execution](https://msdn.microsoft.com/en-us/magazine/mt590969.aspx)




## 实验过程遇到的问题

1. 解决了自定义异步函数的问题（其实就是加了返回值，调用加了await）

2. 担心关闭一次保存不稳，想做成后台保存的，暂时不会。

## 交互说明

+ 页面交互请参考之前的实验说明，大体是参考系统邮件的变化。

+ 两个要求均已经实现，要求一通过保存所有Todo实现，要求二通过加一个设置保存页面信息实现。

+ 关于不同的地方：逻辑上认为点击+号添加后，就会添加新的Todo，已经会在内存里面改变，重新启动仍然存在，通过挂起函数里面的序列化保存实现。一次保存太多东西如果被拒绝就会,还是假装不会失败吧嗯。要求二想要实现在某个页面关闭后，下次重新打开还会回到该页面，不理解为什么要设置到添加页面，所以加了一个设置界面（索性写了配套的model/viewmodel/savefile部分），在这个页面关闭下次还是会被导肮到这里的。

+ 经验之谈：页面结构嵌套太多就搞得导航起来很玄幻，疯狂使用委托事件来实现，就很难受。不过尽力还是保持了架构之间的独立性。

+ 关于改进：和上次比，这次没有在页面间把viewmodel传来传去了，日后要改的地方，其他的几个界面补全/功能补全/继续分层。

