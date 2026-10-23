<a id="ex0003-连续输出两个整数"></a>
# EX0003 连续输出两个整数 / EX0003 Print Two Integers Consecutively

[返回基础语法分类](README.md) · [返回习题总目录](../README.md)

[Back to fundamentals](README.md) · [Back to the exercise catalog](../README.md)

- 主分类：基础语法 / 基本输出<br>
  Main category: Fundamentals / Basic output
- 难度：入门（本仓库学习分级）<br>
  Difficulty: Introductory (this repository's learning levels)
- 标签：output、formatting、integer<br>
  Tags: output, formatting, integer
- 题面来源：根据现有源码整理；原始题库与题号未确认<br>
  Statement source: reconstructed from existing source; original problem collection and ID unconfirmed
- 实现状态：固定数据演示，无标准输入；拓展练习未实现<br>
  Implementation status: fixed-data demonstration without standard input; extension not implemented
- 原文件名：`basic/ab.cpp`<br>
  Original filename: `basic/ab.cpp`

对应源码：[basic/连续输出两个整数_print_adjacent_integers.cpp](../../../basic/连续输出两个整数_print_adjacent_integers.cpp)

Corresponding source: [basic/连续输出两个整数_print_adjacent_integers.cpp](../../../basic/连续输出两个整数_print_adjacent_integers.cpp)

**题目：**定义两个整型变量 `a = 10`、`b = 20`。依次输出 `a` 和 `b`，中间不加空格、逗号或换行，也不进行算术运算。

**Problem:** Define integers `a = 10` and `b = 20`. Print `a` followed by `b`, with no space, comma, or newline between them and no arithmetic operation.

- 输入：无，`10` 和 `20` 已写在源码中。<br>
  Input: None; `10` and `20` are fixed in the source.
- 输出要求：两个变量的十进制表示紧挨在一起，末尾不输出换行符。<br>
  Output requirement: the decimal representations of both variables are adjacent, with no trailing newline.
- 知识点：多个变量、顺序执行、连续输出、分隔符。<br>
  Topics: multiple variables, sequential execution, consecutive output, and separators.

**先想一想：**执行两次 `cout` 会自动换行吗？这个程序会输出 `30` 吗？

**Think first:** Do two `cout` statements automatically start a new line? Will this program print `30`?

<details>
<summary>展开参考输出、提示与易错点 / Expand reference output, hints, and pitfalls</summary>

参考输出：

Reference output:

```text
1020
```

- 第一次输出 `10`，第二次紧接着输出 `20`，因此屏幕显示 `1020`。<br>
  The first output is `10`, immediately followed by `20`, so the screen shows `1020`.
- `cout << a; cout << b;` 不会自动添加空格或换行。<br>
  `cout << a; cout << b;` does not automatically add a space or newline.
- `cout << a << b;` 对这里的两个整数具有相同的可见输出；`cout << a + b;` 才会计算并输出两数之和 `30`。<br>
  `cout << a << b;` has the same visible output for these integers; `cout << a + b;` instead calculates and prints their sum, `30`.
- 原文件名为 `ab.cpp`；对应的现有练习内容是连续输出。<br>
  The original filename was `ab.cpp`; the actual exercise is consecutive output.

</details>

**拓展练习（未实现）：**改为从标准输入读取两个整数，按「一个空格分隔、末尾换行」的格式输出。先约定每个数在 `-1000` 到 `1000` 之间。

**Extension (not implemented):** Read two integers from standard input and print them separated by one space, followed by a newline. First assume that each integer is between `-1000` and `1000`.

输入示例：

Example input:

```text
10 20
```

目标输出：

Target output:

```text
10 20
```

再用 `-3 0` 检查是否输出 `-3 0`。这是输入与格式控制练习，不要求求和。

Also test `-3 0` and verify output `-3 0`. This is an input/formatting exercise, not an addition task.

<a id="复杂度与复习目标"></a>
## 复杂度与复习目标 / Complexity and Revision Goals

本程序处理固定数量的数据与输出，时间复杂度和额外空间复杂度均为 `O(1)`。复习时先独立完成本题，再展开答案核对；拓展题的输入输出要求另列，不代表当前源码行为。

The program processes a fixed amount of data and output, so both time and extra-space complexity are `O(1)`. Attempt the exercise independently before expanding the answer to check it. Extension input/output requirements are stated separately and do not describe the current source behavior.

编译方式见 [仓库快速开始](../../../README.md#快速开始)，替换为本页链接的源文件路径并单独编译。

For compilation, see the [repository quick start](../../../README.md#快速开始); substitute the source path linked on this page and compile it independently.
