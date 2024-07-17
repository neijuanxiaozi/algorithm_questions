#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


/*
909. 蛇梯棋  https://leetcode.cn/problems/snakes-and-ladders/description/?envType=study-plan-v2&envId=top-interview-150
    给你一个大小为 n x n 的整数矩阵 board ，方格按从 1 到 n2 编号，编号遵循 转行交替方式 ，
    从左下角开始 （即，从 board[n - 1][0] 开始）每一行交替方向。
    玩家从棋盘上的方格 1 （总是在最后一行、第一列）开始出发。
    每一回合，玩家需要从当前方格 curr 开始出发，按下述要求前进：
    选定目标方格 next ，目标方格的编号符合范围 [curr + 1, min(curr + 6, n2)] 。
    该选择模拟了掷 六面体骰子 的情景，无论棋盘大小如何，玩家最多只能有 6 个目的地。
    传送玩家：如果目标方格 next 处存在蛇或梯子，那么玩家会传送到蛇或梯子的目的地。否则，玩家传送到目标方格 next 。 
    当玩家到达编号 n2 的方格时，游戏结束。
    r 行 c 列的棋盘，按前述方法编号，棋盘格中可能存在 “蛇” 或 “梯子”；如果 board[r][c] != -1，那个蛇或梯子的目的地将会是 board[r][c]。编号为 1 和 n2 的方格上没有蛇或梯子。
    注意，玩家在每回合的前进过程中最多只能爬过蛇或梯子一次：就算目的地是另一条蛇或梯子的起点，玩家也 不能 继续移动。
    举个例子，假设棋盘是 [[-1,4],[-1,3]] ，第一次移动，玩家的目标方格是 2 。那么这个玩家将会顺着梯子到达方格 3 ，但 不能 顺着方格 3 上的梯子前往方格 4 。
    返回达到编号为 n2 的方格所需的最少移动次数，如果不可能，则返回 -1。
*/

// leetcode官方答案
class Solution {
private:
    // 将位置转换为二维坐标
    pair<int, int> id2rc(int id, int n) {
        int r = (id - 1) / n, c = (id - 1) % n;
        if (r % 2 == 1)
            c = n - 1 - c;
        return {n - 1 - r, c};
    }
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        vector<int> vis(n * n + 1);//记录节点编号是否访问过
        queue<pair<int, int>> q;//队列记录节点编号和步数  第一个int表示当前到达的节点编号 第二个int表示到达此节点的步数
        q.emplace(1, 0);//编号为1的节点 步数为0 入队
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            for (int i = 1; i <= 6; ++i) {//遍历当前节点能到达的每个节点编号
                int next = p.first + i;
                if (next > n * n) //超出边界
                    break;
                
                auto rc = id2rc(next, n);//得到下一个要去节点编号的行和列
                if (board[rc.first][rc.second] > 0) {//要去的地方有蛇或梯
                    next = board[rc.first][rc.second];
                }

                if (next == n * n)//到达终点
                    return p.second  + 1;
                
                if (!vis[next]) {
                    vis[next] = 1;
                    q.emplace(next, p.second + 1);//加入节点和步数
                }
            }

        }
        return -1;
    }
};
/*
200. 岛屿数量 https://leetcode.cn/problems/number-of-islands/description/
    给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
    岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
    此外，你可以假设该网格的四条边均被水包围。

示例 1：
    输入：grid = [
    ["1","1","1","1","0"],
    ["1","1","0","1","0"],
    ["1","1","0","0","0"],
    ["0","0","0","0","0"]
    ]
    输出：1


示例 2：
    输入：grid = [
    ["1","1","0","0","0"],
    ["1","1","0","0","0"],
    ["0","0","1","0","0"],
    ["0","0","0","1","1"]
    ]
    输出：3

提示：
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] 的值为 '0' 或 '1'
*/

// 广搜
class Solution0
{
private:
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
    void bfs(vector<vector<char>> &grid, vector<vector<bool>> &visited, int x, int y)
    {
        queue<pair<int, int>> que;
        que.push({x, y});
        visited[x][y] = true; // 只要加入队列，立刻标记
        while (!que.empty())
        {
            pair<int, int> cur = que.front();
            que.pop();
            int curx = cur.first;
            int cury = cur.second;
            for (int i = 0; i < 4; i++)
            {
                int nextx = curx + dir[i][0];
                int nexty = cury + dir[i][1];
                if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size())
                    continue; // 越界了，直接跳过
                if (!visited[nextx][nexty] && grid[nextx][nexty] == '1')
                {
                    que.push({nextx, nexty});
                    visited[nextx][nexty] = true; // 只要加入队列立刻标记
                }
            }
        }
    }

