# 基础语法复习

[返回习题总目录](../README.md)

本分类现有 5 道题，均为 C++17 固定数据演示，无标准输入。题面根据源码整理，难度均为本仓库的「入门」级；未知的原题来源未补造。第一次学习推荐按 EX0001 → EX0002 → EX0003 → EX0004 → EX0005 的顺序。

## 基本输出

| 编号与题目 | 源码 | 标签 |
| :--- | :--- | :--- |
| [EX0001 输出问候语](ex0001-hello-icpc.md) | [hello_icpc.cpp](../../../basic/hello_icpc.cpp) | `output`、`string-literal` |
| [EX0003 连续输出两个整数](ex0003-print-adjacent-integers.md) | [print_adjacent_integers.cpp](../../../basic/print_adjacent_integers.cpp) | `output`、`formatting`、`integer` |

## 数据类型与变量

| 编号与题目 | 源码 | 标签 |
| :--- | :--- | :--- |
| [EX0002 保存并输出年龄](ex0002-print-age.md) | [print_age.cpp](../../../basic/print_age.cpp) | `variable`、`integer`、`output` |
| [EX0004 保存并输出价格](ex0004-print-price.md) | [print_price.cpp](../../../basic/print_price.cpp) | `variable`、`floating-point`、`output` |

## 赋值运算符

| 编号与题目 | 源码 | 标签 |
| :--- | :--- | :--- |
| [EX0005 推导连续赋值与复合赋值](ex0005-compound-assignment.md) | [compound_assignment.cpp](../../../basic/compound_assignment.cpp) | `assignment`、`compound-assignment`、`associativity` |

## 源码重命名对照

本次仅按练习实际内容重命名，下列 5 个源码的文件内容保持不变。旧文件名仅在此表和对应题目页中保留为检索线索。

| 编号 | 原路径 | 当前路径 |
| :--- | :--- | :--- |
| EX0001 | `basic/helloicpc.cpp` | [basic/hello_icpc.cpp](../../../basic/hello_icpc.cpp) |
| EX0002 | `basic/age.cpp` | [basic/print_age.cpp](../../../basic/print_age.cpp) |
| EX0003 | `basic/ab.cpp` | [basic/print_adjacent_integers.cpp](../../../basic/print_adjacent_integers.cpp) |
| EX0004 | `basic/double.cpp` | [basic/print_price.cpp](../../../basic/print_price.cpp) |
| EX0005 | `basic/5.cpp` | [basic/compound_assignment.cpp](../../../basic/compound_assignment.cpp) |

## 复习检查

- [ ] 能从空文件写出独立的 `main()`，并单独编译运行。
- [ ] 能解释连续输出两个整数与求和的区别，并控制空格和换行。
- [ ] 能区分变量名、变量值和带引号的字符串。
- [ ] 能区分浮点数存储与固定小数位的显示要求。
- [ ] 能独立推导 EX0005 的四组结果，把复合赋值拆成易读的语句。
- [ ] 能区分现有源码行为和题目页中的「未实现」拓展练习。

输出细节：EX0001–EX0004 都没有末尾换行；EX0005 输出四行，每行都有末尾换行。代码块展示的是可见文本，逐字节比较时以各题的说明为准。
