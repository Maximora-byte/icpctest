<a id="基础语法复习"></a>
# 基础语法复习 / Fundamentals Revision

[返回习题总目录](../README.md)

[Back to the exercise catalog](../README.md)

本分类现有 5 道题，均为 C++17 固定数据演示，无标准输入。题面根据源码整理，难度均为本仓库的「入门」级；未知的原题来源未补造。第一次学习推荐按 EX0001 → EX0002 → EX0003 → EX0004 → EX0005 的顺序。

This category has five C++17 fixed-data demonstrations with no standard input. Statements were reconstructed from source, all at this repository's “Introductory” level; no unknown original source has been invented. Recommended first-pass order: EX0001 → EX0002 → EX0003 → EX0004 → EX0005.

<a id="基本输出"></a>
## 基本输出 / Basic Output

| 编号与题目<br>ID and problem | 源码<br>Source | 标签<br>Tags |
| :--- | :--- | :--- |
| [EX0001 输出问候语](ex0001_输出问候语_hello-icpc.md)<br>[EX0001 Print a greeting](ex0001_输出问候语_hello-icpc.md) | [输出问候语_hello_icpc.cpp](../../../basic/输出问候语_hello_icpc.cpp) | `output`、`string-literal` |
| [EX0003 连续输出两个整数](ex0003_连续输出两个整数_print-adjacent-integers.md)<br>[EX0003 Print two integers consecutively](ex0003_连续输出两个整数_print-adjacent-integers.md) | [连续输出两个整数_print_adjacent_integers.cpp](../../../basic/连续输出两个整数_print_adjacent_integers.cpp) | `output`、`formatting`、`integer` |

<a id="数据类型与变量"></a>
## 数据类型与变量 / Data Types and Variables

| 编号与题目<br>ID and problem | 源码<br>Source | 标签<br>Tags |
| :--- | :--- | :--- |
| [EX0002 保存并输出年龄](ex0002_保存并输出年龄_print-age.md)<br>[EX0002 Store and print an age](ex0002_保存并输出年龄_print-age.md) | [输出年龄_print_age.cpp](../../../basic/输出年龄_print_age.cpp) | `variable`、`integer`、`output` |
| [EX0004 保存并输出价格](ex0004_保存并输出价格_print-price.md)<br>[EX0004 Store and print a price](ex0004_保存并输出价格_print-price.md) | [输出价格_print_price.cpp](../../../basic/输出价格_print_price.cpp) | `variable`、`floating-point`、`output` |

<a id="赋值运算符"></a>
## 赋值运算符 / Assignment Operators

| 编号与题目<br>ID and problem | 源码<br>Source | 标签<br>Tags |
| :--- | :--- | :--- |
| [EX0005 推导连续赋值与复合赋值](ex0005_连续赋值与复合赋值_compound-assignment.md)<br>[EX0005 Trace chained and compound assignment](ex0005_连续赋值与复合赋值_compound-assignment.md) | [复合赋值_compound_assignment.cpp](../../../basic/复合赋值_compound_assignment.cpp) | `assignment`、`compound-assignment`、`associativity` |

<a id="源码重命名对照"></a>
## 源码重命名对照 / Source Rename Mapping

下列 5 个源码的文件内容保持不变，仅根据练习实际内容采用双语文件名。历史文件名在此表和对应题目页中保留为检索线索；从此前英文名到当前双语路径的完整对照见仓库 README。

The five source files below retain their original contents; only their filenames now describe their exercise content in both languages. Historical filenames are retained here and on the corresponding problem pages for searching. See the root README for the complete mapping from the previous English filenames to the current bilingual paths.

| 编号<br>ID | 原路径<br>Original path | 当前路径<br>Current path |
| :--- | :--- | :--- |
| EX0001 | `basic/helloicpc.cpp` | [basic/输出问候语_hello_icpc.cpp](../../../basic/输出问候语_hello_icpc.cpp) |
| EX0002 | `basic/age.cpp` | [basic/输出年龄_print_age.cpp](../../../basic/输出年龄_print_age.cpp) |
| EX0003 | `basic/ab.cpp` | [basic/连续输出两个整数_print_adjacent_integers.cpp](../../../basic/连续输出两个整数_print_adjacent_integers.cpp) |
| EX0004 | `basic/double.cpp` | [basic/输出价格_print_price.cpp](../../../basic/输出价格_print_price.cpp) |
| EX0005 | `basic/5.cpp` | [basic/复合赋值_compound_assignment.cpp](../../../basic/复合赋值_compound_assignment.cpp) |

<a id="复习检查"></a>
## 复习检查 / Revision Checklist

- [ ] 能从空文件写出独立的 `main()`，并单独编译运行。<br>
      Write an independent `main()` from an empty file, then compile and run it separately.
- [ ] 能解释连续输出两个整数与求和的区别，并控制空格和换行。<br>
      Explain consecutive integer output versus addition, and control spaces and newlines.
- [ ] 能区分变量名、变量值和带引号的字符串。<br>
      Distinguish variable names, variable values, and quoted strings.
- [ ] 能区分浮点数存储与固定小数位的显示要求。<br>
      Distinguish floating-point storage from fixed-decimal display requirements.
- [ ] 能独立推导 EX0005 的四组结果，把复合赋值拆成易读的语句。<br>
      Independently derive EX0005's four result groups and expand compound assignments into readable statements.
- [ ] 能区分现有源码行为和题目页中的「未实现」拓展练习。<br>
      Distinguish existing source behavior from extensions marked “not implemented” on problem pages.

输出细节：EX0001–EX0004 都没有末尾换行；EX0005 输出四行，每行都有末尾换行。代码块展示的是可见文本，逐字节比较时以各题的说明为准。

Output details: EX0001–EX0004 have no trailing newline; EX0005 prints four lines, each ending with a newline. Code blocks show visible text; follow each problem's notes for byte-for-byte comparison.
