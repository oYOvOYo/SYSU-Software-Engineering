---
layout:     post
title:      "HTML-Study"
date:       2017-02-10
updated:     2017/02/28
tags:
    - Web
    - HTML
categories:
    - Web
---

MDN Web HTML的相关知识

# HTML-Study

> 还是要打好基础，即便是有时间也会被浪费掉的话，不如来好好整理一下，原版请参考reference

---

## Web 技术

1. 基础
    1. HTML 超文本标记语言，描述和定义Web页面内容。
    2. CSS 层叠样式表，描绘Web内容的外观
    3. HTTP 超文本传输协议，用于在Web上传输HTML和其他超媒体文档。
2. 脚本编写
    1. javascript 一种浏览器端编程语言，由于高级用户交互的Web站点和安全浏览器执行的应用。
    2. Web APIs DOM及所有构建Web内容和应用的API和接口。
3. 图像
    1. SVG 可缩放矢量图形 用矢量和形状来描绘图像。
    2. WebGL 通过符合OpenGL ES2.0规范的API将3D图形引入Web中。
4. 其他
    1. MathML 数学标记语言 用于显示复杂数学公式和语法。

## HTML开发者指南

### 可编辑性
```html
<p contenteditable="true">This content can be edit by user</p>
```

### 分类策略

1. 主内容类
2. 表单相关的内容类
3. 特殊内容类

![主内容类](https://developer.mozilla.org/@api/deki/files/6244/=Content_categories_venn.png?size=webview)

### 表单

1. \<input> type 
2. \<form> pattern
...

### 入门

> HTML 是一种标记语言（markup language）。它告诉浏览器如何显示内容。HTML把内容（文字，图片，语言，影片等等）和「presentation」（这个内容是如何显示，比如文字用什么颜色显示等等）分开。HTML使用预先定义的元素集合来识别内容形态。 元素包含一个以上的标记来包含或者表达内容。标记利用尖括号表示，而结束标记（用来指示内容尾端）则在前面加上斜线

HTML由不同的元素集合组成，元素定义了他们所包含内容的语义。

元素的层次化结构称为 DOM: Document Object Model--文档对象模型。

HTML 为由一对尖括号（<>）所括起来的内容赋予了特定含义. 这样的标识称为一个 标签（tag）。结束标签与起始标签在内容上是一样的，但结束标签会在小于符号（<）后多一个整斜线/。 大多数 HTML 元素由一个起始标签和一个结束标签标识。起始标签和结束标签应成对出现，也就是说在一个起始标签之后应有其对应的结束标签。有些元素没有包含文本内容或者其他元素，这称为空元素。它们没有结束标签，一般在结束标签后面空格加上个斜杠（这在XHTML是必需的）。

开始标签包含一些元素特性,包括特征名和特征值，一些元素可以只有特性名，特性值如果包含括号就要使用引号，单个词为了避免出错和易于识别一般也会加上引号。

命名字符：

```
1. &gt; 表示大于符号">" (>)
2. &lt; 表示小于符号"<" (<)
3. &amp; 表示和符号"and"(&)
4. &quot; 表示引用符号" (")
```

文档类型声明告诉了浏览器需要遵循W3C标准来解析HTML和CSS代码，且不必尝试去模拟90年代的IE环境。

```html
<!DOCTYPE html>
<!-- this is comment -->
```

### HTML5

HTML5是一个新的HTML5语言版本包含了新的元素，属性，和行为，同时包含了一系列技术，通常被通常通称为HTML5.

### HTML5的文档节段和纲要

### HTML表单指南

### 音频和视频

```html
<audio src="audio.ogg" preload="auto" controls autoplay loop>
<p>你的浏览器不支持<code>audio</code>标签</p>
</audio>

<video controls>
  <source src="foo.ogg" type="video/ogg">
  <source src="foo.mp4" type="video/mp4">
  Your browser does not support the <code>video</code> element.
</video>
```

使用javascrip播放媒体/备选项（flash/java）/错误处理

### 如何制作快速加载的HTML的页面

1. 减小页面大小
2. 最小化文件数量
3. 减少域名查找
4. 缓存重用的内容
5. 高效排列插件
6. 减少内联脚本的数量
7. 使用现代CSS和合法标记
8. 给内容分块
9. 指定图像和表格大小
10. 选择合适的客户端

## Reference

[MDN Web 技术文档](https://developer.mozilla.org/zh-CN/docs/Web)

[HTML 开发者指南](https://developer.mozilla.org/zh-CN/docs/Web/Guide/HTML)
