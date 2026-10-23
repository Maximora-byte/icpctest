<div align="center">

<a id="-icpc-practice"></a>
<a id="icpc-practice"></a>
# 🧩 ICPC 练习 / ICPC Practice

**C++ 基础练习 · ICPC 学习记录**

**C++ Fundamentals · ICPC Learning Notes**

<sub>C++17 · 独立编译 · MIT License</sub>

<sub>C++17 · Compile Independently · MIT License</sub>

[练习索引](#练习索引) · [快速开始](#快速开始) · [目录结构](#目录结构) · [许可](#许可)

[Exercise Index](#练习索引) · [Quick Start](#快速开始) · [Directory Structure](#目录结构) · [License](#许可)

</div>

<a id="关于这个仓库"></a>
## 关于这个仓库 / About This Repository

自用的 ICPC 练习仓库。目前收录 12 个独立 C++ 源文件：`basic/` 7 个，`luogu/` 5 个，覆盖基础输出、变量、赋值、排序去重、二分与字符串练习。当前 `luogu/P1308_单词统计_word_count.cpp` 已包含整词匹配计数与首次位置输出；此处描述不代表已通过在线评测。

A personal ICPC practice repository containing 12 independent C++ source files: 7 in `basic/` and 5 in `luogu/`. Topics include basic output, variables, assignment, sorting and deduplication, binary search, and strings. The current `luogu/P1308_单词统计_word_count.cpp` counts whole-word matches and outputs the first matching position; this description is not evidence of online-judge acceptance.

每个 `.cpp` 文件都有独立的 `main()`，应单独编译。源码采用中英双语文件名：基础练习位于 `basic/`，按平台编号保存的练习位于 `luogu/`。文件存在不表示已通过在线评测。

Each `.cpp` file has its own `main()` and must be compiled independently. Source filenames are bilingual: basic exercises live in `basic/`, and platform-numbered exercises in `luogu/`. A file's presence does not imply that it has passed an online judge.

复习时可阅读 [分类习题总目录](docs/exercises/README.md)：目前已有 EX0001–EX0005 五份独立题目页，附稳定编号、折叠答案、易错点与拓展练习；其余源码先在下表登记，尚未补齐独立题目页。

For revision, see the [categorized exercise catalog](docs/exercises/README.md): EX0001–EX0005 currently have five standalone problem pages with stable IDs, collapsible answers, pitfalls, and extension exercises. The remaining source files are listed below but do not yet have standalone problem pages.

刚开始接触标准库，可阅读 [标准库入门_Standard_Library_Primer.md：C++ 标准库入门](标准库入门_Standard_Library_Primer.md)，从 `vector`、排序、去重和整行输入学起；现已包含[字符串与引用](标准库入门_Standard_Library_Primer.md#char-reference)、[二分查找与边界速查](标准库入门_Standard_Library_Primer.md#binary-search)、[C 文件操作](标准库入门_Standard_Library_Primer.md#c-file-io)及[二进制读写](标准库入门_Standard_Library_Primer.md#c-binary-file-io)。C 文件操作示例单独按 C11 编译，其他完整示例按 C++17 使用。

New to the standard library? Start with the [C++ standard library primer](标准库入门_Standard_Library_Primer.md), covering `vector`, sorting, deduplication, and whole-line input. It now includes [strings and references](标准库入门_Standard_Library_Primer.md#char-reference), [binary search and boundary lookup](标准库入门_Standard_Library_Primer.md#binary-search), [C file operations](标准库入门_Standard_Library_Primer.md#c-file-io), and [binary file I/O](标准库入门_Standard_Library_Primer.md#c-binary-file-io). Compile the C file-operation examples separately as C11 and the other complete examples as C++17.

<a id="练习索引"></a>
## 练习索引 / Exercise Index

<a id="固定数据基础练习"></a>
### 固定数据基础练习 / Fixed-data Fundamentals

| 文件<br>File | 练习内容<br>Exercise | 当前输出<br>Current output |
| :--- | :--- | :--- |
| [`输出问候语_hello_icpc.cpp`](basic/输出问候语_hello_icpc.cpp) | 第一个程序与文本输出<br>First program and text output | `Hello ICPC` |
| [`输出年龄_print_age.cpp`](basic/输出年龄_print_age.cpp) | 整型变量<br>Integer variable | `18` |
| [`连续输出两个整数_print_adjacent_integers.cpp`](basic/连续输出两个整数_print_adjacent_integers.cpp) | 连续输出两个整数<br>Print two integers consecutively | `1020` |
| [`输出价格_print_price.cpp`](basic/输出价格_print_price.cpp) | 浮点数变量<br>Floating-point variable | `9.9` |
| [`复合赋值_compound_assignment.cpp`](basic/复合赋值_compound_assignment.cpp) | 复合赋值与连续赋值<br>Compound and chained assignment | 4 组变量结果，见下方<br>Four groups of variable values; see below |

<details>
<summary><strong>查看 复合赋值_compound_assignment.cpp 的输出</strong> / View the output of 复合赋值_compound_assignment.cpp</summary>

```text
i=63,j=8
i=3,j=2,k=1
i=2,j=-1,k=3
i=0,j=0,k=0
```

</details>

<a id="输入型练习与学习草稿"></a>
### 输入型练习与学习草稿 / Input-based Exercises and Learning Drafts

下表依据当前源码描述行为，不补造原题条件或评测通过状态。

This table describes the current source behavior without inventing original problem constraints or acceptance results.

| 文件<br>File | 当前内容<br>Current behavior | 输入 / 状态说明<br>Input / status notes |
| :--- | :--- | :--- |
| [`basic/二分查找_binary_search.cpp`](basic/二分查找_binary_search.cpp) | 在固定升序数组 `1, 3, 5, 7, 9, 12, 15` 中二分查找<br>Binary search in the fixed ascending array `1, 3, 5, 7, 9, 12, 15` | 输入目标整数；找到输出从 0 开始的下标，否则输出 `-1`<br>Read a target integer; output its zero-based index if found, otherwise `-1` |
| [`basic/去重排序取第k项_kth_unique_value.cpp`](basic/去重排序取第k项_kth_unique_value.cpp) | 用 `set` 去重排序，读取第 k 个不同值<br>Deduplicate and sort with `set`, then retrieve the kth distinct value | 输入 `n k` 和 n 个整数；k 超出不同值个数时输出 `NO`；当前未检查非正 k 等非法输入<br>Read `n k` and n integers; output `NO` if k exceeds the number of distinct values; invalid inputs such as non-positive k are currently unchecked |
| [`luogu/P1059_去重排序_deduplicate_sort.cpp`](luogu/P1059_去重排序_deduplicate_sort.cpp) | 去重排序<br>Deduplicate and sort | 输入数量和整数；输出不同值个数，再升序输出各值<br>Read a count and integers; output the number of distinct values, then those values in ascending order |
| [`luogu/P1177_升序排序_ascending_sort.cpp`](luogu/P1177_升序排序_ascending_sort.cpp) | `sort` 升序排序<br>Sort ascending with `sort` | 输入数量和整数；保留重复值后输出<br>Read a count and integers; output the sorted values while retaining duplicates |
| [`luogu/P1308_单词统计_word_count.cpp`](luogu/P1308_单词统计_word_count.cpp) | 目标词与文本转小写后统计整词匹配<br>Lowercase the target and text, then count whole-word matches | 输入目标词和一行文本，按空格划分单词；找到时输出次数与首次匹配的零基下标，否则输出 `-1`；不声称通过评测<br>Read a target word and a line; words are separated by spaces. Output the count and zero-based position of the first match, or `-1` if absent; no online-judge acceptance claim |
| [`luogu/P2249_首次出现位置_first_occurrence.cpp`](luogu/P2249_首次出现位置_first_occurrence.cpp) | 查找目标首次出现的位置<br>Find the first occurrence of each target | 输入 `n m`、有序数组及 m 次查询；找到时输出从 1 开始的位置，否则 `-1`<br>Read `n m`, a sorted array, and m queries; output the one-based first position or `-1` |
| [`luogu/P1102_差值配对计数_difference_pairs.cpp`](luogu/P1102_差值配对计数_difference_pairs.cpp) | 排序后用二分边界统计差值配对<br>Sort and count difference pairs using binary-search bounds | 输入 `n C` 和 n 个整数；对每个 A 累加 B = A − C 的出现次数，输出总数<br>Read `n C` and n integers; for each A, add the frequency of B = A − C and output the total |

这些新增源码使用 `bits/stdc++.h`，依赖提供该头文件的 GNU C++ 工具链；仅支持 C++17 的编译器不一定提供它。输入范围、边界与格式仍需按原题自行验证。

These additional source files use `bits/stdc++.h`, requiring a GNU C++ toolchain that provides that header; C++17 support alone does not guarantee its availability. Validate input ranges, boundary cases, and formatting against the original problem yourself.

<a id="快速开始"></a>
## 快速开始 / Quick Start

准备支持 C++17 的 C++ 编译器。以下命令以 `g++` 为例，在仓库根目录执行。

Prepare a C++ compiler with C++17 support. Run the following example commands, using `g++`, from the repository root.

### Linux / macOS

```bash
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Wpedantic basic/输出问候语_hello_icpc.cpp -o build/hello_icpc
./build/hello_icpc
```

### Windows PowerShell

先确认已安装支持 C++17 的 `g++`，并且命令行能够找到它。

First ensure that C++17-capable `g++` is installed and available on your command line.

```powershell
New-Item -ItemType Directory -Force build | Out-Null
g++ -std=c++17 -Wall -Wextra -Wpedantic basic/输出问候语_hello_icpc.cpp -o build/hello_icpc.exe
.\build\hello_icpc.exe
```

运行结果：

Output:

```text
Hello ICPC
```

练习其他文件时，替换命令中的源文件路径和输出文件名即可。请逐个编译，不要将多个 `.cpp`（包括 `basic/` 与 `luogu/`）一起链接为同一个程序，否则会出现多个 `main()` 的链接错误。

To practice another file, replace the source path and output filename in the command. Compile files individually: do not link several `.cpp` files (including those in `basic/` and `luogu/`) into one program, or you will get multiple-`main()` linker errors.

<a id="目录结构"></a>
## 目录结构 / Directory Structure

```text
icpctest/
├── basic/                  # 独立练习 / Independent exercises
│   ├── 输出问候语_hello_icpc.cpp
│   ├── 输出年龄_print_age.cpp
│   ├── 连续输出两个整数_print_adjacent_integers.cpp
│   ├── 输出价格_print_price.cpp
│   ├── 复合赋值_compound_assignment.cpp
│   ├── 二分查找_binary_search.cpp
│   └── 去重排序取第k项_kth_unique_value.cpp
├── luogu/                  # 保留平台题号 / Platform IDs preserved
│   ├── P1059_去重排序_deduplicate_sort.cpp
│   ├── P1102_差值配对计数_difference_pairs.cpp
│   ├── P1177_升序排序_ascending_sort.cpp
│   ├── P1308_单词统计_word_count.cpp
│   └── P2249_首次出现位置_first_occurrence.cpp
├── docs/exercises/         # 分类、题目、模板 / Categories, problems, template
├── 标准库入门_Standard_Library_Primer.md  # 标准库笔记 / Standard library notes
├── .github/                # 协作配置与说明 / Collaboration configuration and guides
├── .gitignore              # 产物与缓存忽略规则 / Build and cache ignore rules
├── LICENSE                 # MIT 许可原文 / Original MIT license
└── README.md               # 仓库说明 / Repository guide
```

建议把编译结果放在 `build/` 或 `bin/` 中。这两个目录及常见的可执行文件、目标文件、库文件和编译缓存均已加入忽略规则，源码保留在 `basic/` 和 `luogu/` 中。

Put compiled outputs in `build/` or `bin/`. Both directories, common executables, object files, libraries, and compilation caches are ignored; keep source files in `basic/` and `luogu/`.

<a id="许可"></a>
## 许可 / License

本仓库采用 [MIT License](LICENSE)，版权署名为 Maximora-byte。MIT 英文许可正文保持原样并以其为准；本双语说明不替代许可正文。

This repository uses the [MIT License](LICENSE), with copyright attributed to Maximora-byte. The English MIT license text is unchanged and authoritative; this bilingual explanation does not replace it.



<a id="filename-index"></a>
## 文件名与旧路径索引 / Filename and Legacy-path Index

普通文档和源码采用「中文名_EnglishName.扩展名」，题号和 EX 编号保留在开头，英文部分使用有意义的词语。目录结构不变；一份内容只保留一个正文文件，避免双份源码或翻译长期分叉。文档正文按中文在前、等义英文紧随的方式维护，表格单元格与折叠提示也采用双语。示例代码、命令参数和程序输出不因翻译而改变语义。

Ordinary documents and source files use “Chinese-name_EnglishName.extension,” retaining problem and EX IDs at the beginning and meaningful English words. Directory structure is unchanged; each item has one canonical file to avoid divergent source or translation copies. Maintain Chinese first with equivalent English immediately following, including table cells and collapsible hints. Translation must not change example-code, command-argument, or output semantics.

下表保留迁移前的路径作为检索线索，并链接到当前文件。仓库内引用已更新；旧标题的片段锚点保留在新文档中。GitHub 不为文件改名提供本文可配置的旧 URL 重定向，因此收藏的旧文件链接需要按本表更新路径。

The table retains pre-migration paths as search terms and links to current files. Internal references are updated, and old heading fragments are preserved in the renamed documents. GitHub does not provide a configurable old-URL redirect here for renamed files, so update bookmarked old file paths using this table.

| 旧路径 / Legacy path | 当前双语路径 / Current bilingual path |
| --- | --- |
| `STD.md` | [标准库入门_Standard_Library_Primer.md](标准库入门_Standard_Library_Primer.md) |
| `.github/AUTO_LABELER.md` | [.github/自动标签说明_AUTO_LABELER.md](.github/自动标签说明_AUTO_LABELER.md) |
| `.github/DEVELOPMENT_FLOW.md` | [.github/开发流程_DEVELOPMENT_FLOW.md](.github/开发流程_DEVELOPMENT_FLOW.md) |
| `docs/exercises/TEMPLATE.md` | [docs/exercises/题目模板_TEMPLATE.md](docs/exercises/题目模板_TEMPLATE.md) |
| `docs/exercises/basics/ex0001-hello-icpc.md` | [docs/exercises/basics/ex0001_输出问候语_hello-icpc.md](docs/exercises/basics/ex0001_输出问候语_hello-icpc.md) |
| `docs/exercises/basics/ex0002-print-age.md` | [docs/exercises/basics/ex0002_保存并输出年龄_print-age.md](docs/exercises/basics/ex0002_保存并输出年龄_print-age.md) |
| `docs/exercises/basics/ex0003-print-adjacent-integers.md` | [docs/exercises/basics/ex0003_连续输出两个整数_print-adjacent-integers.md](docs/exercises/basics/ex0003_连续输出两个整数_print-adjacent-integers.md) |
| `docs/exercises/basics/ex0004-print-price.md` | [docs/exercises/basics/ex0004_保存并输出价格_print-price.md](docs/exercises/basics/ex0004_保存并输出价格_print-price.md) |
| `docs/exercises/basics/ex0005-compound-assignment.md` | [docs/exercises/basics/ex0005_连续赋值与复合赋值_compound-assignment.md](docs/exercises/basics/ex0005_连续赋值与复合赋值_compound-assignment.md) |
| `basic/hello_icpc.cpp` | [basic/输出问候语_hello_icpc.cpp](basic/输出问候语_hello_icpc.cpp) |
| `basic/print_age.cpp` | [basic/输出年龄_print_age.cpp](basic/输出年龄_print_age.cpp) |
| `basic/print_adjacent_integers.cpp` | [basic/连续输出两个整数_print_adjacent_integers.cpp](basic/连续输出两个整数_print_adjacent_integers.cpp) |
| `basic/print_price.cpp` | [basic/输出价格_print_price.cpp](basic/输出价格_print_price.cpp) |
| `basic/compound_assignment.cpp` | [basic/复合赋值_compound_assignment.cpp](basic/复合赋值_compound_assignment.cpp) |
| `basic/erfen.cpp` | [basic/二分查找_binary_search.cpp](basic/二分查找_binary_search.cpp) |
| `basic/quchongpaixu.cpp` | [basic/去重排序取第k项_kth_unique_value.cpp](basic/去重排序取第k项_kth_unique_value.cpp) |
| `luogu/P1059.cpp` | [luogu/P1059_去重排序_deduplicate_sort.cpp](luogu/P1059_去重排序_deduplicate_sort.cpp) |
| `luogu/P1177.cpp` | [luogu/P1177_升序排序_ascending_sort.cpp](luogu/P1177_升序排序_ascending_sort.cpp) |
| `luogu/P1308.cpp` | [luogu/P1308_单词统计_word_count.cpp](luogu/P1308_单词统计_word_count.cpp) |
| `luogu/P2249.cpp` | [luogu/P2249_首次出现位置_first_occurrence.cpp](luogu/P2249_首次出现位置_first_occurrence.cpp) |
| `luogu/P1102.cpp` | [luogu/P1102_差值配对计数_difference_pairs.cpp](luogu/P1102_差值配对计数_difference_pairs.cpp) |

### 保留的标准名称 / Preserved Standard Names

下列名称用于 GitHub 自动展示、工具识别或既有配置，因此不改名；通过双语标题及本索引检索。LICENSE 的 MIT 英文法律文本保持原样。工作流、配置文件及演示运行时数据文件也不为了双语命名而修改。

These names support GitHub rendering, tool discovery, or existing configuration and therefore stay unchanged; find them through bilingual titles and this index. The original English MIT legal text in LICENSE is unchanged. Workflow/configuration files and example runtime data filenames are likewise not changed merely for bilingual naming.

| 双语检索名称 / Bilingual lookup name | 固定路径 / Fixed path |
| --- | --- |
| 仓库说明 / Repository guide | [README.md](README.md) |
| 分类习题总目录 / Categorized exercise catalog | [docs/exercises/README.md](docs/exercises/README.md) |
| 基础语法复习 / Fundamentals revision | [docs/exercises/basics/README.md](docs/exercises/basics/README.md) |
| Copilot 仓库说明 / Copilot repository instructions | [.github/copilot-instructions.md](.github/copilot-instructions.md) |
| MIT 许可证 / MIT License | [LICENSE](LICENSE) |
| 自动标签工作流 / Auto-label workflow | [.github/workflows/auto-label.yml](.github/workflows/auto-label.yml) |
| 忽略规则 / Ignore rules | [.gitignore](.gitignore) |
