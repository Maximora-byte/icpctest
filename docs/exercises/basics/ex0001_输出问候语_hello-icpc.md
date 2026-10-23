<a id="ex0001-输出问候语"></a>
# EX0001 输出问候语 / EX0001 Print a Greeting

[返回基础语法分类](README.md) · [返回习题总目录](../README.md)

[Back to fundamentals](README.md) · [Back to the exercise catalog](../README.md)

- 主分类：基础语法 / 基本输出<br>
  Main category: Fundamentals / Basic output
- 难度：入门（本仓库学习分级）<br>
  Difficulty: Introductory (this repository's learning levels)
- 标签：output、string-literal<br>
  Tags: output, string-literal
- 题面来源：根据现有源码整理；原始题库与题号未确认<br>
  Statement source: reconstructed from existing source; original problem collection and ID unconfirmed
- 实现状态：固定数据演示，无标准输入；拓展练习未实现<br>
  Implementation status: fixed-data demonstration without standard input; extension not implemented
- 原文件名：`basic/helloicpc.cpp`<br>
  Original filename: `basic/helloicpc.cpp`

对应源码：[basic/输出问候语_hello_icpc.cpp](../../../basic/输出问候语_hello_icpc.cpp)

Corresponding source: [basic/输出问候语_hello_icpc.cpp](../../../basic/输出问候语_hello_icpc.cpp)

**题目：**编写一个 C++ 程序，向标准输出写出 `Hello ICPC`。大小写和中间的一个空格都要一致，不添加引号或其他提示文字。

**Problem:** Write a C++ program that prints `Hello ICPC` to standard output. Match the letter case and single space exactly, with no quotation marks or other prompts.

- 输入：无。<br>
  Input: None.
- 输出要求：仅输出题目指定的文本。现有源码末尾不输出换行符。<br>
  Output requirement: print only the specified text. The current source does not output a trailing newline.
- 知识点：`#include <iostream>`、`main()`、字符串字面量、`cout`、`return 0`。<br>
  Topics: `#include <iostream>`, `main()`, string literals, `cout`, and `return 0`.

**先想一想：**字符串两侧的双引号会显示出来吗？`return 0` 会把数字 `0` 输出到屏幕吗？

**Think first:** Do the double quotes around a string appear in the output? Does `return 0` print the number `0` on the screen?

<details>
<summary>展开参考输出、提示与易错点 / Expand reference output, hints, and pitfalls</summary>

参考输出：

Reference output:

```text
Hello ICPC
```

代码块展示的是可见内容；现有程序实际输出为 `Hello ICPC`，末尾没有 `\n`。

The block shows visible content; the program actually outputs `Hello ICPC` with no trailing `\n`.

- `cout << "Hello ICPC";` 输出字符串内容，双引号属于源码语法。<br>
  `cout << "Hello ICPC";` prints the string contents; double quotes are source-code syntax.
- `return 0;` 表示从 `main()` 正常返回，不产生屏幕输出。<br>
  `return 0;` returns normally from `main()` and does not produce screen output.
- C++ 语句结尾的分号、字符串内的空格都要注意。<br>
  Pay attention to statement-ending semicolons and spaces inside strings.

</details>

**拓展练习（未实现）：**在两行中分别输出 `Hello ICPC` 和 `Keep practicing`，并让最后一行也以换行符结束。比较 `\n` 和 `endl`：后者还会刷新输出流。

**Extension (not implemented):** Print `Hello ICPC` and `Keep practicing` on separate lines, including a newline after the last line. Compare `\n` and `endl`: the latter also flushes the output stream.

<a id="复杂度与复习目标"></a>
## 复杂度与复习目标 / Complexity and Revision Goals

本程序处理固定数量的数据与输出，时间复杂度和额外空间复杂度均为 `O(1)`。复习时先独立完成本题，再展开答案核对；拓展题的输入输出要求另列，不代表当前源码行为。

The program processes a fixed amount of data and output, so both time and extra-space complexity are `O(1)`. Attempt the exercise independently before expanding the answer to check it. Extension input/output requirements are stated separately and do not describe the current source behavior.

编译方式见 [仓库快速开始](../../../README.md#快速开始)，替换为本页链接的源文件路径并单独编译。

For compilation, see the [repository quick start](../../../README.md#快速开始); substitute the source path linked on this page and compile it independently.
