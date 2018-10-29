# playerdemo
![Build Status](https://travis-ci.org/itisyang/playerdemo.svg?branch=master)

一个视频播放器，开源版 potplayer。

用于学习和交流音视频技术。

欢迎音视频开发爱好者前来交流相关问题。

## 简介
- 使用 FFmpeg 解码，SDL2 渲染，ffmpeg-3.4，SDL2-2.0.7。

- 在 Windows 下使用 VS2017 + Qt5.9.3 开发（X64）。

- 项目目录下的 .pro 文件，支持在多平台（Windows、Linux、Mac）下 QtCreator 打开编译调试。

![运行画面](https://raw.githubusercontent.com/itisyang/MyImages/master/playerdemo/0.png)

## 沟通
- Issues: 欢迎给我提 issues，关于本项目的问题，请优先提 issues，我会尽量当天回复。

## Windows平台编译调试

1. 下载 FFmpeg、SDL2 动态库，放在 bin 目录下。（注意统一静态库与动态库的版本、位数）。

2. 使用 QtCreator 打开 playerdemo.pro。

3. 编译运行。

## Linux平台编译调试

1. 安装 sdl2-dev。

2. 编译、安装 FFmpeg。（参考文档：https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu#RevertingChangesMadebyThisGuide）

3. 使用 QtCreator 打开 playerdemo.pro。

4. 编译运行。

## Mac平台编译调试
暂无环境


#### [开发问题记录](https://github.com/itisyang/playerdemo/blob/master/note.md)