# playerdemo
![Build Status](https://travis-ci.org/itisyang/playerdemo.svg?branch=master)

一个视频播放器，开源版 potplayer ，用于学习和交流

## 简介
- 使用 FFmpeg 解码，SDL2 渲染，ffmpeg-3.4，SDL2-2.0.7
- 在 Windows 下使用 VS2017 和 Qt5.9.3 开发（X64）
- 项目目录下的 .pro 文件，支持在 Windows 和 Linux 下打开编译

![运行画面](https://raw.githubusercontent.com/itisyang/MyImages/master/playerdemo/0.png)



## 使用
- 工程中包含 .sln 和 .pro 文件,其中 .sln 用于 Windows 环境，.pro 用于 Linux 环境
- 若要编译工程代码，在 Windows 下除了安装 VS+Qt，还需要下载 FFmpeg 和 SDL2 的动态库（64bit），将这些动态库文件放在.\bin目录下面
- 若运行不了，可以将lib目录下的*.lib换成和bin目录下dll一致的版本
- 亦可以选择下载release下面的安装包，安装后，将安装目录下的文件拷贝到bin目录下，依赖库肯定是全的

## 沟通
- 邮件: itisyang@gmail.com，一起探讨音视频相关技术
- Issues: 欢迎给我提 Issues 

## [开发日志记录](https://github.com/itisyang/playerdemo/blob/master/note.md)

