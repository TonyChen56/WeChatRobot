# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**WeChatRobot** is a PC WeChat automation tool consisting of two components:

1. **WeChatRobot.exe** - MFC-based GUI client application that provides the user interface
2. **WeChatHelper.dll** - DLL injected into WeChat process to hook WeChat functions and perform operations

The project uses **WM_COPYDATA** for inter-process communication between the client and the injected DLL.

⚠️ **Important Notice**: This project is a legacy WeChat hooking tool and has not been maintained for a long time. It is provided for learning purposes only and targets a specific old version of WeChat (2.6.8.52).

## Build System

### Requirements

- **Visual Studio 2017** (VS 141 toolset) with C++ desktop development workload
- Windows SDK version 10.0.17763.0
- MFC (statically linked in Win32, dynamically linked in x64)
- OpenSSL 1.0.2l-win32-msvc100 (for WeChatRobot Debug Win32 build)

### Build Configurations

The solution supports two platforms and two configurations:

**Platforms:**
- Win32 (x86)
- x64

**Configurations:**
- Debug
- Release

### Build Commands

Open `WeChatRobot.sln` in Visual Studio 2017 and build using:

```bash
# Build entire solution
msbuild WeChatRobot.sln /p:Configuration=Release /p:Platform=x64

# Build specific project
msbuild WeChatRobot\WeChatRobot.vcxproj /p:Configuration=Release /p:Platform=x64
msbuild WeChatHelper\WeChatHelper.vcxproj /p:Configuration=Release /p:Platform=x64

# Clean build
msbuild WeChatRobot.sln /t:Clean /p:Configuration=Release
```

**Build Outputs:**
- `WeChatRobot.exe` → Release/
- `WeChatHelper.dll` → Release/

## Architecture

### Project Structure

```
WeChatRobot/
├── WeChatRobot/              # MFC GUI Client Application
│   ├── *.cpp/*.h            # Dialog implementations for each feature
│   ├── data.h               # Client-side data structures
│   ├── message.h            # Message definitions
│   ├── WeChatRobot.vcxproj  # Client project file
│   └── WeChatRobot.rc       # MFC resource file
│
├── WeChatHelper/            # DLL Injected into WeChat
│   ├── *.cpp/*.h            # Hook implementations
│   ├── data.h               # Server-side data structures
│   ├── offset.h             # WeChat function offsets/addresses
│   ├── message.h            # Message structures
│   └── WeChatHelper.vcxproj # DLL project file
│
├── assets/                  # Documentation images
├── Release/                 # Build outputs
└── WeChatRobot.sln          # Visual Studio solution
```

### Component Communication

**WeChatRobot (Client):**
- MFC dialog-based application
- Provides GUI for all operations
- Sends commands to WeChatHelper via WM_COPYDATA
- Receives data back from WeChatHelper
- Handles user interactions and displays results

**WeChatHelper (Server/DLL):**
- Injected into WeChat process via `CInjectTools`
- Hooks WeChat functions using addresses defined in `offset.h`
- Intercepts messages, handles, and operations
- Communicates back to WeChatRobot via WM_COPYDATA

### Key Data Structures

**Communication Structures** (defined in both `data.h` files):
- `MessageStruct` - Generic communication messages
- `ChatMessageData` - Chat message data (type, source, sender, content)
- `PersonalInformation` - WeChat user profile information
- `UserInfo` / `UserInfoDetail` - Friend/group member information
- `XmlCardMessage` - WeChat card messages
- `AtMsg` - @ message in groups
- `SendXmlArticleStruct` - XML article messages

**Message Types** are handled via the message structures in `message.h`.

### Core Offset Addresses

The `WeChatHelper/offset.h` file contains hardcoded offsets for WeChat 2.6.8.52:

- Function hooks: `WxSendMessage`, `WxReciveMessage`, `WxFriendList`, etc.
- Data offsets: `MsgContentOffset`, `MsgSourceOffset`, `WxidOffset`, etc.
- Self info base: `WxSelfInfoBase` with various member offsets

⚠️ These offsets are version-specific and will not work with newer WeChat versions.

## Development Workflow

### Adding New Features

