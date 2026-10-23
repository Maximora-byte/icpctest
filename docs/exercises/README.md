<a id="分类习题总目录"></a>
# 分类习题总目录 / Categorized Exercise Catalog

这里收录与仓库源码对应的复习题，按「总目录 → 知识点分类 → 独立题目」组织。每道题保留一个正文文件，用稳定编号和标签交叉检索，题目增多后无需把所有题面塞进一页。

This catalog contains revision exercises corresponding to the repository source files, organized as “catalog → topic category → standalone problem.” Keep one main document per problem and cross-reference stable IDs and tags, rather than crowding every problem statement onto one page as the collection grows.

**当前范围：**本目录已整理 5 道 C++ 基础练习题目页。仓库另有 7 个输入型练习 / 草稿源码，当前行为与状态见[仓库源码索引](../../README.md#输入型练习与学习草稿)，尚未分配新的 EX 编号或补齐题目页。以下说明仅针对已整理的 5 道题。题面根据现有源码整理，尚未确认原始题库与题号；不能据此推断比赛来源或在线评测通过状态。原程序全部使用固定数据、没有标准输入。各题标为「未实现」的拓展练习仅供复习。

**Current scope:** This catalog has five C++ fundamentals problem pages. The repository also contains seven input-based exercise / draft source files; see the [source index](../../README.md#输入型练习与学习草稿) for their current behavior and status. They have not yet received new EX IDs or complete problem pages. The following guidance concerns the five documented problems only. Their statements were reconstructed from existing source; the original problem collection and IDs are unconfirmed, so neither contest origin nor online-judge acceptance can be inferred. All five original programs use fixed data without standard input. Extensions marked “not implemented” are for revision only.

<a id="已收录分类"></a>
## 已收录分类 / Included Categories

| 主分类<br>Main category | 二级知识点<br>Subtopics | 题数<br>Count | 入口<br>Entry point |
| :--- | :--- | ---: | :--- |
| 基础语法 `basics`<br>Fundamentals `basics` | 基本输出、数据类型与变量、赋值运算符<br>Basic output, types and variables, assignment operators | 5 | [基础语法分类与题目索引](basics/README.md)<br>[Fundamentals category and problem index](basics/README.md) |

第一次学习建议依次完成 EX0001 到 EX0005。复习时可以直接从分类页按知识点或标签查找，并在题目页先做题、后展开参考答案。

For a first pass, complete EX0001 through EX0005 in order. For revision, browse topics or tags on the category page, attempt a problem first, and then expand its reference answer.

<a id="后续分类规划"></a>
## 后续分类规划 / Planned Categories

以下是后续收录时可用的分类，**目前均未收录题目**。这里只保留规划，不创建空目录或空题目；第一道题加入时再建立相应分类页，并移入「已收录分类」。

The following categories are available for future additions, but **none currently contains documented problems**. Keep only this plan rather than empty directories or problem pages; create a category page when its first problem is added, then move it into “Included Categories.”

| 预留主分类<br>Reserved category | 建议目录名<br>Suggested directory | 可容纳的知识点<br>Possible topics |
| :--- | :--- | :--- |
| 数组与字符串<br>Arrays and strings | `arrays-strings` | 数组遍历、字符串处理、前缀和、双指针<br>Array traversal, string processing, prefix sums, two pointers |
| 搜索与排序<br>Searching and sorting | `search-sort` | 二分查找、排序、回溯、状态搜索<br>Binary search, sorting, backtracking, state-space search |
| 数据结构<br>Data structures | `data-structures` | 栈、队列、堆、并查集、树状数组、线段树<br>Stacks, queues, heaps, disjoint sets, Fenwick trees, segment trees |
| 贪心<br>Greedy algorithms | `greedy` | 贪心策略、区间选择、交换论证<br>Greedy strategies, interval selection, exchange arguments |
| 图论<br>Graph theory | `graphs` | 图遍历、最短路、最小生成树、拓扑排序<br>Graph traversal, shortest paths, minimum spanning trees, topological sorting |
| 动态规划<br>Dynamic programming | `dynamic-programming` | 线性 DP、背包、区间 DP、状态压缩<br>Linear DP, knapsack, interval DP, bitmask DP |
| 数学<br>Mathematics | `math` | 数论、组合计数、模运算<br>Number theory, combinatorial counting, modular arithmetic |

一道题若同时涉及多个方向，选择主要训练目标作为主分类，其余知识点用标签记录。其他分类需要引用它时，链接到同一个题目文件，不复制题面和答案。

If a problem spans several topics, choose its main learning objective as the primary category and record the others as tags. Other categories should link to that same problem file rather than duplicate the statement and answer.

<a id="编号与维护约定"></a>
## 编号与维护约定 / Numbering and Maintenance Conventions

1. **稳定编号：**使用全库唯一编号 `EX0001`、`EX0002`……，不把类别或难度编码进编号。当前已使用 EX0001–EX0005；新增前搜索已有编号，下一号从 EX0006 开始。题目移动分类时保留编号，不将旧编号分配给另一道题。<br>
   **Stable IDs:** Use globally unique `EX0001`, `EX0002`, etc., without encoding category or difficulty. EX0001–EX0005 are used; search existing IDs before adding a problem, starting the next ID at EX0006. Retain the ID when moving categories, and never assign an old ID to another problem.
2. **文件路径：**题目文档采用 `<主分类>/ex编号_中文标题_english-title.md`，例如 [EX0001](basics/ex0001_输出问候语_hello-icpc.md)。每个分类用自己的 `README.md` 维护二级知识点和题目索引。中文在前，英文紧随，并保留稳定 EX 编号。<br>
   **File paths:** Use `<category>/exID_Chinese-title_english-title.md` for problem documents, for example [EX0001](basics/ex0001_输出问候语_hello-icpc.md). Each category keeps its own `README.md` for subtopics and the problem index. Chinese comes first, followed by an English counterpart; preserve the stable EX ID.
3. **一题一份正文：**一道题可以有多个标签、解法或语言实现，都在同一题目页登记。独立成题的拓展练习再分配新编号，并与原题互相链接。<br>
   **One main document per problem:** Record multiple tags, approaches, or language implementations on the same problem page. Assign a new ID only when an extension becomes a standalone problem, and cross-link it with the original.
4. **元信息保持一致：**题目页记录主分类、难度、标签、来源、实现状态和源码链接。难度「入门 / 基础 / 进阶 / 挑战」是仓库内的学习分级，不冒充平台评分。未知来源写「未确认」，没有验证的通过状态不写「已通过」。<br>
   **Consistent metadata:** Record the main category, difficulty, tags, source, implementation status, and source-code links. “Introductory / Basic / Intermediate / Challenge” are this repository's learning levels, not platform ratings. Mark unknown origins “unconfirmed,” and never claim “accepted” without verification.
5. **分类逐步细化：**先使用分类页的二级标题。题数增多、索引不易浏览时，再拆二级分类页或子目录，并更新全部链接；不要为尚未收录的题提前铺设大量空目录。<br>
   **Refine categories gradually:** Start with subheadings on the category page. When the problem count makes browsing difficult, split into subcategory pages or directories and update every link; do not pre-create many empty directories for undocumented problems.
6. **标签复用：**优先复用分类页已有标签；出现新知识点再新增。标签描述知识点，不重复记录语言、难度和实现状态。<br>
   **Reuse tags:** Prefer existing category tags and add new ones only for new concepts. Tags describe topics, not language, difficulty, or implementation status.
7. **源码命名：**源码采用描述题目行为或算法的 `中文名_english_snake_case` 双语名称，有平台题号时保留题号，保持每题独立编译。原有数字名、缩写名的对应关系见 [重命名对照](basics/README.md#源码重命名对照)；本次全部旧路径与新路径见仓库 README。<br>
   **Source naming:** Use `Chinese-name_english_snake_case` filenames describing the exercise behavior or algorithm, retaining platform problem IDs when present. Compile each problem independently. See the [rename mapping](basics/README.md#源码重命名对照) for earlier numeric or abbreviated names and the root README for the full old-to-new path index.

<a id="新增一道题"></a>
## 新增一道题 / Adding a Problem

1. 选择主分类与未使用的 EX 编号，复制 [题目模板](题目模板_TEMPLATE.md) 到对应分类目录。<br>
   Choose a main category and unused EX ID, then copy the [problem template](题目模板_TEMPLATE.md) into the corresponding category directory.
2. 填写题目、真实输入输出约定、样例、知识点、折叠提示与答案。将推断或自拟内容明确标注；不要给固定数据演示补造原题输入。<br>
   Fill in the task, actual input/output contract, examples, topics, collapsible hints, and answer. Clearly mark inferred or self-authored content; do not invent original-problem input for a fixed-data demonstration.
3. 登记源码链接、难度、标签与来源；用对应源码或实际题面逐项核对，按题目要求编译并测试样例和边界情况。<br>
   Record source-code links, difficulty, tags, and origin. Check each item against the source code or actual problem statement; compile and test examples and boundary cases as required by the problem.
4. 更新分类索引；新建主分类时再更新本页。若重命名或移动文件，同时修正 README、题目页、编译示例和其他引用。<br>
   Update the category index, and update this catalog when creating a main category. If renaming or moving files, also fix the README, problem pages, compilation examples, and all other references.

[返回仓库 README](../../README.md)

[Back to the repository README](../../README.md)
