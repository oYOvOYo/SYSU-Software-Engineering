# Data Encryption Standard (DES)
`jskyzero` `2017/10/02`

[![Build Status](https://travis-ci.org/jskyzero/DES.svg?branch=master)](https://travis-ci.org/jskyzero/DES)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/dwyl/esta/issues)

## Overview
> The Data Encryption Standard (DES) is a block cipher (a form of shared secret encryption) that was selected by the National Bureau of Standards as an official Federal Information Processing Standard (FIPS) for the United States in 1976 and which has subsequently enjoyed widespread use internationally. It is based on a symmetric-key algorithm that uses a 56-bit key.

This implementation wants to make the DES more readable and more structured, I refered some other's implementation like [github/tarequeh/DES](https://github.com/tarequeh/DES).

Padding scheme used in this implementation is [PKCS5]

If you can read Chinese, you can read the More Things part.

## Compilation & Installation

1. Please Make sure you have C Language environment, for example `gcc`and `make`
2. Compilation using:
    ```
    make
    ```
    Then you can find the `des` executable file in `./bin` folder.

## Usage
> I keep the same usage like tarequeh's DES implementation

Say we want to encrypt/ decrypt a file named /home/user/sample.txt

1. Generate a keyfile using:

   ```
   ./bin/des -g /tmp/keyfile.key
   ```

2. Encrypt sample.txt using:

   ```
   ./bin/des -e /tmp/keyfile.key /home/user/sample.txt /home/user/sample.enc
   ```

3. Decrypt sample.txt using:

   ```
   ./bin/des -d /tmp/keyfile.key /home/user/sample.enc /home/user/sample_decrypted.txt
   ```

Don't lose the key file! you won't be able to decrypt an encrypted if you lose the keyfile.


## More Things
+ 本项目将用C实现DES(一种对称密匙块加密算法)
+ 为什么有这个项目？
  + 实现过一次以后对原理的印象会更加深刻。
  + 实现的成品也可以拿来实际加密用。
+ 什么是DES？
  + DES是一种对称加密算法，指加密和解密使用相同的密匙。
  + DES是一种快加密算法，指将明文分区段，并对每一个区段用相同的演算法则和钥匙。
  + DES现在已经不被视为一种安全的加密算法，2001年被高级加密标准（AES）取代。
+ DES算法概要
  + DES 是一种典型的块加密方法:它以64位为分组长度,64位一组的明文作为算法的输入通过一系列复杂的操作,输出同样64位长度的密文。
  + DES 使用加密密钥定义变换过程。
  + DES 的采用64位密钥,但由于每8位中的最后1位用于奇偶校验,实际有效密钥长度为56位。密钥可以是任意的56位的数,且可随时改变。其中极少量的数被认为是弱密钥,但能容易地避开它们。所有的保密性依赖于密钥。
  + DES 算法的基本过程是换位和置换。（具体的操作将在下文模块部分提到）
+ 项目结构
  ```
  .
  ├── bin         // 执行文件
  ├── build       // 中间生成文件
  ├── docs        // 文档
  ├── include     // 头文件
  ├── LICENSE     // 证书
  ├── makefile    // 生成执行文件脚本
  ├── README.md   // 说明文件
  └── src         // 源代码
  ```
+ 模块分解
大致处理流程如图所示
![how to process](docs/process.png)


+ 数据结构
+ 类C语言算法算法过程

## Reference
+ [数据加密标准](https://zh.wikipedia.org/wiki/%E8%B3%87%E6%96%99%E5%8A%A0%E5%AF%86%E6%A8%99%E6%BA%96)
+ [github/tarequeh/DES](https://github.com/tarequeh/DES)