1. **In WeChatRobot (Client):**
   - Create new dialog class (e.g., `CNewFeature.cpp/h`)
   - Add to resource file (`WeChatRobot.rc`)
   - Implement UI and command handling
   - Send WM_COPYDATA messages to WeChatHelper

2. **In WeChatHelper (Server):**
   - Implement hook/operation logic
   - Handle WM_COPYDATA messages
   - Use offsets from `offset.h` for hooking

### Inter-Process Communication

**Sending from WeChatRobot:**
```cpp
COPYDATASTRUCT cds;
cds.dwData = COMMAND_TYPE;
cds.cbData = sizeof(DataStruct);
cds.lpData = &dataStruct;

// Send to WeChatHelper window
::SendMessage(helperWindowHWND, WM_COPYDATA, (WPARAM)this->m_hWnd, (LPARAM)&cds);
```

**Receiving in WeChatHelper:**
```cpp
BOOL CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_COPYDATA)
    {
        COPYDATASTRUCT* pCopyData = (COPYDATASTRUCT*)lParam;
        // Process command based on pCopyData->dwData
    }
}
```

### Testing

1. Start WeChat (version 2.6.8.52)
2. Copy `WeChatRobot.exe` and `WeChatHelper.dll` to same directory
3. Run `WeChatRobot.exe`
4. Click "注入" to inject DLL into WeChat process
5. Test features through the GUI

## Technical Notes

### Dependency Injection

The `CInjectTools` class handles DLL injection into WeChat process. It locates the WeChat window and uses Windows API to inject `WeChatHelper.dll`.

### Hooking Mechanism

WeChatHelper uses function hooking to intercept WeChat operations:
- Calculates actual function addresses using base address + offset
- Hooks functions by replacing prologue with jump instructions
- Intercepts messages before they're processed by WeChat

### Message Handling

All chat messages are intercepted and parsed. The system extracts:
- Message type (text, image, file, etc.)
- Sender information
- Message content
- Source (group or individual chat)

### Known Limitations

- **Version锁定**: Only works with WeChat 2.6.8.52
- **Architecture依赖**: Uses hardcoded offsets that change between versions
- **稳定性**: 多年未维护，可能存在兼容性问题
- **仅供学习**: 不应用于生产环境或商业用途

## Security Considerations

⚠️ **Warning**: This project involves:
- DLL injection into another process
- Function hooking and code interception
- Reverse engineering of proprietary software

Use only for educational purposes in controlled environments. Do not use for:
- Violating WeChat's terms of service
- Unauthorized automation or spam
- Commercial applications
- Any illegal activities

## Documentation and Resources

- **README.md** - Project overview and feature list with screenshots
- **assets/** - Screenshots and documentation images
- **CSDN Blog Posts** (referenced in README):
  - PC微信逆向：HOOK拦截二维码
  - PC微信逆向：发送与接收消息分析
  - PC微信逆向：数据库文件解密

## Common Tasks

### Building for Production

Use Release configuration with static MFC linking for standalone executables:
- Win32 Release: Static MFC linking
- x64 Release: Dynamic MFC linking with Whole Program Optimization

### Debugging

Use Debug configuration to troubleshoot issues:
- Debug information enabled
- Runtime checks enabled
- Multi-threaded debug runtime library

### Adding New Message Types

1. Define struct in both `WeChatRobot/data.h` and `WeChatHelper/data.h`
2. Add to `MessageUnion` in WeChatHelper's data.h
3. Implement handler in both projects
4. Update WM_COPYDATA command types

### Modifying Offsets

When WeChat updates, new offsets must be found using:
- Debugger (x64dbg/OllyDbg)
- Disassembler (IDA Pro)
- Memory scanning tools

Process:
1. Attach debugger to WeChat
2. Locate target function
3. Find data structure offsets
4. Update `offset.h`
5. Rebuild and test

## Legal and Ethical Use

**This project is provided "as is" for educational purposes only.**

- Use only on your own systems
- Do not violate WeChat's terms of service
- Respect user privacy and data protection laws
- Do not use for spam, harassment, or illegal activities
- Authors disclaim all liability for misuse

The author explicitly states this project is not maintained and should be used for learning about Windows programming, MFC, and reverse engineering techniques only.