public:
    int numIslands(vector<vector<char>> &grid)
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false));

        int result = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!visited[i][j] && grid[i][j] == '1')
                {
                    result++;                 // 遇到没访问过的陆地，+1
                    bfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                }
            }
        }
        return result;
    }
};

// 深搜

class Solution1
{
private:
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
    void dfs(vector<vector<char>> &grid, vector<vector<bool>> &visited, int x, int y)
    {
        for (int i = 0; i < 4; i++)
        {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size())
                continue; // 越界了，直接跳过
            if (!visited[nextx][nexty] && grid[nextx][nexty] == '1')
            { // 没有访问过的 同时 是陆地的
                visited[nextx][nexty] = true;
                dfs(grid, visited, nextx, nexty);
            }
        }
    }

public:
    int numIslands(vector<vector<char>> &grid)
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false));

        int result = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (!visited[i][j] && grid[i][j] == '1')
                {
                    visited[i][j] = true;
                    ++result;                 // 遇到没访问过的陆地，+1
                    dfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                }
            }
        }
        return result;
    }
};

/*
并查集:
    并查集主要两个功能: 1. 将两个元素添加到同一个集合 2. 判断两个元素在不在同一个集合
    我们将三个元素 A B C 放在同一个集合 其实就是将三个元素联通在一起 如何联通呢
    只需要用一个一个数组表示 即father[A] = B  father[B] = C 这样就表述A与B与c连通了

    路径压缩:
        如果这棵多叉树高度很深的话，每次find函数 去寻找跟的过程就要递归很多次。
        我们的目的只需要知道这些节点在同一个根下就可以
        除了根节点其他所有节点都挂载根节点下，这样我们在寻根的时候就很快，只需要一步
*/
//并查集题目 1971. 寻找图中是否存在路径 https://leetcode.cn/problems/find-if-path-exists-in-graph/description/
class Solution
{
private:
    int n = 1005;                           // 节点数量
    vector<int> father = vector<int>(n, 0); // C++里的一种数组结构

    // 并查集初始化
    void init()
    {
        for (int i = 0; i < n; ++i)
        {
            father[i] = i;
        }
    }
    // 并查集里寻根的过程
    int find(int u)
    {
        return u == father[u] ? u : father[u] = find(father[u]);
    }

    // 判断 u 和 v是否找到同一个根
    bool isSame(int u, int v)
    {
        u = find(u);
        v = find(v);
        return u == v;
    }

    // 将v->u 这条边加入并查集
    void join(int u, int v)
    {
        u = find(u); // 寻找u的根
        v = find(v); // 寻找v的根
        if (u == v)
            return; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
        father[v] = u;
    }
};

/*
最小生成树:
卡码网 53.寻宝 https://kamacoder.com/problempage.php?pid=1053

题目描述：
    在世界的某个区域，有一些分散的神秘岛屿，每个岛屿上都有一种珍稀的资源或者宝藏。国王打算在这些岛屿上建公路，方便运输。
    不同岛屿之间，路途距离不同，国王希望你可以规划建公路的方案，如何可以以最短的总公路距离将 所有岛屿联通起来。
    给定一张地图，其中包括了所有的岛屿，以及它们之间的距离。以最小化公路建设长度，确保可以链接到所有岛屿。
输入描述：
    第一行包含两个整数V 和 E，V代表顶点数，E代表边数 。顶点编号是从1到V。例如：V=2，一个有两个顶点，分别是1和2。
    接下来共有 E 行，每行三个整数 v1，v2 和 val，v1 和 v2 为边的起点和终点，val代表边的权值。
输出描述：
    输出联通所有岛屿的最小路径总距离
*/
//最小生成树 prim算法
#include<iostream>
#include<vector>
#include <climits>

