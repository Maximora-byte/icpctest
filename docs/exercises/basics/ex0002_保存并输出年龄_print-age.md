<a id="ex0002-保存并输出年龄"></a>
# EX0002 保存并输出年龄 / EX0002 Store and Print an Age

[返回基础语法分类](README.md) · [返回习题总目录](../README.md)

[Back to fundamentals](README.md) · [Back to the exercise catalog](../README.md)

- 主分类：基础语法 / 数据类型与变量<br>
  Main category: Fundamentals / Data types and variables
- 难度：入门（本仓库学习分级）<br>
  Difficulty: Introductory (this repository's learning levels)
- 标签：variable、integer、output<br>
  Tags: variable, integer, output
- 题面来源：根据现有源码整理；原始题库与题号未确认<br>
  Statement source: reconstructed from existing source; original problem collection and ID unconfirmed
- 实现状态：固定数据演示，无标准输入；拓展练习未实现<br>
  Implementation status: fixed-data demonstration without standard input; extension not implemented
- 原文件名：`basic/age.cpp`<br>
  Original filename: `basic/age.cpp`

对应源码：[basic/输出年龄_print_age.cpp](../../../basic/输出年龄_print_age.cpp)

Corresponding source: [basic/输出年龄_print_age.cpp](../../../basic/输出年龄_print_age.cpp)

**题目：**定义一个名为 `age` 的整型变量，将它初始化为 `18`，然后输出这个变量的值。不要直接把输出语句写成固定字符串 `"18"`。

**Problem:** Define an integer variable named `age`, initialize it to `18`, and print its value. Do not replace the output with the fixed string `"18"`.

- 输入：无。<br>
  Input: None.
- 输出要求：仅输出变量的值，末尾不输出换行符。<br>
  Output requirement: print only the variable's value, with no trailing newline.
- 知识点：变量声明、`int`、初始化、变量名和值的区别。<br>
  Topics: variable declarations, `int`, initialization, and variable names versus values.

**先想一想：**`cout << age;` 和 `cout << "age";` 的输出有什么区别？把初始化值改为 `19` 后，输出语句还需要改吗？

**Think first:** How do `cout << age;` and `cout << "age";` differ? If the initial value becomes `19`, must the output statement change?

<details>
<summary>展开参考输出、提示与易错点 / Expand reference output, hints, and pitfalls</summary>

参考输出：

Reference output:

```text
18
```

- `int age = 18;` 声明并初始化变量；`cout << age;` 读取变量的值。<br>
  `int age = 18;` declares and initializes the variable; `cout << age;` reads its value.
- `cout << "age";` 输出三个字母 `age`。<br>
  `cout << "age";` prints the three letters `age`.
- 初始化值改为 `19` 后，`cout << age;` 会输出 `19`，不用修改输出语句。<br>
  After changing the initial value to `19`, `cout << age;` prints `19` without any change to the output statement.
- 局部整型变量应先初始化或成功赋值，再读取；不要练习成 `int age; cout << age;`。<br>
  Initialize or successfully assign a local integer before reading it; do not practice `int age; cout << age;`.

</details>

**拓展练习（未实现）：**读取整数年龄 `age`（练习范围 `0` 到 `120`），输出一年后的年龄 `age + 1`，末尾换行。例如输入 `18`，输出 `19`；输入 `0`，输出 `1`。本题只做整数加法，不涉及生日或日期计算。

**Extension (not implemented):** Read an integer age `age` (practice range `0` to `120`) and print next year's age, `age + 1`, followed by a newline. For input `18`, output `19`; for `0`, output `1`. This exercise is integer addition only, not birthday or date calculation.

<a id="复杂度与复习目标"></a>
## 复杂度与复习目标 / Complexity and Revision Goals

本程序处理固定数量的数据与输出，时间复杂度和额外空间复杂度均为 `O(1)`。复习时先独立完成本题，再展开答案核对；拓展题的输入输出要求另列，不代表当前源码行为。

The program processes a fixed amount of data and output, so both time and extra-space complexity are `O(1)`. Attempt the exercise independently before expanding the answer to check it. Extension input/output requirements are stated separately and do not describe the current source behavior.

编译方式见 [仓库快速开始](../../../README.md#快速开始)，替换为本页链接的源文件路径并单独编译。

For compilation, see the [repository quick start](../../../README.md#快速开始); substitute the source path linked on this page and compile it independently.
