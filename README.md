<div align="center">

# 🧩 ICPC Practice

**C++ 基础练习 · ICPC 学习记录**

<sub>C++17 · 独立编译 · MIT License</sub>

[练习索引](#练习索引) · [快速开始](#快速开始) · [目录结构](#目录结构) · [许可](#许可)

</div>

## 关于这个仓库

自用的 ICPC 练习仓库。目前收录 10 个独立 C++ 源文件：`basic/` 7 个，`luogu/` 3 个，覆盖基础输出、变量、赋值、排序去重、二分与字符串练习。其中 `luogu/P1308.cpp` 仍是未完成的学习草稿。

每个 `.cpp` 文件都有独立的 `main()`，应单独编译。源码保留当前文件名：基础练习位于 `basic/`，按平台编号保存的练习位于 `luogu/`。文件存在不表示已通过在线评测。

复习时可阅读 [分类习题总目录](docs/exercises/README.md)：目前已有 EX0001–EX0005 五份独立题目页，附稳定编号、折叠答案、易错点与拓展练习；其余源码先在下表登记，尚未补齐独立题目页。

刚开始接触标准库，可阅读 [STD.md：C++ 标准库入门](STD.md)，从 `vector`、排序、去重和整行输入学起；现已包含[字符串与引用](STD.md#char-reference)、[二分查找与边界速查](STD.md#binary-search)、[C 文件操作](STD.md#c-file-io)及[二进制读写](STD.md#c-binary-file-io)。C 文件操作示例单独按 C11 编译，其他完整示例按 C++17 使用。

## 练习索引

### 固定数据基础练习

| 文件 | 练习内容 | 当前输出 |
| :--- | :--- | :--- |
| [`hello_icpc.cpp`](basic/hello_icpc.cpp) | 第一个程序与文本输出 | `Hello ICPC` |
| [`print_age.cpp`](basic/print_age.cpp) | 整型变量 | `18` |
| [`print_adjacent_integers.cpp`](basic/print_adjacent_integers.cpp) | 连续输出两个整数 | `1020` |
| [`print_price.cpp`](basic/print_price.cpp) | 浮点数变量 | `9.9` |
| [`compound_assignment.cpp`](basic/compound_assignment.cpp) | 复合赋值与连续赋值 | 4 组变量结果，见下方 |

<details>
<summary><strong>查看 compound_assignment.cpp 的输出</strong></summary>

```text
i=63,j=8
i=3,j=2,k=1
i=2,j=-1,k=3
i=0,j=0,k=0
```

</details>

### 输入型练习与学习草稿

下表依据当前源码描述行为，不补造原题条件或评测通过状态。

| 文件 | 当前内容 | 输入 / 状态说明 |
| :--- | :--- | :--- |
| [`basic/erfen.cpp`](basic/erfen.cpp) | 在固定升序数组 `1, 3, 5, 7, 9, 12, 15` 中二分查找 | 输入目标整数；找到输出从 0 开始的下标，否则输出 `-1` |
| [`basic/quchongpaixu.cpp`](basic/quchongpaixu.cpp) | 用 `set` 去重排序，读取第 k 个不同值 | 输入 `n k` 和 n 个整数；k 超出不同值个数时输出 `NO`；当前未检查非正 k 等非法输入 |
| [`luogu/P1059.cpp`](luogu/P1059.cpp) | 去重排序 | 输入数量和整数；输出不同值个数，再升序输出各值 |
| [`luogu/P1177.cpp`](luogu/P1177.cpp) | `sort` 升序排序 | 输入数量和整数；保留重复值后输出 |
| [`luogu/P1308.cpp`](luogu/P1308.cpp) | 目标词与整行文本转小写 | 未完成：目前没有统计次数、首次位置或结果输出；不可作为完整题解提交 |

这些新增源码使用 `bits/stdc++.h`，依赖提供该头文件的 GNU C++ 工具链；仅支持 C++17 的编译器不一定提供它。输入范围、边界与格式仍需按原题自行验证。

## 快速开始

准备支持 C++17 的 C++ 编译器。以下命令以 `g++` 为例，在仓库根目录执行。

### Linux / macOS

```bash
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Wpedantic basic/hello_icpc.cpp -o build/hello_icpc
./build/hello_icpc
```

### Windows PowerShell

先确认已安装支持 C++17 的 `g++`，并且命令行能够找到它。

```powershell
New-Item -ItemType Directory -Force build | Out-Null
g++ -std=c++17 -Wall -Wextra -Wpedantic basic/hello_icpc.cpp -o build/hello_icpc.exe
.\build\hello_icpc.exe
```

运行结果：

```text
Hello ICPC
```

练习其他文件时，替换命令中的源文件路径和输出文件名即可。请逐个编译，不要将多个 `.cpp`（包括 `basic/` 与 `luogu/`）一起链接为同一个程序，否则会出现多个 `main()` 的链接错误。

## 目录结构

```text
icpctest/
├── basic/                  # 每个文件都是独立练习
│   ├── hello_icpc.cpp
│   ├── print_age.cpp
│   ├── print_adjacent_integers.cpp
│   ├── print_price.cpp
│   ├── compound_assignment.cpp
│   ├── erfen.cpp
│   └── quchongpaixu.cpp
├── luogu/                  # 平台编号练习；P1308 仍未完成
│   ├── P1059.cpp
│   ├── P1177.cpp
│   └── P1308.cpp
├── docs/exercises/         # 分类目录、独立题目与新增题目模板
├── STD.md                  # 标准库入门、完整示例与常见易错点
├── .github/                # 现有协作配置与说明
├── .gitignore              # 编译产物、缓存及编辑器文件忽略规则
├── LICENSE                 # MIT 许可
└── README.md
```

建议把编译结果放在 `build/` 或 `bin/` 中。这两个目录及常见的可执行文件、目标文件、库文件和编译缓存均已加入忽略规则，源码保留在 `basic/` 和 `luogu/` 中。

## 许可

本仓库采用 [MIT License](LICENSE)，版权署名为 Maximora-byte。