using namespace std;
int main() {
    int v, e;
    int x, y, k;
    cin >> v >> e;
    // 填一个默认最大值，题目描述val最大为10000
    vector<vector<int>> grid(v + 1, vector<int>(v + 1, 10001));
    while (e--) {
        cin >> x >> y >> k;
        // 因为是双向图，所以两个方向都要填上
        grid[x][y] = k;
        grid[y][x] = k;

    }
    // 所有节点到最小生成树的最小距离
    vector<int> minDist(v + 1, 10001);

    // 这个节点是否在树里
    vector<bool> isInTree(v + 1, false);

    // 我们只需要循环 n-1次，建立 n - 1条边，就可以把n个节点的图连在一起
    for (int i = 1; i < v; i++) {

        // 1、prim三部曲，第一步：选距离生成树最近节点
        int cur = -1; // 选中哪个节点 加入最小生成树
        int minVal = INT_MAX;
        for (int j = 1; j <= v; j++) { // 1 - v，顶点编号，这里下标从1开始
            //  选取最小生成树节点的条件：
            //  （1）不在最小生成树里
            //  （2）距离最小生成树最近的节点
            if (!isInTree[j] &&  minDist[j] < minVal) {
                minVal = minDist[j];
                cur = j;
            }
        }
        // 2、prim三部曲，第二步：最近节点（cur）加入生成树
        isInTree[cur] = true;

        // 3、prim三部曲，第三步：更新非生成树节点到生成树的距离（即更新minDist数组）
        // cur节点加入之后， 最小生成树加入了新的节点，那么所有节点到 最小生成树的距离（即minDist数组）需要更新一下
        // 由于cur节点是新加入到最小生成树，那么只需要关心与 cur 相连的 非生成树节点 的距离 是否比 原来 非生成树节点到生成树节点的距离更小了呢
        for (int j = 1; j <= v; j++) {
            // 更新的条件：
            // （1）节点是 非生成树里的节点
            // （2）与cur相连的某节点的权值 比 该某节点距离最小生成树的距离小
            // 很多录友看到自己 就想不明白什么意思，其实就是 cur 是新加入 最小生成树的节点，那么 所有非生成树的节点距离生成树节点的最近距离 由于 cur的新加入，需要更新一下数据了
            if (!isInTree[j] && grid[cur][j] < minDist[j]) {
                minDist[j] = grid[cur][j];
            }
        }
    }
    // 统计结果
    int result = 0;
    for (int i = 2; i <= v; i++) { // 不计第一个顶点，因为统计的是边的权值，v个节点有 v-1条边
        result += minDist[i];
    }
    cout << result << endl;
}

//kruskal算法

/**
 * kruscal的思路：
    边的权值排序，因为要优先选最小的边加入到生成树里
    遍历排序后的边
    如果边首尾的两个节点在同一个集合，说明如果连上这条边图中会出现环
    如果边首尾的两个节点不在同一个集合，加入到最小生成树，并把两个节点加入同一个集合

    在代码中，如果将两个节点加入同一个集合，又如何判断两个节点是否在同一个集合呢？
    这里就涉及到并查集。
    并查集主要就两个功能：
        将两个元素添加到一个集合中
        判断两个元素在不在同一个集合
    
    kruskal算法 时间复杂度：nlogn （快排） + logn （并查集） ，所以最后依然是 nlogn 。n为边的数量。
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// l,r为 边两边的节点，val为边的数值
struct Edge {
    int l, r, val;
};

// 节点数量
int n = 10001;
// 并查集标记节点关系的数组
vector<int> father(n, -1); // 节点编号是从1开始的，n要大一些

// 并查集初始化
void init() {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
    }
}

// 并查集的查找操作
int find(int u) {
    return u == father[u] ? u : father[u] = find(father[u]); // 路径压缩
}

// 并查集的加入集合
void join(int u, int v) {
    u = find(u); // 寻找u的根
    v = find(v); // 寻找v的根
    if (u == v) return ; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
    father[v] = u;
}

int main() {

    int v, e;
    int v1, v2, val;
    vector<Edge> edges;
    int result_val = 0;
    cin >> v >> e;
    while (e--) {
        cin >> v1 >> v2 >> val;
        edges.push_back({v1, v2, val});
    }

    // 执行Kruskal算法
    // 按边的权值对边进行从小到大排序
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.val < b.val;
    });

    // 并查集初始化
    init();

    vector<Edge> res; //存储最小生成树的边
    // 从头开始遍历边
    for (Edge edge : edges) {
        // 并查集，搜出两个节点的祖先
        int x = find(edge.l);
        int y = find(edge.r);

        // 如果祖先不同，则不在同一个集合
        if (x != y) {
            res.push_back(edge);//收集加入树的边
            result_val += edge.val; // 这条边可以作为生成树的边
            join(x, y); // 两个节点加入到同一个集合
        }
    }
    cout << result_val << endl;
    return 0;
}

/**
拓扑排序精讲
题目描述：
    某个大型软件项目的构建系统拥有 N 个文件，文件编号从 0 到 N - 1，在这些文件中，某些文件依赖于其他文件的内容，这意味着如果文件 A 依赖于文件 B，则必须在处理文件 A 之前处理文件 B （0 <= A, B <= N - 1）。请编写一个算法，用于确定文件处理的顺序。

输入描述：
    第一行输入两个正整数 M, N。表示 N 个文件之间拥有 M 条依赖关系。
    后续 M 行，每行两个正整数 S 和 T，表示 T 文件依赖于 S 文件。
输出描述：
    输出共一行，如果能处理成功，则输出文件顺序，用空格隔开。
    如果不能成功处理（相互依赖），则输出 -1。
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
int main() {
    int m, n, s, t;
    cin >> n >> m;
    vector<int> inDegree(n, 0); // 记录每个文件的入度

    unordered_map<int, vector<int>> umap;// 记录文件依赖关系
    vector<int> result; // 记录结果

    while (m--) {
        // s->t，先有s才能有t
        cin >> s >> t;
        inDegree[t]++; // t的入度加一
        umap[s].push_back(t); // 记录s指向哪些文件
    }
    queue<int> que;
    for (int i = 0; i < n; i++) {
        // 入度为0的文件，可以作为开头，先加入队列
        if (inDegree[i] == 0) que.push(i);
        //cout << inDegree[i] << endl;
    }
    // int count = 0;
    while (que.size()) {
        int  cur = que.front(); // 当前选中的文件
        que.pop();
        //count++;
        result.push_back(cur);
        vector<int> files = umap[cur]; //获取该文件指向的文件
        if (files.size()) { // cur有后续文件
            for (int i = 0; i < files.size(); i++) {
                inDegree[files[i]] --; // cur的指向的文件入度-1
                if(inDegree[files[i]] == 0) que.push(files[i]);
            }
        }
    }
    if (result.size() == n) {
        for (int i = 0; i < n - 1; i++) cout << result[i] << " ";
        cout << result[n - 1];
    } else cout << -1 << endl;
}

/*
207. 课程表 https://leetcode.cn/problems/course-schedule/description/?envType=study-plan-v2&envId=top-interview-150
    这题也是拓扑排序
    你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
    在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，
    其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
    例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
    请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

示例 1：
    输入：numCourses = 2, prerequisites = [[1,0]]
    输出：true
    解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。


示例 2：
    输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
    输出：false
    解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。
*/

