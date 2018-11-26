# playerdemo


[![GitHub issues](https://img.shields.io/github/issues/itisyang/playerdemo.svg)](https://github.com/itisyang/playerdemo/issues)
[![GitHub stars](https://img.shields.io/github/stars/itisyang/playerdemo.svg)](https://github.com/itisyang/playerdemo/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/itisyang/playerdemo.svg)](https://github.com/itisyang/playerdemo/network)
[![GitHub release](https://img.shields.io/github/release/itisyang/playerdemo.svg)](https://github.com/itisyang/playerdemo/releases)
![Build Status](https://travis-ci.org/itisyang/playerdemo.svg?branch=master)
![language](https://img.shields.io/badge/language-c++-DeepPink.svg)
[![GitHub license](https://img.shields.io/github/license/itisyang/playerdemo.svg)](https://github.com/itisyang/playerdemo/blob/master/LICENSE)

一个视频播放器，开源版 potplayer。  
用于学习和交流音视频技术。  
欢迎音视频开发爱好者前来交流相关问题。  
https://itisyang.github.io/playerdemo/

## 简介
- 使用 FFmpeg 解码，SDL2 渲染，ffmpeg-3.4（X64），SDL2-2.0.7（X64）。  
- 在 Windows 下使用 VS2017 + Qt5.9.x 开发（X64）。  
- 项目目录下的 .pro 文件，支持在多平台（Windows、Linux、Mac）下 QtCreator 打开编译调试。  

![运行画面](https://raw.githubusercontent.com/itisyang/MyImages/master/playerdemo/0.png)

## 沟通
- Issues: 欢迎给我提 issues，关于本项目的问题，请优先提 issues，我会尽量当天回复。

## Windows平台编译调试
1. 下载 FFmpeg、SDL2 动态库，放在 bin 目录下。  
2. 使用 VS2017 打开 playerdemo.sln。（Windows 推荐使用 VS2017 编译，调试功能相对强大一些。亦可选用 QtCreator 打开 playerdemo.pro）  
3. 编译运行。  

## Linux平台编译调试
1. 安装 sdl2-dev。  
2. 编译、安装 FFmpeg。（参考文档：https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu#RevertingChangesMadebyThisGuide）  
3. 使用 QtCreator 打开 playerdemo.pro。  
4. 编译运行。  

## Mac平台编译调试

暂无环境

## 其他

编译时，注意统一静态库与动态库的版本、位数。若开发环境为32位，库及头文件均要32位。


#### [开发问题记录](https://github.com/itisyang/playerdemo/blob/master/note.md)