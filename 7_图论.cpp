#include <vector>
#include <queue>
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
    //每个节点有三个状态 未搜索 搜索中 已完成 对用0 1 2
    vector<int> visited;
    bool valid = true;
public:
    void dfs(int u) {
        visited[u] = 1;
        for (int v : edges[u]) {
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        visited[u] = 2;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto &info : prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        return valid;
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