//广度优先遍历
class Solution {
private:
    // 存储有向图
    vector<vector<int>> edges;
    // 存储每个节点的入度
    vector<int> indeg;
    // 存储答案
    vector<int> result;

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
            ++indeg[info[0]];
        }

        queue<int> q;
        // 将所有入度为 0 的节点放入队列中
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            // 从队首取出一个节点
            int u = q.front();
            q.pop();
            // 放入答案中
            result.push_back(u);
            for (int v: edges[u]) {
                --indeg[v];
                // 如果相邻节点 v 的入度为 0，就可以选 v 对应的课程了
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        if (result.size() != numCourses) {
            return {};
        }
        return result;
    }
};

//深度优先遍历
class Solution {
private:
    vector<vector<int>> edges;//存储所有的边
    vector<int> visited;//每个节点有三个状态 未搜索 搜索中 已完成 对用0 1 2
    bool valid = true;
public:
    void dfs(int u) {
        //将当前节点状态置为正在搜索
        visited[u] = 1;
        //遍历当前节点的出边
        for (int v : edges[u]) {
            //如果未访问过 就向下遍历
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            //如果在向下遍历的过程中出现 遍历过的节点 说明出现了环
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        //当前节点遍历完  状态改为2
        visited[u] = 2;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        //保存所有的边
        for (const auto &info : prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        for (int i = 0; i < numCourses && valid; ++i) {
            //如果当前节点 未搜索就从当前节点出发 深度遍历
            if (!visited[i]) {
                dfs(i);
            }
        }
        return valid;
    }
};

/*****************************最短路径**********************************************/

/*
dijkstra算法
卡码网：47. 参加科学大会 https://kamacoder.com/problempage.php?pid=1047
【题目描述】
    小明是一位科学家，他需要参加一场重要的国际科学大会，以展示自己的最新研究成果。
    小明的起点是第一个车站，终点是最后一个车站。然而，途中的各个车站之间的道路状况、交通拥堵程度以及可能的自然因素（如天气变化）等不同，这些因素都会影响每条路径的通行时间。
    小明希望能选择一条花费时间最少的路线，以确保他能够尽快到达目的地。
【输入描述】
    第一行包含两个正整数，第一个正整数 N 表示一共有 N 个公共汽车站，第二个正整数 M 表示有 M 条公路。
    接下来为 M 行，每行包括三个整数，S、E 和 V，代表了从 S 车站可以单向直达 E 车站，并且需要花费 V 单位的时间。
【输出描述】
    输出一个整数，代表小明从起点到终点所花费的最小时间。
*/
//dijkstra朴素版 时间复杂度O(n^2)
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int main() {
    int n, m, p1, p2, val;
    cin >> n >> m;

    vector<vector<int>> grid(n + 1, vector<int>(n + 1, INT_MAX));
    for(int i = 0; i < m; i++){
        cin >> p1 >> p2 >> val;
        grid[p1][p2] = val;
    }

    int start = 1;
    int end = n;

    // 存储从源点到每个节点的最短距离
    std::vector<int> minDist(n + 1, INT_MAX);

    // 记录顶点是否被访问过
    std::vector<bool> visited(n + 1, false);

    minDist[start] = 0;  // 起始点到自身的距离为0

    for (int i = 1; i <= n; i++) { // 遍历所有节点

        int minVal = INT_MAX;
        int cur = 1;

        // 1、选距离源点最近且未访问过的节点
        for (int v = 1; v <= n; ++v) {
            if (!visited[v] && minDist[v] < minVal) {
                minVal = minDist[v];
                cur = v;
            }
        }

        visited[cur] = true;  // 2、标记该节点已被访问

        // 3、第三步，更新非访问节点到源点的距离（即更新minDist数组）
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && grid[cur][v] != INT_MAX && minDist[cur] + grid[cur][v] < minDist[v]) {
                minDist[v] = minDist[cur] + grid[cur][v];
            }
        }

    }

