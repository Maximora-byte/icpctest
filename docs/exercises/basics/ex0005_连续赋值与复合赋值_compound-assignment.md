<a id="ex0005-推导连续赋值与复合赋值"></a>
# EX0005 推导连续赋值与复合赋值 / EX0005 Trace Chained and Compound Assignment

[返回基础语法分类](README.md) · [返回习题总目录](../README.md)

[Back to fundamentals](README.md) · [Back to the exercise catalog](../README.md)

- 主分类：基础语法 / 赋值运算符<br>
  Main category: Fundamentals / Assignment operators
- 难度：入门（本仓库学习分级）<br>
  Difficulty: Introductory (this repository's learning levels)
- 标签：assignment、compound-assignment、associativity<br>
  Tags: assignment, compound-assignment, associativity
- 题面来源：根据现有源码整理；原始题库与题号未确认<br>
  Statement source: reconstructed from existing source; original problem collection and ID unconfirmed
- 实现状态：固定数据演示，无标准输入；拓展练习未实现<br>
  Implementation status: fixed-data demonstration without standard input; extension not implemented
- 原文件名：`basic/5.cpp`<br>
  Original filename: `basic/5.cpp`

对应源码：[basic/复合赋值_compound_assignment.cpp](../../../basic/复合赋值_compound_assignment.cpp)

Corresponding source: [basic/复合赋值_compound_assignment.cpp](../../../basic/复合赋值_compound_assignment.cpp)

**题目：**按顺序执行下面四组整型变量操作，手算每一组操作后的变量值，再编写程序输出结果。**每组开始时都重新设置变量，不能把上一组结果带入下一组。**

**Problem:** Execute the following four groups of integer operations in order, calculate the resulting variable values by hand, then write a program to print them. **Reset variables at the start of each group; do not carry results over from the previous group.**

| 组别<br>Group | 本组初始赋值<br>Initial assignments | 接着执行的表达式<br>Expression executed next | 输出哪些变量<br>Variables to print |
| :--- | :--- | :--- | :--- |
| 1 | `i = 7; j = 8;` | `i *= j + 1;` | `i`、`j` |
| 2 | `i = j = k = 1;` | `i += j += k;` | `i`、`j`、`k` |
| 3 | `i = 1; j = 2; k = 3;` | `i -= j -= k;` | `i`、`j`、`k` |
| 4 | `i = 2; j = 1; k = 0;` | `i *= j *= k;` | `i`、`j`、`k` |

- 输入：无。<br>
  Input: None.
- 输出要求：共四行。第一行格式为 `i=值,j=值`，后三行格式为 `i=值,j=值,k=值`；使用英文逗号，不加空格，每行末尾都有换行符。<br>
  Output requirement: four lines. The first uses `i=value,j=value`; the last three use `i=value,j=value,k=value`. Use ASCII commas, no spaces, and a newline at the end of every line.
- 知识点：连续赋值、复合赋值、运算符优先级和结合性、`printf` 的 `%d` 与 `\n`。<br>
  Topics: chained and compound assignment, operator precedence and associativity, and `printf`'s `%d` and `\n`.

**先想一想：**

**Think first:**

1. `i *= j + 1` 是把 `i` 乘以 `j + 1`，还是先乘 `j` 再加 `1`？<br>
   Does `i *= j + 1` multiply `i` by `j + 1`, or multiply by `j` first and then add `1`?
2. `i += j += k` 应如何加括号？外层使用的是 `j` 的旧值还是更新后的值？<br>
   How should `i += j += k` be parenthesized? Does the outer assignment use the old or updated value of `j`?
3. 第三组的 `j` 会变成负数吗？第四组中 `k = 0` 会怎样影响结果？<br>
   Does `j` become negative in the third group? How does `k = 0` affect the fourth group?

<details>
<summary>展开完整输出与逐步推导 / Expand full output and step-by-step reasoning</summary>

参考输出：

Reference output:

```text
i=63,j=8
i=3,j=2,k=1
i=2,j=-1,k=3
i=0,j=0,k=0
```

**第 1 组：**`i *= (j + 1)`，所以 `i = 7 × (8 + 1) = 63`，`j` 仍为 `8`。不要算成 `7 × 8 + 1`。

**Group 1:** `i *= (j + 1)`, so `i = 7 × (8 + 1) = 63`; `j` remains `8`. Do not calculate it as `7 × 8 + 1`.

**第 2 组：**`i = j = k = 1` 使三个变量都成为 `1`。复合赋值按右结合分组：`i += (j += k)`。内层将 `j` 变为 `2`，外层把更新后的 `j` 加到 `i`，得到 `i = 3`；`k` 仍为 `1`。

**Group 2:** `i = j = k = 1` sets all three variables to `1`. Compound assignment groups right-associatively: `i += (j += k)`. The inner assignment changes `j` to `2`; the outer adds the updated `j` to `i`, yielding `i = 3`; `k` stays `1`.

**第 3 组：**`i -= (j -= k)`。内层得到 `j = 2 - 3 = -1`；外层得到 `i = 1 - (-1) = 2`；`k` 仍为 `3`。

**Group 3:** `i -= (j -= k)`. The inner result is `j = 2 - 3 = -1`; the outer result is `i = 1 - (-1) = 2`; `k` stays `3`.

**第 4 组：**`i *= (j *= k)`。内层得到 `j = 1 × 0 = 0`；外层得到 `i = 2 × 0 = 0`；`k` 仍为 `0`。

**Group 4:** `i *= (j *= k)`. The inner result is `j = 1 × 0 = 0`; the outer result is `i = 2 × 0 = 0`; `k` stays `0`.

这里的讲解针对 C++17 下的这些具体表达式。「右结合」描述的是表达式如何分组，不应推广成所有表达式都按从右到左的顺序求值。

This explanation applies to these specific expressions under C++17. “Right associativity” describes grouping, not a general rule that all expressions are evaluated from right to left.

</details>

<details>
<summary>展开易错点与更清晰的写法 / Expand pitfalls and clearer alternatives</summary>

- 对这里的简单整型变量，可以用 `i = i * (j + 1)` 理解 `i *= j + 1`。对带副作用的复杂左操作数，不要直接机械替换：复合赋值只对左操作数求值一次。<br>
  For these simple integer variables, `i = i * (j + 1)` helps explain `i *= j + 1`. Do not mechanically substitute this form for a complex left operand with side effects: compound assignment evaluates its left operand only once.
- 为了更容易检查，第二组的核心操作可拆成 `j += k;` 然后 `i += j;`；第三、四组可用同样方法拆开。<br>
  For easier checking, split the second group's core operation into `j += k;` followed by `i += j;`; the third and fourth groups can be split similarly.
- 第一组没有初始化 `k`，也没有读取或输出它；不要自行在第一行追加 `k`。第二组会先给 `k` 赋值再使用。<br>
  The first group neither initializes nor reads or prints `k`; do not add `k` to its output line. The second group assigns `k` before using it.
- `%d` 在这里对应 `int`。保持格式串和参数顺序一致，避免把 `i`、`j`、`k` 打印错位。<br>
  Here `%d` corresponds to `int`. Keep format placeholders and arguments in matching order so `i`, `j`, and `k` are not printed in the wrong positions.
- 原文件虽然使用 `<stdio.h>` 和 `printf`，扩展名仍是 `.cpp`；按仓库的 C++17 命令单独编译。<br>
  Although the source uses `<stdio.h>` and `printf`, its extension is `.cpp`; compile it separately with the repository's C++17 command.

</details>

**拓展练习（未实现）：**从标准输入读取三个整数 `i`、`j`、`k`（每个数在 `-100` 到 `100` 之间），仅执行 `i += j += k`，按 `i j k` 的格式输出，使用空格分隔、末尾换行。

**Extension (not implemented):** Read integers `i`, `j`, and `k` from standard input (each between `-100` and `100`), execute only `i += j += k`, and print `i j k`, separated by spaces and followed by a newline.

输入示例：

Example input:

```text
2 3 4
```

<details>
<summary>展开拓展题答案与自测 / Expand extension answer and self-tests</summary>

目标输出：

Target output:

```text
9 7 4
```

先算 `j = 3 + 4 = 7`，再算 `i = 2 + 7 = 9`。还可以用 `0 0 0`（输出 `0 0 0`）和 `1 2 -3`（输出 `0 -1 -3`）自测。

First calculate `j = 3 + 4 = 7`, then `i = 2 + 7 = 9`. Also test `0 0 0` (output `0 0 0`) and `1 2 -3` (output `0 -1 -3`).

</details>

<a id="复杂度与复习目标"></a>
## 复杂度与复习目标 / Complexity and Revision Goals

本程序处理固定数量的数据与输出，时间复杂度和额外空间复杂度均为 `O(1)`。复习时先独立完成本题，再展开答案核对；拓展题的输入输出要求另列，不代表当前源码行为。

The program processes a fixed amount of data and output, so both time and extra-space complexity are `O(1)`. Attempt the exercise independently before expanding the answer to check it. Extension input/output requirements are stated separately and do not describe the current source behavior.

编译方式见 [仓库快速开始](../../../README.md#快速开始)，替换为本页链接的源文件路径并单独编译。

For compilation, see the [repository quick start](../../../README.md#快速开始); substitute the source path linked on this page and compile it independently.
