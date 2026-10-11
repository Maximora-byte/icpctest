<div align="center">

# 🧩 ICPC Practice

**C++ 基础练习 · ICPC 学习记录**

<sub>C++17 · 独立编译 · MIT License</sub>

[练习索引](#练习索引) · [快速开始](#快速开始) · [目录结构](#目录结构) · [许可](#许可)

</div>

## 关于这个仓库

自用的 ICPC 练习仓库。目前收录 5 个 C++ 基础程序，内容包括输出、变量、浮点数和复合赋值。

每个 `.cpp` 文件都有独立的 `main()`，可以单独编译运行。源码使用描述练习内容的英文文件名，统一保留在 `basic/` 中。

复习时可阅读 [分类习题总目录](docs/exercises/README.md)：按知识点进入独立题目页，附稳定编号、折叠答案、易错点与拓展练习。

## 练习索引

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

练习其他文件时，替换命令中的源文件路径和输出文件名即可。请逐个编译，不要将 `basic/*.cpp` 一起链接为同一个程序，否则会出现多个 `main()` 的链接错误。

## 目录结构

```text
icpctest/
├── basic/                  # 每个文件都是独立练习
│   ├── hello_icpc.cpp
│   ├── print_age.cpp
│   ├── print_adjacent_integers.cpp
│   ├── print_price.cpp
│   └── compound_assignment.cpp
├── docs/exercises/         # 分类目录、独立题目与新增题目模板
├── .github/                # 现有协作配置与说明
├── .gitignore              # 编译产物、缓存及编辑器文件忽略规则
├── LICENSE                 # MIT 许可
└── README.md
```

建议把编译结果放在 `build/` 或 `bin/` 中。这两个目录及常见的可执行文件、目标文件、库文件和编译缓存均已加入忽略规则，源码保留在 `basic/` 中。

## 许可

本仓库采用 [MIT License](LICENSE)，版权署名为 Maximora-byte。
