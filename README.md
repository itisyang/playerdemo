# playerdemo
![Build Status](https://travis-ci.org/itisyang/playerdemo.svg?branch=master)

一个视频播放器，开源版potplayer

## 简介
- 使用FFmpeg解码，SDL2渲染
- 在Windows下使用VS2017和Qt5.9.3开发(X64)
- 项目目录下的.pro文件，支持在Windows和Linux下打开编译

![运行画面](https://raw.githubusercontent.com/itisyang/MyImages/master/playerdemo/0.png)



## 使用
- 工程中包含.sln和.pro文件,其中.sln用于Windows环境,.pro用于Linux环境
- 若要编译工程代码，在Windows下除了安装VS+Qt，还需要下载FFmpeg和SDL2的动态库(64bit)，将这些动态库文件放在.\bin目录下面
- 若运行不了，可以将lib目录下的*.lib换成和bin目录下dll一致的版本

## 沟通
- 邮件: itisyang@gmail.com

## 错误记录
- ~~20180210 Travis CI编译错误，因为FFmpeg版本低，不支持有的借口。待解决~~
- ~~20180212 在CI中使用git下载FFmpeg源码编译，会导致rake错误。待解决~~

