# 小狗远程控制开放车辆

[![License](https://img.shields.io/badge/License-Apache--2.0-blue.svg)](LICENSE)

这是“小狗远程控制”的**公开接入SDK和搭建代码教学**。它用于帮助车辆开发者理解如何把自己的车辆能力接入开放平台。开发者可以自行搭建相关平台或网络环境。

## 开源边界

本仓库开源：

- 公开命令与遥测的数据结构；
- 第三方车辆适配器接口；
- HMAC 请求签名示例；
- 简化的远程控制映射示例；
- 夜间自动开启大灯的通用思路。

本仓库**不包含**：

- 小狗远程控制服务器端源码和数据库；
- 管理后台、计费、风控和审核实现；
- 环境密钥、用户数据或车辆会话数据；
- proof、授权、动力控制或防破解实现；
- 可直接控制任意 OMSI 车辆的万能脚本。

公开 SDK 与闭源平台服务通过版本化开放接口通信。


## 示例

- `examples/cpp/vehicle_adapter_example.cpp`：命令白名单、安全检查和抽象车辆接口。
- `examples/cpp/auto_headlights_example.cpp`：按游戏时间或环境亮度请求开启大灯。
- `examples/python/signed_request_example.py`：从环境变量读取凭据并生成 HMAC-SHA256 请求签名。
- `examples/python/local_command_demo.py`：不联网的本地命令演示。

示例仅用于说明思路，不包含任何官方车辆内部实现。

## 安全规则

- 最终用户安装包不应长期内置开发者主密钥。
- 车辆端必须对命令做白名单、安全状态和重复执行检查。
- 行驶中开门、动力、制动等高风险操作应在车辆端拒绝。
- 不得使用本 SDK 绕过车辆付费、激活、授权或技术保护措施。
- 接入第三方车辆前，应确认拥有相应修改和分发授权。

## 构建 C++ 示例

```bash
cmake -S . -B build
cmake --build build
```

## 许可证

代码采用 [Apache License 2.0](LICENSE)。你可以使用、修改和分发代码，但必须遵守许可证中的版权、NOTICE、专利及免责声明要求。

Apache-2.0 不授予“小狗远程控制”名称、Logo 或官方认证标识的商标使用权。第三方修改版本不得冒充官方版本。

## 安全问题

请不要在公开 Issue 中提交真实密钥或未公开漏洞。参见 [SECURITY.md](SECURITY.md)。
