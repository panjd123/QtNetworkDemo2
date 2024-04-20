# QtNetworkDemo
This is a network demo for this [project](https://github.com/panjd123/Surakarta).

## 使用说明

1. 服务端，设置端口后`Listen Port`开始监听
2. 服务端`Restart`后可重启服务端，重复步骤`1`
3. 客户端，`ip`地址默认为本地回环地址，设置`ip`与端口后`Connect`连接到服务端，成功连接后`ip`一行出现`Connected`并发送`READY_OP`
4. 客户端连接成功后，在`Send`左侧输入信息，`Send`即可将信息以`CHAT_OP`形式发送至服务端，并转发至另一连接的客户端（如果有）
5. 客户端收到信息呈现在`Receive`左侧
6. 客户端`Disconnect`后断开与服务端连接，重复步骤`3`
7. 端口取值为`[1,65535]`内的整数

## 文件说明

- `./ServerDemo/src/`下为服务端`demo`源码
- `./ClientDemo/src/`下为客户端`demo`源码
- 项目均为`CMake`构建
- `./NetworkLibrary/`下为第三阶段提供的网络库

## 编译指南
在`Windows 11`环境下，本项目可通过三种方式编译

- 使用`Qt Creator`打开`ClientDemo/src`与`ServerDemo/src`下的`CMakeLists.txt`文件，直接构建即可。

- 使用`vscode`编译，参考主仓库中的[教程](https://github.com/panjd123/Surakarta/blob/main/guidance/cmake/Vscode%20%2B%20CMake%20%2B%20Qt.md)。

- 命令行编译，需要将请将库`Qt6`添加至`环境变量-系统变量-Path` `F:\Qt6\6.6.1\mingw_64\bin` `F:\Qt6\6.6.1\mingw_64\lib` 替换成你的 Qt6 绝对路径
    编译并运行`ClientDemo`的步骤如下：
    ```
    // powershell
    > cd ClientDemo
    > mkdir build
    > cd build
    > cmake -G Ninja ../src -DCMAKE_CXX_COMPILER:FILEPATH=F:\\Qt6\\Tools\\mingw1120_64\\bin\\g++.exe  // 请替换成你的 Qt6 自带编译器的绝对路径
    > ninja
    > ./bin/ClientDemo
    ```
    编译并运行`ServerDemo`的步骤如下：
    ```
    // powershell
    > cd ServerDemo
    > mkdir build
    > cd build
    > cmake -G Ninja ../src -DCMAKE_CXX_COMPILER:FILEPATH=F:\\Qt6\\Tools\\mingw1120_64\\bin\\g++.exe  // 请替换成你的 Qt6 自带编译器的绝对路径
    > ninja
    > ./bin/ServerDemo
    ```

## Q&A

### Q：什么是`Ninja`？
`Ninja`是`CMake`的一个生成器，可以通过`-G Ninja`参数生成`Ninja`构建文件。由于`Windows`没有`make`，`Ninja`是一个很好的替代品。 [Ninja官方文档](https://ninja-build.org/)

### Q：我可以使用其他生成器吗？
当然可以，`Visual Studio`、`MinGW`、`MSYS2`等都是可以的，只是`Ninja`更快更轻量。

例如，你可以使用命令`cmake -G "MinGW Makefiles" ../src`生成`MinGW`构建文件。

### Q：如何安装`Ninja`？
可以参考[这篇博客](https://nirvana1997.github.io/Ninja%E5%AE%89%E8%A3%85%E4%B8%8E%E4%BD%BF%E7%94%A8/)，安装非常便捷，这也是为什么推荐使用`Ninja`。