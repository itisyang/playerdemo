# playerdemo


[![GitHub issues](https://img.shields.io/github/issues/itisyang/playerdemo.svg)](https://github.com/itisyang/playerdemo/issues)
[![GitHub stars](https://img.shields.io/github/stars/itisyang/playerdemo.svg)](https://github.com/itisyang/playerdemo/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/itisyang/playerdemo.svg)](https://github.com/itisyang/playerdemo/network)
[![GitHub release](https://img.shields.io/github/release/itisyang/playerdemo.svg)](https://github.com/itisyang/playerdemo/releases)
![Build Status](https://github.com/itisyang/playerdemo/actions/workflows/windows.yml/badge.svg)
![Build Status](https://github.com/itisyang/playerdemo/actions/workflows/macos.yml/badge.svg)
![Build Status](https://github.com/itisyang/playerdemo/actions/workflows/ubuntu.yml/badge.svg)
![language](https://img.shields.io/badge/language-c++-DeepPink.svg)
[![GitHub license](https://img.shields.io/github/license/itisyang/playerdemo.svg)](https://github.com/itisyang/playerdemo/blob/master/LICENSE)

一个视频播放器，开源版 potplayer。  
用于学习和交流音视频技术。  
欢迎音视频开发爱好者交流相关问题。  
https://itisyang.github.io/playerdemo/

## 简介
- 使用 FFmpeg-3.4 (x64) 解码，SDL2-2.0.7 (x64) 渲染。  
- 在 Windows 下使用 Qt5.12.x (MinGW x64) 开发。  
- 项目目录下的 .pro 文件，支持在多平台（Windows、Linux、Mac）下 QtCreator 打开编译调试。  

![运行画面](https://raw.githubusercontent.com/itisyang/MyImages/master/playerdemo/0.jpg)

## 沟通
- Issues: 欢迎给我提 issues，关于本项目的问题，请优先提 issues，我会尽量当天回复。

## Windows平台编译调试
1. 下载 FFmpeg、SDL2 动态库，放在 bin 目录下。(直接从官网下载即可，亦可下载本项目最新release，安装后，从安装目录下拷贝动态库。)  
    FFmpeg 库下载地址 [https://ffmpeg.zeranoe.com/builds/](https://ffmpeg.zeranoe.com/builds/)  
    SDL2 库下载地址 [https://www.libsdl.org/download-2.0.php](https://www.libsdl.org/download-2.0.php)  
2. 使用 QtCreator 打开 playerdemo.pro。  
3. 编译运行。  

## Linux平台编译调试  
1. 安装 SDL2相关的开发包 libsdl2-dev。  
    ```
    sudo apt-get install libsdl2-dev
    ```
2. 安装 FFmpeg相关的开发包 libavformat-dev、libavutil-dev、libavcodec-dev、libswscale-dev...
    ```
    sudo apt-get install libavformat-dev
    sudo apt-get install libavutil-dev
    sudo apt-get install libavcodec-dev
    sudo apt-get install libswscale-dev
    ```
3. 使用 QtCreator 打开 playerdemo.pro。  
4. 编译运行。  

## Macos平台编译调试
1. 安装 FFmpeg相关的开发包。
    ```
    brew install ffmpeg
    ```
2. 使用 QtCreator 打开 playerdemo.pro。  
3. 修改 playerdemo.pro 配置 ffmpeg、SDL2 头文件和库目录。
    ```
    # 将下面的路径改为自己设备上的路径
    macx {
        INCLUDEPATH += /usr/local/Cellar/sdl2/2.24.1/include
        LIBS += -L/usr/local/Cellar/sdl2/2.24.1/lib -lSDL2
        INCLUDEPATH += /usr/local/Cellar/ffmpeg@5.1.1/5.1.1_1/include
        LIBS += -L/usr/local/Cellar/ffmpeg@5.1.1/5.1.1_1/lib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale
    }
    ```
    *通过 brew info ffmpeg 查询 ffmpeg 安装目录*  
    *ffmpeg 安装时会自动安装SDL2依赖，通过 brew info SDL2 查询 SDL2 安装目录*  

4. 编译运行。  

## 其他

    编译时，注意统一静态库与动态库的版本、位数。若开发环境为64位，库及头文件均要64位。
