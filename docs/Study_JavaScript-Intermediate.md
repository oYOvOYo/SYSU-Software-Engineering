---
layout:     post
title:      "JavaScript-Intermediate"
date:       2017-02-10
updated:     2017/02/28
tags:
    - Web
    - JavaScript
categories:
    - Study
---

JavaScript-Intermediate的相关知识

# Intermediate JavaScript

[TOC]

## Hoisting

IIFE : Imediately-Invoked Function Expression



## Everything in JS is an object

```javascript
member.name || "unkonwn"
member.address && member.address.state // undefined
```



## Kinds of function invoking

1. 普通函数
2. 方法( method )调用
3. 构造子
4. 应用( apply, call )调用



## Closure

= =

## Prototype

```javascript
console.log("\n\nFor Object")
console.log("Object            :" , Object)
console.log("Object.constructor:" , Object.constructor)
console.log("Object.prototype  :" , Object.prototype)
console.log("Object.__proto__  :" , Object.__proto__)

console.log("Object.prototype.constructor  :" , Object.prototype.constructor)
console.log("typeof Object.prototype       :" , typeof Object.prototype)
console.log("Object.prototype.__proto__    :" , Object.prototype.__proto__)

console.log("\n\n")
console.log("For Function")
console.log("Function            :" , Function)
console.log("Function.constructor:" , Function.constructor)
console.log("Function.prototype  :" , Function.prototype)
console.log("Function.__proto__  :" , Function.__proto__)

console.log("Function.prototype.constructor  :" , Function.prototype.constructor)
console.log("typeof Function.prototype       :" , typeof Function.prototype)
console.log("Function.prototype.__proto__    :" , Function.prototype.__proto__)

var Foo = function () { this.data = "Foo" }

var f1 = new Foo

console.log("\n\n")
console.log("For Foo")
console.log("Foo            :" , Foo)
console.log("Foo.constructor:" , Foo.constructor)
console.log("Foo.prototype  :" , Foo.prototype)
console.log("Foo.__proto__  :" , Foo.__proto__)

console.log("Foo.prototype.constructor  :" , Foo.prototype.constructor)
console.log("typeof Foo.prototype       :" , typeof Foo.prototype)
console.log("Foo.prototype.__proto__    :" , Foo.prototype.__proto__)

console.log("\n\n")
console.log("For f1")
console.log("f1            :" , f1)
console.log("f1.constructor:" , f1.constructor)
console.log("f1.prototype  :" , f1.prototype)
console.log("f1.__proto__  :" , f1.__proto__)

console.log("f1.__proto__.constructor  :" , f1.__proto__.constructor)
console.log("typeof f1.__proto__       :" , typeof f1.__proto__)
console.log("f1.__proto__.__proto__    :" , f1.__proto__.__proto__)
```



