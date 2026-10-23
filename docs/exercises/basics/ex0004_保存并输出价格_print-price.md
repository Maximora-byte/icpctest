<a id="ex0004-保存并输出价格"></a>
# EX0004 保存并输出价格 / EX0004 Store and Print a Price

[返回基础语法分类](README.md) · [返回习题总目录](../README.md)

[Back to fundamentals](README.md) · [Back to the exercise catalog](../README.md)

- 主分类：基础语法 / 数据类型与变量<br>
  Main category: Fundamentals / Data types and variables
- 难度：入门（本仓库学习分级）<br>
  Difficulty: Introductory (this repository's learning levels)
- 标签：variable、floating-point、output<br>
  Tags: variable, floating-point, output
- 题面来源：根据现有源码整理；原始题库与题号未确认<br>
  Statement source: reconstructed from existing source; original problem collection and ID unconfirmed
- 实现状态：固定数据演示，无标准输入；拓展练习未实现<br>
  Implementation status: fixed-data demonstration without standard input; extension not implemented
- 原文件名：`basic/double.cpp`<br>
  Original filename: `basic/double.cpp`

对应源码：[basic/输出价格_print_price.cpp](../../../basic/输出价格_print_price.cpp)

Corresponding source: [basic/输出价格_print_price.cpp](../../../basic/输出价格_print_price.cpp)

**题目：**定义一个 `double` 变量 `price`，初始化为 `9.9`，使用 `cout` 的默认格式输出它，不额外设置小数位数。

**Problem:** Define a `double` variable `price`, initialize it to `9.9`, and print it with `cout`'s default formatting without explicitly setting decimal places.

- 输入：无。<br>
  Input: None.
- 输出要求：输出变量的默认文本表示，末尾不输出换行符。<br>
  Output requirement: print the variable's default text representation, with no trailing newline.
- 知识点：浮点数变量、小数字面量、数值与显示格式的区别。<br>
  Topics: floating-point variables, decimal literals, and values versus display formatting.

**先想一想：**当前输出是 `9.9` 还是 `9.90`？变量类型是 `double`，是否就会自动保留两位小数？

**Think first:** Is the current output `9.9` or `9.90`? Does a `double` variable automatically display two decimal places?

<details>
<summary>展开参考输出、提示与易错点 / Expand reference output, hints, and pitfalls</summary>

参考输出：

Reference output:

```text
9.9
```

- 现有程序没有设置 `fixed` 或 `setprecision`，不会主动补成两位小数。<br>
  The program does not set `fixed` or `setprecision`, so it does not deliberately pad the output to two decimal places.
- `double` 通常不能精确表示所有十进制小数。屏幕显示 `9.9`，不意味着底层存储的数值一定精确等于十进制的 `9.9`。<br>
  A `double` generally cannot represent every decimal fraction exactly. Seeing `9.9` on the screen does not mean the stored value is exactly the decimal number `9.9`.
- 如果练习要求固定两位小数，可以包含 `<iomanip>`，再使用 `cout << fixed << setprecision(2) << price;`。<br>
  If two fixed decimal places are required, include `<iomanip>` and use `cout << fixed << setprecision(2) << price;`.
- 仅使用 `setprecision(2)` 而不配合 `fixed` 时，在默认浮点格式下控制的是有效数字位数，而非小数点后两位。<br>
  With the default floating-point format, `setprecision(2)` without `fixed` controls significant digits, not two digits after the decimal point.

</details>

**拓展练习（未实现）：**读取一个非负价格（练习范围 `0` 到 `10000`），固定输出两位小数，末尾换行。

**Extension (not implemented):** Read a nonnegative price (practice range `0` to `10000`) and print exactly two decimal places, followed by a newline.

| 输入<br>Input | 目标输出<br>Target output |
| :--- | :--- |
| `9.9` | `9.90` |
| `12` | `12.00` |
| `0` | `0.00` |

先用这些无需判断舍入边界的值，确认自己掌握了格式控制。

Use these values, which do not require judging rounding boundaries, to confirm that you understand formatting.

<a id="复杂度与复习目标"></a>
## 复杂度与复习目标 / Complexity and Revision Goals

本程序处理固定数量的数据与输出，时间复杂度和额外空间复杂度均为 `O(1)`。复习时先独立完成本题，再展开答案核对；拓展题的输入输出要求另列，不代表当前源码行为。

The program processes a fixed amount of data and output, so both time and extra-space complexity are `O(1)`. Attempt the exercise independently before expanding the answer to check it. Extension input/output requirements are stated separately and do not describe the current source behavior.

编译方式见 [仓库快速开始](../../../README.md#快速开始)，替换为本页链接的源文件路径并单独编译。

For compilation, see the [repository quick start](../../../README.md#快速开始); substitute the source path linked on this page and compile it independently.