    if (minDist[end] == INT_MAX) cout << -1 << endl; // 不能到达终点
    else cout << minDist[end] << endl; // 到达终点最短路径

}

//dijkstra堆优化版

/*
    用邻接表存储边，并且带权值

其实思路依然是 dijkstra 三部曲：
    第一步，选源点到哪个节点近且该节点未被访问过
    第二步，该最近节点被标记访问过
    第三步，更新非访问节点到源点的距离（即更新minDist数组）
    只不过之前是 通过遍历节点来遍历边，通过两层for循环来寻找距离源点最近节点。 
    这次我们直接遍历边，且通过堆来对边进行排序，达到直接选择距离源点最近节点。

    先来看一下针对这三部曲，如果用堆来优化。
    那么三部曲中的第一步（选源点到哪个节点近且该节点未被访问过），我们如何选？
    我们要选择距离源点近的节点（即：该边的权值最小），所以 我们需要一个 小顶堆 来帮我们对边的权值排序，
    每次从小顶堆堆顶 取边就是权值最小的边。
*/

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>
using namespace std; 
// 小顶堆
class mycomparison {
public:
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
        return lhs.second > rhs.second;
    }
};
// 定义一个结构体来表示带权重的边
struct Edge {
    int to;  // 邻接顶点
    int val; // 边的权重

    Edge(int t, int w): to(t), val(w) {}  // 构造函数
};

int main() {
    int n, m, p1, p2, val;
    cin >> n >> m;

    vector<list<Edge>> grid(n + 1);

    for(int i = 0; i < m; i++){
        cin >> p1 >> p2 >> val; 
        // p1 指向 p2，权值为 val
        grid[p1].push_back(Edge(p2, val));

    }

    int start = 1;  // 起点
    int end = n;    // 终点

    // 存储从源点到每个节点的最短距离
    std::vector<int> minDist(n + 1, INT_MAX);

    // 记录顶点是否被访问过
    std::vector<bool> visited(n + 1, false); 
    
    // 优先队列中存放 pair<节点，源点到该节点的权值>
    priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pq;


    // 初始化队列，源点到源点的距离为0，所以初始为0
    pq.push(pair<int, int>(start, 0)); 
    
    minDist[start] = 0;  // 起始点到自身的距离为0

    while (!pq.empty()) {
        // 1. 第一步，选源点到哪个节点近且该节点未被访问过 （通过优先级队列来实现）
        // <节点， 源点到该节点的距离>
        pair<int, int> cur = pq.top(); pq.pop();

        if (visited[cur.first]) continue;

        // 2. 第二步，该最近节点被标记访问过
        visited[cur.first] = true;

        // 3. 第三步，更新非访问节点到源点的距离（即更新minDist数组）
        for (Edge edge : grid[cur.first]) { // 遍历 cur指向的节点，cur指向的节点为 edge
            // cur指向的节点edge.to，这条边的权值为 edge.val
            if (!visited[edge.to] && minDist[cur.first] + edge.val < minDist[edge.to]) { // 更新minDist
                minDist[edge.to] = minDist[cur.first] + edge.val;
                pq.push(pair<int, int>(edge.to, minDist[edge.to]));
            }
        }

    }

    if (minDist[end] == INT_MAX) cout << -1 << endl; // 不能到达终点
    else cout << minDist[end] << endl; // 到达终点最短路径
}