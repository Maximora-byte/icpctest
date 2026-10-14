# STD.md：从零看懂 C++ 常用标准库

这份笔记从六种常见写法开始：`vector` 存数、循环输入、`sort` 排序、`set` 去重、`getline` 读一行、`stringstream` 拆分一行。

**目标：不只会复制，还能说清楚每一行在做什么。** 你只需要先接触过变量、`cin`、`cout`、`if` 和 `for`；下面也会简单解释用到的语法。

文件名保留为 `STD.md`。注意：

- `std` 是 C++ 标准库使用的**命名空间**，可以先理解成工具所属的名字；例如 `std::vector`。
- STL 通常指标准模板库，常见内容包括容器、迭代器和算法。先把它们理解成“装数据的盒子”“指向某个位置的标记”“处理数据的工具”就够了。
- C++ 标准库还包括输入输出、字符串等内容。这份笔记会一起介绍。

## 怎么读

**第一次学习，按顺序读必读部分，到第 6 节就可以停。** 每学一个完整示例，先运行，再换几个数试试。选读部分遇到题目需要时再查。

### 初学必读

0. [怎样运行示例、头文件是什么](#start)
1. [vector：存放一排整数，并输入它们](#vector)
2. [sort 和 set：排序，再去重](#sort-set)
3. [string：整行输入与五种常用操作](#getline)
4. [stringstream：把一行拆成单词或数字](#stringstream)
5. [cin 后接 getline：为什么会读到空行](#mixed-input)
   - [把四步串起来：读整行、转小写、拆单词、比较计数](#word-count)
   - [char& 为什么能改原字符：联系引用和指针](#char-reference)
   - [四种字符串模板：需要原位置时手动扫描](#string-templates)
6. [六种原始写法速查与易错点](#recap)

### 按需选读

7. [vector 的增删、倒序排序](#more-vector)
8. [保留 vector：sort + unique + erase 去重](#unique)
9. [二分查找：找有没有、找位置、数出现次数](#binary-search)
   - [手写二分：l、r、mid 三个变量与完整模板](#binary-search-lrmid)
10. [求和：long long 和 0LL](#sum)
11. [map、queue、stack：计数、排队、叠盘子](#containers)
12. [小练习与提交前检查](#practice)

<a id="start"></a>
## 0. 先学会运行一个示例

### 完整程序和代码片段要分开看

本文标有“**完整示例**”的代码可以单独复制到 `main.cpp`，选择 **C++17** 编译运行。每次只复制一个完整示例，不要把几个 `main()` 拼在一起。

标有“**片段**”的代码只讲某一行写法，需要放进完整程序的合适位置，不能单独运行。

完整程序一般有这几部分：

- `#include <vector>`：引入某种工具的声明，叫**头文件**。用什么工具，就包含相应头文件。
- `using namespace std;`：本文的短练习都写这一行，于是可以把 `std::cin` 简写成 `cin`。大型项目通常更倾向于明确写 `std::`，避免名字冲突。
- `int main() { ... }`：程序从这里开始执行，花括号里的语句从上往下运行。
- `return 0;`：正常结束程序。
- `// ...`：注释，是给人看的说明，不会执行。
- `cout << value << '\n';`：输出 `value`，然后换行。`'\n'` 是一个换行字符。

本文使用标准头文件，不依赖某些编译器才支持的 `bits/stdc++.h`。

### 用什么头文件

| 要用的工具 | 头文件 | 可以先这样理解 |
| --- | --- | --- |
| `cin`、`cout` | `<iostream>` | 输入和输出 |
| `vector` | `<vector>` | 能调整长度的一排格子 |
| `sort`、`unique`、二分相关函数 | `<algorithm>` | 常用算法工具 |
| `set` | `<set>` | 不重复、默认从小到大排列的集合 |
| `string`、字符串版本的 `getline` | `<string>` | 文本和整行读取 |
| `tolower`、`toupper` | `<cctype>` | 把单个英文字母转成小写 / 大写 |
| `stringstream` | `<sstream>` | 把已有字符串当作输入来读 |
| `numeric_limits` | `<limits>` | 查询类型的数值范围，本文用来清理一行输入 |
| `accumulate` | `<numeric>` | 从一个初始值开始累加 |
| `map` / `queue` / `stack` | `<map>` / `<queue>` / `<stack>` | 计数表 / 队列 / 栈 |

### 编译与运行

如果用编辑器或在线编译器，选择 C++17，把示例输入粘贴到输入区，再运行。不要把“输入”“输出”这些说明文字也粘进去。

已安装 `g++` 时，也可以在 `main.cpp` 所在目录打开终端：

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

本文的数字输入示例假设输入符合题目格式，整数在相应类型范围内，且数据量能放进内存。前几例额外检查 `n` 能否读取及是否为负数，帮助避免直接创建错误长度的容器；这不是完整的输入校验程序。

<a id="vector"></a>
## 1. vector：存放一排整数

**什么时候用：** 要保存多个同类型的值，例如一组分数，后面还要排序、访问或修改。

需要 `<vector>`；输入输出还需要 `<iostream>`。

### 先看原来的写法

**片段：** 假设 `n` 已经是一个非负整数。

```cpp
vector<int> v(n);
for (int i = 0; i < n; i++) {
    cin >> v[i];
}
```

逐段拆开：

- `vector`：容器的种类。
- `<int>`：每个格子存一个整数。
- `v`：你给这排格子取的名字，可以换成 `scores`、`numbers`。
- `(n)`：创建 **n 个已经存在的元素**。这里每个 `int` 初始都是 `0`。
- `v[i]`：访问下标为 `i` 的元素。**下标从 0 开始**，不是从 1 开始。

例如 `n = 3`，合法位置是 `v[0]`、`v[1]`、`v[2]`。`v[3]` 已经越界，不能访问。

`for (int i = 0; i < n; i++)` 表示：

1. 一开始令 `i = 0`。
2. 只要 `i < n`，就执行花括号里的输入。
3. `i++` 让 `i` 加 1，再检查条件。
4. `i` 变成 `n` 时停止，所以一共读入 n 个数。

### 完整示例 1：读入并原样输出

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

```text
5
8 3 8 1 5
```

**输出**：

```text
8 3 8 1 5
```

`!(cin >> n)` 表示读取失败；`||` 表示“或者”。这一段 `if` 的意思是：读不到数量，或者数量为负，就结束程序。正常输入时会继续往下执行。

`if (i > 0)` 用来在第二个及之后的数字前输出空格，避免数字挤成 `83815`。`cin >>` 读取整数时会跳过空格和换行，所以这 5 个数也可以分成几行输入。

**最容易踩的坑：** `int n; vector<int> v(n);` 中的 `n` 尚未赋值，不能拿来当长度。应先读入并检查 `n`，再创建 `v`。

<a id="sort-set"></a>
## 2. sort 和 set：排序，再去重

### sort：让原来的 vector 排好序

需要 `<algorithm>`。

**片段：** 假设 `v` 是已经有数据的 `vector<int>`。

```cpp
sort(v.begin(), v.end());
```

这一行直接修改 `v`，默认从小到大排序。`8 3 8 1 5` 会变成 `1 3 5 8 8`，重复值还在。

`begin()` 和 `end()` 返回的东西叫**迭代器**。初学时把它想成“位置标记”：

- `v.begin()`：开始位置。
- `v.end()`：最后一个元素**后面**的位置，不是最后一个元素。
- `[begin, end)`：包含开头、不包含结尾，叫**左闭右开区间**。所以这一对位置正好表示整个 `v`。

不要读取 `v.end()` 指向的值，它不是一个元素。空 `vector` 的 `begin()` 等于 `end()`，排序空区间是允许的。

### set：生成一个不含重复值的集合

需要 `<set>`。

**片段：** 假设 `v` 已经有数据。

```cpp
set<int> unique_values(v.begin(), v.end());
```

这一行把 `v` 里的元素放进一个新 `set`：

- 同样的数只保留一份。
- 这里的 `set<int>` 遍历时默认从小到大。
- **原来的 `v` 不变**，重复值仍然在 `v` 里。
- 创建 `set` 前不要求 `v` 有序；下面先排序只是为了展示两步的不同效果。
- 它不会保留原来的输入顺序，也不能像 `vector` 那样写 `unique_values[0]`。

### 完整示例 2：观察排序和去重的区别

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

```text
5
8 3 8 1 5
```

**输出**：

```text
sorted: 1 3 5 8 8
unique: 1 3 5 8
```

`for (int value : v)` 叫**范围 for 循环**：依次把 `v` 里的元素复制给 `value`，每拿到一个就执行一次循环体。这里用来输出，不需要自己维护下标，也适用于 `set`。

记住：**排序不等于去重；set 去重不等于修改 vector。**

<a id="getline"></a>
## 3. string：整行输入与五种常用操作

### 先记住这张五工具速查表

下面假设已经声明 `string text;`。`string` 是**类型名**，`text` 才是你给字符串起的**变量名**；笔记里的“`string[i]` 访问字符”实际应写成 `text[i]`，不能直接把类型名当变量用。

| 工具 | 实际写法 | 用途 |
| --- | --- | --- |
| `getline()` | `getline(cin, text)` | 读取整行，保留行内空格 |
| `tolower()` | `tolower(...)`，安全的完整写法见下文 | 把**单个字符**转小写，整串要用循环 |
| 下标 `[]` | `text[i]` | 访问下标为 `i` 的字符，下标从 0 开始 |
| `substr()` | `text.substr(pos, count)` | 从下标 `pos` 开始，最多截取 `count` 个字符 |
| `size()` | `text.size()` | 获取当前长度，空格也计入 |

`text.size()` 和 `text.substr(...)` 中的点表示“使用 `text` 自己的操作”；`getline`、`tolower` 则直接调用。字符串相关操作需要 `<string>`，`tolower` 另需 `<cctype>`，输入输出需要 `<iostream>`。

这一节先用英文、数字和空格来理解“字符”。严格说，`std::string` 存的是一串 `char`，`size()` 统计的是这些存储单元的数量；UTF-8 中文通常占多个字节，所以这里的长度、下标和截取**不能直接当作汉字个数或汉字位置**。

### getline：读取完整一行

**什么时候用：** 一行文本中可能有空格，例如 `hello ICPC world`。

需要 `<string>` 和 `<iostream>`。

- `cin >> word`：读一个以空白分隔的字符串，遇到空格、制表符或换行就停。
- `getline(cin, line)`：读到这一行结束，保留行内空格；消耗结尾的换行，但不把换行放进 `line`。

**片段：** 单独读一行时这样写。

```cpp
string line;
getline(cin, line);
```

这里的 `line` 必须是 `string`。你前面若写了 `set<int> s`，就不能拿同一个 `s` 去做 `getline(cin, s)`。即使都起名为 `s`，集合和字符串也不是同一种类型，而且同一个作用域不能重复声明同名变量。

建议集合用 `unique_values`，整行文本用 `line`，一眼就能认出用途。

### 完整示例 3：保留行内空格

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

```text
hello ICPC world
```

**输出**：

```text
[hello ICPC world]
```

方括号只是让文本的边界更明显。如果输入空行，输出就是 `[]`。如果先用 `cin >> n` 读了数字，再读下一行，请看第 5 节，不能直接照搬这两行。

### size 和 text[i]：先知道有多长，再按位置取字符

把 `string text = "Hello ICPC!";` 想成一排格子：

| 下标 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 字符 | H | e | l | l | o | 空格 | I | C | P | C | ! |

- `text.size()` 是 `11`，中间的空格和末尾的 `!` 都算一个字符。
- `text[0]` 是 `'H'`，`text[6]` 是 `'I'`。单引号表示一个 `char`，双引号表示字符串文本。
- 对长度为 `n` 的非空字符串，正文字符的下标是 **0 到 n - 1**。遍历条件写 `i < text.size()`，不要写 `<=`。
- `text.empty()` 判断是否为空。空字符串的 `size()` 是 `0`，没有正文字符，不要去取“第一个”或“最后一个”字符。
- `size()` 返回无符号整数类型。别在空字符串上计算 `text.size() - 1`，它不会得到想象中的 `-1`。

`[]` 不会替你检查范围。C++17 中，`text[text.size()]` 是结尾的空字符 `\0`，**不是正文字符，也不能拿来添加字符**；更大的下标越界。初学时统一只在 `i < text.size()` 时访问正文即可。想让越界访问抛出异常，可以用 `text.at(i)`，但仍应先写对范围。

### tolower：一次只处理一个字符

需要 `<cctype>`。例如 `'A'` 可以变成 `'a'`；小写英文、数字、空格和标点保持原样。它**不会直接接收整个 string**，也不会自动把结果写回原变量。

**片段：** 安全地转换一个字符，并保存结果。

```cpp
char ch = 'A';
ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
```

从内往外读这一长行：

1. `static_cast<unsigned char>(ch)`：先把 `ch` 转成 `unsigned char`，再交给 `tolower`。有些机器的普通 `char` 能为负数，直接传入这样的值可能产生未定义行为；这一步避免这个问题。
2. `tolower(...)`：得到转换结果。它的返回类型是 `int`，不是 `string`。
3. `static_cast<char>(...)`：把结果转回 `char`，再用 `ch =` 保存；此时 `ch` 是 `'a'`。

整串转换时，把这一步放进循环，对每个字符做一次。下面的完整示例会演示。

**适用范围：** 这里主要处理竞赛题里的英文字母。`tolower` 的规则受当前 C locale（字符分类和转换规则）影响；本例没有改变它。它不是通用的 Unicode 大小写转换工具，不能把 UTF-8 文本逐字节传进去就当作完成了所有语言的大小写转换。

### substr：起点 + 数量，不是起点 + 终点

仍假设 `text` 是 `"Hello ICPC!"`：

| 写法 | 结果 | 为什么 |
| --- | --- | --- |
| `text.substr(0, 5)` | `"Hello"` | 从下标 0 开始，取 5 个 |
| `text.substr(6, 4)` | `"ICPC"` | 从下标 6 开始，取 4 个，不是取到下标 4 |
| `text.substr(6)` | `"ICPC!"` | 省略数量，就取到末尾 |
| `text.substr(6, 100)` | `"ICPC!"` | 数量超过剩余长度，只取剩下的部分 |
| `text.substr(text.size(), 3)` | `""` | 起点正好在末尾，得到空字符串 |

`substr` 返回一个**新字符串**，原来的 `text` 不变。想保存结果，可以写 `string part = text.substr(6, 4);`。

边界记住三点：

- `pos` 必须满足 `0 <= pos <= text.size()`；若 `pos > text.size()`，会抛出 `std::out_of_range` 异常，没处理时程序会结束。
- 起点合法时，`count = 0` 得到空字符串；数量太大只会截到末尾。
- 空字符串可以写 `text.substr(0, 5)`，结果仍为空；不能写 `text.substr(1)`。起点和数量都不要传负数，它们会转成无符号数，不表示“从后面数”。

### 完整示例 3A：五个工具一起用

读一行，输出长度和原来的首字符，再转成小写，最后截取前 5 个字符。空行也能安全处理。

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

```text
Hello ICPC!
```

**输出**：

```text
length: 11
first: [H]
lower: [hello icpc!]
prefix: [hello]
```

按顺序理解：

1. `getline` 读取整行；前面的 `!` 检查是否读取失败。输入空行会成功读到空字符串，并继续执行；完全没有输入才会在这里结束。
2. `size()` 输出长度。先用 `!text.empty()` 确认非空，再读取 `text[0]`，所以空行不会误取首字符。
3. `string::size_type` 是字符串长度和下标使用的无符号整数类型，与 `size()` 的结果类型一致。循环从 0 开始，`++i` 每轮加 1，直到 `i == text.size()` 停止；空行时循环一次也不执行。
4. 每轮把 `text[i]` 转成小写并写回同一位置，所以最后整个 `text` 都是转换后的内容。
5. `text.substr(0, 5)` 取最多前 5 个字符；少于 5 个就全部取出，空行则得到空字符串。它没有把 `text` 变短。

可以再试输入一行 `A`：长度是 `1`，首字符是 `A`，转换后和截取结果都是 `a`。直接按回车输入空行时，长度是 `0`，首字符一行显示 `first: (empty)`，后两行的方括号都是 `[]`。

<a id="stringstream"></a>
## 4. stringstream：把一行拆开读

**什么时候用：** 已经得到一整行文本，想从里面逐个提取单词或数字。

需要 `<sstream>`；字符串需要 `<string>`。

**片段：** 假设 `line` 已经存好一行文本。

```cpp
stringstream ss(line);
string word;
while (ss >> word) {
    cout << word << '\n';
}
```

逐行理解：

1. `stringstream ss(line);`：创建一个叫 `ss` 的输入工具，让它从字符串 `line` 中读内容。
2. `string word;`：准备一个变量存每次读到的单词。
3. `ss >> word`：试着读下一个单词。它读的是字符串，不是继续等键盘输入。
4. `while (...)`：只要读取成功就执行一次花括号里的代码；读完后自动结束。

它会把连续空格、制表符等空白当作分隔。它**不会自动按逗号分割**，所以 `red,blue` 会被当成一个单词。

### 完整示例 4：一行变成多个单词

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

```text
I love  ICPC
```

**输出**：

```text
I
love
ICPC
```

如果要提取整数，把接收变量改成 `int x;`，再写 `while (ss >> x)`；可能超出 `int` 范围时用 `long long x;`。**x 必须先声明类型**，不能直接复制一个从未声明过的 `x`。

读整数时，遇到无法继续解析为整数的内容或超出该类型范围的数字，会读取失败，循环停止。例如 `10 abc 20` 用整数方式只会读到 `10`，不会跳过 `abc` 再继续读 `20`。`stringstream` 不是完整的格式检查器；题目若规定“这一行全是整数”，应按这个前提使用。

<a id="mixed-input"></a>
## 5. cin 后接 getline：为什么会读到空行

假设输入格式是：第一行一个编号，第二行若干整数。

`cin >> id` 读走编号后，第一行末尾的换行通常还在输入中。这时立刻 `getline(cin, line)`，它读到这个换行就结束，于是得到空字符串。

### 推荐做法：明确丢掉第一行的剩余内容

**片段：** `id` 是已声明的整数，`line` 是已声明的字符串；另需 `<limits>`。

```cpp
cin >> id;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, line);
```

中间这一长行可以先整体记住：**一直丢弃字符，直到遇到并丢掉下一个换行**。`numeric_limits<streamsize>::max()` 提供足够大的忽略上限。

只在“上一行剩余内容不要了，真正要读的是下一行”时这样做。如果编号和有用文本就在同一行，这样写会把文本一起丢掉。

### 完整示例 5：先读编号，再把下一行的整数求和

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

```text
7
10 20 30
```

**输出**：

```text
id: 7
sum: 60
```

`total += x` 等价于 `total = total + x`。这段假定第二行每个整数，以及累加途中和最终得到的总和，都在 `long long` 范围内。第二行若是空行，一个数也读不到，和保持为 `0`。

### 另一种写法，先知道限制再用

**片段：** `line` 是 `string`。

```cpp
getline(cin >> ws, line);
```

`ws` 会先跳过**所有连续空白**，包括多个换行以及有意保留的行首空格。因此：

- 不在意空行、行首空格时，这种写法方便。
- 要保留空行或行首空格时，用前面的 `ignore(..., '\n')`，并确认输入格式确实是“读下一行”。
- 如果从程序开始就一直用 `getline`，通常不需要额外清理换行。

不要用“先随便 `getline` 一次”当万能修复，它可能把真正需要的那一行读走。

<a id="word-count"></a>
### 把四步串起来：读整行 → 转小写 → 拆单词 → 比较

**想完成什么：** 第一行输入一个英文目标词，第二行输入一整行文本，统计目标词出现几次，忽略英文字母大小写。例如查找 `Hello`，`hello` 和 `HELLO` 都算，但 `helloworld` 不算。

下面四步都是**片段**，最后有一份可以直接运行的完整程序。它们使用同一组变量：`word` 是目标词，`text` 是整行文本，`temp` 是每次拆出的词。

#### 第 1 步：读完整一行

**片段：** 输入格式是“第一行目标词，第二行文本”，需要 `<iostream>`、`<string>`、`<limits>`。

```cpp
string word;
string text;
cin >> word;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, text);
```

你可能见过更短的 `cin.ignore();`。**不带参数时，它最多只丢掉 1 个字符**：只有当前紧接着一个待清理的换行时，才刚好符合这里的用途。如果第一行目标词后还有空格，它可能只丢掉一个空格，后面的 `getline` 仍会读到第一行剩余内容。

这里用 `ignore(..., '\n')` 明确清理第一行的剩余内容，再读第二行。它的适用前提仍是“有用文本在下一行”；目标词和文本在同一行时，这样写会把文本丢掉。若从头到尾都用 `getline`，也不要无缘无故先 `ignore()`，否则可能吞掉有用字符。

#### 第 2 步：把文本和目标词都转成小写

**片段：** `text`、`word` 已有内容；另需 `<cctype>`。

```cpp
for (char& c : text) {
    c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
}
for (char& c : word) {
    c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
}
```

- `for (char& c : text)`：依次处理 `text` 中的每个字符；你见到的 `s` 只是另一个变量名，这里统一叫 `text`。
- `char&` 中的 `&` 表示**引用**，可以理解成“给原来的那个字符起别名”。修改 `c`，就是修改字符串里的那个字符。
- 若写成 `for (char c : text)`，`c` 是一份副本，修改它不会让原来的 `text` 变小写。
- `word` 也要做同样的转换；只转换文本，目标词 `Hello` 仍然无法和 `hello` 相等。

安全转换的内外两层 `static_cast` 和非 Unicode 限制，见[第 3 节的 tolower 说明](#getline)。这里仍按英文大小写转换来理解。

#### 第 3 步：从整行里逐个取词

**片段：** `text` 已转成小写；另需 `<sstream>`。

```cpp
stringstream ss(text);
string temp;
while (ss >> temp) {
    // 每成功取出一个新词，就在这里处理这个 temp。
}
```

`ss` 从已有的 `text` 中读，不是再等键盘输入。`while (ss >> temp)` 每次先尝试读取**下一个新词**：成功才进入循环体，读完或读取失败就停止。不要把取词放在循环外只做一次，也不要在循环结束后再拿旧的 `temp` 多统计一次。

连续空格、制表符等空白会被跳过，不会生成“空单词”。第二行为空或只有空白时，循环一次也不执行。更多拆分规则见[第 4 节](#stringstream)。

#### 第 4 步：比较当前词，相等就计数

**片段：** `word` 是已转小写的目标词，`temp` 是循环中刚读出的词。

```cpp
// 这一行放在 while 循环外，开始统计前只执行一次。
long long count = 0;

// 下面的 if 放在 while (ss >> temp) 的循环体内。
if (temp == word) {
    ++count;
}
```

- `==` 是**比较是否相等**；一个 `=` 是赋值，不能把这里写成 `temp = word`。
- 这里比较的是两个字符串的全部内容，不是“包含关系”。`hello` 等于 `hello`，`helloworld` 不等于 `hello`。
- `++count` 表示次数加 1。`count` 必须在循环外初始化为 `0`，否则每读一个词都清零，就记不住前面的次数。

### 完整示例 5A：忽略英文大小写，统计整词次数

输入第一行是一个非空目标词，第二行是待统计文本。这里把**按空白分隔出的每一段文本**当作一个词；不自动删除标点，所以 `hello,` 和 `hello` 不相等。输出只有次数。

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

```text
Hello
hello  HELLO world helloworld Hello
```

**输出**：

```text
3
```

处理过程：目标词先变成 `hello`；第二行拆出 `hello`、`hello`、`world`、`helloworld`、`hello`，其中 3 个与目标词完全相等。若第二行是空行、全是空格，或者没有匹配词，都会输出 `0`；如果缺少第二行，则读取失败，直接结束。

这是一份演示四步如何配合的计数程序。遇到[洛谷 P1308](https://www.luogu.com.cn/problem/P1308) 等具体题目，还要按题面补上首次出现位置、未找到时的输出等要求；不要把这份示例直接当作完整题解提交。

<a id="char-reference"></a>
### char& 为什么能改原字符：联系引用和指针

**记住一句话：字符串循环里的 `char& c`，就是为了直接修改原来的字符。** `char &c` 和 `char& c` 只是空格位置不同，含义一样。

#### 先分清副本、引用、指针

**片段：** 先有一个普通整数，再分别建立副本、引用和指针。

```cpp
int value = 10;
int copy = value;      // 复制一份值，copy 和 value 是两个变量
int& alias = value;   // alias 是 value 的另一个名字
int* p = &value;      // p 保存 value 的地址
```

- `copy = 20;`：只改副本，不改 `value`。
- `alias = 20;`：通过别名修改 `value`，不用写 `*alias`。
- `*p = 20;`：通过指针找到它指向的整数，再修改那个整数；这里改的也是 `value`。这个 `*p` 操作叫**解引用**。

同一个 `&`，要看出现在哪里：

- `int& alias = value;` 的 `&` 在**声明类型处**，表示 `alias` 是引用。
- `int* p = &value;` 的 `&value` 在**表达式里**，表示取出 `value` 的地址。
- 声明里的 `int*` 表示“指向 int 的指针”；之后表达式里的 `*p` 才表示访问它指向的整数。

引用和指针有关联，但不要混成同一种写法：

| 比较什么 | 引用 `int& alias = value;` | 指针 `int* p = &value;` |
| --- | --- | --- |
| 初学时怎么理解 | 原对象的别名 | 保存对象地址的变量 |
| 怎样修改原对象 | `alias = 20;` | `*p = 20;` |
| 能否换目标 | 初始化后不能重新绑定别的对象 | 可以用 `p = &other;` 改为指向另一个有效对象 |
| 能否表示“没有目标” | 正常使用时必须绑定有效对象，没有 `nullptr` 这种引用状态 | 可以设为 `nullptr`，但此时不能解引用 |

局部引用不能只写 `int& alias;` 就放着，声明时要初始化，例如 `int& alias = value;`。指针也不要先写一个未初始化的 `int* p;` 就拿去用：先写 `int* p = &value;`，或用 `int* p = nullptr;` 表示暂时没有目标。`p != nullptr` 只是在排除空指针；真正解引用时，还要确认它指向的对象仍然有效。

这些是 C++ 的使用规则。学到这里，不需要猜测“编译器一定怎样存引用”，也不要把引用当作可以随意重新指向的指针。

### 完整示例 5B：通过别名和指针修改整数

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

**输出**：

```text
value: 20
alias: 30
value / other: 30 50
alias / other: 50 60
p is null
```

前两次修改都作用于 `value`。`p = &other` 之后，`*p` 改的是 `other`，所以 `value` 仍是 `30`。`alias = other` 则把数值 `50` 赋给 `value`；后来 `other` 变成 `60`，`alias` 仍代表 `value`，读到的还是 `50`。

#### 套回字符串：副本和原字符的区别

看到“修改字符串里的每个字符”，就想到 `for (char& c : s)`：`s` 是一个已经声明的 `string`，每一轮的 `c` 都是当前原字符的别名。循环进入下一轮时，会为下一个字符建立这一轮的引用；这不等于对同一个引用重新绑定。

通用思路是：**遍历一个字符 → 算出新字符 → 赋回 `c`**。若笔记写成 `c = xxx(c)`，`xxx` 只是“你要做的转换”的占位名，不是 C++ 内置函数。实际代码要换成已经定义的函数，例如 `<cctype>` 里的 `tolower` 或 `toupper`。

| 想做什么 | 循环体中的安全写法 |
| --- | --- |
| 转成小写 | `c = static_cast<char>(tolower(static_cast<unsigned char>(c)));` |
| 转成大写 | `c = static_cast<char>(toupper(static_cast<unsigned char>(c)));` |

两种转换都先把输入转成 `unsigned char`，把结果转回 `char`，最后赋回 `c`。只调用 `tolower(c)` 或 `toupper(c)` 而不保存返回值，不会自动修改 `c`。转换规则依赖当前 C locale；下面没有改变默认规则，主要用于英文字母，不能把逐字节转换当作通用 Unicode 处理。空格、数字和常见标点在本例中保持不变。

### 完整示例 5C：同一字符串，对比复制与原地修改

先用 `char c` 转小写并输出副本，再查看原字符串；然后用 `char& c` 真正修改原字符，最后转大写。

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

```text
HeLLo ICPC!
```

**输出**：

```text
copy loop output: [hello icpc!]
text after copy: [HeLLo ICPC!]
text after reference: [hello icpc!]
text after uppercase: [HELLO ICPC!]
```

第一行虽然输出了小写，但修改的是每轮的副本，所以第二行的 `text` 仍保持原样。后面两次使用 `char&`，才真正把 `text` 改成小写、再改成大写。输入空行时，三个循环都不执行，四行方括号内都为空；没有任何输入时直接结束。

<a id="string-templates"></a>
### 四种字符串模板：先看题目要你做什么

这些模板里的 `s` 都是已经声明并读入内容的 `string`，不是新的特殊类型。需要哪一种就选哪一种，不必每题都写四遍。

| 需求 | 选择的写法 | 详细解释 |
| --- | --- | --- |
| 1. 逐个检查字符 | 需要下标就用 `s[i]`；不需要下标就用 `for (char c : s)` | [下标范围](#getline)、[副本和引用](#char-reference) |
| 2. 修改原字符串中的字符 | `for (char& c : s)`，算出新字符后赋回 `c` | [转小写、转大写及对照示例](#char-reference) |
| 3. 简单拆成单词 | `stringstream ss(s); string word;`，再用 `while (ss >> word)` | [拆词规则](#stringstream)、[完整四步示例](#word-count) |
| 4. 拆词时还要原字符串里的位置 | 用下标 `i` 手动扫描，记住 `start`，再 `substr(start, i - start)` | 见下面的扫描示例 |

#### 模板 1：检查字符，需要位置就保留下标

**片段：** `s` 已读好；下面逐行输出每个字符的下标和字符本身，需 `<string>`、`<iostream>`。

```cpp
for (string::size_type i = 0; i < s.size(); ++i) {
    cout << i << ": [" << s[i] << "]\n";
}
```

`string::size_type` 与 `size()` 的结果类型一致，可以避免直接拿 `int` 和无符号长度比较的警告。条件必须是 `i < s.size()`。只写一行 `s[i];` 并不会输出、比较或修改它；要像上面这样真正使用这个字符。

如果只想看看字符、判断它是不是某个值，不需要位置，可以写 `for (char c : s)`，在循环体里使用 `c`。这时拿到的是副本，修改副本不会改原串。

#### 模板 2：改原串，就加 &

大小写转换直接用前面的[安全转换模板](#char-reference)。换成“遇到某个字符就替换”，思路也一样。

**片段：** 把已经读入的 `s` 中每个短横线 `'-'` 改成空格。

```cpp
for (char& c : s) {
    if (c == '-') {
        c = ' ';
    }
}
```

例如 `hello-ICPC` 会变成 `hello ICPC`。这里改的是原串；若后面需要原始内容，要提前保存一份。若题目只让忽略大小写，不要额外替换标点或删空格。

#### 模板 3：只要单词，用 stringstream

前面的[第 4 节](#stringstream)已有完整写法，关键组合是 `stringstream ss(s)`、声明接收变量 `string word`、再 `while (ss >> word)`。默认情况下，连续空格、制表符等空白都会被当作分隔；它不会自动去掉单词上的标点。

这种简单取词循环没有替你记录每个词在原串中的起点。**第几个单词**和**第几个字符**是两回事；不能直接把词序号当作原位置。

#### 模板 4：需要原字符位置，用下标扫描

下面约定**只用普通空格 `' '` 分词**。这与 `stringstream` 按一般空白分词不同：制表符 `\t` 在这个手动模板里属于词的一部分，不会被自动跳过。先按题面选好分隔规则。

扫描过程只有三件事：

1. `i` 指向当前还没处理的字符。遇到空格就 `++i`，再 `continue`，直接开始下一轮。
2. 遇到非空格，把当前位置保存成 `start`，它是这个词的**起点**。然后一直往后走，直到遇到空格或字符串结束。
3. 此时 `i` 是这个词**结尾后面一位**，所以词对应区间是 `[start, i)`，长度是 `i - start`。用 `s.substr(start, i - start)` 取出词。

关键条件必须写成 `i < s.size() && s[i] != ' '`：先确认没到末尾，才访问 `s[i]`。`&&` 左边为假时不会执行右边。只写 `while (s[i] != ' ')` 会在最后一个词后没有空格时继续越过边界。

例如原串示意是 `··hi··ICPC·ok··`，这里每个 `·` 只用来表示一个普通空格，实际字符串里没有这个点：

| 取出的词 | start：起点 | i：词末尾后一位 | i - start：长度 |
| --- | --- | --- | --- |
| `hi` | 2 | 4 | 2 |
| `ICPC` | 6 | 10 | 4 |
| `ok` | 11 | 13 | 2 |

下标从 `0` 开始，前导空格、连续空格和尾部空格都在原串中占位置。两端各有两个空格时，整个字符串长度是 `15`；去掉最后两个空格，长度变成 `13`，最后一个词的 `i` 正好等于 `s.size()`，仍然能够正常取出 `ok`。

### 完整示例 5D：输出每个词和它在原串中的起点

程序不删除空格、不修改字符串，输出格式是 `[词] 起点下标`。分隔符只认普通空格 `' '`；空行和全空格行没有单词，因此不输出任何行。

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

```text
  hi  ICPC ok
```

**输出**：

```text
[hi] 2
[ICPC] 6
[ok] 11
```

再给输入末尾加两个空格，输出仍相同。若输入 `hi, ICPC!`，输出 `[hi,] 0` 和 `[ICPC!] 4`，标点会保留在词里；如果要支持其他分隔规则，先按题意调整，不能默认所有题都这样分词。

`i` 在跳空格或扫描单词时都会前进，最终到达 `s.size()`，所以空串、全空格、连续空格和最后一个词后没有空格时都能结束。位置仍按 `std::string` 的存储单元计数，UTF-8 中文不能直接按汉字个数理解。

**选择口诀：整句用 getline → 改大小写用 char& → 只要词用 stringstream → 要原字符位置就手动扫描。** 这个扫描结构可用于补上前面提到的 P1308 位置记录，但仍需按题面处理目标词比较、计数和最终输出格式。

<a id="recap"></a>
## 6. 六种原始写法速查

下面都是**片段**，不是一段可以直接整体运行的程序。所需头文件见第 0 节。

| 想做什么 | 写法 | 使用前提 / 结果 |
| --- | --- | --- |
| 准备 n 个整数 | `vector<int> v(n);` | `n` 已读入、非负且大小合理 |
| 读入 n 个数 | `for (int i = 0; i < n; i++) { cin >> v[i]; }` | `v` 已有 n 个元素 |
| 从小到大排序 | `sort(v.begin(), v.end());` | 原地修改 `v`，重复值不消失 |
| 得到去重集合 | `set<int> unique_values(v.begin(), v.end());` | 新集合有序、不重复；`v` 不变 |
| 读取整行 | `getline(cin, line);` | 先声明 `string line;`，留意前一次数字输入的换行 |
| 按空白提取单词 | `stringstream ss(line); string word; while (ss >> word) { /* 使用 word */ }` | `line` 已有内容；读到末尾就结束 |

遇到报错，先检查：

1. 工具的头文件有没有包含？写了 `using namespace std;`，或给工具加了 `std::` 吗？
2. 变量有没有先声明，读取数量后才创建 `vector` 吗？
3. 集合和字符串是不是错误地都用了 `s`？传给 `getline` 的第二个参数是不是 `string`？
4. 下标是不是写成了 `i <= n`，从而访问了不存在的 `v[n]`？
5. 数字输入后是否正确处理了换行？
6. 是否把几个完整示例拼到一起，导致出现多个 `main()`？

**到这里，你已经可以完成“读一组数 → 排序 → 去重”和“读一行 → 拆成单词/整数”。下面按需要选读即可。**

<a id="more-vector"></a>
## 7. 选读：vector 的增删、倒序排序

### 先知道长度，还是边读边追加？

- `vector<int> v(n);`：一开始就有 n 个元素，适合用 `v[i]` 输入。
- `vector<int> v;`：一开始是空的，适合用 `v.push_back(x)` 逐个往末尾追加。
- **不要先建 n 个元素，又追加 n 次**，否则会得到 2n 个元素，前 n 个还可能全是 0。

常用操作（`v` 是 `vector<int>`，`x` 是整数）：

| 写法 | 作用 | 注意 |
| --- | --- | --- |
| `v.size()` | 当前元素个数 | 是无符号整数类型，初学先别写 `v.size() - 1`，空容器时会出问题 |
| `v.empty()` | 判断是否为空 | 空时结果为 `true` |
| `v.push_back(x)` | 在末尾添加 x | 长度增加 1 |
| `v.pop_back()` | 删除最后一个元素 | 必须非空；它不返回被删的值 |
| `v.front()` / `v.back()` | 访问第一个 / 最后一个元素 | 必须非空 |
| `v.clear()` | 删除所有元素 | 之后长度为 0 |

`reserve(n)` 只是提前准备存储空间，**不会创建 n 个元素**。`vector<int> v; v.reserve(5);` 之后仍然不能访问 `v[0]`；要么用 `push_back`，要么用 `resize(5)` 真的创建元素。

### 倒序也可以直接排序

**片段：** `v` 已有数据，需要 `<algorithm>`。

```cpp
sort(v.rbegin(), v.rend());
```

这里的 `rbegin()`、`rend()` 表示反向遍历的区间。排序后，从普通的开头看，`v` 就是从大到小。别把 `begin()` 与 `rend()` 混成一对。

### 完整示例 6：追加、删除、倒序排序

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

**输出**：

```text
size: 3
values: 8 3 1
```

<a id="unique"></a>
## 8. 选读：保留 vector 的去重方式

**什么时候用：** 想去掉重复数，又想继续用下标访问结果。

需要 `<vector>` 和 `<algorithm>`。常见组合是：

**片段：** `v` 是 `vector<int>`。

```cpp
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

别急着死记，按三步理解：

1. `sort` 先排序，让相同的数挨在一起。
2. `unique` 只压缩**相邻的重复元素**，把保留的元素放到前面，返回“新的有效部分的终点”。**它自己不会缩短 `v.size()`。** 终点后面的值不应再当作有效去重结果使用。
3. `erase` 删除从新终点到旧终点的部分，容器才真正变短。

所以，仅写 `unique(...)` 不够；没有排序时，它也不会消除所有相隔很远的重复值。这个组合会改变原来顺序，若题目要求保留首次出现顺序，就不能直接套它。

### 完整示例 7：排序并原地去重

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

**输出**：

```text
size: 3
values: 1 2 3
```

<a id="binary-search"></a>
## 9. 选读：二分查找一定先确认有序

**什么时候用：** 对已经排好序的一组数据，反复查某个数是否存在、第一次出现在哪里、出现几次。

需要 `<algorithm>`。本文使用默认比较规则，**先按从小到大排序**，再使用下面的函数；不要拿第 7 节的倒序结果直接用。

| 函数 | 在从小到大排列的区间中找什么 | 返回什么 |
| --- | --- | --- |
| `binary_search(begin, end, x)` | x 是否存在 | `bool`，即 `true` 或 `false` |
| `lower_bound(begin, end, x)` | 第一个大于或等于 x 的位置 | 迭代器 |
| `upper_bound(begin, end, x)` | 第一个严格大于 x 的位置 | 迭代器 |

用 `1 2 2 2 5` 查 `2`：

- `lower_bound` 指向下标 1。
- `upper_bound` 指向下标 4，也就是值 5 的位置。
- 两个位置相减：`4 - 1 = 3`，所以 2 出现 3 次。

`lower_bound` 找到的是“第一个 >= x”的位置，**不保证那个数就等于 x**。查不存在的 `3`，它会指向 `5`；查 `9`，会得到 `end()`。

### 完整示例 8：找下标、计数，并处理找不到

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

**输出**：

```text
first index: 1
count: 3
has 3: 0
9 not found
```

新语法解释：

- `auto`：让编译器从右侧表达式推断变量类型，这里推断的是迭代器类型，不是元素值。
- `*pos`：取出这个位置的元素值。只有 `pos != v.end()` 时才可以这样读。
- `&&`：表示“并且”，左边为假时不会执行右边。所以先检查 `pos != v.end()`，再读取 `*pos`，顺序很重要。
- 对 `vector`，`pos - v.begin()` 得到从 0 开始的下标；迭代器相减不能照搬到 `set` 或 `map`。
- `cout` 默认把 `bool` 输出为 `1`（真）或 `0`（假），所以 `has 3: 0` 表示没有 3。

为了查很多次，通常先排序一次，再做多次二分，不要每查一次都重新排序。

<a id="binary-search-lrmid"></a>
### 手写二分入门：脑子里先记住 l、r、mid

**以后看到二分，先记这三个变量：`l` 是左边界，`r` 是右边界，`mid` 是中间位置。** 二分就是：看中间的数，每次排除不可能有答案的那一半，继续在剩下的范围里找。

下面只学一种：**在从小到大排好的整数数组中，找一个等于 `x` 的数**。允许相等的数挨在一起，例如 `1 2 2 5` 也符合要求。不是所有题目的“二分”都能直接套这一版。

#### 先分清：下标是位置，元素值是格子里的数

例如 `vector<int> a = {1, 3, 5, 7, 9, 11, 13};`，一共有 `n = 7` 个数：

```text
下标：  0   1   2   3   4   5   6
数值：  1   3   5   7   9  11  13
        ↑           ↑           ↑
        l          mid          r
```

- `l`、`r`、`mid` 都保存**下标**，不是数组里的数。下标从 `0` 开始，所以最后一个下标是 `n - 1`。
- 开始时 `l = 0`、`r = n - 1`，表示整排格子都有可能。
- 这一轮 `mid = 3`，但 `a[mid] = 7`。查找时要比较 **`a[mid]` 和 `x`**，不能拿 `mid` 和 `x` 比。
- `[l, r]` 表示从 `l` 到 `r`，**两端都包含**。例如 `[2, 4]` 里有下标 `2、3、4`，共 3 个位置。它和前面字符串扫描的半开区间 `[start, i)` 不一样。

#### 先把骨架补完整：中间太小向右找，太大向左找

你记住的骨架是 `int l = 0;`、`int r = n - 1;` 和 `while (l <= r)`。但循环中**只算 `mid` 还不够**：必须在找到时退出，或更新边界，否则会一直查看同一个位置。

**片段：** `a` 已从小到大排好，`n` 是它的长度，`x` 是目标值；这里的 `n` 是非负的 `int`。

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

1. **`while (l <= r)`：只要还有候选位置，就继续找。** `l == r` 时还剩一个格子，也要检查，所以这里不能少写等号。
2. **`mid`：取当前范围中间的下标。** 整数除法会舍去小数，例如 `[0, 5]` 的 `mid` 是 `2`。`(l + r) / 2` 容易记，但下标很大时 `l + r` 可能超出 `int` 范围；在这里合法的非负下标范围内，`l + (r - l) / 2` 能避免这个加法溢出。
3. **相等：记下位置并 `break`。** `found` 保存的是下标；`-1` 不是合法下标，不能写 `a[-1]`。若之后想访问 `a[found]`，必须先确认 `found != -1`。
4. **中间太小：`l = mid + 1`。** 因为数组有序，`mid` 及它左边的数都不会更大，全都不可能等于 `x`，所以一起排除。
5. **中间太大：`r = mid - 1`。** 同理，`mid` 及它右边的数都太大，一起排除。
6. **没找到就不断缩小范围，直到 `l > r`。** 这时一个候选位置都不剩，循环结束，`found` 仍是 `-1`。

为什么必须 `+1` / `-1`？因为这一轮已经确认 `mid` 不等于目标，下一轮不要再查它。若误写成 `l = mid`，当 `l == r == mid` 且中间值偏小时，范围完全不变，就会死循环。**这一版的初始化、`<=` 和 `±1` 是一整套，不要和别的二分模板混着用。**

#### 手算一次：在 1、3、5、7、9、11、13 中找 9

`x = 9`，`found` 开始为 `-1`。每一行都是“先算中间，再比较，再更新”：

| 轮次 | l | r | mid | a[mid] | 比较与下一步 |
| --- | --- | --- | --- | --- | --- |
| 1 | 0 | 6 | 3 | 7 | `7 < 9`，令 `l = 4`，剩 `[4, 6]` |
| 2 | 4 | 6 | 5 | 11 | `11 > 9`，令 `r = 4`，剩 `[4, 4]` |
| 3 | 4 | 4 | 4 | 9 | 相等，令 `found = 4`，退出循环 |

答案是**下标 4**，不是数值 9。它对应从 1 开始数的“第 5 个”，但程序按从 0 开始的下标输出 `4`。最后一轮 `l == r` 仍然进入循环，这就是 `<=` 的作用。

如果把目标改为 `8`，前两轮一样；第三轮看到 `9 > 8`，令 `r = 3`。此时 `l = 4 > r = 3`，循环结束，结果为 `-1`。结束后不要再用越界的边界去访问数组。

### 完整示例 8A：自己写二分，输出找到的下标

输入依次是：非负整数 `n`、`n` 个**已从小到大排好**的整数、目标值 `x`。输出一个从 `0` 开始的下标；不存在就输出 `-1`。当 `n = 0` 时没有数组元素，读完 `n` 就直接读 `x`。

这份程序不自动排序：目的是看清二分本身，也避免悄悄改变题目里的原位置。若实际题目允许排序，可以先 `sort`；此后得到的是**排序后的下标**，不是原输入位置。

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

```text
7
1 3 5 7 9 11 13
9
```

**输出**：

```text
4
```

#### 别只测找到的情况：这些边界也要会解释

| 数组 a | x | 这份程序的输出 | 原因 |
| --- | --- | --- | --- |
| 空数组（`n = 0`） | 42 | `-1` | `l = 0`、`r = -1`，循环一次也不执行，不访问数组 |
| `7` | 7 | `0` | 唯一的格子就在下标 0 |
| `7` | 6 | `-1` | 唯一的数不匹配，排除后范围为空 |
| `2 8` | 8 | `1` | 先排除下标 0，再检查下标 1 |
| `1 3 5` | 0 或 9 | `-1` | 比最小值还小或比最大值还大，都不存在 |
| `1 2 2 2 5` | 2 | `2` | 第一轮中间就找到一个 2，但它不是第一个 2 |

空数组可以直接输入两行 `0`、`42`，无需补一行数组元素。这里用有符号的 `int n` 计算 `n - 1`，所以空数组时得到 `-1`；不要直接把 `a.size() - 1` 照搬过来，`size()` 返回无符号类型，空数组时减一不会得到期望的负数。

**有重复值时，这个模板只保证找到其中一个匹配位置，不保证第一个或最后一个。** 要求第一次出现，用本节前面的 `lower_bound`，并检查返回位置不是 `end()` 且对应值等于 `x`；要求次数，可以结合 `upper_bound`。

最后记住：

- **有序才能排除一半。** 未排序或从大到小的数据，不能直接用这一版；程序不会替你检查是否有序。
- 每轮把候选范围大约缩小一半，二分查找的时间复杂度是 **`O(log n)`**，额外空间是 **`O(1)`**；空数组会直接结束。直观上，约 100 万个数也只需约 20 轮比较。
- 这是查找部分的复杂度。完整程序还需要 `O(n)` 时间读入、`O(n)` 空间保存数组；若另加排序，还要计算排序的时间。
- 口令：**左 l，右 r，中间 mid；小了往右，大了往左；找到就停，边界交错就没有。**

<a id="sum"></a>
## 10. 选读：求和时注意 long long 和 0LL

一个数能放进 `int`，不代表许多数的总和也能。常见竞赛环境的 `int` 是 32 位，最大约 21 亿；`long long` 通常是 64 位，范围大得多，但也有上限。

你可以用第 5 节的 `long long total = 0;` 配合循环求和，也可以用 `<numeric>` 中的 `accumulate`。

**片段：** `v` 已经有数据，并包含 `<numeric>`。

```cpp
long long total = accumulate(v.begin(), v.end(), 0LL);
```

第三个参数是累加的初始值，还决定**保存每一步累加结果的变量类型**，也叫累加器类型：

- `0` 使累加器为 `int`，每一步结果都要存回 `int`，可能容纳不下。
- `0LL` 使累加器为 `long long`，从一开始就用更大的类型保存每一步结果。
- 仅把最终接收变量写成 `long long`，不能补救中途超出类型范围的问题。

用 `long long` 也要保证每次相加的中间结果都在它的范围内，不能只看最后的答案是否放得下。

### 完整示例 9：求一个超过常见 int 范围的总和

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

**输出**：

```text
6000000000
```

类似地，如果 `a`、`b` 是 `int`，需要大整数乘法时应让**计算本身**进入 `long long`，例如 `1LL * a * b`；仅写 `long long result = a * b;` 仍可能先发生 `int` 溢出。

<a id="containers"></a>
## 11. 选读：再认识三种常用工具

先记住用途就好，不必一次掌握全部操作。

| 工具 | 适合做什么 | 直观类比 |
| --- | --- | --- |
| `map` | 给每个名字或数字关联一个值，比如统计次数 | “单词 → 次数”的表 |
| `queue` | 按进入顺序处理，先来的先处理 | 排队 |
| `stack` | 后放入的先处理 | 叠盘子，先拿最上面一个 |

### map：统计每个单词出现几次

需要 `<map>`。`map<string, int> count;` 表示“键是字符串，值是整数”。这里**键**就是要统计的单词，**值**就是次数。

`count[word]++` 的意思是把这个单词的次数加 1；对于这个类型的 `map`，若该单词还不存在，`operator[]` 会先插入它，并把对应的整数初始化为 `0`，再加 1。

所以 `count[word]` 不只是查询，还可能添加新键。只想判断是否存在时，可以用 `count.find(word) != count.end()`。

### 完整示例 10：单词计数

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

```text
banana apple banana pear apple banana
```

**输出**：

```text
apple 2
banana 3
pear 1
```

这里遍历 `map` 时按键从小到大输出；对样例中的小写英文单词，可以理解成字典顺序，不是首次出现顺序。

每个 `entry` 是一个“键和值组成的对”：`entry.first` 是单词，`entry.second` 是次数。`const auto&` 可以先读成“给当前元素起一个只读的别名，不复制它”，暂时不需要深入引用的全部规则。

### queue 和 stack：只从规定的一端取数据

- `queue<int> q;` 需要 `<queue>`：`push(x)` 加到队尾，`front()` 看队头，`pop()` 删除队头。
- `stack<int> st;` 需要 `<stack>`：`push(x)` 压到栈顶，`top()` 看栈顶，`pop()` 删除栈顶。
- 两者都可以用 `empty()` 判断是否为空、`size()` 查询数量。
- **pop() 不返回元素**，要先 `front()` 或 `top()` 读取，再 `pop()`。
- 空容器不能调用这些读取或删除操作，先检查 `empty()`。

### 完整示例 11：同样放入 1、2、3，取出顺序不同

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

**输出**：

```text
queue: 1 2 3
stack: 3 2 1
```

`!q.empty()` 表示“q 不是空的”，所以每轮都能安全读取队头；`stack` 同理。

<a id="practice"></a>
## 12. 小练习与提交前检查

### 先自己改，再看提示

1. 把示例 2 改成从大到小输出排序结果。去重的 `set<int>` 输出顺序会跟着变吗？
2. 输入 `5` 和 `4 4 1 2 1`，输出有多少种不同的数。
3. 输入一整行英文，统计单词数量。连续两个空格应不应该多算一个单词？
4. 在排好序的 `1 2 2 2 5` 里，分别查找 `0`、`2`、`3`、`9`，检查每个数出现几次。

<details>
<summary>点击看提示和预期结果</summary>

1. 用 `sort(v.rbegin(), v.rend())` 改变 `vector` 的排序方向。默认 `set<int>` 仍按从小到大遍历，因为它有自己的排序规则。
2. 可以把输入放进 `set`，再输出它的 `size()`。不同的数是 `1 2 4`，答案为 `3`。
3. 用 `getline`、`stringstream`、`string word`，每次 `ss >> word` 成功就计数加 1。连续空白不会产生额外单词。
4. 用 `upper_bound(...) - lower_bound(...)` 得到次数，结果分别为 `0`、`3`、`0`、`0`。先保证序列从小到大。

</details>

### 每次复制前，问自己这几件事

- 我需要保留原顺序吗？`sort`、`set` 和排序去重会改变顺序。
- 我要读一个词，还是完整一行？数字后接整行是否处理了换行？
- 容器里真的有这么多元素吗？`reserve` 不等于 `resize`，`end()` 也不是最后一个元素。
- 二分前数据是从小到大的吗？找不到时有没有先检查 `end()`？
- 总和或乘积会不会超出类型范围？`accumulate` 的初始值用对了吗？
- 题目输出只要求答案吗？示例中的 `sorted:`、`size:` 等标签用于讲解，提交题目时按题面要求调整。

再试几组边界数据：`n = 0`、只有一个数、全部相同、包含负数、文本为空。能解释这些输入会发生什么，比单纯背下代码更有用。

[回到阅读导航](#怎么读) · [返回仓库首页](README.md)

