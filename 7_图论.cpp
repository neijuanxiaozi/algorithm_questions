#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

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
207. 课程表 https://leetcode.cn/problems/course-schedule/description/?envType=study-plan-v2&envId=top-interview-150

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
    vector<vector<int>> edges;
    vector<int> indeg;

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
            ++indeg[info[0]];
        }

        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        int visited = 0;
        while (!q.empty()) {
            ++visited;
            int u = q.front();
            q.pop();
            for (int v: edges[u]) {
                --indeg[v];
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        return visited == numCourses;
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

/*
210. 课程表II 与课程表I一样 只是需要记录答案 https://leetcode.cn/problems/course-schedule-ii/description/?envType=study-plan-v2&envId=top-interview-150

*/

//广度
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> indeg;
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        vector<int> res;//新增

        for (auto &item : prerequisites) {
            edges[item[1]].push_back(item[0]);
            ++indeg[item[0]];
        }

        queue<int> que;
        for (int i = 0; i < indeg.size(); ++i) {
            if (indeg[i] == 0) {
                que.push(i);
            }
        }

        int visited = 0;
        while (!que.empty()) {
            ++visited;
            int temp = que.front();
            que.pop();
            res.push_back(temp);//新增
            for (auto &item : edges[temp]) {
                --indeg[item];
                if (indeg[item] == 0) {
                    que.push(item);
                }
            }
        }
        if (visited == numCourses) {//新增
            return res;//新增
        }//新增
        return {};
    }
};

//深度
class Solution {
private:
    // 存储有向图
    vector<vector<int>> edges;
    // 标记每个节点的状态：0=未搜索，1=搜索中，2=已完成
    vector<int> visited;
    // 用数组来模拟栈，下标 0 为栈底，n-1 为栈顶
    vector<int> result;
    // 判断有向图中是否有环
    bool valid = true;

public:
    void dfs(int u) {
        // 将节点标记为「搜索中」
        visited[u] = 1;
        // 搜索其相邻节点
        // 只要发现有环，立刻停止搜索
        for (int v: edges[u]) {
            // 如果「未搜索」那么搜索相邻节点
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            // 如果「搜索中」说明找到了环
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        // 将节点标记为「已完成」
        visited[u] = 2;
        // 将节点入栈
        result.push_back(u);
    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        // 每次挑选一个「未搜索」的节点，开始进行深度优先搜索
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        if (!valid) {
            return {};
        }
        // 如果没有环，那么就有拓扑排序
        // 注意下标 0 为栈底，因此需要将数组反序输出
        reverse(result.begin(), result.end());
        return result;
    }
};


/*
909. 蛇梯棋  https://leetcode.cn/problems/snakes-and-ladders/description/?envType=study-plan-v2&envId=top-interview-150

给你一个大小为 n x n 的整数矩阵 board ，方格按从 1 到 n2 编号，编号遵循 转行交替方式 ，从左下角开始 （即，从 board[n - 1][0] 开始）每一行交替方向。
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