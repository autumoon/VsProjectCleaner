# VsProjectCleaner

> 一个轻量级的 Visual Studio 工程清理工具，同时支持 **C#** 和 **C++** 项目。

[![Platform](https://img.shields.io/badge/platform-Windows-blue)]()
[![Language](https://img.shields.io/badge/language-C%2B%2B%20%2F%20MFC-red)]()
[![Toolset](https://img.shields.io/badge/toolset-v140%20%2F%20VS2015-purple)]()
[![License](https://img.shields.io/badge/license-MIT-green)]()

VsProjectCleaner 用于**快速清理 Visual Studio 工程产生的临时目录和文件**，
释放磁盘空间、加速备份、保持工作区干净。

它不同于一般的"按目录名删除"工具——**它会先识别工程类型，再针对性清理**，
避免误删 C++ 工程里名为 `bin` 的第三方库目录，也不会漏删 C# 项目的 `publish` 输出。

---

## ✨ 特性

- 🎯 **按工程类型精准清理**：识别 `.csproj` / `.vcxproj`，分别处理 C# 和 C++ 的特有产物
- 🖱️ **拖入即清理**：把工程根目录拖入窗口，立即开始清理
- 📋 **列表管理**：支持多个工程目录，可手动添加 / 删除 / 清空
- 🔁 **配置持久化**：目录列表、窗口尺寸自动保存，下次启动自动恢复并清理
- 📜 **实时日志栏**：每一步扫描 / 删除 / 完成都实时输出，可滚动查看
- 🗑️ **回收站优先**：默认删除到回收站（可切换为永久删除），误删可恢复
- 📦 **单文件零依赖**：静态链接 MFC + CRT，只需一个 EXE，无需安装任何运行时
- 🖥️ **x64 原生**：仅一个二进制，覆盖所有 64 位 Windows

---

## 📋 清理规则

### 工程识别

拖入的根目录下**递归查找**以下任一文件，视为有效工程根：

| 文件 | 说明 |
|---|---|
| `*.sln` | Visual Studio 解决方案 |
| `*.csproj` | C# 项目 |
| `*.vcxproj` | C++ 项目 |

不含以上任一文件的目录会被跳过，不做任何删除。

### 按工程类型针对性清理（工程根的直接子目录）

| 工程类型 | 删除目录 |
|---|---|
| C#（含 `.csproj`） | `bin/`、`publish/` |
| C++（含 `.vcxproj`） | `ipch/`、`x64/` |

> **为什么这样设计？**
> C++ 工程里的 `bin/` 常常存放着第三方预编译库（如 Qt、OpenCV 的 DLL），
> 一刀切删除会造成严重损失。因此 `bin/`、`publish/` **只在确认是 C# 工程根时才删**。

### 通用规则（全树递归，不分工程类型）

**目录名命中即删**：

```
.vs  obj  Debug  Release
TestResults  MigrationBackup
.vscode  .idea
```

**文件后缀命中即删**：

```
.aps  .dep  .exp  .idb  .ilk  .ipch  .manifest
.ncb  .obj  .pch  .pdb  .pd_Thumbs.db
.sdf  .suo  .scc  .user
.binlog  .coverage  .trx  .VC.db
```

### 兜底规则

拖入根目录第一层的 `ipch/`、`x64/` 会被无条件删除（防止工程根未识别到 `.vcxproj` 时漏删）。

### 空目录清理

清理完成后，全树递归删除**变空**的目录。

---

## 🚀 使用方式

### 1. 拖入即清理（推荐）

1. 启动 `VsProjectCleaner.exe`
2. 把一个或多个工程根目录从资源管理器拖到窗口的列表区域
3. 立即开始清理，日志栏实时输出每一步操作

### 2. 手动管理列表

- 点击 **「添加目录」** 手动选择工程根目录
- 点击 **「删除目录」** 移除选中的条目
- 点击 **「清空」** 移除所有条目
- 点击 **「确定」** 清理整个列表（适用于：清理后又生成了新的产物，需要再清一遍）

### 3. 启动自动清理

程序关闭时会把当前列表写入同目录的 `VsProjectCleaner.ini`，
下次启动时会自动恢复列表并**立即清理**。

> 如果不希望启动自动清理，删除 INI 里的 `INI_SRC_DIRS` 行即可。

### 删除方式

- **默认**：删除到回收站（可恢复）
- **永久删除**：勾选界面上的相应选项（谨慎使用，不可恢复）

---

## ⚙️ 配置文件

程序在同目录下查找/生成 `VsProjectCleaner.ini`，格式为 INI，UTF-8 with BOM：

```ini
[INI_PRESUFFIX]
INI_REMPATH = true
INI_REALDEL = false
INI_SRC_DIRS = E:\Path\To\Project
INI_ROOT_DIRS = ipch|x64
INI_ALL_DIRS = .vs|obj|Debug|Release|TestResults|MigrationBackup|.vscode|.idea
INI_FILE_SUFFIXS = .aps|.dep|.exp|...|.VC.db
INI_WIN_WIDTH = 624
INI_WIN_HEIGHT = 441
```

| 键 | 说明 |
|---|---|
| `INI_REMPATH` | 是否记住上次的目录列表 |
| `INI_REALDEL` | 是否永久删除（`false` = 删除到回收站） |
| `INI_SRC_DIRS` | 上次的目录列表，`\|` 分隔 |
| `INI_ROOT_DIRS` | 工程根下直接删除的目录名，`\|` 分隔 |
| `INI_ALL_DIRS` | 全树递归删除的目录名，`\|` 分隔 |
| `INI_FILE_SUFFIXS` | 全树递归删除的文件后缀，`\|` 分隔 |
| `INI_WIN_WIDTH` / `INI_WIN_HEIGHT` | 上次窗口尺寸 |

> **自定义规则**：直接编辑 INI 文件即可，程序启动时读取。
> 例如想保留 `.vscode` 目录，把 `INI_ALL_DIRS` 里的 `.vscode` 删掉即可。

---

## 🔨 编译

### 环境要求

- Visual Studio 2015 或更高版本（Toolset v140 及以上）
- Windows SDK 8.1 及以上
- MFC 组件（VS 安装时勾选）

### 编译步骤

1. 用 VS 打开 `VsProjectCleaner.sln`
2. 配置切到 `Release | x64`
3. 生成解决方案

或者命令行：

```powershell
msbuild DllTestor\DllTestor.vcxproj /p:Configuration=Release /p:Platform=x64 /m
```

产物：`x64\Release\VsProjectCleaner.exe`

> **仅支持 x64**：项目未配置 Win32 的 include 路径（历史遗留），如需 x86 请自行补全 `AdditionalIncludeDirectories`。

### 依赖

源码依赖 `..\..\Common\often\` 下的公共库（`GetDirFiles`、`StdStrFile`、`SimpleIni`、`MfcStrFile` 等）。

- 如果你在自己环境编译，请确保该路径存在，或修改 `DllTestor.vcxproj` 里的 `AdditionalIncludeDirectories`
- 如果你是从本仓库首次编译并缺少 `Common\often`，请提交 Issue

---

## 🖼️ 界面预览

> TODO: 上传一张主界面截图到 `docs/screenshot.png`，然后把下面这行的注释去掉。

<!-- ![screenshot](docs/screenshot.png) -->

界面从上到下：

1. **顶部按钮**：添加目录 / 删除目录 / 清空
2. **中间列表**：待处理的工程根目录，支持拖拽添加
3. **底部日志**：实时输出清理过程
4. **底部按钮**：确定 / 取消

---

## 📌 注意事项

- ⚠️ **删除后不可恢复**：勾选"永久删除"后请务必确认列表内容正确
- ⚠️ **`.vscode` / `.idea` 会被删除**：若你在工程根下自定义了调试配置，请先备份或从 `INI_ALL_DIRS` 中移除
- ⚠️ **建议先跑一次「删除到回收站」模式**，确认清理列表符合预期后再切换永久删除
- ✅ 支持网络路径和长路径（>260 字符）
- ✅ 支持多盘符、混合解决方案（同时含 C# 和 C++ 项目）

---

## 🤝 贡献

欢迎提交 Issue 和 Pull Request。

- **报告 Bug**：请附上程序版本、Windows 版本、复现步骤
- **提交规则**：请说明你要处理的工程类型和对应的临时产物路径

---

## 📄 许可证

[MIT License](LICENSE)

---

## 🙏 致谢

- `SimpleIni` — [brofield/simpleini](https://github.com/brofield/simpleini)
- `EasySize` — 对话框自适应布局
- 以及其他在 `Common\often` 下的自研工具库

---

## 📊 项目状态

- ✅ C# 工程清理（`.csproj`）
- ✅ C++ 工程清理（`.vcxproj`）
- ✅ 混合解决方案
- ✅ 拖入即清理
- ✅ 日志栏实时输出
- ⬜ 深色主题（未计划）
- ⬜ 命令行模式（未计划）