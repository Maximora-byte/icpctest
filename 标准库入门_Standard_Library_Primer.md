<a id="stdmd从零看懂-c-常用标准库"></a>
# C++ 标准库入门 / C++ Standard Library Primer

这份笔记从六种常见写法开始：`vector` 存数、循环输入、`sort` 排序、`set` 去重、`getline` 读一行、`stringstream` 拆分一行。

These notes begin with six common patterns: storing numbers in a `vector`, reading input in a loop, sorting with `sort`, removing duplicates with `set`, reading a line with `getline`, and splitting a line with `stringstream`.

**目标：不只会复制，还能说清楚每一行在做什么。** 你只需要先接触过变量、`cin`、`cout`、`if` 和 `for`；下面也会简单解释用到的语法。

**Goal: not just to copy code, but to explain what every line does.** You only need some prior exposure to variables, `cin`, `cout`, `if`, and `for`; the syntax used below is also explained briefly.

本文采用中英双语文件名；旧路径与新路径的对应关系见 [仓库 README 的文件名索引](README.md#filename-index)。注意：

This document uses a bilingual filename; the [filename index in the repository README](README.md#filename-index) maps the legacy path to the current path. Keep these distinctions in mind:

- `std` 是 C++ 标准库使用的**命名空间**，可以先理解成工具所属的名字；例如 `std::vector`。<br>`std` is the **namespace** used by the C++ standard library. For now, think of it as the name that a tool belongs to, as in `std::vector`.
- STL 通常指标准模板库，常见内容包括容器、迭代器和算法。先把它们理解成“装数据的盒子”“指向某个位置的标记”“处理数据的工具”就够了。<br>STL usually means the Standard Template Library, whose common components include containers, iterators, and algorithms. For now, think of them as “boxes that hold data,” “markers that point to a position,” and “tools that process data.”
- C++ 标准库还包括输入输出、字符串等内容。这份笔记会一起介绍。<br>The C++ standard library also includes input/output, strings, and more. These notes cover those as well.

<a id="怎么读"></a>
## 怎么读 / How to Read These Notes

**第一次学习，按顺序读必读部分，到第 6 节就可以停。** 每学一个完整示例，先运行，再换几个数试试。选读部分遇到题目需要时再查。

**On your first pass, read the required sections in order and stop after Section 6.** For each complete example, run it first, then try changing a few numbers. Consult the optional sections when a problem calls for them.

<a id="初学必读"></a>
### 初学必读 / Required Reading for Beginners

0. [怎样运行示例、头文件是什么](#start)<br>[How to run the examples and what headers are](#start)
1. [vector：存放一排整数，并输入它们](#vector)<br>[vector: store a row of integers and read them in](#vector)
2. [sort 和 set：排序，再去重](#sort-set)<br>[sort and set: sort, then remove duplicates](#sort-set)
3. [string：整行输入与五种常用操作](#getline)<br>[string: whole-line input and five common operations](#getline)
4. [stringstream：把一行拆成单词或数字](#stringstream)<br>[stringstream: split a line into words or numbers](#stringstream)
5. [cin 后接 getline：为什么会读到空行](#mixed-input)<br>[getline after cin: why an empty line is read](#mixed-input)
   - [把四步串起来：读整行、转小写、拆单词、比较计数](#word-count)<br>[Connect four steps: read a line, lowercase it, split words, and compare and count](#word-count)
   - [char& 为什么能改原字符：联系引用和指针](#char-reference)<br>[Why char& changes the original character: references and pointers](#char-reference)
   - [四种字符串模板：需要原位置时手动扫描](#string-templates)<br>[Four string templates: scan manually when original positions matter](#string-templates)
6. [六种原始写法速查与易错点](#recap)<br>[Quick reference and common mistakes for the six original patterns](#recap)

<a id="按需选读"></a>
### 按需选读 / Optional Reading as Needed

7. [vector 的增删、倒序排序](#more-vector)<br>[Adding and removing vector elements; descending sorting](#more-vector)
8. [保留 vector：sort + unique + erase 去重](#unique)<br>[Keep a vector: remove duplicates with sort + unique + erase](#unique)
9. [二分查找：找有没有、找位置、数出现次数](#binary-search)<br>[Binary search: check existence, find positions, and count occurrences](#binary-search)
   - [lower 和 upper 记忆法：≥、> 与次数 = r - l](#bound-memory-guide)<br>[Remembering lower and upper: ≥, >, and count = r - l](#bound-memory-guide)
   - [手写二分：l、r、mid 三个变量与完整模板](#binary-search-lrmid)<br>[Handwritten binary search: l, r, mid, and complete templates](#binary-search-lrmid)
   - [lower_bound：第一个大于或等于目标的位置](#lower-bound-guide)<br>[lower_bound: the first position greater than or equal to the target](#lower-bound-guide)
   - [边界二分：找到后继续找，求首次或末次出现](#binary-search-first-match)<br>[Boundary binary search: keep searching after a match to find the first or last occurrence](#binary-search-first-match)
   - [二分三种写法速查：普通二分、左边界、lower_bound](#binary-search-cheatsheet)<br>[Three binary-search patterns: ordinary search, left boundary, and lower_bound](#binary-search-cheatsheet)
10. [求和：long long 和 0LL](#sum)<br>[Summation: long long and 0LL](#sum)
11. [map、queue、stack：计数、排队、叠盘子](#containers)<br>[map, queue, and stack: counting, lining up, and stacking plates](#containers)
12. [小练习与提交前检查](#practice)<br>[Short exercises and a pre-submission checklist](#practice)
13. [C 文件读写：按五类选择函数与完整示例](#c-file-io)<br>[C file I/O: choose functions from five categories, with complete examples](#c-file-io)
   - [先判断数据形式：字符、字符串、格式化、二进制数据块](#c-file-function-choice)<br>[Identify the data format first: characters, strings, formatted data, or binary blocks](#c-file-function-choice)
   - [二进制文件读写：wb、rb、fwrite 和 fread](#c-binary-file-io)<br>[Binary file I/O: wb, rb, fwrite, and fread](#c-binary-file-io)

<a id="start"></a>
<a id="0-先学会运行一个示例"></a>
## 0. 先学会运行一个示例 / 0. Learn to Run an Example First

<a id="完整程序和代码片段要分开看"></a>
### 完整程序和代码片段要分开看 / Distinguish Complete Programs from Code Snippets

除第 13 节明确标出的 C 示例外，本文标有“**完整示例**”的代码可以单独复制到 `main.cpp`，选择 **C++17** 编译运行。每次只复制一个完整示例，不要把几个 `main()` 拼在一起。

Except for the explicitly labeled C examples in Section 13, any code labeled **Complete example** can be copied on its own into `main.cpp` and compiled and run as **C++17**. Copy only one complete example at a time; do not combine several `main()` functions.

标有“**片段**”的代码只讲某一行写法，需要放进完整程序的合适位置，不能单独运行。

Code labeled **Snippet** explains a particular piece of syntax. It must be placed appropriately inside a complete program and cannot run on its own.

完整程序一般有这几部分：

A complete program usually contains these parts:

- `#include <vector>`：引入某种工具的声明，叫**头文件**。用什么工具，就包含相应头文件。<br>`#include <vector>`: includes declarations for a tool through a **header**. Include the appropriate header for each tool you use.
- `using namespace std;`：前面的 C++ 短练习都写这一行，于是可以把 `std::cin` 简写成 `cin`。大型项目通常更倾向于明确写 `std::`，避免名字冲突。<br>`using namespace std;`: the introductory short C++ exercises include this line, allowing `std::cin` to be shortened to `cin`. Larger projects generally prefer explicit `std::` prefixes to avoid name collisions.
- `int main() { ... }`：程序从这里开始执行，花括号里的语句从上往下运行。<br>`int main() { ... }`: execution starts here, with the statements inside the braces running from top to bottom.
- `return 0;`：正常结束程序。<br>`return 0;`: ends the program normally.
- `// ...`：注释，是给人看的说明，不会执行。<br>`// ...`: a comment, written for readers rather than executed.
- `cout << value << '\n';`：输出 `value`，然后换行。`'\n'` 是一个换行字符。<br>`cout << value << '\n';`: outputs `value`, then starts a new line. `'\n'` is a newline character.

本文使用标准头文件，不依赖某些编译器才支持的 `bits/stdc++.h`。

These notes use standard headers rather than relying on `bits/stdc++.h`, which only some compilers support.

<a id="用什么头文件"></a>
### 用什么头文件 / Which Headers to Include

| 要用的工具<br>Tool | 头文件<br>Header | 可以先这样理解<br>An initial way to understand it |
| --- | --- | --- |
| `cin`、`cout` | `<iostream>` | 输入和输出<br>Input and output |
| `vector` | `<vector>` | 能调整长度的一排格子<br>A row of slots whose length can change |
| `sort`、`unique`、二分相关函数<br>`sort`, `unique`, and binary-search functions | `<algorithm>` | 常用算法工具<br>Common algorithm tools |
| `set` | `<set>` | 不重复、默认从小到大排列的集合<br>A collection of distinct values, ordered from smallest to largest by default |
| `string`、字符串版本的 `getline`<br>`string` and the string overload of `getline` | `<string>` | 文本和整行读取<br>Text and whole-line input |
| `tolower`、`toupper` | `<cctype>` | 把单个英文字母转成小写 / 大写<br>Convert one English letter to lowercase / uppercase |
| `stringstream` | `<sstream>` | 把已有字符串当作输入来读<br>Read an existing string as input |
| `numeric_limits` | `<limits>` | 查询类型的数值范围，本文用来清理一行输入<br>Query a type's numeric limits; used here to discard the remainder of an input line |
| `accumulate` | `<numeric>` | 从一个初始值开始累加<br>Add values starting from an initial value |
| `map` / `queue` / `stack` | `<map>` / `<queue>` / `<stack>` | 计数表 / 队列 / 栈<br>Counting table / queue / stack |

<a id="编译与运行"></a>
### 编译与运行 / Compiling and Running

如果用编辑器或在线编译器，选择 C++17，把示例输入粘贴到输入区，再运行。不要把“输入”“输出”这些说明文字也粘进去。

In an editor or online compiler, select C++17, paste the example input into the input area, and run the program. Do not also paste explanatory labels such as “Input” or “Output.”

已安装 `g++` 时，也可以在 `main.cpp` 所在目录打开终端：

If `g++` is installed, you can instead open a terminal in the directory containing `main.cpp`:

Linux / macOS：

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp -o main
./main
```

Windows PowerShell：

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp -o main.exe
.\main.exe
```

运行后输入样例，最后按回车。有些示例明确写着“无需输入”，直接运行即可。若提示找不到 `g++`，先按所用编辑器或编译器的安装说明配置 C++ 环境。

After launching the program, enter the sample input and press Enter at the end. Some examples explicitly say “No input required”; simply run those. If `g++` cannot be found, first configure a C++ environment using your editor's or compiler's installation instructions.

本文的数字输入示例假设输入符合题目格式，整数在相应类型范围内，且数据量能放进内存。前几例额外检查 `n` 能否读取及是否为负数，帮助避免直接创建错误长度的容器；这不是完整的输入校验程序。

The numeric-input examples assume that the input follows the problem's format, that integers fit in their respective types, and that the data fits in memory. The first few examples additionally check whether `n` was read successfully and whether it is negative, helping avoid creating a container with an invalid length. These are not complete input-validation programs.

<a id="vector"></a>
<a id="1-vector存放一排整数"></a>
## 1. vector：存放一排整数 / 1. vector: Store a Row of Integers

**什么时候用：** 要保存多个同类型的值，例如一组分数，后面还要排序、访问或修改。

**When to use it:** To store multiple values of the same type, such as a set of scores, for later sorting, access, or modification.

需要 `<vector>`；输入输出还需要 `<iostream>`。

Requires `<vector>`; input and output also require `<iostream>`.

<a id="先看原来的写法"></a>
### 先看原来的写法 / Start with the Original Pattern

**片段：** 假设 `n` 已经是一个非负整数。

**Snippet:** Assume that `n` is already a nonnegative integer.

```cpp
vector<int> v(n);
for (int i = 0; i < n; i++) {
    cin >> v[i];
}
```

逐段拆开：

Break it down piece by piece:

- `vector`：容器的种类。<br>`vector`: the kind of container.
- `<int>`：每个格子存一个整数。<br>`<int>`: each slot stores one integer.
- `v`：你给这排格子取的名字，可以换成 `scores`、`numbers`。<br>`v`: your name for this row of slots; you could use `scores` or `numbers` instead.
- `(n)`：创建 **n 个已经存在的元素**。这里每个 `int` 初始都是 `0`。<br>`(n)`: creates **n elements that already exist**. Each `int` here initially contains `0`.
- `v[i]`：访问下标为 `i` 的元素。**下标从 0 开始**，不是从 1 开始。<br>`v[i]`: accesses the element at index `i`. **Indices start at 0**, not 1.

例如 `n = 3`，合法位置是 `v[0]`、`v[1]`、`v[2]`。`v[3]` 已经越界，不能访问。

For example, if `n = 3`, the valid positions are `v[0]`, `v[1]`, and `v[2]`. `v[3]` is already out of bounds and must not be accessed.

`for (int i = 0; i < n; i++)` 表示：

`for (int i = 0; i < n; i++)` means:

1. 一开始令 `i = 0`。<br>Initially set `i = 0`.
2. 只要 `i < n`，就执行花括号里的输入。<br>As long as `i < n`, execute the input statement inside the braces.
3. `i++` 让 `i` 加 1，再检查条件。<br>`i++` increases `i` by 1, then the condition is checked again.
4. `i` 变成 `n` 时停止，所以一共读入 n 个数。<br>Stop when `i` reaches `n`, so exactly n numbers are read.

<a id="完整示例-1读入并原样输出"></a>
### 完整示例 1：读入并原样输出 / Complete Example 1: Read Values and Output Them Unchanged

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = 0;
    if (!(cin >> n) || n < 0) {
        return 0;
    }

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << v[i];
    }
    cout << '\n';
    return 0;
}
```

**输入**（第一项是数量，后面恰好有 5 个整数）：

**Input** (the first item is the count, followed by exactly 5 integers):

```text
5
8 3 8 1 5
```

**输出**：

**Output**:

```text
8 3 8 1 5
```

`!(cin >> n)` 表示读取失败；`||` 表示“或者”。这一段 `if` 的意思是：读不到数量，或者数量为负，就结束程序。正常输入时会继续往下执行。

`!(cin >> n)` indicates that reading failed; `||` means “or.” This `if` means: end the program if the count cannot be read or is negative. With normal input, execution continues below.

`if (i > 0)` 用来在第二个及之后的数字前输出空格，避免数字挤成 `83815`。`cin >>` 读取整数时会跳过空格和换行，所以这 5 个数也可以分成几行输入。

`if (i > 0)` prints a space before the second and subsequent numbers so they do not run together as `83815`. When reading integers, `cin >>` skips spaces and newlines, so these 5 numbers can also be entered across several lines.

**最容易踩的坑：** `int n; vector<int> v(n);` 中的 `n` 尚未赋值，不能拿来当长度。应先读入并检查 `n`，再创建 `v`。

**A common pitfall:** In `int n; vector<int> v(n);`, `n` has not been assigned a value and must not be used as a length. Read and check `n` first, then create `v`.

<a id="sort-set"></a>
<a id="2-sort-和-set排序再去重"></a>
## 2. sort 和 set：排序，再去重 / 2. sort and set: Sort, Then Remove Duplicates

<a id="sort让原来的-vector-排好序"></a>
### sort：让原来的 vector 排好序 / sort: Sort the Original vector

需要 `<algorithm>`。

Requires `<algorithm>`.

**片段：** 假设 `v` 是已经有数据的 `vector<int>`。

**Snippet:** Assume that `v` is a `vector<int>` that already contains data.

```cpp
sort(v.begin(), v.end());
```

这一行直接修改 `v`，默认从小到大排序。`8 3 8 1 5` 会变成 `1 3 5 8 8`，重复值还在。

This line modifies `v` directly, sorting in ascending order by default. `8 3 8 1 5` becomes `1 3 5 8 8`; duplicate values remain.

`begin()` 和 `end()` 返回的东西叫**迭代器**。初学时把它想成“位置标记”：

The values returned by `begin()` and `end()` are called **iterators**. As a beginner, think of them as “position markers”:

- `v.begin()`：开始位置。<br>`v.begin()`: the starting position.
- `v.end()`：最后一个元素**后面**的位置，不是最后一个元素。<br>`v.end()`: the position **after** the last element, not the last element itself.
- `[begin, end)`：包含开头、不包含结尾，叫**左闭右开区间**。所以这一对位置正好表示整个 `v`。<br>`[begin, end)`: includes the beginning but excludes the end, a **half-open interval**. This pair of positions therefore represents all of `v`.

不要读取 `v.end()` 指向的值，它不是一个元素。空 `vector` 的 `begin()` 等于 `end()`，排序空区间是允许的。

Do not read a value through `v.end()`; it does not refer to an element. An empty `vector` has equal `begin()` and `end()` iterators, and sorting an empty range is allowed.

<a id="set生成一个不含重复值的集合"></a>
### set：生成一个不含重复值的集合 / set: Create a Collection Without Duplicate Values

需要 `<set>`。

Requires `<set>`.

**片段：** 假设 `v` 已经有数据。

**Snippet:** Assume that `v` already contains data.

```cpp
set<int> unique_values(v.begin(), v.end());
```

这一行把 `v` 里的元素放进一个新 `set`：

This line puts the elements of `v` into a new `set`:

- 同样的数只保留一份。<br>Only one copy of each distinct number is kept.
- 这里的 `set<int>` 遍历时默认从小到大。<br>This `set<int>` is traversed in ascending order by default.
- **原来的 `v` 不变**，重复值仍然在 `v` 里。<br>**The original `v` is unchanged**; duplicate values remain in `v`.
- 创建 `set` 前不要求 `v` 有序；下面先排序只是为了展示两步的不同效果。<br>`v` does not have to be sorted before creating a `set`. Sorting first below simply demonstrates the different effects of the two steps.
- 它不会保留原来的输入顺序，也不能像 `vector` 那样写 `unique_values[0]`。<br>It does not preserve the original input order, and you cannot write `unique_values[0]` as you would with a `vector`.

<a id="完整示例-2观察排序和去重的区别"></a>
### 完整示例 2：观察排序和去重的区别 / Complete Example 2: Compare Sorting with Removing Duplicates

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int n = 0;
    if (!(cin >> n) || n < 0) {
        return 0;
    }
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end());
    cout << "sorted:";
    for (int value : v) {
        cout << ' ' << value;
    }
    cout << '\n';

    set<int> unique_values(v.begin(), v.end());
    cout << "unique:";
    for (int value : unique_values) {
        cout << ' ' << value;
    }
    cout << '\n';
    return 0;
}
```

**输入**：

**Input**:

```text
5
8 3 8 1 5
```

**输出**：

**Output**:

```text
sorted: 1 3 5 8 8
unique: 1 3 5 8
```

`for (int value : v)` 叫**范围 for 循环**：依次把 `v` 里的元素复制给 `value`，每拿到一个就执行一次循环体。这里用来输出，不需要自己维护下标，也适用于 `set`。

`for (int value : v)` is a **range-based for loop**: it copies each element of `v` into `value` in turn and executes the loop body once for each element. Here it is used for output, so you do not need to maintain an index yourself. It also works with a `set`.

记住：**排序不等于去重；set 去重不等于修改 vector。**

Remember: **sorting does not remove duplicates, and deduplicating into a set does not modify the vector.**

<a id="getline"></a>
<a id="3-string整行输入与五种常用操作"></a>
## 3. string：整行输入与五种常用操作 / 3. string: Whole-Line Input and Five Common Operations

<a id="先记住这张五工具速查表"></a>
### 先记住这张五工具速查表 / Start with This Five-Tool Quick Reference

下面假设已经声明 `string text;`。`string` 是**类型名**，`text` 才是你给字符串起的**变量名**；笔记里的“`string[i]` 访问字符”实际应写成 `text[i]`，不能直接把类型名当变量用。

Assume below that `string text;` has been declared. `string` is the **type name**; `text` is the **variable name** you give the string. A note saying “access a character with `string[i]`” should actually use `text[i]`; a type name cannot be used directly as a variable.

| 工具<br>Tool | 实际写法<br>Actual syntax | 用途<br>Purpose |
| --- | --- | --- |
| `getline()` | `getline(cin, text)` | 读取整行，保留行内空格<br>Read a whole line while preserving spaces within it |
| `tolower()` | `tolower(...)`，安全的完整写法见下文<br>`tolower(...)`; see the complete safe form below | 把**单个字符**转小写，整串要用循环<br>Lowercase **one character**; use a loop for a whole string |
| 下标 `[]`<br>Subscript `[]` | `text[i]` | 访问下标为 `i` 的字符，下标从 0 开始<br>Access the character at index `i`; indices start at 0 |
| `substr()` | `text.substr(pos, count)` | 从下标 `pos` 开始，最多截取 `count` 个字符<br>Extract at most `count` characters starting at index `pos` |
| `size()` | `text.size()` | 获取当前长度，空格也计入<br>Obtain the current length, including spaces |

`text.size()` 和 `text.substr(...)` 中的点表示“使用 `text` 自己的操作”；`getline`、`tolower` 则直接调用。字符串相关操作需要 `<string>`，`tolower` 另需 `<cctype>`，输入输出需要 `<iostream>`。

The dot in `text.size()` and `text.substr(...)` means “use an operation belonging to `text`”; `getline` and `tolower` are called directly. String-related operations require `<string>`, `tolower` additionally requires `<cctype>`, and input/output requires `<iostream>`.

这一节先用英文、数字和空格来理解“字符”。严格说，`std::string` 存的是一串 `char`，`size()` 统计的是这些存储单元的数量；UTF-8 中文通常占多个字节，所以这里的长度、下标和截取**不能直接当作汉字个数或汉字位置**。

This section uses English letters, digits, and spaces to introduce “characters.” Strictly speaking, `std::string` stores a sequence of `char` values, and `size()` counts those storage units. Chinese characters encoded in UTF-8 usually occupy multiple bytes, so lengths, indices, and substrings here **cannot be interpreted directly as counts or positions of Chinese characters**.

<a id="getline读取完整一行"></a>
### getline：读取完整一行 / getline: Read a Whole Line

**什么时候用：** 一行文本中可能有空格，例如 `hello ICPC world`。

**When to use it:** When a line of text may contain spaces, such as `hello ICPC world`.

需要 `<string>` 和 `<iostream>`。

Requires `<string>` and `<iostream>`.

- `cin >> word`：读一个以空白分隔的字符串，遇到空格、制表符或换行就停。<br>`cin >> word`: reads one whitespace-delimited string, stopping at a space, tab, or newline.
- `getline(cin, line)`：读到这一行结束，保留行内空格；消耗结尾的换行，但不把换行放进 `line`。<br>`getline(cin, line)`: reads to the end of the line, preserving spaces within it; it consumes the trailing newline without storing it in `line`.

**片段：** 单独读一行时这样写。

**Snippet:** Use this when reading a line on its own.

```cpp
string line;
getline(cin, line);
```

这里的 `line` 必须是 `string`。你前面若写了 `set<int> s`，就不能拿同一个 `s` 去做 `getline(cin, s)`。即使都起名为 `s`，集合和字符串也不是同一种类型，而且同一个作用域不能重复声明同名变量。

Here, `line` must be a `string`. If you previously wrote `set<int> s`, you cannot use that same `s` in `getline(cin, s)`. Even if both are named `s`, a set and a string are different types; moreover, two variables with the same name cannot be declared in the same scope.

建议集合用 `unique_values`，整行文本用 `line`，一眼就能认出用途。

Use `unique_values` for the set and `line` for a whole line of text, so their purposes are immediately clear.

<a id="完整示例-3保留行内空格"></a>
### 完整示例 3：保留行内空格 / Complete Example 3: Preserve Spaces Within a Line

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    getline(cin, line);
    cout << '[' << line << ']' << '\n';
    return 0;
}
```

**输入**：

**Input**:

```text
hello ICPC world
```

**输出**：

**Output**:

```text
[hello ICPC world]
```

方括号只是让文本的边界更明显。如果输入空行，输出就是 `[]`。如果先用 `cin >> n` 读了数字，再读下一行，请看第 5 节，不能直接照搬这两行。

The square brackets simply make the text's boundaries clearer. An empty input line produces `[]`. If you first read a number using `cin >> n` and then want the next line, see Section 5 rather than copying these two lines unchanged.

<a id="size-和-texti先知道有多长再按位置取字符"></a>
### size 和 text[i]：先知道有多长，再按位置取字符 / size and text[i]: Find the Length, Then Access Characters by Position

把 `string text = "Hello ICPC!";` 想成一排格子：

Think of `string text = "Hello ICPC!";` as a row of slots:

| 下标<br>Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 字符<br>Character | H | e | l | l | o | 空格<br>Space | I | C | P | C | ! |

- `text.size()` 是 `11`，中间的空格和末尾的 `!` 都算一个字符。<br>`text.size()` is `11`; both the space in the middle and the final `!` count as one character.
- `text[0]` 是 `'H'`，`text[6]` 是 `'I'`。单引号表示一个 `char`，双引号表示字符串文本。<br>`text[0]` is `'H'`, and `text[6]` is `'I'`. Single quotes denote a `char`; double quotes denote string text.
- 对长度为 `n` 的非空字符串，正文字符的下标是 **0 到 n - 1**。遍历条件写 `i < text.size()`，不要写 `<=`。<br>For a nonempty string of length `n`, the content characters have indices **0 through n - 1**. Use `i < text.size()` as the traversal condition, not `<=`.
- `text.empty()` 判断是否为空。空字符串的 `size()` 是 `0`，没有正文字符，不要去取“第一个”或“最后一个”字符。<br>`text.empty()` checks whether the string is empty. An empty string has `size()` equal to `0` and no content characters; do not try to access its “first” or “last” character.
- `size()` 返回无符号整数类型。别在空字符串上计算 `text.size() - 1`，它不会得到想象中的 `-1`。<br>`size()` returns an unsigned integer type. Do not calculate `text.size() - 1` for an empty string; the result is not the `-1` you might expect.

`[]` 不会替你检查范围。C++17 中，`text[text.size()]` 是结尾的空字符 `\0`，**不是正文字符，也不能拿来添加字符**；更大的下标越界。初学时统一只在 `i < text.size()` 时访问正文即可。想让越界访问抛出异常，可以用 `text.at(i)`，但仍应先写对范围。

`[]` does not check bounds for you. In C++17, `text[text.size()]` is the terminating null character `\0`, **not a content character and not a place to append a character**; any larger index is out of bounds. As a beginner, simply access content only when `i < text.size()`. You can use `text.at(i)` to throw an exception on out-of-range access, but you should still get the range right first.

<a id="tolower一次只处理一个字符"></a>
### tolower：一次只处理一个字符 / tolower: Process One Character at a Time

需要 `<cctype>`。例如 `'A'` 可以变成 `'a'`；小写英文、数字、空格和标点保持原样。它**不会直接接收整个 string**，也不会自动把结果写回原变量。

Requires `<cctype>`. For example, `'A'` can become `'a'`; lowercase English letters, digits, spaces, and punctuation remain unchanged. It **does not directly accept an entire string**, nor does it automatically write the result back to the original variable.

**片段：** 安全地转换一个字符，并保存结果。

**Snippet:** Safely convert one character and save the result.

```cpp
char ch = 'A';
ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
```

从内往外读这一长行：

Read this long line from the inside out:

1. `static_cast<unsigned char>(ch)`：先把 `ch` 转成 `unsigned char`，再交给 `tolower`。有些机器的普通 `char` 能为负数，直接传入这样的值可能产生未定义行为；这一步避免这个问题。<br>`static_cast<unsigned char>(ch)`: first converts `ch` to `unsigned char`, then passes it to `tolower`. On some machines, plain `char` can hold negative values; passing such a value directly may cause undefined behavior. This step avoids that problem.
2. `tolower(...)`：得到转换结果。它的返回类型是 `int`，不是 `string`。<br>`tolower(...)`: obtains the converted result. Its return type is `int`, not `string`.
3. `static_cast<char>(...)`：把结果转回 `char`，再用 `ch =` 保存；此时 `ch` 是 `'a'`。<br>`static_cast<char>(...)`: converts the result back to `char`, then `ch =` saves it. `ch` is now `'a'`.

整串转换时，把这一步放进循环，对每个字符做一次。下面的完整示例会演示。

To convert an entire string, put this step in a loop and perform it once for every character. The complete example below demonstrates this.

**适用范围：** 这里主要处理竞赛题里的英文字母。`tolower` 的规则受当前 C locale（字符分类和转换规则）影响；本例没有改变它。它不是通用的 Unicode 大小写转换工具，不能把 UTF-8 文本逐字节传进去就当作完成了所有语言的大小写转换。

**Scope:** Here, the main use is English letters in programming-contest problems. `tolower` follows the current C locale, which defines character classification and conversion rules; this example does not change it. It is not a general Unicode case-conversion tool: feeding it UTF-8 text byte by byte does not implement case conversion for all languages.

<a id="substr起点--数量不是起点--终点"></a>
### substr：起点 + 数量，不是起点 + 终点 / substr: Starting Position + Count, Not Starting Position + End Position

仍假设 `text` 是 `"Hello ICPC!"`：

Again, assume that `text` is `"Hello ICPC!"`:

| 写法<br>Expression | 结果<br>Result | 为什么<br>Why |
| --- | --- | --- |
| `text.substr(0, 5)` | `"Hello"` | 从下标 0 开始，取 5 个<br>Start at index 0 and take 5 characters |
| `text.substr(6, 4)` | `"ICPC"` | 从下标 6 开始，取 4 个，不是取到下标 4<br>Start at index 6 and take 4 characters, rather than ending at index 4 |
| `text.substr(6)` | `"ICPC!"` | 省略数量，就取到末尾<br>Omitting the count takes everything to the end |
| `text.substr(6, 100)` | `"ICPC!"` | 数量超过剩余长度，只取剩下的部分<br>If the count exceeds the remaining length, take only what remains |
| `text.substr(text.size(), 3)` | `""` | 起点正好在末尾，得到空字符串<br>Starting exactly at the end produces an empty string |

`substr` 返回一个**新字符串**，原来的 `text` 不变。想保存结果，可以写 `string part = text.substr(6, 4);`。

`substr` returns a **new string**; the original `text` is unchanged. To save the result, write `string part = text.substr(6, 4);`.

边界记住三点：

Remember three boundary rules:

- `pos` 必须满足 `0 <= pos <= text.size()`；若 `pos > text.size()`，会抛出 `std::out_of_range` 异常，没处理时程序会结束。<br>`pos` must satisfy `0 <= pos <= text.size()`. If `pos > text.size()`, a `std::out_of_range` exception is thrown; if unhandled, it terminates the program.
- 起点合法时，`count = 0` 得到空字符串；数量太大只会截到末尾。<br>With a valid starting position, `count = 0` produces an empty string; an excessive count simply stops at the end.
- 空字符串可以写 `text.substr(0, 5)`，结果仍为空；不能写 `text.substr(1)`。起点和数量都不要传负数，它们会转成无符号数，不表示“从后面数”。<br>For an empty string, `text.substr(0, 5)` is valid and still returns an empty string, but `text.substr(1)` is not valid. Do not pass negative values for the position or count: they convert to unsigned values and do not mean “count from the end.”

<a id="完整示例-3a五个工具一起用"></a>
### 完整示例 3A：五个工具一起用 / Complete Example 3A: Use All Five Tools Together

读一行，输出长度和原来的首字符，再转成小写，最后截取前 5 个字符。空行也能安全处理。

Read one line, output its length and original first character, convert it to lowercase, and finally extract the first 5 characters. Empty lines are also handled safely.

```cpp
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text;
    if (!getline(cin, text)) {
        return 0;
    }

    cout << "length: " << text.size() << '\n';
    if (!text.empty()) {
        cout << "first: [" << text[0] << "]\n";
    } else {
        cout << "first: (empty)\n";
    }

    for (string::size_type i = 0; i < text.size(); ++i) {
        text[i] = static_cast<char>(tolower(static_cast<unsigned char>(text[i])));
    }

    cout << "lower: [" << text << "]\n";
    cout << "prefix: [" << text.substr(0, 5) << "]\n";
    return 0;
}
```

**输入**：

**Input**:

```text
Hello ICPC!
```

**输出**：

**Output**:

```text
length: 11
first: [H]
lower: [hello icpc!]
prefix: [hello]
```

按顺序理解：

Understand the steps in order:

1. `getline` 读取整行；前面的 `!` 检查是否读取失败。输入空行会成功读到空字符串，并继续执行；完全没有输入才会在这里结束。<br>`getline` reads the whole line; the preceding `!` checks whether reading failed. An empty line successfully produces an empty string and execution continues; no input at all makes the program stop here.
2. `size()` 输出长度。先用 `!text.empty()` 确认非空，再读取 `text[0]`，所以空行不会误取首字符。<br>`size()` outputs the length. Checking `!text.empty()` before reading `text[0]` prevents incorrectly accessing a first character when the line is empty.
3. `string::size_type` 是字符串长度和下标使用的无符号整数类型，与 `size()` 的结果类型一致。循环从 0 开始，`++i` 每轮加 1，直到 `i == text.size()` 停止；空行时循环一次也不执行。<br>`string::size_type` is the unsigned integer type used for string lengths and indices, matching the return type of `size()`. The loop starts at 0, `++i` adds 1 each iteration, and it stops when `i == text.size()`. For an empty line, it never executes.
4. 每轮把 `text[i]` 转成小写并写回同一位置，所以最后整个 `text` 都是转换后的内容。<br>Each iteration lowercases `text[i]` and writes it back to the same position, so all of `text` eventually contains the converted content.
5. `text.substr(0, 5)` 取最多前 5 个字符；少于 5 个就全部取出，空行则得到空字符串。它没有把 `text` 变短。<br>`text.substr(0, 5)` takes at most the first 5 characters. If fewer than 5 exist, it takes all of them; an empty line yields an empty string. It does not shorten `text` itself.

可以再试输入一行 `A`：长度是 `1`，首字符是 `A`，转换后和截取结果都是 `a`。直接按回车输入空行时，长度是 `0`，首字符一行显示 `first: (empty)`，后两行的方括号都是 `[]`。

Try entering a line containing `A`: the length is `1`, the first character is `A`, and both the converted text and the extracted prefix are `a`. If you press Enter immediately to input an empty line, the length is `0`, the first-character line displays `first: (empty)`, and the final two lines both contain `[]`.

<a id="stringstream"></a>
<a id="4-stringstream把一行拆开读"></a>
## 4. stringstream：把一行拆开读 / 4. stringstream: Read a Line Piece by Piece

**什么时候用：** 已经得到一整行文本，想从里面逐个提取单词或数字。

**When to use it:** When you already have an entire line of text and want to extract individual words or numbers from it.

需要 `<sstream>`；字符串需要 `<string>`。

Requires `<sstream>`; strings require `<string>`.

**片段：** 假设 `line` 已经存好一行文本。

**Snippet:** Assume that `line` already contains a line of text.

```cpp
stringstream ss(line);
string word;
while (ss >> word) {
    cout << word << '\n';
}
```

逐行理解：

Understand it line by line:

1. `stringstream ss(line);`：创建一个叫 `ss` 的输入工具，让它从字符串 `line` 中读内容。<br>`stringstream ss(line);`: creates an input tool named `ss` that reads content from the string `line`.
2. `string word;`：准备一个变量存每次读到的单词。<br>`string word;`: prepares a variable to hold each word read.
3. `ss >> word`：试着读下一个单词。它读的是字符串，不是继续等键盘输入。<br>`ss >> word`: tries to read the next word. It reads from the string rather than waiting for more keyboard input.
4. `while (...)`：只要读取成功就执行一次花括号里的代码；读完后自动结束。<br>`while (...)`: executes the code inside the braces each time reading succeeds, and stops automatically when reading is finished.

它会把连续空格、制表符等空白当作分隔。它**不会自动按逗号分割**，所以 `red,blue` 会被当成一个单词。

Consecutive spaces, tabs, and other whitespace act as delimiters. It **does not automatically split on commas**, so `red,blue` is treated as one word.

<a id="完整示例-4一行变成多个单词"></a>
### 完整示例 4：一行变成多个单词 / Complete Example 4: Turn One Line into Multiple Words

```cpp
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string line;
    getline(cin, line);

    stringstream ss(line);
    string word;
    while (ss >> word) {
        cout << word << '\n';
    }
    return 0;
}
```

**输入**（`love` 与 `ICPC` 之间有两个空格）：

**Input** (there are two spaces between `love` and `ICPC`):

```text
I love  ICPC
```

**输出**：

**Output**:

```text
I
love
ICPC
```

如果要提取整数，把接收变量改成 `int x;`，再写 `while (ss >> x)`；可能超出 `int` 范围时用 `long long x;`。**x 必须先声明类型**，不能直接复制一个从未声明过的 `x`。

To extract integers, change the receiving variable to `int x;` and use `while (ss >> x)`. Use `long long x;` if values might exceed the range of `int`. **Declare the type of x first**; you cannot simply copy code using an undeclared `x`.

读整数时，遇到无法继续解析为整数的内容或超出该类型范围的数字，会读取失败，循环停止。例如 `10 abc 20` 用整数方式只会读到 `10`，不会跳过 `abc` 再继续读 `20`。`stringstream` 不是完整的格式检查器；题目若规定“这一行全是整数”，应按这个前提使用。

When reading integers, content that cannot be parsed as an integer, or a number outside the type's range, makes extraction fail and the loop stop. For example, integer extraction from `10 abc 20` reads only `10`; it does not skip `abc` and continue to `20`. `stringstream` is not a complete format validator. If the problem specifies that “this line contains only integers,” use it under that assumption.

<a id="mixed-input"></a>
<a id="5-cin-后接-getline为什么会读到空行"></a>
## 5. cin 后接 getline：为什么会读到空行 / 5. getline After cin: Why an Empty Line Is Read

假设输入格式是：第一行一个编号，第二行若干整数。

Suppose the input format is an ID on the first line and several integers on the second.

`cin >> id` 读走编号后，第一行末尾的换行通常还在输入中。这时立刻 `getline(cin, line)`，它读到这个换行就结束，于是得到空字符串。

After `cin >> id` reads the ID, the newline at the end of the first line usually remains in the input. Calling `getline(cin, line)` immediately afterward reaches that newline and stops, producing an empty string.

<a id="推荐做法明确丢掉第一行的剩余内容"></a>
### 推荐做法：明确丢掉第一行的剩余内容 / Recommended Approach: Explicitly Discard the Remainder of the First Line

**片段：** `id` 是已声明的整数，`line` 是已声明的字符串；另需 `<limits>`。

**Snippet:** `id` is a declared integer and `line` is a declared string; `<limits>` is also required.

```cpp
cin >> id;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, line);
```

中间这一长行可以先整体记住：**一直丢弃字符，直到遇到并丢掉下一个换行**。`numeric_limits<streamsize>::max()` 提供足够大的忽略上限。

For now, remember the long middle line as one operation: **discard characters until the next newline is encountered and discarded too**. `numeric_limits<streamsize>::max()` supplies a sufficiently large ignore limit.

只在“上一行剩余内容不要了，真正要读的是下一行”时这样做。如果编号和有用文本就在同一行，这样写会把文本一起丢掉。

Only do this when “the rest of the previous line is unwanted, and the real text to read is on the next line.” If the ID and useful text are on the same line, this discards that text too.

<a id="完整示例-5先读编号再把下一行的整数求和"></a>
### 完整示例 5：先读编号，再把下一行的整数求和 / Complete Example 5: Read an ID, Then Sum the Integers on the Next Line

```cpp
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
using namespace std;

int main() {
    int id = 0;
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string line;
    getline(cin, line);
    stringstream ss(line);

    long long x = 0;
    long long total = 0;
    while (ss >> x) {
        total += x;
    }

    cout << "id: " << id << '\n';
    cout << "sum: " << total << '\n';
    return 0;
}
```

**输入**：

**Input**:

```text
7
10 20 30
```

**输出**：

**Output**:

```text
id: 7
sum: 60
```

`total += x` 等价于 `total = total + x`。这段假定第二行每个整数，以及累加途中和最终得到的总和，都在 `long long` 范围内。第二行若是空行，一个数也读不到，和保持为 `0`。

`total += x` is equivalent to `total = total + x`. This code assumes that each integer on the second line, every intermediate sum, and the final total fit within `long long`. If the second line is empty, no numbers are read and the sum remains `0`.

<a id="另一种写法先知道限制再用"></a>
### 另一种写法，先知道限制再用 / An Alternative: Understand Its Limits First

**片段：** `line` 是 `string`。

**Snippet:** `line` is a `string`.

```cpp
getline(cin >> ws, line);
```

`ws` 会先跳过**所有连续空白**，包括多个换行以及有意保留的行首空格。因此：

`ws` first skips **all consecutive whitespace**, including multiple newlines and any leading spaces you intended to preserve. Therefore:

- 不在意空行、行首空格时，这种写法方便。<br>This form is convenient if empty lines and leading spaces do not matter.
- 要保留空行或行首空格时，用前面的 `ignore(..., '\n')`，并确认输入格式确实是“读下一行”。<br>To preserve empty lines or leading spaces, use the earlier `ignore(..., '\n')` and make sure the format really calls for “reading the next line.”
- 如果从程序开始就一直用 `getline`，通常不需要额外清理换行。<br>If you use `getline` consistently from the start of the program, extra newline cleanup is usually unnecessary.

不要用“先随便 `getline` 一次”当万能修复，它可能把真正需要的那一行读走。

Do not treat “call `getline` once just to clear something” as a universal fix; it may consume the very line you need.

<a id="word-count"></a>
<a id="把四步串起来读整行--转小写--拆单词--比较"></a>
### 把四步串起来：读整行 → 转小写 → 拆单词 → 比较 / Connect Four Steps: Read a Line → Lowercase It → Split Words → Compare

**想完成什么：** 第一行输入一个英文目标词，第二行输入一整行文本，统计目标词出现几次，忽略英文字母大小写。例如查找 `Hello`，`hello` 和 `HELLO` 都算，但 `helloworld` 不算。

**What we want to do:** Read an English target word from the first line and a whole line of text from the second, then count occurrences of the target while ignoring English letter case. For example, when searching for `Hello`, both `hello` and `HELLO` count, but `helloworld` does not.

下面四步都是**片段**，最后有一份可以直接运行的完整程序。它们使用同一组变量：`word` 是目标词，`text` 是整行文本，`temp` 是每次拆出的词。

The following four steps are **snippets**, followed by a complete program you can run directly. They share the same variables: `word` is the target word, `text` is the whole line of text, and `temp` holds each extracted word.

<a id="第-1-步读完整一行"></a>
#### 第 1 步：读完整一行 / Step 1: Read a Whole Line

**片段：** 输入格式是“第一行目标词，第二行文本”，需要 `<iostream>`、`<string>`、`<limits>`。

**Snippet:** The input format is “target word on the first line, text on the second”; requires `<iostream>`, `<string>`, and `<limits>`.

```cpp
string word;
string text;
cin >> word;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, text);
```

你可能见过更短的 `cin.ignore();`。**不带参数时，它最多只丢掉 1 个字符**：只有当前紧接着一个待清理的换行时，才刚好符合这里的用途。如果第一行目标词后还有空格，它可能只丢掉一个空格，后面的 `getline` 仍会读到第一行剩余内容。

You may have seen the shorter `cin.ignore();`. **With no arguments, it discards at most 1 character**: it serves our purpose only if the very next character is the newline to be cleared. If spaces follow the target word on the first line, it may discard just one space, leaving `getline` to read the rest of the first line.

这里用 `ignore(..., '\n')` 明确清理第一行的剩余内容，再读第二行。它的适用前提仍是“有用文本在下一行”；目标词和文本在同一行时，这样写会把文本丢掉。若从头到尾都用 `getline`，也不要无缘无故先 `ignore()`，否则可能吞掉有用字符。

Here, `ignore(..., '\n')` explicitly clears the rest of the first line before reading the second. It still assumes that “the useful text is on the next line”; if the target and text are on the same line, this discards the text. If you use `getline` throughout, do not call `ignore()` first for no reason, because it may swallow useful characters.

<a id="第-2-步把文本和目标词都转成小写"></a>
#### 第 2 步：把文本和目标词都转成小写 / Step 2: Convert Both the Text and Target Word to Lowercase

**片段：** `text`、`word` 已有内容；另需 `<cctype>`。

**Snippet:** `text` and `word` already contain text; `<cctype>` is also required.

```cpp
for (char& c : text) {
    c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
}
for (char& c : word) {
    c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
}
```

- `for (char& c : text)`：依次处理 `text` 中的每个字符；你见到的 `s` 只是另一个变量名，这里统一叫 `text`。<br>`for (char& c : text)`: processes each character of `text` in turn. Any `s` you have seen is simply a different variable name; here we consistently use `text`.
- `char&` 中的 `&` 表示**引用**，可以理解成“给原来的那个字符起别名”。修改 `c`，就是修改字符串里的那个字符。<br>The `&` in `char&` denotes a **reference**: think of it as giving the original character another name. Changing `c` changes that character in the string.
- 若写成 `for (char c : text)`，`c` 是一份副本，修改它不会让原来的 `text` 变小写。<br>With `for (char c : text)`, `c` is a copy, so changing it does not lowercase the original `text`.
- `word` 也要做同样的转换；只转换文本，目标词 `Hello` 仍然无法和 `hello` 相等。<br>Apply the same conversion to `word` too. If you convert only the text, the target `Hello` still cannot equal `hello`.

安全转换的内外两层 `static_cast` 和非 Unicode 限制，见[第 3 节的 tolower 说明](#getline)。这里仍按英文大小写转换来理解。

For the inner and outer `static_cast` operations used for safe conversion and the non-Unicode limitation, see the [tolower explanation in Section 3](#getline). Here, too, think of this as English letter-case conversion.

<a id="第-3-步从整行里逐个取词"></a>
#### 第 3 步：从整行里逐个取词 / Step 3: Extract Words from the Whole Line One at a Time

**片段：** `text` 已转成小写；另需 `<sstream>`。

**Snippet:** `text` has been converted to lowercase; `<sstream>` is also required.

```cpp
stringstream ss(text);
string temp;
while (ss >> temp) {
    // 每成功取出一个新词，就在这里处理这个 temp。
}
```

`ss` 从已有的 `text` 中读，不是再等键盘输入。`while (ss >> temp)` 每次先尝试读取**下一个新词**：成功才进入循环体，读完或读取失败就停止。不要把取词放在循环外只做一次，也不要在循环结束后再拿旧的 `temp` 多统计一次。

`ss` reads from the existing `text`, rather than waiting for more keyboard input. Each evaluation of `while (ss >> temp)` first attempts to read **the next new word**: the body runs only on success, and the loop stops at the end or on a read failure. Do not extract only once outside the loop, and do not count the old `temp` again after the loop finishes.

连续空格、制表符等空白会被跳过，不会生成“空单词”。第二行为空或只有空白时，循环一次也不执行。更多拆分规则见[第 4 节](#stringstream)。

Consecutive spaces, tabs, and other whitespace are skipped and do not produce “empty words.” If the second line is empty or contains only whitespace, the loop never runs. For more splitting rules, see [Section 4](#stringstream).

<a id="第-4-步比较当前词相等就计数"></a>
#### 第 4 步：比较当前词，相等就计数 / Step 4: Compare the Current Word and Count a Match

**片段：** `word` 是已转小写的目标词，`temp` 是循环中刚读出的词。

**Snippet:** `word` is the lowercased target, and `temp` is the word just read inside the loop.

```cpp
// 这一行放在 while 循环外，开始统计前只执行一次。
long long count = 0;

// 下面的 if 放在 while (ss >> temp) 的循环体内。
if (temp == word) {
    ++count;
}
```

- `==` 是**比较是否相等**；一个 `=` 是赋值，不能把这里写成 `temp = word`。<br>`==` **compares for equality**; a single `=` is assignment. Do not write `temp = word` here.
- 这里比较的是两个字符串的全部内容，不是“包含关系”。`hello` 等于 `hello`，`helloworld` 不等于 `hello`。<br>This compares the complete contents of the two strings, not whether one contains the other. `hello` equals `hello`, but `helloworld` does not equal `hello`.
- `++count` 表示次数加 1。`count` 必须在循环外初始化为 `0`，否则每读一个词都清零，就记不住前面的次数。<br>`++count` increases the count by 1. Initialize `count` to `0` outside the loop; otherwise, resetting it whenever a word is read would lose the previous count.

<a id="完整示例-5a忽略英文大小写统计整词次数"></a>
### 完整示例 5A：忽略英文大小写，统计整词次数 / Complete Example 5A: Count Whole-Word Matches Ignoring English Letter Case

输入第一行是一个非空目标词，第二行是待统计文本。这里把**按空白分隔出的每一段文本**当作一个词；不自动删除标点，所以 `hello,` 和 `hello` 不相等。输出只有次数。

The first input line contains a nonempty target word, and the second contains the text to count. Here, a word is **each whitespace-delimited piece of text**; punctuation is not removed automatically, so `hello,` and `hello` are different. The output contains only the count.

```cpp
#include <cctype>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string word;
    string text;
    if (!(cin >> word)) {
        return 0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!getline(cin, text)) {
        return 0;
    }

    for (char& c : text) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    for (char& c : word) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    stringstream ss(text);
    string temp;
    long long count = 0;
    while (ss >> temp) {
        if (temp == word) {
            ++count;
        }
    }

    cout << count << '\n';
    return 0;
}
```

**输入**（第二行的 `hello` 和 `HELLO` 之间有两个空格）：

**Input** (there are two spaces between `hello` and `HELLO` on the second line):

```text
Hello
hello  HELLO world helloworld Hello
```

**输出**：

**Output**:

```text
3
```

处理过程：目标词先变成 `hello`；第二行拆出 `hello`、`hello`、`world`、`helloworld`、`hello`，其中 3 个与目标词完全相等。若第二行是空行、全是空格，或者没有匹配词，都会输出 `0`；如果缺少第二行，则读取失败，直接结束。

Processing: the target becomes `hello`; the second line yields `hello`, `hello`, `world`, `helloworld`, and `hello`, of which 3 exactly match the target. An empty second line, a line containing only spaces, or a line without matches produces `0`. If the second line is missing, reading fails and the program exits immediately.

这是一份演示四步如何配合的计数程序。遇到[洛谷 P1308](https://www.luogu.com.cn/problem/P1308) 等具体题目，还要按题面补上首次出现位置、未找到时的输出等要求；不要把这份示例直接当作完整题解提交。

This counting program demonstrates how the four steps fit together. For a specific problem such as [Luogu P1308](https://www.luogu.com.cn/problem/P1308), you must also implement the statement's requirements, such as the first occurrence's position and the output for no match. Do not submit this example unchanged as a complete solution.

<a id="char-reference"></a>
<a id="char-为什么能改原字符联系引用和指针"></a>
### char& 为什么能改原字符：联系引用和指针 / Why char& Changes the Original Character: References and Pointers

**记住一句话：字符串循环里的 `char& c`，就是为了直接修改原来的字符。** `char &c` 和 `char& c` 只是空格位置不同，含义一样。

**Remember this: `char& c` in a string loop lets you modify the original character directly.** `char &c` and `char& c` differ only in spacing and mean the same thing.

<a id="先分清副本引用指针"></a>
#### 先分清副本、引用、指针 / First Distinguish Copies, References, and Pointers

**片段：** 先有一个普通整数，再分别建立副本、引用和指针。

**Snippet:** Start with an ordinary integer, then create a copy, a reference, and a pointer to it.

```cpp
int value = 10;
int copy = value;      // 复制一份值，copy 和 value 是两个变量
int& alias = value;   // alias 是 value 的另一个名字
int* p = &value;      // p 保存 value 的地址
```

- `copy = 20;`：只改副本，不改 `value`。<br>`copy = 20;`: changes only the copy, not `value`.
- `alias = 20;`：通过别名修改 `value`，不用写 `*alias`。<br>`alias = 20;`: changes `value` through its alias; there is no need to write `*alias`.
- `*p = 20;`：通过指针找到它指向的整数，再修改那个整数；这里改的也是 `value`。这个 `*p` 操作叫**解引用**。<br>`*p = 20;`: follows the pointer to the integer it points to and changes that integer. Here that also changes `value`. The `*p` operation is called **dereferencing**.

同一个 `&`，要看出现在哪里：

The meaning of `&` depends on where it appears:

- `int& alias = value;` 的 `&` 在**声明类型处**，表示 `alias` 是引用。<br>In `int& alias = value;`, `&` appears in the **type declaration**, indicating that `alias` is a reference.
- `int* p = &value;` 的 `&value` 在**表达式里**，表示取出 `value` 的地址。<br>In `int* p = &value;`, `&value` appears in an **expression**, taking the address of `value`.
- 声明里的 `int*` 表示“指向 int 的指针”；之后表达式里的 `*p` 才表示访问它指向的整数。<br>In a declaration, `int*` means “pointer to int”; it is `*p` in a subsequent expression that accesses the integer being pointed to.

引用和指针有关联，但不要混成同一种写法：

References and pointers are related, but do not confuse their syntax:

| 比较什么<br>Comparison | 引用 `int& alias = value;`<br>Reference `int& alias = value;` | 指针 `int* p = &value;`<br>Pointer `int* p = &value;` |
| --- | --- | --- |
| 初学时怎么理解<br>Beginner's interpretation | 原对象的别名<br>Another name for the original object | 保存对象地址的变量<br>A variable holding an object's address |
| 怎样修改原对象<br>How to modify the original object | `alias = 20;` | `*p = 20;` |
| 能否换目标<br>Can the target change? | 初始化后不能重新绑定别的对象<br>Cannot be rebound to a different object after initialization | 可以用 `p = &other;` 改为指向另一个有效对象<br>Can point to another valid object using `p = &other;` |
| 能否表示“没有目标”<br>Can it represent “no target”? | 正常使用时必须绑定有效对象，没有 `nullptr` 这种引用状态<br>Must be bound to a valid object in normal use; there is no reference state equivalent to `nullptr` | 可以设为 `nullptr`，但此时不能解引用<br>Can be set to `nullptr`, but must not then be dereferenced |

局部引用不能只写 `int& alias;` 就放着，声明时要初始化，例如 `int& alias = value;`。指针也不要先写一个未初始化的 `int* p;` 就拿去用：先写 `int* p = &value;`，或用 `int* p = nullptr;` 表示暂时没有目标。`p != nullptr` 只是在排除空指针；真正解引用时，还要确认它指向的对象仍然有效。

You cannot leave a local reference as just `int& alias;`; initialize it when declaring it, for example with `int& alias = value;`. Likewise, do not declare an uninitialized `int* p;` and use it: start with `int* p = &value;`, or use `int* p = nullptr;` to represent no target for now. `p != nullptr` only rules out a null pointer; before dereferencing, you must also ensure the pointed-to object is still valid.

这些是 C++ 的使用规则。学到这里，不需要猜测“编译器一定怎样存引用”，也不要把引用当作可以随意重新指向的指针。

These are C++ usage rules. At this stage, you do not need to speculate about “how the compiler must store a reference,” nor should you treat a reference as a pointer that can freely change its target.

<a id="完整示例-5b通过别名和指针修改整数"></a>
### 完整示例 5B：通过别名和指针修改整数 / Complete Example 5B: Modify Integers Through an Alias and a Pointer

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 10;
    int other = 40;
    int& alias = value;
    int* p = &value;

    alias = 20;
    cout << "value: " << value << '\n';
    *p = 30;
    cout << "alias: " << alias << '\n';

    p = &other;
    *p = 50;
    cout << "value / other: " << value << ' ' << other << '\n';

    alias = other;  // 把 other 的值赋给 value，不是让 alias 换目标
    other = 60;
    cout << "alias / other: " << alias << ' ' << other << '\n';

    p = nullptr;
    if (p == nullptr) {
        cout << "p is null\n";  // 此时不能使用 *p
    }
    return 0;
}
```

**输入**：无需输入。

**Input**: No input required.

**输出**：

**Output**:

```text
value: 20
alias: 30
value / other: 30 50
alias / other: 50 60
p is null
```

前两次修改都作用于 `value`。`p = &other` 之后，`*p` 改的是 `other`，所以 `value` 仍是 `30`。`alias = other` 则把数值 `50` 赋给 `value`；后来 `other` 变成 `60`，`alias` 仍代表 `value`，读到的还是 `50`。

The first two modifications both affect `value`. After `p = &other`, `*p` modifies `other`, so `value` remains `30`. In contrast, `alias = other` assigns the numeric value `50` to `value`. When `other` later becomes `60`, `alias` still denotes `value`, so reading it still produces `50`.

<a id="套回字符串副本和原字符的区别"></a>
#### 套回字符串：副本和原字符的区别 / Back to Strings: A Copy Versus the Original Character

看到“修改字符串里的每个字符”，就想到 `for (char& c : s)`：`s` 是一个已经声明的 `string`，每一轮的 `c` 都是当前原字符的别名。循环进入下一轮时，会为下一个字符建立这一轮的引用；这不等于对同一个引用重新绑定。

When you see “modify every character in a string,” think of `for (char& c : s)`: `s` is an already-declared `string`, and each iteration's `c` is an alias for the current original character. The next iteration creates its own reference to the next character; this is not rebinding the same reference.

通用思路是：**遍历一个字符 → 算出新字符 → 赋回 `c`**。若笔记写成 `c = xxx(c)`，`xxx` 只是“你要做的转换”的占位名，不是 C++ 内置函数。实际代码要换成已经定义的函数，例如 `<cctype>` 里的 `tolower` 或 `toupper`。

The general pattern is: **visit one character → calculate its replacement → assign it back to `c`**. If notes use `c = xxx(c)`, `xxx` is merely a placeholder for “the conversion you want,” not a built-in C++ function. In real code, replace it with a defined function such as `tolower` or `toupper` from `<cctype>`.

| 想做什么<br>Goal | 循环体中的安全写法<br>Safe syntax inside the loop body |
| --- | --- |
| 转成小写<br>Convert to lowercase | `c = static_cast<char>(tolower(static_cast<unsigned char>(c)));` |
| 转成大写<br>Convert to uppercase | `c = static_cast<char>(toupper(static_cast<unsigned char>(c)));` |

两种转换都先把输入转成 `unsigned char`，把结果转回 `char`，最后赋回 `c`。只调用 `tolower(c)` 或 `toupper(c)` 而不保存返回值，不会自动修改 `c`。转换规则依赖当前 C locale；下面没有改变默认规则，主要用于英文字母，不能把逐字节转换当作通用 Unicode 处理。空格、数字和常见标点在本例中保持不变。

Both conversions first cast the input to `unsigned char`, cast the result back to `char`, and finally assign it back to `c`. Merely calling `tolower(c)` or `toupper(c)` without saving the return value does not modify `c` automatically. Conversion rules depend on the current C locale. The example below keeps the default rules and mainly handles English letters; byte-by-byte conversion is not general Unicode processing. Spaces, digits, and common punctuation remain unchanged in this example.

<a id="完整示例-5c同一字符串对比复制与原地修改"></a>
### 完整示例 5C：同一字符串，对比复制与原地修改 / Complete Example 5C: Compare Copies with In-Place Changes to the Same String

先用 `char c` 转小写并输出副本，再查看原字符串；然后用 `char& c` 真正修改原字符，最后转大写。

First use `char c` to lowercase and print copies, then inspect the original string. Next use `char& c` to actually change the original characters, and finally convert them to uppercase.

```cpp
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text;
    if (!getline(cin, text)) {
        return 0;
    }

    cout << "copy loop output: [";
    for (char c : text) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        cout << c;
    }
    cout << "]\n";
    cout << "text after copy: [" << text << "]\n";

    for (char& c : text) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    cout << "text after reference: [" << text << "]\n";

    for (char& c : text) {
        c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    }
    cout << "text after uppercase: [" << text << "]\n";
    return 0;
}
```

**输入**：

**Input**:

```text
HeLLo ICPC!
```

**输出**：

**Output**:

```text
copy loop output: [hello icpc!]
text after copy: [HeLLo ICPC!]
text after reference: [hello icpc!]
text after uppercase: [HELLO ICPC!]
```

第一行虽然输出了小写，但修改的是每轮的副本，所以第二行的 `text` 仍保持原样。后面两次使用 `char&`，才真正把 `text` 改成小写、再改成大写。输入空行时，三个循环都不执行，四行方括号内都为空；没有任何输入时直接结束。

Although the first line prints lowercase letters, only each iteration's copy was changed, so `text` remains unchanged on the second line. The next two loops use `char&` to actually convert `text` to lowercase and then uppercase. For an empty input line, none of the three loops executes, and the brackets on all four output lines are empty. With no input at all, the program exits immediately.

<a id="string-templates"></a>
<a id="四种字符串模板先看题目要你做什么"></a>
### 四种字符串模板：先看题目要你做什么 / Four string templates: first identify what the problem asks you to do

这些模板里的 `s` 都是已经声明并读入内容的 `string`，不是新的特殊类型。需要哪一种就选哪一种，不必每题都写四遍。

In all these templates, `s` is an ordinary `string` that has already been declared and filled with input, not a new special type. Choose whichever template you need; you do not need to write all four for every problem.

| 需求<br>Requirement | 选择的写法<br>Syntax to choose | 详细解释<br>Detailed explanation |
| --- | --- | --- |
| 1. 逐个检查字符<br>1. Examine characters one by one | 需要下标就用 `s[i]`；不需要下标就用 `for (char c : s)`<br>Use `s[i]` when you need the index; use `for (char c : s)` when you do not | [下标范围](#getline)、[副本和引用](#char-reference)<br>[Index range](#getline), [copies and references](#char-reference) |
| 2. 修改原字符串中的字符<br>2. Modify characters in the original string | `for (char& c : s)`，算出新字符后赋回 `c`<br>Use `for (char& c : s)` and assign the new character back to `c` | [转小写、转大写及对照示例](#char-reference)<br>[Lowercase and uppercase conversion, with comparison examples](#char-reference) |
| 3. 简单拆成单词<br>3. Split into words simply | `stringstream ss(s); string word;`，再用 `while (ss >> word)`<br>Use `stringstream ss(s); string word;`, followed by `while (ss >> word)` | [拆词规则](#stringstream)、[完整四步示例](#word-count)<br>[Splitting rules](#stringstream), [complete four-step example](#word-count) |
| 4. 拆词时还要原字符串里的位置<br>4. Split into words and retain their positions in the original string | 用下标 `i` 手动扫描，记住 `start`，再 `substr(start, i - start)`<br>Scan manually with index `i`, remember `start`, and then use `substr(start, i - start)` | 见下面的扫描示例<br>See the scanning example below |

<a id="模板-1检查字符需要位置就保留下标"></a>
#### 模板 1：检查字符，需要位置就保留下标 / Template 1: examine characters, keeping their indices when positions matter

**片段：** `s` 已读好；下面逐行输出每个字符的下标和字符本身，需 `<string>`、`<iostream>`。

**Snippet:** `s` has already been read. The following prints each character's index and the character itself on a separate line; it requires `<string>` and `<iostream>`.

```cpp
for (string::size_type i = 0; i < s.size(); ++i) {
    cout << i << ": [" << s[i] << "]\n";
}
```

`string::size_type` 与 `size()` 的结果类型一致，可以避免直接拿 `int` 和无符号长度比较的警告。条件必须是 `i < s.size()`。只写一行 `s[i];` 并不会输出、比较或修改它；要像上面这样真正使用这个字符。

`string::size_type` matches the return type of `size()`, avoiding warnings from comparing an `int` directly with an unsigned length. The condition must be `i < s.size()`. A line containing only `s[i];` does not print, compare, or modify it; you must actually use the character, as above.

如果只想看看字符、判断它是不是某个值，不需要位置，可以写 `for (char c : s)`，在循环体里使用 `c`。这时拿到的是副本，修改副本不会改原串。

If you only want to examine characters or test whether they equal a particular value, and do not need their positions, write `for (char c : s)` and use `c` in the loop body. This gives you a copy; modifying the copy does not change the original string.

<a id="模板-2改原串就加-"></a>
#### 模板 2：改原串，就加 & / Template 2: add & to modify the original string

大小写转换直接用前面的[安全转换模板](#char-reference)。换成“遇到某个字符就替换”，思路也一样。

For case conversion, use the earlier [safe conversion template](#char-reference) directly. The same idea applies when replacing a particular character whenever it appears.

**片段：** 把已经读入的 `s` 中每个短横线 `'-'` 改成空格。

**Snippet:** Replace every hyphen `'-'` in the already-read string `s` with a space.

```cpp
for (char& c : s) {
    if (c == '-') {
        c = ' ';
    }
}
```

例如 `hello-ICPC` 会变成 `hello ICPC`。这里改的是原串；若后面需要原始内容，要提前保存一份。若题目只让忽略大小写，不要额外替换标点或删空格。

For example, `hello-ICPC` becomes `hello ICPC`. This modifies the original string; save a copy beforehand if you will need its original contents later. If the problem only asks you to ignore case, do not additionally replace punctuation or remove spaces.

<a id="模板-3只要单词用-stringstream"></a>
#### 模板 3：只要单词，用 stringstream / Template 3: use stringstream when you only need words

前面的[第 4 节](#stringstream)已有完整写法，关键组合是 `stringstream ss(s)`、声明接收变量 `string word`、再 `while (ss >> word)`。默认情况下，连续空格、制表符等空白都会被当作分隔；它不会自动去掉单词上的标点。

The earlier [Section 4](#stringstream) gives the complete syntax. The key combination is `stringstream ss(s)`, a receiving variable declared as `string word`, and then `while (ss >> word)`. By default, whitespace such as consecutive spaces and tabs acts as a separator; punctuation attached to words is not removed automatically.

这种简单取词循环没有替你记录每个词在原串中的起点。**第几个单词**和**第几个字符**是两回事；不能直接把词序号当作原位置。

This simple word-extraction loop does not record where each word starts in the original string. **The word number** and **the character position** are different things; you cannot use the word's ordinal number directly as its original position.

<a id="模板-4需要原字符位置用下标扫描"></a>
#### 模板 4：需要原字符位置，用下标扫描 / Template 4: scan by index when you need original character positions

下面约定**只用普通空格 `' '` 分词**。这与 `stringstream` 按一般空白分词不同：制表符 `\t` 在这个手动模板里属于词的一部分，不会被自动跳过。先按题面选好分隔规则。

The following assumes that **only ordinary spaces `' '` separate words**. Unlike `stringstream`, which splits on whitespace generally, this manual template treats a tab `\t` as part of a word and does not skip it automatically. Choose the separator rules according to the problem statement first.

扫描过程只有三件事：

The scan does just three things:

1. `i` 指向当前还没处理的字符。遇到空格就 `++i`，再 `continue`，直接开始下一轮。<br>`i` points to the next unprocessed character. On a space, execute `++i` and then `continue` to begin the next iteration immediately.
2. 遇到非空格，把当前位置保存成 `start`，它是这个词的**起点**。然后一直往后走，直到遇到空格或字符串结束。<br>On a non-space character, save the current position as `start`, the word's **starting position**. Then keep moving forward until reaching a space or the end of the string.
3. 此时 `i` 是这个词**结尾后面一位**，所以词对应区间是 `[start, i)`，长度是 `i - start`。用 `s.substr(start, i - start)` 取出词。<br>At that point, `i` is **one position past the end** of the word, so the word occupies `[start, i)` and has length `i - start`. Extract it with `s.substr(start, i - start)`.

关键条件必须写成 `i < s.size() && s[i] != ' '`：先确认没到末尾，才访问 `s[i]`。`&&` 左边为假时不会执行右边。只写 `while (s[i] != ' ')` 会在最后一个词后没有空格时继续越过边界。

The crucial condition must be `i < s.size() && s[i] != ' '`: first ensure you have not reached the end, and only then access `s[i]`. When the left side of `&&` is false, the right side is not evaluated. Writing only `while (s[i] != ' ')` continues past the boundary if the last word has no trailing space.

例如原串示意是 `··hi··ICPC·ok··`，这里每个 `·` 只用来表示一个普通空格，实际字符串里没有这个点：

For example, imagine the original string as `··hi··ICPC·ok··`. Each `·` represents one ordinary space; these dots are not actually in the string:

| 取出的词<br>Extracted word | start：起点<br>start: starting position | i：词末尾后一位<br>i: one position past the word | i - start：长度<br>i - start: length |
| --- | --- | --- | --- |
| `hi` | 2 | 4 | 2 |
| `ICPC` | 6 | 10 | 4 |
| `ok` | 11 | 13 | 2 |

下标从 `0` 开始，前导空格、连续空格和尾部空格都在原串中占位置。两端各有两个空格时，整个字符串长度是 `15`；去掉最后两个空格，长度变成 `13`，最后一个词的 `i` 正好等于 `s.size()`，仍然能够正常取出 `ok`。

Indices start at `0`; leading, consecutive, and trailing spaces all occupy positions in the original string. With two spaces at each end, the full length is `15`. Removing the final two spaces makes it `13`, and the last word's `i` equals `s.size()` exactly; `ok` is still extracted correctly.

<a id="完整示例-5d输出每个词和它在原串中的起点"></a>
### 完整示例 5D：输出每个词和它在原串中的起点 / Complete example 5D: print each word and its starting position in the original string

程序不删除空格、不修改字符串，输出格式是 `[词] 起点下标`。分隔符只认普通空格 `' '`；空行和全空格行没有单词，因此不输出任何行。

The program neither removes spaces nor modifies the string. Its output format is `[word] starting_index`. Only an ordinary space `' '` counts as a separator; empty lines and all-space lines contain no words and therefore produce no output lines.

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    if (!getline(cin, s)) {
        return 0;
    }

    string::size_type i = 0;
    while (i < s.size()) {
        if (s[i] == ' ') {
            ++i;
            continue;
        }

        string::size_type start = i;
        while (i < s.size() && s[i] != ' ') {
            ++i;
        }
        string word = s.substr(start, i - start);
        cout << '[' << word << "] " << start << '\n';
    }
    return 0;
}
```

**输入**（开头两个空格，`hi` 后两个空格，`ok` 后没有空格）：

**Input** (two leading spaces, two spaces after `hi`, and no spaces after `ok`):

```text
  hi  ICPC ok
```

**输出**：

**Output:**

```text
[hi] 2
[ICPC] 6
[ok] 11
```

再给输入末尾加两个空格，输出仍相同。若输入 `hi, ICPC!`，输出 `[hi,] 0` 和 `[ICPC!] 4`，标点会保留在词里；如果要支持其他分隔规则，先按题意调整，不能默认所有题都这样分词。

Adding two spaces at the end of the input leaves the output unchanged. For input `hi, ICPC!`, the output is `[hi,] 0` and `[ICPC!] 4`; punctuation remains part of the words. To support other separator rules, first adapt the code to the problem statement rather than assuming every problem splits words this way.

`i` 在跳空格或扫描单词时都会前进，最终到达 `s.size()`，所以空串、全空格、连续空格和最后一个词后没有空格时都能结束。位置仍按 `std::string` 的存储单元计数，UTF-8 中文不能直接按汉字个数理解。

`i` advances both when skipping spaces and when scanning words, eventually reaching `s.size()`. Thus the scan terminates for an empty string, an all-space string, consecutive spaces, and a last word with no trailing space. Positions still count the storage units of `std::string`; for UTF-8 Chinese, they cannot simply be interpreted as counts of Chinese characters.

**选择口诀：整句用 getline → 改大小写用 char& → 只要词用 stringstream → 要原字符位置就手动扫描。** 这个扫描结构可用于补上前面提到的 P1308 位置记录，但仍需按题面处理目标词比较、计数和最终输出格式。

**Selection mnemonic: use getline for a whole line → char& to change case → stringstream when you only need words → manual scanning for original character positions.** This scan can supply the position tracking mentioned earlier for P1308, but target-word comparison, counting, and final output formatting must still follow that problem's requirements.

<a id="recap"></a>
<a id="6-六种原始写法速查"></a>
## 6. 六种原始写法速查 / 6. Quick reference for six basic forms

下面都是**片段**，不是一段可以直接整体运行的程序。所需头文件见第 0 节。

Everything below is a **snippet**, not one program you can run as a whole. See Section 0 for the required headers.

| 想做什么<br>What you want to do | 写法<br>Syntax | 使用前提 / 结果<br>Preconditions / result |
| --- | --- | --- |
| 准备 n 个整数<br>Prepare n integers | `vector<int> v(n);` | `n` 已读入、非负且大小合理<br>`n` has been read, is nonnegative, and has a reasonable size |
| 读入 n 个数<br>Read n numbers | `for (int i = 0; i < n; i++) { cin >> v[i]; }` | `v` 已有 n 个元素<br>`v` already contains n elements |
| 从小到大排序<br>Sort in ascending order | `sort(v.begin(), v.end());` | 原地修改 `v`，重复值不消失<br>Modifies `v` in place; duplicate values remain |
| 得到去重集合<br>Create a collection of distinct values | `set<int> unique_values(v.begin(), v.end());` | 新集合有序、不重复；`v` 不变<br>The new set is sorted and contains no duplicates; `v` is unchanged |
| 读取整行<br>Read a whole line | `getline(cin, line);` | 先声明 `string line;`，留意前一次数字输入的换行<br>Declare `string line;` first, and watch for the newline left by previous numeric input |
| 按空白提取单词<br>Extract words separated by whitespace | `stringstream ss(line); string word; while (ss >> word) { /* 使用 word */ }`<br>`stringstream ss(line); string word; while (ss >> word) { /* use word */ }` | `line` 已有内容；读到末尾就结束<br>`line` already contains text; extraction stops at the end |

遇到报错，先检查：

When an error occurs, first check:

1. 工具的头文件有没有包含？写了 `using namespace std;`，或给工具加了 `std::` 吗？<br>Have you included the tool's header? Have you written `using namespace std;` or prefixed the tool with `std::`?
2. 变量有没有先声明，读取数量后才创建 `vector` 吗？<br>Have you declared the variables first, and created the `vector` only after reading the number of elements?
3. 集合和字符串是不是错误地都用了 `s`？传给 `getline` 的第二个参数是不是 `string`？<br>Have you accidentally used `s` for both the set and the string? Is the second argument passed to `getline` a `string`?
4. 下标是不是写成了 `i <= n`，从而访问了不存在的 `v[n]`？<br>Did you write the index condition as `i <= n`, thus accessing the nonexistent `v[n]`?
5. 数字输入后是否正确处理了换行？<br>Have you handled the newline correctly after numeric input?
6. 是否把几个完整示例拼到一起，导致出现多个 `main()`？<br>Have you combined several complete examples, resulting in multiple `main()` functions?

**到这里，你已经可以完成“读一组数 → 排序 → 去重”和“读一行 → 拆成单词/整数”。下面按需要选读即可。**

**At this point, you can already perform “read a group of numbers → sort → remove duplicates” and “read a line → split into words/integers.” Read the remaining sections as needed.**

<a id="more-vector"></a>
<a id="7-选读vector-的增删倒序排序"></a>
## 7. 选读：vector 的增删、倒序排序 / 7. Optional: adding and removing vector elements, and sorting in descending order

<a id="先知道长度还是边读边追加"></a>
### 先知道长度，还是边读边追加？ / Do you know the length in advance, or will you append as you read?

- `vector<int> v(n);`：一开始就有 n 个元素，适合用 `v[i]` 输入。<br>`vector<int> v(n);`: starts with n elements, suitable for input using `v[i]`.
- `vector<int> v;`：一开始是空的，适合用 `v.push_back(x)` 逐个往末尾追加。<br>`vector<int> v;`: starts empty, suitable for appending elements one by one with `v.push_back(x)`.
- **不要先建 n 个元素，又追加 n 次**，否则会得到 2n 个元素，前 n 个还可能全是 0。<br>**Do not create n elements first and then append n more**, or you will end up with 2n elements, with the first n possibly all equal to 0.

常用操作（`v` 是 `vector<int>`，`x` 是整数）：

Common operations (`v` is a `vector<int>`, and `x` is an integer):

| 写法<br>Syntax | 作用<br>Purpose | 注意<br>Caution |
| --- | --- | --- |
| `v.size()` | 当前元素个数<br>Current number of elements | 是无符号整数类型，初学先别写 `v.size() - 1`，空容器时会出问题<br>Returns an unsigned integer type; beginners should avoid writing `v.size() - 1`, which causes problems for an empty container |
| `v.empty()` | 判断是否为空<br>Check whether it is empty | 空时结果为 `true`<br>Returns `true` when empty |
| `v.push_back(x)` | 在末尾添加 x<br>Add x at the end | 长度增加 1<br>Increases the length by 1 |
| `v.pop_back()` | 删除最后一个元素<br>Remove the last element | 必须非空；它不返回被删的值<br>Must be nonempty; does not return the removed value |
| `v.front()` / `v.back()` | 访问第一个 / 最后一个元素<br>Access the first / last element | 必须非空<br>Must be nonempty |
| `v.clear()` | 删除所有元素<br>Remove all elements | 之后长度为 0<br>The length becomes 0 |

`reserve(n)` 只是提前准备存储空间，**不会创建 n 个元素**。`vector<int> v; v.reserve(5);` 之后仍然不能访问 `v[0]`；要么用 `push_back`，要么用 `resize(5)` 真的创建元素。

`reserve(n)` only allocates storage ahead of time; it **does not create n elements**. After `vector<int> v; v.reserve(5);`, you still cannot access `v[0]`. Either use `push_back` or actually create the elements with `resize(5)`.

<a id="倒序也可以直接排序"></a>
### 倒序也可以直接排序 / You can also sort directly in descending order

**片段：** `v` 已有数据，需要 `<algorithm>`。

**Snippet:** `v` already contains data; requires `<algorithm>`.

```cpp
sort(v.rbegin(), v.rend());
```

这里的 `rbegin()`、`rend()` 表示反向遍历的区间。排序后，从普通的开头看，`v` 就是从大到小。别把 `begin()` 与 `rend()` 混成一对。

Here, `rbegin()` and `rend()` describe a range traversed in reverse. After sorting, `v` is in descending order when viewed from its normal beginning. Do not mix `begin()` and `rend()` as a pair.

<a id="完整示例-6追加删除倒序排序"></a>
### 完整示例 6：追加、删除、倒序排序 / Complete example 6: append, remove, and sort in descending order

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    v.push_back(3);
    v.push_back(8);
    v.push_back(1);
    v.push_back(99);
    v.pop_back();  // 此时非空，删除刚刚追加的 99

    sort(v.rbegin(), v.rend());
    cout << "size: " << v.size() << '\n';
    cout << "values:";
    for (int value : v) {
        cout << ' ' << value;
    }
    cout << '\n';
    return 0;
}
```

**输入**：无需输入，数据已经写在程序中。

**Input:** No input is needed; the data is written into the program.

**输出**：

**Output:**

```text
size: 3
values: 8 3 1
```

<a id="unique"></a>
<a id="8-选读保留-vector-的去重方式"></a>
## 8. 选读：保留 vector 的去重方式 / 8. Optional: removing duplicates while keeping a vector

**什么时候用：** 想去掉重复数，又想继续用下标访问结果。

**When to use it:** You want to remove duplicate numbers while continuing to access the result by index.

需要 `<vector>` 和 `<algorithm>`。常见组合是：

Requires `<vector>` and `<algorithm>`. The usual combination is:

**片段：** `v` 是 `vector<int>`。

**Snippet:** `v` is a `vector<int>`.

```cpp
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

别急着死记，按三步理解：

Do not rush to memorize it mechanically; understand these three steps:

1. `sort` 先排序，让相同的数挨在一起。<br>`sort` sorts first so that equal numbers become adjacent.
2. `unique` 只压缩**相邻的重复元素**，把保留的元素放到前面，返回“新的有效部分的终点”。**它自己不会缩短 `v.size()`。** 终点后面的值不应再当作有效去重结果使用。<br>`unique` only compacts **adjacent duplicate elements**, places the retained elements at the front, and returns the “end of the new valid portion.” **It does not reduce `v.size()` on its own.** Values beyond that endpoint should no longer be used as part of the valid deduplicated result.
3. `erase` 删除从新终点到旧终点的部分，容器才真正变短。<br>`erase` removes the portion from the new endpoint to the old endpoint, actually shortening the container.

所以，仅写 `unique(...)` 不够；没有排序时，它也不会消除所有相隔很远的重复值。这个组合会改变原来顺序，若题目要求保留首次出现顺序，就不能直接套它。

Therefore, `unique(...)` alone is not enough. Without sorting, it also does not eliminate all duplicates that occur far apart. This combination changes the original order, so it cannot be applied directly if the problem requires preserving first-occurrence order.

<a id="完整示例-7排序并原地去重"></a>
### 完整示例 7：排序并原地去重 / Complete example 7: sort and remove duplicates in place

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {3, 1, 3, 2, 2};
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    cout << "size: " << v.size() << '\n';
    cout << "values:";
    for (int value : v) {
        cout << ' ' << value;
    }
    cout << '\n';
    return 0;
}
```

**输入**：无需输入。`{3, 1, 3, 2, 2}` 表示用这些数直接创建 `vector`。

**Input:** No input is needed. `{3, 1, 3, 2, 2}` creates the `vector` directly from these numbers.

**输出**：

**Output:**

```text
size: 3
values: 1 2 3
```

<a id="binary-search"></a>
<a id="9-选读二分查找一定先确认有序"></a>
## 9. 选读：二分查找一定先确认有序 / 9. Optional: always confirm the data is sorted before binary search

**什么时候用：** 对已经排好序的一组数据，反复查某个数是否存在、第一次出现在哪里、出现几次。

**When to use it:** You repeatedly query sorted data to check whether a number exists, where it first occurs, or how many times it occurs.

需要 `<algorithm>`。本文使用默认比较规则，**先按从小到大排序**，再使用下面的函数；不要拿第 7 节的倒序结果直接用。

Requires `<algorithm>`. This guide uses the default comparison, so **sort in ascending order first** before using the following functions. Do not apply them directly to the descending-order result from Section 7.

| 函数<br>Function | 在从小到大排列的区间中找什么<br>What it looks for in an ascending range | 返回什么<br>Return value |
| --- | --- | --- |
| `binary_search(begin, end, x)` | x 是否存在<br>Whether x exists | `bool`，即 `true` 或 `false`<br>`bool`, namely `true` or `false` |
| `lower_bound(begin, end, x)` | 第一个大于或等于 x 的位置<br>The first position whose value is greater than or equal to x | 迭代器<br>An iterator |
| `upper_bound(begin, end, x)` | 第一个严格大于 x 的位置<br>The first position whose value is strictly greater than x | 迭代器<br>An iterator |

用 `1 2 2 2 5` 查 `2`：

Search for `2` in `1 2 2 2 5`:

- `lower_bound` 指向下标 1。<br>`lower_bound` points to index 1.
- `upper_bound` 指向下标 4，也就是值 5 的位置。<br>`upper_bound` points to index 4, the position containing 5.
- 两个位置相减：`4 - 1 = 3`，所以 2 出现 3 次。<br>Subtract the two positions: `4 - 1 = 3`, so 2 occurs 3 times.

`lower_bound` 找到的是“第一个 >= x”的位置，**不保证那个数就等于 x**。查不存在的 `3`，它会指向 `5`；查 `9`，会得到 `end()`。

`lower_bound` finds the position of the “first value >= x”; it **does not guarantee that the value equals x**. Searching for the absent `3` points to `5`; searching for `9` returns `end()`.

<a id="完整示例-8找下标计数并处理找不到"></a>
### 完整示例 8：找下标、计数，并处理找不到 / Complete example 8: find an index, count occurrences, and handle missing values

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {2, 5, 2, 1, 2};
    sort(v.begin(), v.end());  // 得到 1 2 2 2 5

    int x = 2;
    auto left = lower_bound(v.begin(), v.end(), x);
    auto right = upper_bound(v.begin(), v.end(), x);
    cout << "first index: " << left - v.begin() << '\n';
    cout << "count: " << right - left << '\n';
    cout << "has 3: " << binary_search(v.begin(), v.end(), 3) << '\n';

    auto pos = lower_bound(v.begin(), v.end(), 9);
    if (pos != v.end() && *pos == 9) {
        cout << "found 9" << '\n';
    } else {
        cout << "9 not found" << '\n';
    }
    return 0;
}
```

**输入**：无需输入。

**Input:** No input is needed.

**输出**：

**Output:**

```text
first index: 1
count: 3
has 3: 0
9 not found
```

新语法解释：

New syntax explained:

- `auto`：让编译器从右侧表达式推断变量类型，这里推断的是迭代器类型，不是元素值。<br>`auto`: lets the compiler infer the variable's type from the expression on the right. Here, the inferred type is an iterator type, not an element value.
- `*pos`：取出这个位置的元素值。只有 `pos != v.end()` 时才可以这样读。<br>`*pos`: retrieves the element value at this position. You may read it this way only when `pos != v.end()`.
- `&&`：表示“并且”，左边为假时不会执行右边。所以先检查 `pos != v.end()`，再读取 `*pos`，顺序很重要。<br>`&&`: means “and”; the right side is not evaluated if the left side is false. Therefore, check `pos != v.end()` before reading `*pos`; the order matters.
- 对 `vector`，`pos - v.begin()` 得到从 0 开始的下标；迭代器相减不能照搬到 `set` 或 `map`。<br>For a `vector`, `pos - v.begin()` gives the zero-based index; this iterator subtraction cannot be applied directly to `set` or `map`.
- `cout` 默认把 `bool` 输出为 `1`（真）或 `0`（假），所以 `has 3: 0` 表示没有 3。<br>By default, `cout` prints a `bool` as `1` (true) or `0` (false), so `has 3: 0` means that 3 is absent.

为了查很多次，通常先排序一次，再做多次二分，不要每查一次都重新排序。

For many queries, usually sort once and then perform multiple binary searches; do not sort again for every query.

<a id="bound-memory-guide"></a>
<a id="lower-和-upper-怎么记两个边界夹住所有-x"></a>
### lower 和 upper 怎么记：两个边界夹住所有 x / Remembering lower and upper: two boundaries enclose all occurrences of x

**lower ≥，upper >，次数 = upper − lower。**

**lower ≥, upper >, count = upper − lower.**

前提：下面使用默认比较规则，`vector<int> a` 已经**从小到大排好（允许重复）**。口诀里的 `lower`、`upper` 指返回的**位置**，相减求的是位置之间的距离，不是两个元素值相减。

Precondition: the following uses the default comparison, and `vector<int> a` is already **sorted in ascending order (duplicates allowed)**. In the mnemonic, `lower` and `upper` mean the returned **positions**. Their difference is the distance between positions, not the difference between two element values.

| 函数<br>Function | 找什么<br>What it finds | 遇到等于 x 的元素<br>When it encounters elements equal to x |
| --- | --- | --- |
| `lower_bound` | 第一个 `>= x` 的位置<br>The first position with a value `>= x` | 允许等于，取第一个<br>Equality is allowed; take the first |
| `upper_bound` | 第一个 `> x` 的位置<br>The first position with a value `> x` | 不允许等于，越过所有 x<br>Equality is not allowed; skip all occurrences of x |

<a id="两行写法把迭代器直接变成下标"></a>
#### 两行写法：把迭代器直接变成下标 / Two lines: turn iterators directly into indices

**片段：** `a` 已按上面的要求有序，`x` 是目标值；需要 `<algorithm>`、`<vector>`，这里沿用 `using namespace std;`。

**Snippet:** `a` is sorted as required above, and `x` is the target. Requires `<algorithm>` and `<vector>`; we continue using `using namespace std;` here.

```cpp
int l = lower_bound(a.begin(), a.end(), x) - a.begin();
int r = upper_bound(a.begin(), a.end(), x) - a.begin();
```

- 函数先返回迭代器；再减去 `a.begin()`，才得到**从 0 开始的位置编号**。<br>The functions first return iterators; subtracting `a.begin()` then gives **zero-based position numbers**.
- `l`：第一个 `>= x` 的位置；`r`：第一个 `> x` 的位置。没有满足条件的元素时，对应位置等于 `a.size()`。<br>`l`: the first position with a value `>= x`; `r`: the first position with a value `> x`. If no element satisfies the condition, the corresponding position equals `a.size()`.
- 这两行用 `int` 存位置，前提是数组长度也能放进 `int`；处理更大的 `vector` 时，可把 `int l`、`int r` 改成 `auto l`、`auto r`，保留迭代器差值的类型。<br>These two lines store positions in `int`, assuming the array length also fits in `int`. For a larger `vector`, change `int l` and `int r` to `auto l` and `auto r` to retain the iterator-difference type.
- 这里的减法适用于 `vector` 的迭代器，不能直接照搬给 `set` 或 `map`。<br>This subtraction works for `vector` iterators; do not apply it directly to `set` or `map`.

<a id="用-122246-看懂-l-r"></a>
#### 用 1、2、2、2、4、6 看懂 [l, r) / Understanding [l, r) with 1, 2, 2, 2, 4, 6

查 `x = 2`，逐格对照条件（这是帮助记忆的演示，库函数实际使用二分查找）：

For `x = 2`, test each cell against the conditions (this demonstration is a memory aid; the library functions actually use binary search):

| 下标<br>Index | 0 | 1 | 2 | 3 | 4 | 5 |
| --- | --- | --- | --- | --- | --- | --- |
| 元素值<br>Element value | 1 | 2 | 2 | 2 | 4 | 6 |
| `>= 2` | 否<br>No | **第一个是**<br>**First yes** | 是<br>Yes | 是<br>Yes | 是<br>Yes | 是<br>Yes |
| `> 2` | 否<br>No | 否<br>No | 否<br>No | 否<br>No | **第一个是**<br>**First yes** | 是<br>Yes |

因此 `l = 1`、`r = 4`。所有 `2` 都在**左闭右开区间 `[l, r)`**，也就是下标 `1、2、3`：包含 `l`，不包含 `r`。

Thus `l = 1` and `r = 4`. All occurrences of `2` lie in the **left-inclusive, right-exclusive interval `[l, r)`**, namely indices `1, 2, 3`: it includes `l` but excludes `r`.

- 次数：`r - l = 4 - 1 = 3`。<br>Count: `r - l = 4 - 1 = 3`.
- 第一次出现：`l`；最后一次出现：`r - 1`，这两个说法都要以 **`l < r`，确实存在 x** 为前提。<br>First occurrence: `l`; last occurrence: `r - 1`. Both statements require **`l < r`, meaning x really exists**.
- **`upper_bound` 不是最后一个等于 x 的位置。** 本例 `r = 4` 指向数值 `4`，最后一个 `2` 的下标是 `3`。<br>**`upper_bound` is not the last position equal to x.** Here, `r = 4` points to the value `4`; the final `2` is at index `3`.
- 这里的 `[l, r)` 表示所有等于 `x` 的元素；它不是后面手写二分模板的当前搜索区间 `[l, r]`，不要把两种含义混用。<br>Here, `[l, r)` describes all elements equal to `x`. It is not the current search interval `[l, r]` in the later handwritten binary-search template; do not confuse the two meanings.

**片段：** 接在上面两行之后，需要输出时另加 `<iostream>`。

**Snippet:** Place this after the two lines above; add `<iostream>` when output is needed.

```cpp
cout << "count: " << r - l << '\n';
if (l < r) {
    cout << "first index: " << l << '\n';
    cout << "last index: " << r - 1 << '\n';
    cout << "value: " << a[l] << '\n';  // 此时 l 一定指向一个 x
} else {
    cout << "not found" << '\n';
}
```

<a id="没找到碰到末尾时位置还能不能用"></a>
#### 没找到、碰到末尾时，位置还能不能用？ / Can you still use the positions when nothing is found or the end is reached?

仍看同一个数组 `1 2 2 2 4 6`：

Consider the same array `1 2 2 2 4 6`:

| 查找 x<br>Search target x | l | r | 次数 r - l<br>Count r - l | 怎么理解<br>Interpretation |
| --- | --- | --- | --- | --- |
| `0` | 0 | 0 | 0 | 都指向 `1`，数组里没有 `0`<br>Both point to `1`; there is no `0` in the array |
| `2` | 1 | 4 | 3 | `[1, 4)` 中有三个 `2`<br>There are three occurrences of `2` in `[1, 4)` |
| `3` | 4 | 4 | 0 | 都指向 `4`，数组里没有 `3`<br>Both point to `4`; there is no `3` in the array |
| `6` | 5 | 6 | 1 | `r` 在末尾后一位，`6` 仍出现一次<br>`r` is one position past the end; `6` still occurs once |
| `9` | 6 | 6 | 0 | 两个迭代器都等于 `end()`，没有 `9`<br>Both iterators equal `end()`; there is no `9` |

**目标不存在时，`l == r`，区间为空，次数就是 `0`。** 空数组也是 `l = r = 0`。

**When the target is absent, `l == r`, the interval is empty, and the count is `0`.** An empty array also gives `l = r = 0`.

`end() - a.begin()` 可以计算，结果是长度 `n`；但 `end()` 不能解引用，`a[n]` 不能访问。尤其别把 `a[r]` 当作最后一个 `x`：`r` 可能等于 `n`。只有 `l < r` 时，才可以用 `a[l]` 或 `a[r - 1]` 读取匹配元素；空区间时也不能直接使用 `r - 1`。

You may compute `end() - a.begin()`, which equals the length `n`, but you cannot dereference `end()` or access `a[n]`. In particular, do not treat `a[r]` as the last `x`: `r` may equal `n`. Only when `l < r` may you read matching elements using `a[l]` or `a[r - 1]`; you cannot directly use `r - 1` for an empty interval either.

只想判断有没有，可以用 `l < r`；要完整的可运行程序，回看本节的“完整示例 8”；想拆开理解迭代器与精确匹配，再看 [lower_bound 入门](#lower-bound-guide)。

To test only whether the target exists, use `l < r`. For a complete runnable program, revisit “Complete example 8” in this section. To understand iterators and exact matching separately, see the [lower_bound introduction](#lower-bound-guide).

<a id="binary-search-lrmid"></a>
<a id="手写二分入门脑子里先记住-lrmid"></a>
### 手写二分入门：脑子里先记住 l、r、mid / Handwritten binary search: start by remembering l, r, and mid

**以后看到二分，先记这三个变量：`l` 是左边界，`r` 是右边界，`mid` 是中间位置。** 二分就是：看中间的数，每次排除不可能有答案的那一半，继续在剩下的范围里找。

**Whenever you see binary search, first remember these three variables: `l` is the left boundary, `r` is the right boundary, and `mid` is the middle position.** Binary search examines the middle number, discards the half that cannot contain the answer, and continues searching the remaining range.

下面只学一种：**在从小到大排好的整数数组中，找一个等于 `x` 的数**。允许相等的数挨在一起，例如 `1 2 2 5` 也符合要求。不是所有题目的“二分”都能直接套这一版。

We will learn just one version here: **find a number equal to `x` in an integer array sorted in ascending order**. Equal numbers may be adjacent, so `1 2 2 5` also satisfies the requirement. Not every problem involving “binary search” can use this version directly.

<a id="先分清下标是位置元素值是格子里的数"></a>
#### 先分清：下标是位置，元素值是格子里的数 / First distinguish indices, which are positions, from values, which are the numbers in the cells

例如 `vector<int> a = {1, 3, 5, 7, 9, 11, 13};`，一共有 `n = 7` 个数：

For example, `vector<int> a = {1, 3, 5, 7, 9, 11, 13};` contains `n = 7` numbers:

```text
下标：  0   1   2   3   4   5   6
数值：  1   3   5   7   9  11  13
        ↑           ↑           ↑
        l          mid          r
```

- `l`、`r`、`mid` 都保存**下标**，不是数组里的数。下标从 `0` 开始，所以最后一个下标是 `n - 1`。<br>`l`, `r`, and `mid` all store **indices**, not numbers from the array. Indices start at `0`, so the final index is `n - 1`.
- 开始时 `l = 0`、`r = n - 1`，表示整排格子都有可能。<br>Initially, `l = 0` and `r = n - 1`, meaning every cell in the row is a candidate.
- 这一轮 `mid = 3`，但 `a[mid] = 7`。查找时要比较 **`a[mid]` 和 `x`**，不能拿 `mid` 和 `x` 比。<br>In this iteration, `mid = 3`, but `a[mid] = 7`. During the search, compare **`a[mid]` with `x`**, not `mid` with `x`.
- `[l, r]` 表示从 `l` 到 `r`，**两端都包含**。例如 `[2, 4]` 里有下标 `2、3、4`，共 3 个位置。它和前面字符串扫描的半开区间 `[start, i)` 不一样。<br>`[l, r]` runs from `l` to `r`, **including both endpoints**. For example, `[2, 4]` contains indices `2, 3, 4`, a total of 3 positions. This differs from the half-open interval `[start, i)` used earlier for string scanning.

<a id="先把骨架补完整中间太小向右找太大向左找"></a>
#### 先把骨架补完整：中间太小向右找，太大向左找 / Complete the skeleton: search right when the middle is too small, left when it is too large

你记住的骨架是 `int l = 0;`、`int r = n - 1;` 和 `while (l <= r)`。但循环中**只算 `mid` 还不够**：必须在找到时退出，或更新边界，否则会一直查看同一个位置。

The skeleton to remember is `int l = 0;`, `int r = n - 1;`, and `while (l <= r)`. But **computing `mid` alone is not enough** inside the loop: you must exit when a match is found or update the boundaries, otherwise you will keep examining the same position.

**片段：** `a` 已从小到大排好，`n` 是它的长度，`x` 是目标值；这里的 `n` 是非负的 `int`。

**Snippet:** `a` is sorted in ascending order, `n` is its length, and `x` is the target. Here, `n` is a nonnegative `int`.

```cpp
int l = 0;          // 左边界：第一个还没排除的位置
int r = n - 1;      // 右边界：最后一个还没排除的位置
int found = -1;     // -1 表示目前还没找到

while (l <= r) {
    int mid = l + (r - l) / 2;

    if (a[mid] == x) {
        found = mid;        // 记住找到的下标
        break;              // 已经找到，退出 while
    } else if (a[mid] < x) {
        l = mid + 1;        // 中间太小，去右边找
    } else {
        r = mid - 1;        // 中间太大，去左边找
    }
}
```

按这几句话读懂它：

Read it using these explanations:

1. **`while (l <= r)`：只要还有候选位置，就继续找。** `l == r` 时还剩一个格子，也要检查，所以这里不能少写等号。<br>**`while (l <= r)`: keep searching while candidate positions remain.** When `l == r`, one cell remains and still needs to be checked, so do not omit the equality sign.
2. **`mid`：取当前范围中间的下标。** 整数除法会舍去小数，例如 `[0, 5]` 的 `mid` 是 `2`。`(l + r) / 2` 容易记，但下标很大时 `l + r` 可能超出 `int` 范围；在这里合法的非负下标范围内，`l + (r - l) / 2` 能避免这个加法溢出。<br>**`mid`: take the index in the middle of the current range.** Integer division discards the fractional part; for example, `[0, 5]` has `mid = 2`. `(l + r) / 2` is easy to remember, but `l + r` may exceed the range of `int` for large indices. Within the valid nonnegative index range used here, `l + (r - l) / 2` avoids that addition overflow.
3. **相等：记下位置并 `break`。** `found` 保存的是下标；`-1` 不是合法下标，不能写 `a[-1]`。若之后想访问 `a[found]`，必须先确认 `found != -1`。<br>**Equal: record the position and `break`.** `found` stores an index. `-1` is not a valid index, so do not write `a[-1]`. To access `a[found]` afterward, first confirm that `found != -1`.
4. **中间太小：`l = mid + 1`。** 因为数组有序，`mid` 及它左边的数都不会更大，全都不可能等于 `x`，所以一起排除。<br>**Middle too small: `l = mid + 1`.** Because the array is sorted, the value at `mid` and all values to its left are no larger than `a[mid]`. None can equal `x`, so discard them together.
5. **中间太大：`r = mid - 1`。** 同理，`mid` 及它右边的数都太大，一起排除。<br>**Middle too large: `r = mid - 1`.** Similarly, the value at `mid` and all values to its right are too large, so discard them together.
6. **没找到就不断缩小范围，直到 `l > r`。** 这时一个候选位置都不剩，循环结束，`found` 仍是 `-1`。<br>**If no match is found, keep shrinking the range until `l > r`.** No candidate positions remain, the loop ends, and `found` is still `-1`.

为什么必须 `+1` / `-1`？因为这一轮已经确认 `mid` 不等于目标，下一轮不要再查它。若误写成 `l = mid`，当 `l == r == mid` 且中间值偏小时，范围完全不变，就会死循环。**这一版的初始化、`<=` 和 `±1` 是一整套，不要和别的二分模板混着用。**

Why are `+1` and `-1` necessary? This iteration has already established that `mid` does not match the target, so the next iteration should not check it again. If you mistakenly write `l = mid`, then when `l == r == mid` and the middle value is too small, the range never changes and the loop runs forever. **This version's initialization, `<=`, and `±1` form one consistent set; do not mix them with other binary-search templates.**

<a id="手算一次在-135791113-中找-9"></a>
#### 手算一次：在 1、3、5、7、9、11、13 中找 9 / Work it out by hand: find 9 in 1, 3, 5, 7, 9, 11, 13

`x = 9`，`found` 开始为 `-1`。每一行都是“先算中间，再比较，再更新”：

With `x = 9`, `found` starts at `-1`. Each row means “compute the middle, compare, then update”:

| 轮次<br>Iteration | l | r | mid | a[mid] | 比较与下一步<br>Comparison and next step |
| --- | --- | --- | --- | --- | --- |
| 1 | 0 | 6 | 3 | 7 | `7 < 9`，令 `l = 4`，剩 `[4, 6]`<br>`7 < 9`: set `l = 4`, leaving `[4, 6]` |
| 2 | 4 | 6 | 5 | 11 | `11 > 9`，令 `r = 4`，剩 `[4, 4]`<br>`11 > 9`: set `r = 4`, leaving `[4, 4]` |
| 3 | 4 | 4 | 4 | 9 | 相等，令 `found = 4`，退出循环<br>Equal: set `found = 4` and exit the loop |

答案是**下标 4**，不是数值 9。它对应从 1 开始数的“第 5 个”，但程序按从 0 开始的下标输出 `4`。最后一轮 `l == r` 仍然进入循环，这就是 `<=` 的作用。

The answer is **index 4**, not the value 9. It is the “5th element” when counting from 1, but the program prints the zero-based index `4`. The last iteration still enters the loop when `l == r`; that is why `<=` is needed.

如果把目标改为 `8`，前两轮一样；第三轮看到 `9 > 8`，令 `r = 3`。此时 `l = 4 > r = 3`，循环结束，结果为 `-1`。结束后不要再用越界的边界去访问数组。

If the target changes to `8`, the first two iterations are the same. In the third, `9 > 8` leads to `r = 3`. Now `l = 4 > r = 3`, so the loop ends with result `-1`. After the search ends, do not use out-of-range boundaries to access the array.

<a id="完整示例-8a自己写二分输出找到的下标"></a>
### 完整示例 8A：自己写二分，输出找到的下标 / Complete example 8A: write binary search yourself and print the matching index

输入依次是：非负整数 `n`、`n` 个**已从小到大排好**的整数、目标值 `x`。输出一个从 `0` 开始的下标；不存在就输出 `-1`。当 `n = 0` 时没有数组元素，读完 `n` 就直接读 `x`。

The input is, in order: a nonnegative integer `n`, `n` integers **already sorted in ascending order**, and the target `x`. Print a zero-based index, or `-1` if the target is absent. When `n = 0`, there are no array elements, so read `x` immediately after `n`.

这份程序不自动排序：目的是看清二分本身，也避免悄悄改变题目里的原位置。若实际题目允许排序，可以先 `sort`；此后得到的是**排序后的下标**，不是原输入位置。

This program does not sort automatically: the aim is to make binary search itself clear and avoid silently changing the original positions in the problem. If the actual problem permits sorting, you may call `sort` first; the resulting index then belongs to the **sorted array**, not the original input.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    if (!(cin >> n) || n < 0) {
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (!(cin >> a[i])) {
            return 0;
        }
    }

    int x;
    if (!(cin >> x)) {
        return 0;
    }

    int l = 0;
    int r = n - 1;
    int found = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == x) {
            found = mid;
            break;
        } else if (a[mid] < x) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << found << '\n';
    return 0;
}
```

**输入**：

**Input:**

```text
7
1 3 5 7 9 11 13
9
```

**输出**：

**Output:**

```text
4
```

<a id="别只测找到的情况这些边界也要会解释"></a>
#### 别只测找到的情况：这些边界也要会解释 / Do not test only successful searches: be able to explain these edge cases too

| 数组 a<br>Array a | x | 这份程序的输出<br>This program's output | 原因<br>Reason |
| --- | --- | --- | --- |
| 空数组（`n = 0`）<br>Empty array (`n = 0`) | 42 | `-1` | `l = 0`、`r = -1`，循环一次也不执行，不访问数组<br>`l = 0` and `r = -1`; the loop never runs and the array is not accessed |
| `7` | 7 | `0` | 唯一的格子就在下标 0<br>The only cell is at index 0 |
| `7` | 6 | `-1` | 唯一的数不匹配，排除后范围为空<br>The only value does not match; discarding it leaves an empty range |
| `2 8` | 8 | `1` | 先排除下标 0，再检查下标 1<br>Discard index 0 first, then check index 1 |
| `1 3 5` | 0 或 9<br>0 or 9 | `-1` | 比最小值还小或比最大值还大，都不存在<br>Values smaller than the minimum or larger than the maximum are both absent |
| `1 2 2 2 5` | 2 | `2` | 第一轮中间就找到一个 2，但它不是第一个 2<br>The first iteration finds a 2 in the middle, but not the first 2 |

空数组可以直接输入两行 `0`、`42`，无需补一行数组元素。这里用有符号的 `int n` 计算 `n - 1`，所以空数组时得到 `-1`；不要直接把 `a.size() - 1` 照搬过来，`size()` 返回无符号类型，空数组时减一不会得到期望的负数。

For an empty array, simply enter `0` and `42` on two lines; no line of array elements is needed. Here, `n - 1` uses a signed `int n`, so an empty array gives `-1`. Do not directly substitute `a.size() - 1`: `size()` returns an unsigned type, so subtracting one for an empty array will not give the negative value you expect.

**有重复值时，这个模板只保证找到其中一个匹配位置，不保证第一个或最后一个。** 要求第一次出现，用本节前面的 `lower_bound`，并检查返回位置不是 `end()` 且对应值等于 `x`；要求次数，可以结合 `upper_bound`。

**With duplicate values, this template guarantees only some matching position, not the first or last one.** For the first occurrence, use the earlier `lower_bound` and check that the returned position is not `end()` and its value equals `x`. For the count, combine it with `upper_bound`.

最后记住：

Finally, remember:

- **有序才能排除一半。** 未排序或从大到小的数据，不能直接用这一版；程序不会替你检查是否有序。<br>**You can discard half only because the data is sorted.** This version cannot be used directly on unsorted or descending data, and the program does not check sortedness for you.
- 每轮把候选范围大约缩小一半，二分查找的时间复杂度是 **`O(log n)`**，额外空间是 **`O(1)`**；空数组会直接结束。直观上，约 100 万个数也只需约 20 轮比较。<br>Each iteration roughly halves the candidate range, giving binary search time complexity **`O(log n)`** and extra space **`O(1)`**; an empty array finishes immediately. Intuitively, even about one million numbers require only about 20 comparison rounds.
- 这是查找部分的复杂度。完整程序还需要 `O(n)` 时间读入、`O(n)` 空间保存数组；若另加排序，还要计算排序的时间。<br>These complexities apply to the search itself. The full program also needs `O(n)` time to read the input and `O(n)` space to store the array. If you add sorting, include its running time too.
- 口令：**左 l，右 r，中间 mid；小了往右，大了往左；找到就停，边界交错就没有。**<br>Mnemonic: **left l, right r, middle mid; too small goes right, too large goes left; stop on a match, and crossed boundaries mean no match.**

<a id="lower-bound-guide"></a>
<a id="lower_bound-入门找第一个大于或等于-x-的位置"></a>
### lower_bound 入门：找第一个大于或等于 x 的位置 / Introduction to lower_bound: find the first position with a value greater than or equal to x

**先记一句话：`lower_bound` 找的是“第一个 `>= x` 的位置”，不是“第一个小于 x 的数”，也不保证找到了 x 本身。** 它是 `<algorithm>` 里的现成工具，可以帮你完成一种常见的二分查找。

**Remember this first: `lower_bound` finds “the first position with a value `>= x`,” not “the first number smaller than x,” and it does not guarantee that x itself is present.** It is a ready-made tool in `<algorithm>` for a common form of binary search.

下面统一使用**从小到大排好（允许相等）**的 `vector<int> a` 和默认比较规则。没排好序不能直接套；从大到小的数组也不适用这一写法。若题目允许先排序，可以用 `sort(a.begin(), a.end())`，但查到的下标就属于排序后的数组。

Throughout the following, we use `vector<int> a` **sorted in ascending order (equal values allowed)** and the default comparison. Do not apply this directly to unsorted data; this form is also unsuitable for descending arrays. If the problem permits sorting first, use `sort(a.begin(), a.end())`, but any index you find then belongs to the sorted array.

<a id="第-1-步调用工具得到一个位置"></a>
#### 第 1 步：调用工具，得到一个位置 / Step 1: call the tool to obtain a position

**片段：** `a` 已有序，`x` 是目标值，需要 `<algorithm>` 和 `<vector>`。

**Snippet:** `a` is sorted and `x` is the target; requires `<algorithm>` and `<vector>`.

```cpp
auto it = lower_bound(a.begin(), a.end(), x);
```

把这一行拆开看：

Break down this line:

- `a.begin()`：查找范围的起点。<br>`a.begin()`: the start of the search range.
- `a.end()`：最后一个元素**后面**的位置，不是最后一个元素。<br>`a.end()`: the position **after** the final element, not the final element itself.
- `[a.begin(), a.end())`：左边包含、右边不包含，表示查整个数组。这里使用库函数的半开区间，不是手写模板的闭区间 `[l, r]`。<br>`[a.begin(), a.end())`: includes the left endpoint and excludes the right, meaning the entire array is searched. This is the library function's half-open interval, not the handwritten template's closed interval `[l, r]`.
- `x`：要比较的目标值。<br>`x`: the target value to compare against.
- `it`：返回的**迭代器**，可以先理解成“指向数组某个位置的标记”；它不是数值，也不是整数下标。`it` 是变量名，换个名字也可以。<br>`it`: the returned **iterator**, which you can initially think of as a “marker pointing to a position in the array.” It is neither an element value nor an integer index. `it` is just a variable name; another name would work too.
- `auto`：让编译器推断 `it` 的类型，不需要初学时写出那一长串迭代器类型。<br>`auto`: lets the compiler infer the type of `it`, so beginners do not need to write out the long iterator type.

如果有满足条件的元素，`it` 指向第一个；如果所有元素都小于 `x`，返回 `a.end()`。空数组也会返回 `a.end()`。

If any element meets the condition, `it` points to the first one. If all elements are smaller than `x`, the function returns `a.end()`. An empty array also returns `a.end()`.

<a id="第-2-步要下标就减去起点要数值先确认不是-end"></a>
#### 第 2 步：要下标，就减去起点；要数值，先确认不是 end / Step 2: subtract the start for an index; check against end before reading a value

**片段：** 接在上面一行后面，需要输入输出时另加 `<iostream>`。

**Snippet:** Place this after the preceding line; add `<iostream>` for input/output.

```cpp
auto index = it - a.begin();  // vector 中的位置差，就是从 0 开始的下标
cout << index << '\n';

if (it != a.end()) {
    cout << *it << '\n';     // *it 才是这个位置上的元素值
}
```

- `it - a.begin()` 是从开头走到该位置的距离。这里的 `auto index` 保存的是一个整数，与前面的迭代器 `it` 不是同一种东西。<br>`it - a.begin()` is the distance from the beginning to that position. Here, `auto index` stores an integer, which is different from the iterator `it` above.
- 若 `it == a.end()`，相减仍然合法，结果等于 `a.size()`，即 `n`；**这个结果不是能访问的元素下标**。不能因此去读 `a[n]` 或 `*it`。<br>If `it == a.end()`, subtraction is still valid and equals `a.size()`, namely `n`. **This result is not an index of an element you can access.** It does not allow you to read `a[n]` or `*it`.
- 空数组时 `begin() == end()`，相减得到 `0`，但数组中仍然没有元素，不能访问 `a[0]`。<br>For an empty array, `begin() == end()` and subtraction gives `0`, but there are still no elements, so you cannot access `a[0]`.
- 这套“迭代器相减求下标”适用于这里的 `vector`，不要直接照搬给 `set` 或 `map`。<br>This method of subtracting iterators to obtain indices works for the `vector` here; do not apply it directly to `set` or `map`.

<a id="用同一排数把找到位置和找到目标分清"></a>
#### 用同一排数，把“找到位置”和“找到目标”分清 / Use the same row of numbers to distinguish “finding a position” from “finding the target”

```text
下标：  0   1   2   3   4   5
数值：  1   2   2   2   5   (end)
                            ↑
                       后面没有元素
```

对数组 `1 2 2 2 5`，分别查找下面的 `x`：

For the array `1 2 2 2 5`, search for each of these values of `x`:

| x | 返回位置换成下标<br>Returned position as an index | 能读取的值<br>Value that can be read | x 真的存在吗？<br>Does x actually exist? |
| --- | --- | --- | --- |
| 0 | 0 | 1 | 不存在；1 是第一个 `>= 0` 的数<br>No; 1 is the first number `>= 0` |
| 1 | 0 | 1 | 存在，首次出现下标为 0<br>Yes; its first occurrence is at index 0 |
| 2 | 1 | 2 | 存在，返回三个 2 中最左边的那个<br>Yes; returns the leftmost of the three 2s |
| 3 | 4 | 5 | 不存在；5 是第一个 `>= 3` 的数<br>No; 5 is the first number `>= 3` |
| 5 | 4 | 5 | 存在，首次出现下标为 4<br>Yes; its first occurrence is at index 4 |
| 9 | 5（即 n）<br>5 (that is, n) | 无，返回 `end()`<br>None; returns `end()` | 不存在，所有数都小于 9<br>No; all numbers are smaller than 9 |

可以把返回位置想成一条分界线：它前面的数都 `< x`，从它开始的数都 `>= x`。因此 `it - a.begin()` 也等于数组里**严格小于 x 的元素个数**。若想把 `x` 插入有序数组，这也是一个能保持有序的插入位置；但 `lower_bound` 本身只查找，**不会插入或修改元素**。

Think of the returned position as a dividing line: all numbers before it are `< x`, and all numbers from it onward are `>= x`. Therefore, `it - a.begin()` also equals **the number of elements strictly smaller than x**. If you wanted to insert `x` into the sorted array, this is also a position that would preserve sorted order. However, `lower_bound` only searches; **it does not insert or modify elements**.

这里与前面的手写示例有个重要区别：手写模板看到相等就停止，只保证找到某一个；`lower_bound` 会给出第一个满足 `>= x` 的位置，所以当目标存在时，它能确定首次出现的位置。

There is an important difference from the earlier handwritten example: that template stops at equality and guarantees only some matching position. `lower_bound` returns the first position satisfying `>= x`, so when the target exists, it identifies its first occurrence.

<a id="第-3-步判断-x-是否存在两个条件都不能少"></a>
#### 第 3 步：判断 x 是否存在，两个条件都不能少 / Step 3: test whether x exists; both conditions are essential

**片段：** `it` 是刚才查到的位置。

**Snippet:** `it` is the position just found.

```cpp
if (it != a.end() && *it == x) {
    cout << "first match index: " << it - a.begin() << '\n';
} else {
    cout << "first match index: -1\n";
}
```

为什么需要两个条件？

Why are two conditions needed?

1. `it != a.end()`：先保证这个位置上真的有元素，才可以读 `*it`。<br>`it != a.end()`: first ensure that an element really exists at this position before reading `*it`.
2. `*it == x`：再确认元素等于目标。例如查 `3` 时，`it` 指向 `5`，虽不是 `end()`，仍然没有找到 `3`。<br>`*it == x`: then confirm that the element equals the target. For example, searching for `3` makes `it` point to `5`; although it is not `end()`, `3` has still not been found.

`&&` 从左往右判断，左边为假就不再执行右边，这叫**短路**。所以这里必须先检查 `end()`，不要反过来先读 `*it`。也不能把 `&&` 换成 `||` 或单个 `&`。

`&&` evaluates from left to right and skips the right side if the left side is false. This is called **short-circuiting**. Therefore, check against `end()` first; do not reverse the order and read `*it` first. You also cannot replace `&&` with `||` or a single `&`.

<a id="完整示例-8b同时输出-lower_bound-位置和精确匹配结果"></a>
### 完整示例 8B：同时输出 lower_bound 位置和精确匹配结果 / Complete example 8B: print both the lower_bound position and the exact-match result

输入依次为非负整数 `n`、`n` 个已从小到大排好的整数、目标值 `x`。程序输出三行：第一个 `>= x` 的位置、该位置的值（或 `(end)`）、首次精确匹配的下标（没有就 `-1`）。当 `n = 0` 时，不输入数组元素，直接输入 `x`。

The input is, in order, a nonnegative integer `n`, `n` integers already sorted in ascending order, and the target `x`. The program prints three lines: the first position with a value `>= x`, the value there (or `(end)`), and the index of the first exact match (or `-1` if absent). When `n = 0`, enter no array elements and provide `x` directly.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    if (!(cin >> n) || n < 0) {
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (!(cin >> a[i])) {
            return 0;
        }
    }

    int x;
    if (!(cin >> x)) {
        return 0;
    }

    auto it = lower_bound(a.begin(), a.end(), x);
    auto index = it - a.begin();
    cout << "lower_bound index: " << index << '\n';

    if (it != a.end()) {
        cout << "value: " << *it << '\n';
    } else {
        cout << "value: (end)\n";
    }

    if (it != a.end() && *it == x) {
        cout << "first match index: " << index << '\n';
    } else {
        cout << "first match index: -1\n";
    }
    return 0;
}
```

**输入**：

**Input:**

```text
5
1 2 2 2 5
3
```

**输出**：

**Output:**

```text
lower_bound index: 4
value: 5
first match index: -1
```

这三行正好说明：找到了第一个 `>= 3` 的位置，但没找到数值 `3`。把目标改成 `2`，三行就分别是 `lower_bound index: 1`、`value: 2`、`first match index: 1`。

These three lines illustrate exactly this: the first position with a value `>= 3` was found, but the value `3` was not. Change the target to `2`, and the three lines become `lower_bound index: 1`, `value: 2`, and `first match index: 1`.

再自己试几个边界：

Try a few more edge cases yourself:

- 空数组：输入两行 `0`、`2`，得到位置 `0`、值 `(end)`、精确匹配下标 `-1`。<br>Empty array: enter `0` and `2` on two lines; the position is `0`, the value is `(end)`, and the exact-match index is `-1`.
- 只有 `7`：查 `6` 得到位置 `0`、值 `7`，但精确匹配下标为 `-1`；查 `7` 才是匹配下标 `0`。<br>Only `7`: searching for `6` gives position `0` and value `7`, but the exact-match index is `-1`. Searching for `7` gives match index `0`.
- 只有 `7`：查 `8` 得到位置 `1`、值 `(end)`、精确匹配下标 `-1`。<br>Only `7`: searching for `8` gives position `1`, value `(end)`, and exact-match index `-1`.
- 全是 `2 2 2 2`：查 `2` 返回首次出现的下标 `0`。<br>All equal, `2 2 2 2`: searching for `2` returns its first-occurrence index, `0`.

在这里的 `vector` 上，查找时间是 `O(log n)`；读入数据、可能需要的排序应另外计算。只查有没有可以用 `binary_search`；要第一个位置用 `lower_bound`；要次数可用本节前面的 `upper_bound - lower_bound`。

For the `vector` used here, search time is `O(log n)`; input processing and any required sorting are counted separately. Use `binary_search` if you only need an existence test, `lower_bound` for the first position, and the earlier `upper_bound - lower_bound` for the count.

**复制前检查：数据有序吗？我要的是位置还是值？返回 end 了吗？题目要求精确相等吗？**

**Check before copying: Is the data sorted? Do I need a position or a value? Was end returned? Does the problem require exact equality?**

<a id="binary-search-first-match"></a>
<a id="边界二分找到以后别停继续往左找第一个-x"></a>
### 边界二分：找到以后别停，继续往左找第一个 x / Boundary binary search: do not stop on a match; keep moving left to find the first x

前面的手写示例找到 `x` 就 `break`，所以有重复值时只能保证找到某一个。现在把目标改为：**找到 x 第一次出现的下标；如果不存在，返回 -1。** 数组仍必须从小到大排好。

The earlier handwritten example executes `break` on finding `x`, so with duplicates it guarantees only some matching position. Now change the goal to: **find the index of the first occurrence of x; return -1 if it is absent.** The array must still be sorted in ascending order.

核心变化只有一句：**相等时先用 `ans` 记住答案，再令 `r = mid - 1`，继续检查左边有没有更早的 x。** 这时不能 `break`。

There is only one key change: **on equality, first save the answer in `ans`, then set `r = mid - 1` to continue checking for an earlier x on the left.** Do not `break` here.

**片段：** `a` 是已排序数组，`n` 是非负的 `int` 长度，`x` 是目标值。

**Snippet:** `a` is a sorted array, `n` is its nonnegative `int` length, and `x` is the target.

```cpp
int l = 0;
int r = n - 1;
int ans = -1;

while (l <= r) {
    int mid = l + (r - l) / 2;
    if (a[mid] == x) {
        ans = mid;          // 找到一个，先记下来
        r = mid - 1;        // 继续向左，看看有没有更早的
    } else if (a[mid] < x) {
        l = mid + 1;        // 太小了，去右边
    } else {
        r = mid - 1;        // 太大了，去左边
    }
}
```

可以把 `ans` 理解成“**目前找到的最靠左答案**”：

Think of `ans` as “**the leftmost answer found so far**”:

- 开始为 `-1`，表示还没有找到过相等的数。<br>It starts at `-1`, meaning no equal value has been found yet.
- 遇到相等就更新 `ans`。后面只在它左边继续找，若再找到，新答案的下标一定更小。<br>Update `ans` whenever equality is found. Subsequent searching takes place only to its left, so any later answer must have a smaller index.
- 即使左边没有别的 `x`，之前的答案也已经存在 `ans` 里，不会丢。<br>Even if no other `x` exists on the left, the earlier answer is already stored in `ans` and will not be lost.
- 不相等时不要把 `ans` 重新设为 `-1`，否则会把已经找到的答案清掉。<br>Do not reset `ans` to `-1` on a nonmatch, or you will erase an answer already found.
- 循环结束后读 `ans`，不要把最后计算的 `mid` 当作答案。<br>Read `ans` after the loop ends; do not use the last computed `mid` as the answer.

这里继续使用 `l + (r - l) / 2`，避免合法非负下标较大时 `l + r` 的加法溢出。`l = 0`、`r = n - 1`、`l <= r` 和 `mid ± 1` 仍然是一整套边界约定。

We continue using `l + (r - l) / 2` to avoid overflow in `l + r` when valid nonnegative indices are large. `l = 0`, `r = n - 1`, `l <= r`, and `mid ± 1` still form a consistent set of boundary conventions.

<a id="手算重复值为什么最终得到下标-1而不是-2"></a>
#### 手算重复值：为什么最终得到下标 1，而不是 2？ / Work through duplicates by hand: why does the final answer become index 1 rather than 2?

数组是 `1 2 2 2 5`，目标 `x = 2`，`ans` 最初为 `-1`：

The array is `1 2 2 2 5`, the target is `x = 2`, and `ans` starts at `-1`:

| 轮次<br>Iteration | l | r | mid | a[mid] | ans 的变化<br>Change in ans | 下一步<br>Next step |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 0 | 4 | 2 | 2 | `-1 → 2` | 相等但不停，令 `r = 1`<br>Equal, but keep going; set `r = 1` |
| 2 | 0 | 1 | 0 | 1 | 保持 `2`<br>Keep `2` | 太小，令 `l = 1`<br>Too small; set `l = 1` |
| 3 | 1 | 1 | 1 | 2 | `2 → 1` | 再次相等，令 `r = 0`<br>Equal again; set `r = 0` |

此时 `l = 1 > r = 0`，结束，输出 `ans = 1`。注意第 2 轮没有找到目标，但之前记下的 `2` 仍被保留。

Now `l = 1 > r = 0`, so the loop ends and prints `ans = 1`. Notice that iteration 2 did not find the target, but the previously recorded `2` was retained.

<a id="完整示例-8c手写二分找目标首次出现的下标"></a>
### 完整示例 8C：手写二分，找目标首次出现的下标 / Complete example 8C: handwritten binary search for the target's first-occurrence index

输入格式和示例 8A 相同：非负整数 `n`、`n` 个已从小到大排好的整数、目标值 `x`。输出第一次出现的下标；不存在输出 `-1`。空数组时不输入数组元素，直接输入 `x`。

The input format is the same as example 8A: a nonnegative integer `n`, `n` integers already sorted in ascending order, and the target `x`. Print the first-occurrence index, or `-1` if absent. For an empty array, enter no array elements and provide `x` directly.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    if (!(cin >> n) || n < 0) {
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (!(cin >> a[i])) {
            return 0;
        }
    }

    int x;
    if (!(cin >> x)) {
        return 0;
    }

    int l = 0;
    int r = n - 1;
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == x) {
            ans = mid;
            r = mid - 1;
        } else if (a[mid] < x) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << ans << '\n';
    return 0;
}
```

**输入**：

**Input:**

```text
5
1 2 2 2 5
2
```

**输出**：

**Output:**

```text
1
```

再换几组试试：空数组查任意数得到 `-1`；数组 `7` 查 `7` 得到 `0`，查 `6` 或 `8` 得到 `-1`；数组 `2 2 2 2` 查 `2` 得到 `0`；把上面样例的目标改成 `3`，得到 `-1`。

Try several more cases: searching for any number in an empty array gives `-1`; in array `7`, searching for `7` gives `0`, while `6` or `8` gives `-1`; searching for `2` in `2 2 2 2` gives `0`; changing the preceding sample's target to `3` gives `-1`.

**它与 lower_bound 的原始返回结果不是一回事。** 在 `1 2 2 2 5` 里查 `3`，本例 `ans = -1`；`lower_bound` 则指向下标 `4` 的数值 `5`，因为它找的是第一个 `>= 3`。只有给 `lower_bound` 加上“不是 `end()` 且值等于 `x`”的判断，得到的首次精确匹配结果才与本例一致。

**This is not the same as the raw return value of lower_bound.** Searching for `3` in `1 2 2 2 5` gives `ans = -1` here, whereas `lower_bound` points to the value `5` at index `4`, because it seeks the first value `>= 3`. Only after checking that the `lower_bound` result “is not `end()` and has a value equal to `x`” does its first exact-match result agree with this example.

<a id="如果要找最后一个-x-呢"></a>
#### 如果要找最后一个 x 呢？ / What if you want the last x?

仍在同一个升序数组中查找，把上面循环里**相等时的分支**改为下面这段，其他两个分支不变：

Still searching the same ascending array, replace **the equality branch** in the preceding loop with the following, leaving the other two branches unchanged:

```cpp
if (a[mid] == x) {
    ans = mid;
    l = mid + 1;  // 先记住，再继续向右找更晚的位置
}
```

这是**替换相等分支的片段**，不要在原来的 `if / else if / else` 后面又额外加一个 `if`。例如 `1 2 2 2 5` 查 `2`，最后出现的下标是 `3`。找不到时 `ans` 仍为 `-1`。

This is a **snippet that replaces the equality branch**; do not add a separate `if` after the original `if / else if / else`. For example, searching for `2` in `1 2 2 2 5` gives last-occurrence index `3`. If no match exists, `ans` remains `-1`.

<a id="从找第一次理解找最小--最大满足条件的位置"></a>
#### 从“找第一次”理解“找最小 / 最大满足条件的位置” / From “find the first occurrence” to “find the minimum / maximum position satisfying a condition”

在这一节里，“最小 / 最大”先理解为**最左 / 最右下标**。能用二分排除一半，关键是条件在查找范围内具有**单调性**：真和假不能来回交替，要有清晰的分界。

In this section, interpret “minimum / maximum” first as **leftmost / rightmost index**. The key to discarding half the range with binary search is **monotonicity** of the condition within the search range: true and false must not alternate back and forth; there must be a clear boundary.

| 想找什么<br>What you want to find | 条件从左到右的排列<br>Condition values from left to right | 条件成立时<br>When the condition is true | 条件不成立时<br>When the condition is false |
| --- | --- | --- | --- |
| 第一个满足条件的位置<br>First position satisfying the condition | 假、假、真、真<br>False, false, true, true | `ans = mid; r = mid - 1;`，继续往左<br>`ans = mid; r = mid - 1;`, continuing left | `l = mid + 1;` |
| 最后一个满足条件的位置<br>Last position satisfying the condition | 真、真、假、假<br>True, true, false, false | `ans = mid; l = mid + 1;`，继续往右<br>`ans = mid; l = mid + 1;`, continuing right | `r = mid - 1;` |

两行都允许全真或全假；用 `ans = -1` 初始化，全假时就能表示没找到。仍然要写完整的初始化、`while (l <= r)` 和中点计算。

Both rows allow all-true or all-false cases. Initialize with `ans = -1` so that all-false means no match. You must still include the full initialization, `while (l <= r)`, and midpoint calculation.

对升序数组，`a[mid] >= x` 是“假 → 真”，适合找第一个 `>= x`；`a[mid] <= x` 是“真 → 假”，适合找最后一个 `<= x`。如果题目换成别的条件，必须先证明也有这样的分界，不能只凭“找最小 / 最大”就套模板。

For an ascending array, `a[mid] >= x` changes from “false → true,” making it suitable for finding the first value `>= x`; `a[mid] <= x` changes from “true → false,” making it suitable for finding the last value `<= x`. If a problem uses another condition, first prove that it has such a boundary too. Do not apply the template merely because the problem asks for a “minimum / maximum.”

特别注意：**`a[mid] == x` 本身可能是“假 → 真 → 假”，不能直接塞进这张两分支表。** 上面的首次精确匹配程序之所以正确，是因为它把“小于、等于、大于”分成三种情况，并利用了数组有序。

In particular, **`a[mid] == x` itself may follow “false → true → false,” so it cannot be plugged directly into this two-branch table.** The first-exact-match program above works because it distinguishes three cases, “less than, equal to, greater than,” and relies on the array being sorted.

这些模板每轮仍然排除约一半候选位置，查找部分的时间复杂度为 `O(log n)`、额外空间为 `O(1)`。记忆口令：**找到先记 ans；要更靠左就缩 r，要更靠右就抬 l；方向能不能这么走，先看有序或单调。**

These templates still discard about half the candidate positions each iteration. The search takes `O(log n)` time and `O(1)` extra space. Mnemonic: **save matches in ans first; shrink r to go further left, raise l to go further right; before choosing either direction, check sortedness or monotonicity.**

<a id="binary-search-cheatsheet"></a>
<a id="二分三种写法速查找到就停还是继续找"></a>
### 二分三种写法速查：找到就停，还是继续找？ / Three binary-search forms at a glance: stop on a match or keep searching?

**共同前提：`a` 已从小到大排好，允许重复值。** 下面是核心片段，完整初始化和循环见各行链接；手写模板的答案变量初值为 `-1`，循环结束后读取它（普通二分示例用 `found`，左边界示例用 `ans`）。

**Shared precondition: `a` is sorted in ascending order, with duplicates allowed.** The following gives core snippets; see each row's link for full initialization and loops. Initialize the handwritten template's answer variable to `-1` and read it after the loop finishes (`found` in the ordinary example, `ans` in the left-boundary example).

| 写法<br>Form | 要找什么<br>What it finds | 核心动作 / 返回结果<br>Core action / return value |
| --- | --- | --- |
| [普通二分](#binary-search-lrmid)<br>[Ordinary binary search](#binary-search-lrmid) | 判断 `x` 是否存在，或找任意一个匹配下标<br>Test whether `x` exists, or find any matching index | 遇到 `a[mid] == x` 就 `found = mid; break;`，找到即结束；有重复值时不保证最左边<br>On `a[mid] == x`, execute `found = mid; break;` and stop immediately; duplicates do not guarantee the leftmost match |
| [左边界二分](#binary-search-first-match)<br>[Left-boundary binary search](#binary-search-first-match) | 找 `x` 第一次出现的下标<br>The index of the first occurrence of `x` | 遇到 `a[mid] == x` 就 `ans = mid; r = mid - 1;`，记下后继续向左，不能 `break`；不存在时仍为 `-1`<br>On `a[mid] == x`, execute `ans = mid; r = mid - 1;`, save the match, and continue left without `break`; remains `-1` if absent |
| [STL `lower_bound`](#lower-bound-guide) | 找第一个 `>= x` 的位置<br>The first position with a value `>= x` | `auto it = lower_bound(a.begin(), a.end(), x);`；返回迭代器，没有这样的元素就返回 `a.end()`<br>`auto it = lower_bound(a.begin(), a.end(), x);` returns an iterator, or `a.end()` if no such element exists |

例如 `1 2 2 2 5` 查 `2`：普通二分可能找到中间的 `2`；左边界二分得到下标 `1`；`lower_bound` 也指向下标 `1`。但查 `3` 时，两个精确匹配模板得到 `-1`，`lower_bound` 会指向下标 `4` 的 `5`。

For example, when searching for `2` in `1 2 2 2 5`, ordinary binary search may find the middle `2`; left-boundary binary search gives index `1`; `lower_bound` also points to index `1`. But for target `3`, both exact-match templates give `-1`, whereas `lower_bound` points to `5` at index `4`.

**用 `lower_bound` 判断“是否真有 x”，必须再检查一次：**

**To use `lower_bound` to determine whether x really exists, you must perform an additional check:**

**片段：** `a` 是已排序的 `vector<int>`，`x` 已定义，需要 `<algorithm>`、`<vector>`，并使用 `std` 命名空间。

**Snippet:** `a` is a sorted `vector<int>` and `x` has been defined. Requires `<algorithm>` and `<vector>`, with the `std` namespace in use.

```cpp
auto it = lower_bound(a.begin(), a.end(), x);
bool found = (it != a.end() && *it == x);
```

先检查不是 `end()`，才能读取 `*it`；不是 `end()` 也可能只是找到了更大的数，所以相等判断不能省。`found` 为 `true` 时，`it - a.begin()` 才是 `x` 首次出现的下标。

Check that the iterator is not `end()` before reading `*it`. Even a non-`end()` result may only identify a larger number, so the equality test is essential. Only when `found` is `true` does `it - a.begin()` give the index of x's first occurrence.

**记忆口令：普通二分找到就停；左边界找到先记，再向左；`lower_bound` 找的是第一个大于或等于。**

**Mnemonic: ordinary binary search stops on a match; left-boundary search saves a match and then continues left; `lower_bound` finds the first value greater than or equal to the target.**

<a id="sum"></a>
<a id="10-选读求和时注意-long-long-和-0ll"></a>
## 10. 选读：求和时注意 long long 和 0LL / 10. Optional: Watch `long long` and `0LL` When Summing

一个数能放进 `int`，不代表许多数的总和也能。常见竞赛环境的 `int` 是 32 位，最大约 21 亿；`long long` 通常是 64 位，范围大得多，但也有上限。

A single number fitting in `int` does not mean the sum of many numbers will fit. In common contest environments, `int` is 32 bits, with a maximum of about 2.1 billion; `long long` is usually 64 bits and has a much larger, but still finite, range.

你可以用第 5 节的 `long long total = 0;` 配合循环求和，也可以用 `<numeric>` 中的 `accumulate`。

You can sum values in a loop using `long long total = 0;` from Section 5, or use `accumulate` from `<numeric>`.

**片段：** `v` 已经有数据，并包含 `<numeric>`。

**Snippet:** `v` already contains data, and `<numeric>` has been included.

```cpp
long long total = accumulate(v.begin(), v.end(), 0LL);
```

第三个参数是累加的初始值，还决定**保存每一步累加结果的变量类型**，也叫累加器类型：

The third argument is the initial sum and also determines **the type of the variable that stores the result of every addition**, known as the accumulator type:

- `0` 使累加器为 `int`，每一步结果都要存回 `int`，可能容纳不下。<br>
  `0` makes the accumulator an `int`. Each intermediate result must be stored back in an `int` and may not fit.
- `0LL` 使累加器为 `long long`，从一开始就用更大的类型保存每一步结果。<br>
  `0LL` makes the accumulator a `long long`, so the larger type stores every intermediate result from the start.
- 仅把最终接收变量写成 `long long`，不能补救中途超出类型范围的问题。<br>
  Declaring only the variable receiving the final result as `long long` cannot fix an out-of-range intermediate calculation.

用 `long long` 也要保证每次相加的中间结果都在它的范围内，不能只看最后的答案是否放得下。

Even with `long long`, every intermediate sum must fit in its range. Checking only whether the final answer fits is not enough.

<a id="完整示例-9求一个超过常见-int-范围的总和"></a>
### 完整示例 9：求一个超过常见 int 范围的总和 / Complete Example 9: Compute a Sum Beyond the Usual `int` Range

```cpp
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
    vector<long long> v = {2000000000LL, 2000000000LL, 2000000000LL};
    long long total = accumulate(v.begin(), v.end(), 0LL);
    cout << total << '\n';
    return 0;
}
```

**输入**：无需输入。

**Input:** None required.

**输出**：

**Output:**

```text
6000000000
```

类似地，如果 `a`、`b` 是 `int`，需要大整数乘法时应让**计算本身**进入 `long long`，例如 `1LL * a * b`；仅写 `long long result = a * b;` 仍可能先发生 `int` 溢出。

Similarly, if `a` and `b` are `int` values and you need multiplication with a larger integer range, make **the calculation itself** use `long long`, for example `1LL * a * b`. Merely writing `long long result = a * b;` may still cause `int` overflow before assignment.

<a id="containers"></a>
<a id="11-选读再认识三种常用工具"></a>
## 11. 选读：再认识三种常用工具 / 11. Optional: Three More Common Tools

先记住用途就好，不必一次掌握全部操作。

Start by remembering what each tool is for; you do not need to learn every operation at once.

| 工具<br>Tool | 适合做什么<br>Best suited to | 直观类比<br>Everyday analogy |
| --- | --- | --- |
| `map` | 给每个名字或数字关联一个值，比如统计次数<br>Associate a value with each name or number, for example to count occurrences | “单词 → 次数”的表<br>A “word → count” table |
| `queue` | 按进入顺序处理，先来的先处理<br>Process items in arrival order, first in, first out | 排队<br>A waiting line |
| `stack` | 后放入的先处理<br>Process the most recently added item first | 叠盘子，先拿最上面一个<br>Stacked plates: take the top one first |

<a id="map统计每个单词出现几次"></a>
### map：统计每个单词出现几次 / `map`: Count How Often Each Word Appears

需要 `<map>`。`map<string, int> count;` 表示“键是字符串，值是整数”。这里**键**就是要统计的单词，**值**就是次数。

Requires `<map>`. `map<string, int> count;` means “string keys and integer values.” Here, the **key** is the word being counted, and the **value** is its number of occurrences.

`count[word]++` 的意思是把这个单词的次数加 1；对于这个类型的 `map`，若该单词还不存在，`operator[]` 会先插入它，并把对应的整数初始化为 `0`，再加 1。

`count[word]++` increases this word's count by 1. For this type of `map`, if the word is not yet present, `operator[]` first inserts it and initializes its associated integer to `0`, then increments it.

所以 `count[word]` 不只是查询，还可能添加新键。只想判断是否存在时，可以用 `count.find(word) != count.end()`。

Therefore, `count[word]` is not just a lookup: it may add a new key. To test only whether a key exists, use `count.find(word) != count.end()`.

<a id="完整示例-10单词计数"></a>
### 完整示例 10：单词计数 / Complete Example 10: Word Counts

```cpp
#include <iostream>
#include <map>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);

    map<string, int> count;
    string word;
    while (ss >> word) {
        count[word]++;
    }

    for (const auto& entry : count) {
        cout << entry.first << ' ' << entry.second << '\n';
    }
    return 0;
}
```

**输入**：

**Input:**

```text
banana apple banana pear apple banana
```

**输出**：

**Output:**

```text
apple 2
banana 3
pear 1
```

这里遍历 `map` 时按键从小到大输出；对样例中的小写英文单词，可以理解成字典顺序，不是首次出现顺序。

This traversal of `map` outputs keys in ascending order. For the lowercase English words in this example, think of it as dictionary order, not the order in which the words first appeared.

每个 `entry` 是一个“键和值组成的对”：`entry.first` 是单词，`entry.second` 是次数。`const auto&` 可以先读成“给当前元素起一个只读的别名，不复制它”，暂时不需要深入引用的全部规则。

Each `entry` is a “key-value pair”: `entry.first` is the word, and `entry.second` is the count. For now, read `const auto&` as “give the current element a read-only alias without copying it”; you do not yet need all the rules for references.

<a id="queue-和-stack只从规定的一端取数据"></a>
### queue 和 stack：只从规定的一端取数据 / `queue` and `stack`: Retrieve Data Only from the Designated End

- `queue<int> q;` 需要 `<queue>`：`push(x)` 加到队尾，`front()` 看队头，`pop()` 删除队头。<br>
  `queue<int> q;` requires `<queue>`: `push(x)` adds to the back, `front()` inspects the front, and `pop()` removes the front.
- `stack<int> st;` 需要 `<stack>`：`push(x)` 压到栈顶，`top()` 看栈顶，`pop()` 删除栈顶。<br>
  `stack<int> st;` requires `<stack>`: `push(x)` adds to the top, `top()` inspects the top, and `pop()` removes the top.
- 两者都可以用 `empty()` 判断是否为空、`size()` 查询数量。<br>
  Both support `empty()` to test whether they are empty and `size()` to get the number of elements.
- **pop() 不返回元素**，要先 `front()` 或 `top()` 读取，再 `pop()`。<br>
  **`pop()` does not return the element.** Read it with `front()` or `top()` first, then call `pop()`.
- 空容器不能调用这些读取或删除操作，先检查 `empty()`。<br>
  Do not call these access or removal operations on an empty container; check `empty()` first.

<a id="完整示例-11同样放入-123取出顺序不同"></a>
### 完整示例 11：同样放入 1、2、3，取出顺序不同 / Complete Example 11: Insert the Same 1, 2, 3, but Retrieve Them in Different Orders

```cpp
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int main() {
    queue<int> q;
    stack<int> st;
    for (int x = 1; x <= 3; x++) {
        q.push(x);
        st.push(x);
    }

    cout << "queue:";
    while (!q.empty()) {
        cout << ' ' << q.front();
        q.pop();
    }
    cout << '\n';

    cout << "stack:";
    while (!st.empty()) {
        cout << ' ' << st.top();
        st.pop();
    }
    cout << '\n';
    return 0;
}
```

**输入**：无需输入。

**Input:** None required.

**输出**：

**Output:**

```text
queue: 1 2 3
stack: 3 2 1
```

`!q.empty()` 表示“q 不是空的”，所以每轮都能安全读取队头；`stack` 同理。

`!q.empty()` means “q is not empty,” so reading the front is safe in every iteration. The same reasoning applies to `stack`.

<a id="practice"></a>
<a id="12-小练习与提交前检查"></a>
## 12. 小练习与提交前检查 / 12. Short Exercises and a Pre-submission Checklist

<a id="先自己改再看提示"></a>
### 先自己改，再看提示 / Try Your Own Changes Before Reading the Hints

1. 把示例 2 改成从大到小输出排序结果。去重的 `set<int>` 输出顺序会跟着变吗？<br>
   Modify Example 2 to output its sorted results in descending order. Will the output order of the deduplicating `set<int>` change as well?
2. 输入 `5` 和 `4 4 1 2 1`，输出有多少种不同的数。<br>
   Given `5` followed by `4 4 1 2 1`, output the number of distinct values.
3. 输入一整行英文，统计单词数量。连续两个空格应不应该多算一个单词？<br>
   Read a whole line of English and count its words. Should two consecutive spaces count as an extra word?
4. 在排好序的 `1 2 2 2 5` 里，分别查找 `0`、`2`、`3`、`9`，检查每个数出现几次。<br>
   In the sorted sequence `1 2 2 2 5`, search separately for `0`, `2`, `3`, and `9`, and check how often each occurs.

<details>
<summary>点击看提示和预期结果 | Click for Hints and Expected Results</summary>

1. 用 `sort(v.rbegin(), v.rend())` 改变 `vector` 的排序方向。默认 `set<int>` 仍按从小到大遍历，因为它有自己的排序规则。<br>
   Use `sort(v.rbegin(), v.rend())` to reverse the sorting direction of the `vector`. A default `set<int>` still iterates in ascending order because it has its own ordering rule.
2. 可以把输入放进 `set`，再输出它的 `size()`。不同的数是 `1 2 4`，答案为 `3`。<br>
   Insert the input into a `set`, then output its `size()`. The distinct values are `1 2 4`, so the answer is `3`.
3. 用 `getline`、`stringstream`、`string word`，每次 `ss >> word` 成功就计数加 1。连续空白不会产生额外单词。<br>
   Use `getline`, `stringstream`, and `string word`, increasing the count by 1 each time `ss >> word` succeeds. Consecutive whitespace does not produce extra words.
4. 用 `upper_bound(...) - lower_bound(...)` 得到次数，结果分别为 `0`、`3`、`0`、`0`。先保证序列从小到大。<br>
   Use `upper_bound(...) - lower_bound(...)` to obtain the counts, which are `0`, `3`, `0`, and `0`, respectively. First ensure that the sequence is in ascending order.

</details>

<a id="每次复制前问自己这几件事"></a>
### 每次复制前，问自己这几件事 / Ask Yourself These Questions Before Copying Code

- 我需要保留原顺序吗？`sort`、`set` 和排序去重会改变顺序。<br>
  Do I need to preserve the original order? `sort`, `set`, and sorting followed by deduplication change the order.
- 我要读一个词，还是完整一行？数字后接整行是否处理了换行？<br>
  Am I reading one word or an entire line? If a whole line follows a number, have I handled the newline?
- 容器里真的有这么多元素吗？`reserve` 不等于 `resize`，`end()` 也不是最后一个元素。<br>
  Does the container really contain this many elements? `reserve` is not `resize`, and `end()` is not the last element.
- 二分前数据是从小到大的吗？找不到时有没有先检查 `end()`？<br>
  Is the data in ascending order before binary search? Have I checked for `end()` when no match is found?
- 总和或乘积会不会超出类型范围？`accumulate` 的初始值用对了吗？<br>
  Could the sum or product exceed the type's range? Have I chosen the correct initial value for `accumulate`?
- 题目输出只要求答案吗？示例中的 `sorted:`、`size:` 等标签用于讲解，提交题目时按题面要求调整。<br>
  Does the problem require only the answer in its output? Labels such as `sorted:` and `size:` are for explanation; adjust them to the problem statement before submitting.

再试几组边界数据：`n = 0`、只有一个数、全部相同、包含负数、文本为空。能解释这些输入会发生什么，比单纯背下代码更有用。

Try more boundary cases: `n = 0`, a single number, all values equal, negative numbers, and empty text. Being able to explain what happens for these inputs is more useful than simply memorizing code.

<a id="c-file-io"></a>
<a id="13-选读c-文件读写按五类选择函数"></a>
## 13. 选读：C 文件读写，按五类选择函数 / 13. Optional: C File I/O, Choosing Functions by Five Categories

先记住顺序：**`fopen()` 打开 → `fgetc()` 读取 / `fprintf()` 写入 → `fclose()` 关闭。**

Remember the sequence first: **open with `fopen()` → read with `fgetc()` / write with `fprintf()` → close with `fclose()`.**

前面的示例主要使用 C++；这一节单独介绍 **C 标准库**的文件操作。完整示例保存成 `.c` 文件，只需要 `#include <stdio.h>`，不需要 `using namespace std;`。文件里的数据能保留下来，下次运行程序时还可以读取。

The earlier examples mainly use C++; this section separately introduces file operations in the **C standard library**. Save complete examples as `.c` files. They need only `#include <stdio.h>`, not `using namespace std;`. Data stored in a file remains available to read the next time the program runs.

<a id="c-file-function-choice"></a>
<a id="先按五类选函数不必把十个名字混着背"></a>
### 先按五类选函数，不必把十个名字混着背 / Choose Among Five Categories First, Rather Than Memorizing Ten Mixed-up Names

**先问“读还是写”，再问“这次处理什么数据”。** 打开、关闭负责整个过程；中间按字符、字符串、格式化数据或二进制数据块，选择一对读写函数。

**First ask “reading or writing?”, then “what kind of data am I handling this time?”** Opening and closing bracket the entire process. In between, choose a pair of read/write functions for characters, strings, formatted data, or binary blocks.

| 类别<br>Category | 读取 / 开始<br>Read / start | 写入 / 结束<br>Write / finish | 什么时候选<br>When to choose it |
| --- | --- | --- | --- |
| 1. 打开与关闭<br>1. Opening and closing | `fopen` 打开<br>`fopen` opens | `fclose` 关闭<br>`fclose` closes | 每次操作文件的开始和收尾<br>The beginning and end of each file operation |
| 2. 单个字符<br>2. Individual characters | `fgetc` | `fputc` | 一次处理一个字节，例如逐字节复制<br>Process one byte at a time, for example byte-by-byte copying |
| 3. 字符串<br>3. Strings | `fgets` | `fputs` | 读取一行或行的一部分，或原样写出字符串<br>Read a line or part of a line, or write a string as-is |
| 4. 格式化数据<br>4. Formatted data | `fscanf` | `fprintf` | 按 `%d`、`%s` 等格式，把数字/字符串与文本互相转换<br>Convert between numbers/strings and text according to formats such as `%d` and `%s` |
| 5. 二进制数据块<br>5. Binary blocks | `fread` | `fwrite` | 按“每个元素的大小 × 元素个数”读写内存中的数据<br>Read or write data in memory as “size of each element × number of elements” |

例如：读一个字节选 `fgetc`；读带空格的一行先考虑 `fgets`；把文本 `90` 读成整数选 `fscanf`；把整数的内存表示原样存起来选 `fwrite`。`fread` 不会自动把数字文本解析成整数。

For example, choose `fgetc` to read one byte; consider `fgets` first for a line containing spaces; choose `fscanf` to read the text `90` as an integer; choose `fwrite` to store an integer's memory representation unchanged. `fread` does not automatically parse numeric text into integers.

这里的“字符串”指 C 字符数组中的文本，不是前面 C++ 的 `string`。`fgets` 受数组容量限制，长行可能分几次读；`fputs` 不自动补换行，需要时自己在字符串中写 `\n`。详细返回值与边界见下文，不必另背一套规则。

“String” here means text in a C character array, not the C++ `string` used earlier. `fgets` is limited by the array's capacity, so a long line may require several reads. `fputs` does not add a newline automatically; include `\n` in the string when needed. Detailed return values and boundary cases appear below, so there is no separate set of rules to memorize.

**顺序永远是：打开并判空 → 读写并检查结果 → 关闭并检查结果。** 把 `fopen/fclose` 归为一类，不代表打开后马上关闭再读写；关闭后的旧文件流不能继续使用。

**The order is always: open and check for a null pointer → read/write and check the result → close and check the result.** Grouping `fopen/fclose` together does not mean closing immediately after opening and then performing I/O. A closed stream can no longer be used.

- 文本读取用 `"r"`，覆盖写入用 `"w"`，末尾追加用 `"a"`；二进制读取/覆盖写入用 `"rb"` / `"wb"`。<br>
  Use `"r"` to read text, `"w"` to overwrite, and `"a"` to append at the end; use `"rb"` / `"wb"` for binary reading/overwriting.
- `"w"`、`"wb"` 在打开成功时就清空旧内容。以下示例各自独立，只在空练习目录运行；不要把多个完整程序拼在一起，也不要换成有用文件的路径。<br>
  `"w"` and `"wb"` clear existing contents as soon as opening succeeds. The following examples are independent; run them only in an empty practice directory. Do not combine complete programs or change their paths to files you need to keep.
- 读取先看是否成功：`fgetc` 用 `int` 接收并比较 `EOF`；`fgets` 检查是否为 `NULL`；`fscanf` 检查成功赋值项数；`fread/fwrite` 检查完整元素个数。读完或失败后，用 `ferror` 判断读取错误；最后别漏查 `fclose`。<br>
  First check whether reading succeeded: receive `fgetc` in an `int` and compare against `EOF`; check `fgets` for `NULL`; check the number of successful assignments from `fscanf`; check the number of complete elements from `fread/fwrite`. After reading finishes or fails, use `ferror` to check for a read error. Do not forget to check `fclose` at the end.

不重复抄代码，按需要跳到现有完整示例：

Rather than copying the code again, jump to the existing complete example you need:

- [示例 12：写入文本，再逐字节读回](#c-file-text-demo)，练习打开、关闭、格式化写入和字符读取。<br>
  [Example 12: Write Text, Then Read It Back Byte by Byte](#c-file-text-demo), to practice opening, closing, formatted output, and character input.
- [示例 13：逐字节复制文件](#c-file-copy-demo)，练习 `fgetc/fputc` 配对。<br>
  [Example 13: Copy a File Byte by Byte](#c-file-copy-demo), to practice the `fgetc/fputc` pair.
- [示例 14：写出并读回一个二进制整数](#c-file-binary-demo)，练习 `fwrite/fread` 配对。<br>
  [Example 14: Write and Read Back a Binary Integer](#c-file-binary-demo), to practice the `fwrite/fread` pair.
- 字符串与格式化读取的独立片段，见下文“再补四个常用函数”。<br>
  For separate string-input and formatted-input snippets, see “Four More Common Functions” below.

<a id="先掌握的八个文件操作函数"></a>
### 先掌握的八个文件操作函数 / Eight File Functions to Learn First

`FILE *fp` 是“指向文件流的指针”。初学时可以把 `fp` 理解成程序操作已打开文件的入口；它不是文件名，也不是文件内容。

`FILE *fp` is a “pointer to a file stream.” As a beginner, think of `fp` as the program's handle for working with an opened file. It is neither the filename nor the file's contents.

下面的英文是帮助记忆函数名的助记说法；星级表示本节建议的学习顺序：⭐⭐⭐ 先掌握，⭐⭐ 接着学，并不是所有场景下的绝对重要性排名。

The English phrases below are mnemonics to help you remember the function names. The stars indicate this section's suggested learning order: ⭐⭐⭐ learn first, ⭐⭐ learn next. They are not an absolute ranking of importance in every situation.

建议学习顺序：**先熟练 `fopen` → `fclose` → `fgetc` → `fprintf`，再学习 `fgets` → `fscanf` → `fputc` → `fputs`。**

Suggested learning order: **first become comfortable with `fopen` → `fclose` → `fgetc` → `fprintf`, then learn `fgets` → `fscanf` → `fputc` → `fputs`.**

| 函数<br>Function | 英文助记<br>English mnemonic | 作用<br>Purpose | 返回值要点<br>Key return-value facts | 学习优先级<br>Learning priority |
| --- | --- | --- | --- | --- |
| `fopen()` | File Open | 打开文件<br>Open a file | 成功返回 `FILE *`，失败返回 `NULL`<br>Returns a `FILE *` on success, `NULL` on failure | ⭐⭐⭐ |
| `fclose()` | File Close | 关闭文件，尝试写出缓冲的输出<br>Close a file, attempting to write buffered output | 成功返回 `0`，失败返回 `EOF`<br>Returns `0` on success, `EOF` on failure | ⭐⭐⭐ |
| `fgetc()` | File Get Character | 读取一个字符（字节），并向后移动<br>Read one character (byte) and advance | 成功返回字节值（转换为 `int`），文件结束或读取错误时返回 `EOF`<br>Returns the byte value converted to `int` on success, or `EOF` at end-of-file or on a read error | ⭐⭐⭐ |
| `fprintf()` | File Print Formatted | 格式化写入文件<br>Write formatted output to a file | 成功返回写出的字符数，出错返回负数<br>Returns the number of characters written on success, or a negative value on error | ⭐⭐⭐ |
| `fputc()` | File Put Character | 写入一个字符（字节）<br>Write one character (byte) | 成功返回写出的字节值（转换为 `int`），失败返回 `EOF`<br>Returns the written byte value converted to `int` on success, or `EOF` on failure | ⭐⭐ |
| `fgets()` | File Get String | 读取一行或其中一部分，最多 `n - 1` 个字节<br>Read a line or part of one, up to `n - 1` bytes | 成功返回缓冲区指针；未读到数据就结束或读取错误时返回 `NULL`<br>Returns the buffer pointer on success; returns `NULL` if end-of-file occurs before any data is read, or on a read error | ⭐⭐ |
| `fputs()` | File Put String | 写入一个字符串，不自动补换行<br>Write a string without automatically adding a newline | 成功返回非负值，失败返回 `EOF`<br>Returns a nonnegative value on success, `EOF` on failure | ⭐⭐ |
| `fscanf()` | File Scan Formatted | 格式化读取文件<br>Read formatted input from a file | 返回成功赋值的项数；首次转换前发生输入失败时返回 `EOF`<br>Returns the number of successfully assigned items; returns `EOF` if input failure occurs before the first conversion | ⭐⭐ |

<a id="fileeofnull-都不是函数"></a>
### FILE、EOF、NULL 都不是函数 / `FILE`, `EOF`, and `NULL` Are Not Functions

- **`FILE` 是 `<stdio.h>` 提供的文件流相关类型，不是函数。** `FILE *fp` 声明的是文件流指针；成功打开后，通过这个指针操作文件，不需要自己修改 `FILE` 的内部内容。<br>
  **`FILE` is a type related to file streams provided by `<stdio.h>`, not a function.** `FILE *fp` declares a file-stream pointer. After a successful open, use this pointer to work with the file; you do not need to modify the internals of `FILE` yourself.
- **`EOF` 是 `<stdio.h>` 定义的负 `int` 宏常量，不是函数，也不是文件中的字符。** 对 `fgetc` 来说，它可能表示文件读完，也可能表示读取错误。读取后用 `ferror(fp)` 检查错误，用 `feof(fp)` 检查是否已经遇到文件尾；不要用 `feof` 预测下一次读取是否成功。<br>
  **`EOF` is a negative `int` macro constant defined by `<stdio.h>`, not a function or a character stored in the file.** For `fgetc`, it can indicate either end-of-file or a read error. After reading, use `ferror(fp)` to check for an error and `feof(fp)` to check whether end-of-file has already been encountered. Do not use `feof` to predict whether the next read will succeed.
- **`NULL` 是表示空指针常量的宏，不是函数。** `fopen` 返回 `NULL` 表示打开失败；不能继续用这个空指针读取、写入或关闭文件。<br>
  **`NULL` is a macro representing a null pointer constant, not a function.** A `NULL` result from `fopen` means opening failed; do not use that null pointer to read, write, or close a file.

<a id="fopen先选对模式再检查是否打开成功"></a>
### fopen：先选对模式，再检查是否打开成功 / `fopen`: Choose the Right Mode, Then Check Whether Opening Succeeded

| 模式<br>Mode | 用途<br>Purpose | 文件不存在时<br>If the file does not exist | 文件已经存在时<br>If the file already exists |
| --- | --- | --- | --- |
| `"r"` | 只读<br>Read only | 打开失败，返回 `NULL`<br>Opening fails and returns `NULL` | 从开头读取，不修改内容<br>Read from the beginning without changing the contents |
| `"w"` | 只写<br>Write only | 尝试创建<br>Attempt to create it | **打开成功时立即清空旧内容**，再从开头写入<br>**Immediately clear the old contents when opening succeeds**, then write from the beginning |
| `"a"` | 追加写入<br>Append | 尝试创建<br>Attempt to create it | 保留旧内容，每次写入都追加到末尾<br>Preserve old contents and append every write at the end |

创建文件仍可能因为路径错误、目录不存在或权限不足而失败。**看到 `"w"`，先确认这个文件可以被清空。** 只想读文件时不要用 `"w"`。

Creating a file can still fail because of an incorrect path, a missing directory, or insufficient permissions. **Whenever you see `"w"`, first confirm that the file may be cleared.** Do not use `"w"` if you only want to read a file.

`"example.txt"` 是相对路径，通常相对于程序运行时的**工作目录**，不一定是 `.c` 源文件所在目录。编辑器的运行设置可能改变工作目录；找不到文件时，先检查目录和文件名。

`"example.txt"` is a relative path, normally interpreted relative to the program's **working directory** when it runs, which is not necessarily the directory containing the `.c` source file. An editor's run settings may change the working directory. If a file cannot be found, check the directory and filename first.

**片段：** 已包含 `<stdio.h>`，放在 `main` 内。

**Snippet:** `<stdio.h>` has been included; place this inside `main`.

```c
FILE *fp = fopen("example.txt", "r");
if (fp == NULL) {
    perror("fopen");
    return 1;
}
/* 打开成功后，才能用 fp 读取；用完还要 fclose(fp)。 */
```

`NULL` 表示没有得到可用的文件流；此时不能把 `fp` 传给 `fgetc`、`fprintf` 或 `fclose`。`perror` 是辅助报错函数，向标准错误输出打印提示；`return 1;` 表示程序失败结束。

`NULL` means no usable file stream was obtained; in that case, do not pass `fp` to `fgetc`, `fprintf`, or `fclose`. `perror` is a helper that prints an error message to standard error; `return 1;` ends the program with a failure status.

<a id="fgetc用-int-接住结果再与-eof-比较"></a>
### fgetc：用 int 接住结果，再与 EOF 比较 / `fgetc`: Receive the Result in an `int`, Then Compare It with `EOF`

**片段：** `fp` 已经成功以读取模式打开。

**Snippet:** `fp` has already been opened successfully in a reading mode.

```c
int ch;
while ((ch = fgetc(fp)) != EOF) {
    putchar(ch);
}
```

- `ch = fgetc(fp)`：先读一次，把返回值存进 `ch`。<br>
  `ch = fgetc(fp)`: perform one read and store the return value in `ch`.
- `!= EOF`：只有确实读到数据，才进入循环体；空文件第一次读取就返回 `EOF`，不会输出字符。<br>
  `!= EOF`: enter the loop body only when data was actually read. An empty file returns `EOF` on the first read, so no characters are output.
- `putchar(ch)`：把刚读到的字符显示到屏幕；空格和换行也会照常读出、显示。<br>
  `putchar(ch)`: display the character just read on the screen. Spaces and newlines are also read and displayed normally.
- **`ch` 必须用 `int`，不要用 `char`。** 要同时保留所有字节值和特殊标记 `EOF`，提前存进 `char` 可能丢失信息，导致提前结束或无法结束。<br>
  **`ch` must be an `int`, not a `char`.** It must preserve both all byte values and the special marker `EOF`. Storing the result in a `char` first can lose information, causing the loop to stop too early or fail to stop.
- `EOF` 是 `<stdio.h>` 定义的标记，不是文件里真的存着一个叫 EOF 的字符。读取错误也会返回 `EOF`；循环后用 `ferror(fp)` 检查是否出错，完整示例会演示。<br>
  `EOF` is a marker defined by `<stdio.h>`, not an actual character named EOF stored in the file. Read errors also return `EOF`; check `ferror(fp)` after the loop for errors, as shown in the complete example.

这里按字节读取，适合先练习英文文本。UTF-8 中文的一个汉字通常占多个字节，不能把一次 `fgetc` 理解成读完一个汉字。不要用 `while (!feof(fp))` 判断“下一次有没有数据”：先调用读取函数，再检查这次的结果。

This reads byte by byte, so English text is a good starting point for practice. A Chinese character in UTF-8 usually occupies multiple bytes; one call to `fgetc` should not be understood as reading an entire Chinese character. Do not use `while (!feof(fp))` to decide “whether the next read has data.” Call the input function first, then check that read's result.

<a id="四种单字符操作数据从哪里来到哪里去"></a>
### 四种单字符操作：数据从哪里来，到哪里去 / Four Single-character Operations: Where Data Comes From and Where It Goes

| 操作<br>Operation | 数据流向<br>Data flow | 常见理解<br>Common interpretation |
| --- | --- | --- |
| `getchar()` | 标准输入 `stdin` → 程序<br>Standard input `stdin` → program | 通常从键盘读取一个字符<br>Usually read one character from the keyboard |
| `fputc(ch, fp)` | 程序 → `fp` 指向的文件流<br>Program → file stream pointed to by `fp` | 向已打开的文件写入一个字符<br>Write one character to an opened file |
| `fgetc(fp)` | `fp` 指向的文件流 → 程序<br>File stream pointed to by `fp` → program | 从已打开的文件读取一个字符<br>Read one character from an opened file |
| `putchar(ch)` | 程序 → 标准输出 `stdout`<br>Program → standard output `stdout` | 通常向屏幕输出一个字符<br>Usually output one character to the screen |

这里的“键盘”和“屏幕”是常见情况；`stdin`、`stdout` 可以被重定向到文件或管道，所以不要把它们和物理设备完全等同。可以把 `getchar()` 理解为 `fgetc(stdin)`，把 `putchar(ch)` 理解为 `fputc(ch, stdout)`。

“Keyboard” and “screen” describe common cases; `stdin` and `stdout` can be redirected to files or pipes, so they are not identical to physical devices. You can think of `getchar()` as `fgetc(stdin)` and `putchar(ch)` as `fputc(ch, stdout)`.

下面是**两个独立的核心片段，不是完整程序，也不要直接连在一起执行**。已包含 `<stdio.h>`；`fp` 已按说明成功打开；`int status = 0;` 用来记录错误。

The following are **two independent core snippets, not complete programs; do not simply run them one after the other**. `<stdio.h>` has been included, `fp` has been opened successfully as specified, and `int status = 0;` is used to record errors.

**片段 A：键盘 → 程序 → 文件。** `fp` 以 `"w"` 或 `"a"` 模式打开，只处理这次读到的一个字符。

**Snippet A: keyboard → program → file.** `fp` is opened in `"w"` or `"a"` mode. This handles only the single character read by this call.

```c
int ch = getchar();                        // 标准输入（通常是键盘）→ 程序
if (ch != EOF && fputc(ch, fp) == EOF) {     // 程序 → 文件
    perror("write character");
    status = 1;
}
```

**片段 B：文件 → 程序 → 屏幕。** `fp` 以 `"r"` 模式打开，只处理这次读到的一个字符。

**Snippet B: file → program → screen.** `fp` is opened in `"r"` mode. This handles only the single character read by this call.

```c
int ch = fgetc(fp);                        // 文件 → 程序
if (ch != EOF && putchar(ch) == EOF) {       // 程序 → 标准输出（通常是屏幕）
    perror("display character");
    status = 1;
}
```

- `&&` 从左往右判断；如果 `ch == EOF`，右边的输出函数不会执行，避免把 EOF 当成普通字符写出去。<br>
  `&&` evaluates from left to right. If `ch == EOF`, the output function on the right is not called, preventing EOF from being written as an ordinary character.
- `getchar()` 和 `fgetc()` 都用 `int` 接收结果。`EOF` 也可能表示读取错误：片段 A 后检查 `ferror(stdin)`，片段 B 后检查 `ferror(fp)`；不能把所有 EOF 都当作正常读完。<br>
  Receive the results of both `getchar()` and `fgetc()` in an `int`. `EOF` can also indicate a read error: check `ferror(stdin)` after Snippet A and `ferror(fp)` after Snippet B. Do not assume every EOF means normal completion.
- 空格和换行也是字符。在终端输入 `A` 再按回车，通常先读到 `'A'`，下一次读取才会读到 `'\n'`；一次 `getchar()` 不会自动读完或丢弃整行。<br>
  Spaces and newlines are characters too. If you type `A` in a terminal and press Enter, the first read usually obtains `'A'`, and the next obtains `'\n'`. One call to `getchar()` does not automatically consume or discard an entire line.
- 两段分别对应“读入再写出”的两条路线。用完文件都要检查 `fclose(fp)`；片段 B 的屏幕输出还要检查 `fflush(stdout)`，完整错误处理可参照后面的完整示例。<br>
  The two snippets illustrate two different “read, then write” routes. In both cases, check `fclose(fp)` when finished with the file. For Snippet B's screen output, also check `fflush(stdout)`. Refer to the later complete example for full error handling.

<a id="fprintf比-printf-多一个写到哪里"></a>
### fprintf：比 printf 多一个“写到哪里” / `fprintf`: Like `printf`, but with an Extra “Where to Write” Argument

`printf("score=%d\n", score);` 通常把文本显示到屏幕；`fprintf(fp, "score=%d\n", score);` 则写进 `fp` 对应的文件。

`printf("score=%d\n", score);` usually displays text on the screen, whereas `fprintf(fp, "score=%d\n", score);` writes it to the file associated with `fp`.

- `%d` 对应 `int`，`%s` 对应字符串，`%c` 对应字符，`\n` 表示换行；格式和实参类型必须匹配。<br>
  `%d` corresponds to `int`, `%s` to a string, `%c` to a character, and `\n` to a newline. Format specifiers must match the argument types.
- 例如 `score` 为 `90` 时，文件得到一行 `score=90`，不是二进制形式的整数。<br>
  For example, if `score` is `90`, the file receives the text line `score=90`, not an integer in binary representation.
- 检查 `fprintf(...) < 0` 可以发现写入错误；没有立即报错，也仍需检查后面的 `fclose`，因为数据可能暂存在缓冲区中。<br>
  Checking `fprintf(...) < 0` can detect a write error. Even if no error is reported immediately, still check the subsequent `fclose`, because data may temporarily remain in a buffer.
- 如果要原样写入一个字符串 `text`，用 `fprintf(fp, "%s", text)`；不要把内容不确定的 `text` 直接当作格式串。<br>
  To write a string `text` as-is, use `fprintf(fp, "%s", text)`. Do not directly use `text` as the format string when its contents are uncertain.

<a id="c-file-text-demo"></a>
<a id="完整示例-12先写入文件再逐字节读回"></a>
### 完整示例 12：先写入文件，再逐字节读回 / Complete Example 12: Write a File, Then Read It Back Byte by Byte

**请在新建的空练习目录中运行。** 示例只使用 `file_io_example.txt`，每次运行都会用 `"w"` 清空同名文件；不要改成有用文件的名字。

**Run this in a newly created, empty practice directory.** The example uses only `file_io_example.txt` and clears any file with that name using `"w"` every time it runs. Do not change it to the name of a file you need.

保存为 `file_io_demo.c`：

Save as `file_io_demo.c`:

```c
#include <stdio.h>

int main(void) {
    const char *filename = "file_io_example.txt";
    int status = 0;  // 0 表示成功；发生错误后改成 1

    /* 第一步：打开文件，写入，再关闭。 */
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("open for writing");
        return 1;
    }

    if (fprintf(fp, "Hello, file!\nscore=%d\n", 90) < 0) {
        perror("write file");
        status = 1;
    }
    if (fclose(fp) != 0) {
        perror("close after writing");
        status = 1;
    }
    if (status != 0) {
        return status;
    }

    /* 第二步：重新以只读模式打开，从开头读取。 */
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("open for reading");
        return 1;
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (putchar(ch) == EOF) {
            perror("print to screen");
            status = 1;
            break;
        }
    }
    if (ferror(fp)) {
        perror("read file");
        status = 1;
    }
    if (fclose(fp) != 0) {
        perror("close after reading");
        status = 1;
    }
    if (fflush(stdout) != 0) {
        perror("flush screen output");
        status = 1;
    }
    return status;
}
```

**输入：** 无需键盘输入。程序自行写入练习文件，然后读取它。

**Input:** No keyboard input is required. The program writes the practice file itself, then reads it.

**文件内容与屏幕输出均为：**

**Both the file contents and the screen output are:**

```text
Hello, file!
score=90
```

运行顺序是“写模式打开 → 写入两行 → 关闭 → 读模式打开 → 循环读取 → 关闭”。`ferror(fp)` 非零表示这个流发生过错误；正常读到文件末尾时它不会因此变为非零。`status` 用来记住错误，让程序报错后仍能执行关闭操作。最后的辅助调用 `fflush(stdout)` 尝试写出屏幕输出的缓冲数据，也检查输出错误。

The execution order is “open for writing → write two lines → close → open for reading → read in a loop → close.” A nonzero `ferror(fp)` means an error has occurred on this stream; merely reaching end-of-file normally does not make it nonzero. `status` remembers errors so the program can still close the file after reporting an error. The final helper call, `fflush(stdout)`, attempts to write buffered screen output and also checks for output errors.

已安装 `gcc` 时，在新建的练习目录中编译运行：

With `gcc` installed, compile and run in the newly created practice directory:

Linux / macOS：

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic file_io_demo.c -o file_io_demo
./file_io_demo
```

Windows PowerShell：

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic file_io_demo.c -o file_io_demo.exe
.\file_io_demo.exe
```

<a id="fclose成功打开的文件用完就关闭"></a>
### fclose：成功打开的文件，用完就关闭 / `fclose`: Close Every Successfully Opened File When Finished

- 每次成功 `fopen` 得到的文件流，都应在正常路径和错误路径中关闭一次；不要等程序退出才处理。<br>
  Every stream obtained from a successful `fopen` should be closed exactly once, on both normal and error paths. Do not wait until program exit to deal with it.
- 写入出错后也要尝试关闭。上例先记住错误，再 `fclose`，不会直接 `return` 而漏关文件。<br>
  Attempt to close even after a write error. The example first records the error and then calls `fclose`, rather than returning immediately and leaving the file unclosed.
- 检查 `fclose(fp) != 0`：缓冲数据在关闭时写出，也可能此时才报告错误。关闭成功不等于对断电等情况作出持久化保证。<br>
  Check `fclose(fp) != 0`: buffered data is written during closing, and an error may be reported only then. A successful close is not a guarantee of durability against power failures or similar events.
- **调用 `fclose` 后，不要再读写或再次关闭这个旧文件流，即使关闭时报错也一样。** 上例第二阶段给 `fp` 重新赋予的是另一次 `fopen` 返回的新文件流。<br>
  **After calling `fclose`, do not read from, write to, or close that old stream again, even if closing reported an error.** In the second stage of the example, `fp` receives a new stream returned by another call to `fopen`.

可以再做三个小实验：把 `90` 改成别的整数；仅保留读取阶段读取一个空文件，观察没有输出但正常结束；仅保留读取阶段并把文件名改成不存在的名字，观察打开失败。后两个实验必须去掉写入阶段，否则程序会先创建并填入文件，测不到空文件或文件不存在的情况。

Try three more small experiments: change `90` to another integer; retain only the reading stage and read an empty file, observing no output but normal completion; retain only the reading stage and use a nonexistent filename, observing an open failure. The last two experiments must remove the writing stage; otherwise, the program creates and fills the file first, preventing you from testing an empty or missing file.

<a id="再补四个常用函数写字符读行写字符串按格式读"></a>
### 再补四个常用函数：写字符、读行、写字符串、按格式读 / Four More Common Functions: Write a Character, Read a Line, Write a String, and Read Formatted Data

下面都是**独立片段**，不是完整程序。已包含 `<stdio.h>`，`fp` 已按所需模式成功打开，`int status = 0;` 用来记录错误。片段执行后仍要检查 `fclose(fp)`；向屏幕输出后还要检查 `fflush(stdout)`，可以参照上面的完整示例收尾。

These are all **independent snippets**, not complete programs. `<stdio.h>` has been included, `fp` has been opened successfully in the required mode, and `int status = 0;` records errors. You must still check `fclose(fp)` after each snippet; after screen output, also check `fflush(stdout)`. Use the complete example above as a guide for cleanup.

<a id="fputc-和-fputs写一个字符或写一段字符串"></a>
#### fputc 和 fputs：写一个字符，或写一段字符串 / `fputc` and `fputs`: Write One Character or a String

**写入片段：** `fp` 以 `"w"` 或 `"a"` 模式打开。

**Writing snippet:** `fp` is opened in `"w"` or `"a"` mode.

```c
if (fputc('A', fp) == EOF) {
    perror("fputc");
    status = 1;
}
if (fputs("BC\n", fp) == EOF) {
    perror("fputs");
    status = 1;
}
```

两次写入都成功时，得到一行 `ABC`。`fputc` 一次写一个字节，成功返回写出的字节值（转换为 `int`），失败返回 `EOF`。

If both writes succeed, the result is one line containing `ABC`. `fputc` writes one byte at a time, returning the written byte value converted to `int` on success, or `EOF` on failure.

`fputs` 把字符串写到结尾的 `\0` 之前，**不写入 `\0`，也不自动补换行**；这里的换行来自字符串里的 `\n`。它成功返回非负值，失败返回 `EOF`，不要把成功返回值当作写出的字符数。`fputs` 不做格式替换，字符串中的 `%d` 也会原样写出。

`fputs` writes the string up to its terminating `\0`, **without writing `\0` or automatically adding a newline**. The newline here comes from `\n` in the string. It returns a nonnegative value on success or `EOF` on failure; do not interpret a successful return value as the number of characters written. `fputs` performs no format substitution, so `%d` in a string is also written literally.

<a id="fgets一次最多读-n---1-个字节不保证读完一整行"></a>
#### fgets：一次最多读 n - 1 个字节，不保证读完一整行 / `fgets`: Read at Most `n - 1` Bytes at a Time, Not Necessarily a Whole Line

**读取片段：** `fp` 以 `"r"` 模式打开。

**Reading snippet:** `fp` is opened in `"r"` mode.

```c
char line[16];
if (fgets(line, sizeof line, fp) != NULL) {
    if (fputs(line, stdout) == EOF) {
        perror("display line");
        status = 1;
    }
} else if (ferror(fp)) {
    perror("fgets");
    status = 1;
}
```

- 第二个参数是缓冲区大小 `n`，包含为结尾 `\0` 留的位置；本例 `n = 16`，最多读取 15 个字节，成功后补 `\0`，使 `line` 成为 C 字符串。<br>
  The second argument is the buffer size `n`, including space for the terminating `\0`. Here, `n = 16`, so at most 15 bytes are read; on success, `\0` is appended to make `line` a C string.
- 遇到换行会停；**如果这次读到了换行，`\n` 会保留在字符串里**。`fputs(line, stdout)` 会原样显示，不会额外加换行。<br>
  Reading stops at a newline; **if a newline is read in this call, `\n` remains in the string**. `fputs(line, stdout)` displays the string as-is without adding another newline.
- 如果一行太长，先读满 15 个字节就返回，剩余内容要下次 `fgets` 才能继续读。因此“成功一次”不一定等于“读完一行”。大小参数不能超过实际数组容量。<br>
  If a line is too long, the function returns after reading 15 bytes, leaving the rest for a later `fgets` call. Thus, “one successful call” does not necessarily mean “one complete line.” The size argument must not exceed the actual array capacity.
- 读到 EOF 前已有数据时，仍成功返回 `line`；还没读到数据就遇到 EOF，或发生读取错误时，返回 `NULL`。返回 `NULL` 后不要使用这次缓冲区的内容，先用 `ferror(fp)` 区分错误与正常结束。<br>
  If some data has been read before EOF, the call still succeeds and returns `line`. If EOF occurs before any data is read, or a read error occurs, it returns `NULL`. After a `NULL` result, do not use the contents of the buffer from this call; first use `ferror(fp)` to distinguish an error from normal completion.

<a id="fscanf按格式读取先检查成功赋值了几项"></a>
#### fscanf：按格式读取，先检查成功赋值了几项 / `fscanf`: Read According to a Format, Then Check How Many Items Were Assigned

**读取片段：** `fp` 以 `"r"` 模式打开，文件预期包含一个不带空格的英文名字和一个 `int` 范围内的整数，例如 `Alice 90`。

**Reading snippet:** `fp` is opened in `"r"` mode. The file is expected to contain an English name without spaces and an integer within the `int` range, for example `Alice 90`.

```c
char name[16];
int score;
int count = fscanf(fp, "%15s %d", name, &score);
if (count == 2) {
    if (printf("%s %d\n", name, score) < 0) {
        perror("display record");
        status = 1;
    }
} else if (ferror(fp)) {
    perror("fscanf");
    status = 1;
} else {
    fprintf(stderr, "expected a name and an integer\n");
    status = 1;
}
```

- `fscanf` 与 `scanf` 类似，只是第一个参数指定从哪个文件读。`%d` 读整数，要传 `&score`；字符数组 `name` 直接传名字。<br>
  `fscanf` is similar to `scanf`, except its first argument specifies the file to read. `%d` reads an integer and requires `&score`; pass the character array `name` directly by name.
- **返回值是成功赋值的项数，不是读取的字符数。** 本例只有 `count == 2` 时才能使用两个结果；`Alice oops` 只成功读到名字，返回 `1`。如果首次转换前就发生输入失败（例如空文件），返回 `EOF`；其他格式也可能因不匹配返回 `0`，例如用 `%d` 读取 `oops`。<br>
  **The return value is the number of successfully assigned items, not the number of characters read.** In this example, use both results only when `count == 2`. Input `Alice oops` successfully reads only the name and returns `1`. An input failure before the first conversion, such as an empty file, returns `EOF`. Other formats may return `0` on a matching failure, for example when `%d` tries to read `oops`.
- `name` 能放 16 个字符，`%15s` 限制最多读取 15 个字节，剩下一个位置留给 `\0`。**用 `%s` 读入数组一定要给出合适的宽度。** 超长单词的剩余部分仍在文件里，可能影响下一项读取，并不是自动跳过。<br>
  `name` holds 16 characters. `%15s` limits input to 15 bytes, reserving the remaining position for `\0`. **Always specify an appropriate width when reading into an array with `%s`.** The remainder of an overlong word stays in the file and may affect the next input item; it is not automatically skipped.
- `%s` 以空白分隔单词，不能读取带空格的整行名字；想保留一整行，优先考虑 `fgets`。本例假设输入的整数在 `int` 范围内，不能把 `fscanf` 当作任意输入都安全的数字校验器。<br>
  `%s` separates words at whitespace and cannot read a whole name containing spaces. Prefer `fgets` when you want to retain an entire line. This example assumes that the input integer fits in `int`; do not treat `fscanf` as a safe numeric validator for arbitrary input.
- 循环读取时，也应让读取结果决定是否继续，例如读一个整数用 `while (fscanf(fp, "%d", &score) == 1)`；不要用 `while (!feof(fp))`。<br>
  In a reading loop, the read result should likewise determine whether to continue. For example, to read one integer at a time, use `while (fscanf(fp, "%d", &score) == 1)`, not `while (!feof(fp))`.

<a id="三种读取方式循环条件为什么不同"></a>
### 三种读取方式：循环条件为什么不同？ / Three Reading Methods: Why Are Their Loop Conditions Different?

| 调用<br>Call | 一次读取什么<br>What one call reads | 成功时继续循环的条件<br>Condition for continuing after success |
| --- | --- | --- |
| `fgetc(fp)` | 一个字符（字节），包括空格和换行<br>One character (byte), including spaces and newlines | 返回值 `!= EOF`<br>Return value `!= EOF` |
| `fgets(str, n, fp)` | 最多 `n - 1` 个字节，通常是一行，也可能只是一行的一部分<br>Up to `n - 1` bytes, usually a line but possibly only part of one | 返回值 `!= NULL`<br>Return value `!= NULL` |
| `fscanf(fp, "%99s", str)` | 跳过前导空白，再读一段不含空白的字符串，最多 99 个字节<br>Skip leading whitespace, then read a whitespace-free string of at most 99 bytes | 返回值 `== 1`<br>Return value `== 1` |

**`fscanf` 返回成功赋值的数据项数量，是 `int`，不是指针，因此不能照搬 `fgets` 的 `!= NULL`。** 这里仅有一个 `%s`，所以检查 `== 1`；上面的名字加分数有两项，就要检查 `== 2`。

**`fscanf` returns the number of successfully assigned data items as an `int`, not a pointer, so you cannot copy the `!= NULL` test used with `fgets`.** Here there is only one `%s`, so check `== 1`; the name-and-score example above has two items, so it requires `== 2`.

下面是**三个独立的循环片段**，只展示“读到数据才处理”的结构。均已包含 `<stdio.h>`，`fp` 已成功以 `"r"` 打开；对比同一文件时，每次重新打开，从开头分别运行，不要把三个片段接在同一个流后面。

The following are **three independent loop snippets**, showing only the structure of “process data only after successfully reading it.” All assume `<stdio.h>` has been included and `fp` has been opened successfully in `"r"` mode. When comparing the same file, reopen it for each snippet and run each separately from the beginning; do not concatenate all three on the same stream.

**逐字节读取：**

**Read byte by byte:**

```c
int ch;
while ((ch = fgetc(fp)) != EOF) {
    /* 在这里处理这次读到的 ch。 */
}
```

**按行或行的一部分读取：**

**Read lines or parts of lines:**

```c
char str[100];
while (fgets(str, sizeof str, fp) != NULL) {
    /* 在这里处理这次读到的 str。 */
}
```

**按空白分隔读取字符串：**

**Read whitespace-delimited strings:**

```c
char str[100];
while (fscanf(fp, "%99s", str) == 1) {
    /* 在这里处理这次读到的 str。 */
}
```

- `fgetc` 的结果仍须用 `int` 保存。后两段的数组容量都是 100，最多存入 99 个数据字节，再补一个 `\0`；表中的 `n` 不能超过实际数组容量。<br>
  The result of `fgetc` must still be stored in an `int`. The arrays in the other two snippets each have capacity 100, allowing at most 99 data bytes followed by one `\0`. The `n` in the table must not exceed the actual array capacity.
- `fgets` 保留读到的 `\n`；长行会分多次返回。`%99s` 不把分隔空白存入 `str`；长于 99 字节的单词也会留下一部分供下次读取，不能把每次成功都当成一个完整单词。<br>
  `fgets` preserves a `\n` that it reads, and returns long lines over multiple calls. `%99s` does not store separating whitespace in `str`; a word longer than 99 bytes also leaves a remainder for the next read, so not every successful call represents a whole word.
- 例如文件是 `A B\n`：`fgetc` 成功 4 次，`fgets` 成功 1 次（保留空格与换行），`%99s` 成功 2 次，分别得到 `A` 和 `B`。空文件三种循环都不进入；只有空白的文件仍能被前两种读取，`%99s` 则跳过空白后遇到文件尾。<br>
  For example, with file contents `A B\n`, `fgetc` succeeds 4 times; `fgets` succeeds once, preserving the space and newline; and `%99s` succeeds twice, obtaining `A` and `B`. None of the three loops enters its body for an empty file. The first two methods can still read a whitespace-only file, whereas `%99s` skips the whitespace and then encounters end-of-file.
- **退出循环不一定表示正常读完。** 三段循环后都要检查 `ferror(fp)`，最后检查 `fclose(fp)`，参照完整示例处理错误。一般的 `fscanf` 格式还可能匹配失败，例如 `%d` 遇到 `oops` 返回 `0`；不要把 `0` 写成上面 `%99s` 读到空文件时的结果。<br>
  **Leaving the loop does not necessarily mean normal completion.** After all three loops, check `ferror(fp)` and finally check `fclose(fp)`, following the complete example's error handling. General `fscanf` formats can also fail to match; for instance, `%d` encountering `oops` returns `0`. Do not mistake `0` for the result of the `%99s` call above when reading an empty file.

<a id="c-file-copy-demo"></a>
<a id="完整示例-13把第一个文件复制到第二个文件"></a>
### 完整示例 13：把第一个文件复制到第二个文件 / Complete Example 13: Copy the First File to the Second

把步骤记成三句话：

Remember the steps in three sentences:

1. 用 `fopen()` 打开两个文件：源文件负责读，目标文件负责写。<br>
   Use `fopen()` to open two files: the source for reading and the destination for writing.
2. 用 `fgetc()` 从源文件读一个字节，再用 `fputc()` 把它写入目标文件，重复到读完或出错。<br>
   Use `fgetc()` to read one byte from the source, then `fputc()` to write it to the destination. Repeat until reading finishes or an error occurs.
3. 用 `fclose()` 关闭两个文件；中途出错也要关闭已经成功打开的文件。<br>
   Use `fclose()` to close both files. Even if an error occurs partway through, close any file that was successfully opened.

**请继续在空练习目录中操作。** 先手动新建 `copy_source.txt`，写入下面的内容；`copy_result.txt` 是专用输出文件，若已存在就会被清空。**必须确保源、目标指向两个不同文件**；文件名不同也可能通过符号链接或硬链接指向同一个文件，本例不自动检测这种情况。

**Continue working in an empty practice directory.** First manually create `copy_source.txt` with the contents below. `copy_result.txt` is the dedicated output file and will be cleared if it already exists. **You must ensure that the source and destination refer to two different files.** Different filenames can still refer to the same file through symbolic or hard links; this example does not detect that automatically.

源文件内容：

Source file contents:

```text
Hello, copy!
score=90
```

保存为 `file_copy_demo.c`：

Save as `file_copy_demo.c`:

```c
#include <stdio.h>

int main(void) {
    /* 先打开源文件：如果源文件不存在，不会创建或清空目标文件。 */
    FILE *src = fopen("copy_source.txt", "rb");
    if (src == NULL) {
        perror("open source");
        return 1;
    }

    FILE *dst = fopen("copy_result.txt", "wb");
    if (dst == NULL) {
        perror("open destination");
        if (fclose(src) != 0) {
            perror("close source");
        }
        return 1;
    }

    int status = 0;
    int ch;
    while ((ch = fgetc(src)) != EOF) {
        if (fputc(ch, dst) == EOF) {
            perror("write destination");
            status = 1;
            break;
        }
    }
    if (ferror(src)) {
        perror("read source");
        status = 1;
    }
    if (fclose(dst) != 0) {
        perror("close destination");
        status = 1;
    }
    if (fclose(src) != 0) {
        perror("close source");
        status = 1;
    }
    return status;
}
```

`src` 表示源文件流，`dst` 表示目标文件流。这里使用 `"rb"`、`"wb"`：`b` 表示二进制模式，避免某些系统的文本模式做换行转换，便于原样复制字节；`"wb"` 仍有 `"w"` 的清空风险。

`src` is the source stream and `dst` is the destination stream. This example uses `"rb"` and `"wb"`: `b` selects binary mode, avoiding the newline conversions performed by text mode on some systems so bytes can be copied unchanged. `"wb"` still carries the same truncation risk as `"w"`.

Linux / macOS：

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic file_copy_demo.c -o file_copy_demo
./file_copy_demo
```

Windows PowerShell：

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic file_copy_demo.c -o file_copy_demo.exe
.\file_copy_demo.exe
```

**输入：** 无需键盘输入，数据来自提前准备好的 `copy_source.txt`。**结果：** 成功时屏幕没有额外输出，`copy_result.txt` 与源文件的字节内容一致，程序返回 `0`；失败返回 `1` 并报错。复制失败时目标文件可能只写入了一部分，不能把它当作完整备份。

**Input:** No keyboard input is needed; the data comes from the previously prepared `copy_source.txt`. **Result:** On success, there is no extra screen output, `copy_result.txt` has exactly the same bytes as the source, and the program returns `0`. On failure, it reports an error and returns `1`. A failed copy may leave only part of the data in the destination, so do not treat it as a complete backup.

空源文件会复制成空文件；源文件不存在时会直接报错，不会碰目标文件。可以把源文件改成长一点、带空格或空行的内容再试。示例一直用 `int ch`，先确认不是 `EOF` 才传给 `fputc`，因此不会把 EOF 标记写进文件。

An empty source is copied to an empty file. If the source does not exist, the program reports an error immediately without touching the destination. Try a longer source containing spaces or blank lines. The example always uses `int ch` and verifies that it is not `EOF` before passing it to `fputc`, so it never writes the EOF marker into the file.

**记忆口令：打开先判空，读取用 `int`，写入看返回，用完要关闭；`"w"` 会清空，`"a"` 才追加。** 做在线评测题时，仍按题目要求使用标准输入输出或指定文件名，不要把这个练习文件名直接带进提交答案。

**Memory aid: check for null after opening, use `int` for character input, check write return values, and close when finished; `"w"` clears, while `"a"` appends.** For online-judge problems, still follow the statement's requirements for standard input/output or specific filenames. Do not copy this practice filename directly into your submission.

<a id="c-binary-file-io"></a>
<a id="二进制文件读写wbrbfwrite-和-fread"></a>
### 二进制文件读写：wb、rb、fwrite 和 fread / Binary File I/O: `wb`, `rb`, `fwrite`, and `fread`

前面的复制示例已经用过 `"wb"`、`"rb"`。现在再学两个函数：**`fwrite` 把内存中的一块数据写进文件，`fread` 把文件中的一块数据读进内存。** 它们也声明在 `<stdio.h>` 中。

The copying example already used `"wb"` and `"rb"`. Now learn two more functions: **`fwrite` writes a block of data from memory to a file, and `fread` reads a block of data from a file into memory.** Both are also declared in `<stdio.h>`.

先记住这五步；每次打开、读写和关闭都要检查结果：

Start by remembering these five steps, checking the result every time you open, read, write, or close:

| 写法<br>Form | 作用<br>Purpose |
| --- | --- |
| `fopen(filename, "wb")` | 以二进制写模式打开；不存在就尝试创建，已存在则在打开成功时立即清空<br>Open for binary writing; attempt to create a missing file, or immediately clear an existing file when opening succeeds |
| `fwrite(...)` | 从指定的内存地址写出若干个元素<br>Write a number of elements from the specified memory address |
| `fclose(fp)` | 关闭写入的文件流，并检查缓冲数据能否成功写出<br>Close the output stream and check whether buffered data is written successfully |
| `fopen(filename, "rb")` | 以二进制只读模式重新打开；文件不存在时失败<br>Reopen for binary reading only; fail if the file does not exist |
| `fread(...)`，然后 `fclose(fp)`<br>`fread(...)`, then `fclose(fp)` | 读入指定个数的元素，最后关闭文件流<br>Read the specified number of elements, then close the stream |

<a id="文件扩展名不决定格式b-也不会自动把整数转成二进制数据"></a>
#### 文件扩展名不决定格式，b 也不会自动把整数转成二进制数据 / The Extension Does Not Determine the Format, and `b` Does Not Automatically Convert Integers to Binary Data

- `filename` 只是保存文件名的变量。例如 `const char *filename = "file5.txt";`，即使后缀是 `.txt`，也可以用 `"wb"`、`"rb"` 按二进制模式读写。<br>
  `filename` is just a variable holding the filename. For example, with `const char *filename = "file5.txt";`, you can still use `"wb"` and `"rb"` for binary I/O even though the extension is `.txt`.
- `b` 控制文件流的模式，避免某些系统的文本模式进行换行等转换；**实际写入什么内容，还取决于你调用哪个函数、给它什么数据。** 用 `"wb"` 打开后调用 `fprintf(fp, "%d", n)`，写入的仍然是数字文本。<br>
  `b` controls the stream mode, avoiding conversions such as newline translation performed by text mode on some systems. **What is actually written still depends on which function you call and which data you give it.** Calling `fprintf(fp, "%d", n)` after opening with `"wb"` still writes numeric text.
- `fprintf(fp, "%d", n)` 把 `90` 格式化成字符 `'9'`、`'0'`；`fwrite(&n, sizeof n, 1, fp)` 则写出 `n` 的内存表示，不会做十进制文本转换，也不会自动添加换行。<br>
  `fprintf(fp, "%d", n)` formats `90` as the characters `'9'` and `'0'`. In contrast, `fwrite(&n, sizeof n, 1, fp)` writes `n`'s memory representation without converting it to decimal text or adding a newline.
- 反过来，`fread` 不会把文本 `"90"` 解析成整数 `90`；读取数字文本要用相应的文本解析方法。不要仅凭 `.txt` 或 `.bin` 后缀判断怎样读取。<br>
  Conversely, `fread` does not parse the text `"90"` into the integer `90`. To read numeric text, use an appropriate text-parsing method. Do not decide how to read a file solely from its `.txt` or `.bin` extension.

<a id="重点拆开fwrite-和-fread-的四个参数"></a>
#### 重点拆开：fwrite 和 fread 的四个参数 / A Closer Look at the Four Arguments of `fwrite` and `fread`

下面是**两个独立的核心片段，不是完整程序**。假设 `n` 的类型是 `int`；写入时 `n` 已赋值且 `fp` 以 `"wb"` 成功打开，读取时 `fp` 以 `"rb"` 成功打开。

These are **two independent core snippets, not complete programs**. Assume `n` has type `int`. For writing, `n` has been assigned a value and `fp` has been opened successfully in `"wb"` mode; for reading, `fp` has been opened successfully in `"rb"` mode.

```c
fwrite(&n, sizeof(int), 1, fp);  // 从 n 所在的位置写出 1 个 int
fread(&n, sizeof(int), 1, fp);   // 读入 1 个 int，存放到 n 所在的位置
```

这两行只展示参数，**实际程序必须像下面的完整示例一样检查返回值**。

These two lines demonstrate only the arguments. **A real program must check the return values, as the complete example below does.**

| 参数<br>Argument | 本例<br>In this example | 怎么理解<br>Meaning |
| --- | --- | --- |
| 第 1 个：内存地址<br>1st: memory address | `&n` | `fwrite` 从这里取数据；`fread` 把数据放到这里。`&n` 是取地址，不能直接传整数值 `n`<br>`fwrite` takes data from here; `fread` places data here. `&n` takes the address; do not pass the integer value `n` directly |
| 第 2 个：每个元素的大小<br>2nd: size of each element | `sizeof(int)` | 一个 `int` 占多少字节；不要写死成 `4`<br>The number of bytes occupied by one `int`; do not hard-code `4` |
| 第 3 个：元素个数<br>3rd: number of elements | `1` | 本次想写入或读取 1 个元素，不是 1 个字节<br>Request writing or reading 1 element, not 1 byte |
| 第 4 个：文件流<br>4th: file stream | `fp` | 已成功打开、模式适合这次操作的文件流<br>A successfully opened stream whose mode is appropriate for the operation |

当 `n` 是 `int` 时，`sizeof n` 与 `sizeof(int)` 相等。下面优先写 `sizeof n`，这样以后修改 `n` 的类型时，不容易忘记同步修改大小；不要误写成 `sizeof &n`，那得到的是指针的大小。

When `n` is an `int`, `sizeof n` equals `sizeof(int)`. The code below prefers `sizeof n`, making it less likely that you forget to update the size if `n`'s type changes later. Do not accidentally write `sizeof &n`, which gives the pointer's size.

**返回值是成功读写的完整元素个数，类型为 `size_t`，不是字节数。** 本例请求 1 个元素，所以只有返回 `1` 才表示这个整数完整读写成功。若 `sizeof n` 恰好为 4，成功处理 4 个字节时返回的仍是 `1`。

**The return value is the number of complete elements successfully read or written, with type `size_t`, not the number of bytes.** This example requests 1 element, so only a return value of `1` means the whole integer was successfully read or written. Even if `sizeof n` happens to be 4, successfully handling those 4 bytes still returns `1`.

`fread` 返回不足 `1` 时，可能是文件已经结束、只剩不完整的整数，或者发生读取错误；用 `ferror(fp)` 区分读取错误。**未完整读入时不要使用 `n`，即使之前把它初始化为 `0` 也一样**，因为部分读取可能已经改动了它的字节。`fwrite` 返回不足 `1` 表示写入失败；即使返回 `1`，也仍要检查后续 `fclose`。

If `fread` returns less than `1`, the file may have ended, may contain only an incomplete integer, or a read error may have occurred; use `ferror(fp)` to distinguish a read error. **Do not use `n` unless it was read completely, even if it was initialized to `0` beforehand**, because a partial read may already have changed some of its bytes. A return value below `1` from `fwrite` means the write failed. Even if it returns `1`, still check the subsequent `fclose`.

<a id="c-file-binary-demo"></a>
<a id="完整示例-14把一个整数按二进制写入再读回"></a>
### 完整示例 14：把一个整数按二进制写入，再读回 / Complete Example 14: Write an Integer in Binary, Then Read It Back

**只在新建的空练习目录中运行。** 这里专门使用 `file5.txt` 展示“扩展名不决定格式”；`"wb"` 每次都会清空同名文件，不要把文件名改成有用文件的路径。示例只读取本程序刚刚写出的数据，适合同一程序、同一平台上的入门练习。

**Run only in a newly created, empty practice directory.** The example deliberately uses `file5.txt` to show that the extension does not determine the format. `"wb"` clears any file with that name each time; do not change the filename to the path of a file you need. The example reads only data just written by this same program, making it suitable for introductory practice with the same program on the same platform.

保存为 `binary_file_demo.c`：

Save as `binary_file_demo.c`:

```c
#include <stdio.h>

int main(void) {
    const char *filename = "file5.txt";
    int n = 90;
    int status = 0;

    /* 第一步：写出 n 的内存表示，再关闭文件。 */
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("open for writing");
        return 1;
    }
    if (fwrite(&n, sizeof n, 1, fp) != 1) {
        perror("write integer");
        status = 1;
    }
    if (fclose(fp) != 0) {
        perror("close after writing");
        status = 1;
    }
    if (status != 0) {
        return status;
    }

    /* 第二步：重新打开，把文件里的整数读回 n。 */
    n = 0;
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("open for reading");
        return 1;
    }
    if (fread(&n, sizeof n, 1, fp) != 1) {
        if (ferror(fp)) {
            perror("read integer");
        } else {
            fprintf(stderr, "file does not contain a complete int\n");
        }
        status = 1;
    }
    if (fclose(fp) != 0) {
        perror("close after reading");
        status = 1;
    }
    if (status != 0) {
        return status;  // 没有完整读到整数或关闭失败时，不输出 n
    }

    if (printf("%d\n", n) < 0) {
        perror("display integer");
        status = 1;
    }
    if (fflush(stdout) != 0) {
        perror("flush screen output");
        status = 1;
    }
    return status;
}
```

Linux / macOS：

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic binary_file_demo.c -o binary_file_demo
./binary_file_demo
```

Windows PowerShell：

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic binary_file_demo.c -o binary_file_demo.exe
.\binary_file_demo.exe
```

**输入：** 无需键盘输入。**屏幕输出：** `90`，然后换行；成功返回 `0`，失败返回 `1` 并报错。屏幕上的 `90` 是 `printf` 格式化后的文本，不能据此认为文件中存的也是字符 `"90"`；用文本编辑器打开这个文件，不应期待直接看到数字 `90`。

**Input:** No keyboard input is required. **Screen output:** `90`, followed by a newline. The program returns `0` on success, or reports an error and returns `1` on failure. The `90` on the screen is text formatted by `printf`; this does not mean the file also contains the characters `"90"`. Do not expect to see the number `90` directly when opening this file in a text editor.

可以把 `n = 90` 改成 `n = -7` 再运行。想练习空文件、不足一个 `int` 的文件或文件不存在的情况，要**仅保留第二步及后面的输出检查**，并在它前面声明 `filename`、`int n = 0;`、`int status = 0;`、`FILE *fp;`；否则第一步会先创建文件并写入完整数据，测不到这些情况。读取失败时应报错，不应输出 `n`。

Try changing `n = 90` to `n = -7` and running again. To test an empty file, a file shorter than one `int`, or a missing file, **retain only the second step and the output checks that follow**, declaring `filename`, `int n = 0;`, `int status = 0;`, and `FILE *fp;` before it. Otherwise, the first step creates the file and writes complete data, preventing these tests. A failed read should report an error, not output `n`.

**可移植性先记一句：直接写内存表示，不等于设计好了通用文件格式。** 不同平台的 `int` 大小、字节顺序和表示可能不同，不能保证另一个环境原样读回。以后学结构体时，整块 `fwrite` 还涉及填充字节、布局差异；指针成员只会写出地址表示，不会自动保存它指向的数据。需要跨平台或长期保存时，应明确规定各字段的大小、编码和字节顺序，再分别读写；本节先练习这两个函数的基本用法。

**Remember this portability rule first: writing a memory representation directly is not the same as designing a universal file format.** Platforms may differ in the size, byte order, and representation of `int`, so another environment is not guaranteed to read it back unchanged. When you later learn structures, writing an entire structure with `fwrite` also involves padding bytes and layout differences. Pointer members store only address representations, not the pointed-to data. For cross-platform use or long-term storage, explicitly define each field's size, encoding, and byte order, then read and write the fields individually. This section focuses on the basic use of these two functions.

**二进制读写口令：`wb` 打开 → `fwrite` 写 → 关闭 → `rb` 打开 → `fread` 读 → 关闭；地址、大小、个数、文件流，返回值数完整元素。**

**Binary I/O memory aid: open with `wb` → write with `fwrite` → close → open with `rb` → read with `fread` → close; address, size, count, stream, and a return value counting complete elements.**

想核对函数定义，可查 [C11 委员会草案 N1570](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf) 的 7.21.5.1（`fclose`）、7.21.5.3（`fopen`）、7.21.6.1–7.21.6.2（`fprintf`、`fscanf`）、7.21.7.1–7.21.7.4（`fgetc`、`fgets`、`fputc`、`fputs`）以及 7.21.8.1–7.21.8.2（`fread`、`fwrite`）；初学时先掌握上面的示例即可。

To check the function definitions, consult the [C11 committee draft N1570](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf), sections 7.21.5.1 (`fclose`), 7.21.5.3 (`fopen`), 7.21.6.1–7.21.6.2 (`fprintf`, `fscanf`), 7.21.7.1–7.21.7.4 (`fgetc`, `fgets`, `fputc`, `fputs`), and 7.21.8.1–7.21.8.2 (`fread`, `fwrite`). As a beginner, focus first on mastering the examples above.

[回到阅读导航](#怎么读) · [返回仓库首页](README.md)

[Back to the Reading Guide](#怎么读) · [Back to the Repository Home](README.md)
