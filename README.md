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
- `./Release/`下为可执行`demo`文件
- `./NetworkLibrary/`下为第三阶段提供的网络库