/*
93. 复原 IP 地址 https://leetcode.cn/problems/restore-ip-addresses/description/
    题目描述:有效 IP 地址 正好由四个整数 每个整数位于 0 到 255 之间组成,且不能含有前导 0
    整数之间用 '.' 分隔。

    例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址,
    但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是无效 IP 地址。
    给定一个只包含数字的字符串 s ,用以表示一个 IP 地址,返回所有可能的有效 IP 地址,
    这些地址可以通过在 s 中插入 '.' 来形成。
    你不能重新排序或删除 s 中的任何数字。你可以按任何顺序返回答案。

    示例 1：
    输入：s = "25525511135"
    输出：["255.255.11.135","255.255.111.35"]


    示例 2：
    输入：s = "0000"
    输出：["0.0.0.0"]


    示例 3：
    输入：s = "101023"
    输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]


    提示：
    1 <= s.length <= 20
    s 仅由数字组成
*/

#include <vector>
#include <string>
using namespace std;

class Solution
{
private:
    vector<string> res; // 记录结果
    // startIndex: 搜索的起始位置,pointNum:添加逗点的数量
    void backtracking(string &s, int startIndex, int pointNum)
    {
        if (pointNum == 3)
        { // 逗点数量为3时,分隔结束
            // 判断第四段子字符串是否合法,如果合法就放进res中
            if (isValid(s, startIndex, s.size() - 1))
            {
                res.push_back(s);
            }
            return;
        }
        for (int i = startIndex; i < s.size(); ++i)
        {
            if (isValid(s, startIndex, i))
            {                                     // 判断 [startIndex,i] 这个区间的子串是否合法
                s.insert(s.begin() + i + 1, '.'); // 在i的后面插入一个逗点
                pointNum++;
                backtracking(s, i + 2, pointNum); // 插入逗点之后下一个子串的起始位置为i+2
                pointNum--;                       // 回溯
                s.erase(s.begin() + i + 1);       // 回溯删掉逗点
            }
            else
                break; // 不合法,直接结束本层循环
        }
    }
    // 判断字符串s在左闭又闭区间[start, end]所组成的数字是否合法
    bool isValid(const string &s, int start, int end)
    {
        if (start > end)
        {
            return false;
        }
        if (s[start] == '0' && start != end)
        { // 0开头的数字不合法
            return false;
        }
        int num = 0;
        for (int i = start; i <= end; ++i)
        {
            if (s[i] > '9' || s[i] < '0')
            { // 遇到非数字字符不合法
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255)
            { // 如果大于255了不合法
                return false;
            }
        }
        return true;
    }

public:
    vector<string> restoreIpAddresses(string s)
    {
        res.clear();
        if (s.size() < 4 || s.size() > 12)
            return res; // 算是剪枝了
        backtracking(s, 0, 0);
        return res;
    }
};

/*hard
332.重新安排行程   https://leetcode.cn/problems/reconstruct-itinerary/description/
    给你一份航线列表 tickets ,其中 tickets[i] = [fromi, toi] 表示飞机出发和降落的机场地点。
    请你对该行程进行重新规划排序。
    所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生,所以该行程必须从 JFK 开始。
    如果存在多种有效的行程,请你按字典排序返回最小的行程组合。

    例如,行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小,排序更靠前。
    假定所有机票至少存在一种合理的行程。且所有的机票 必须都用一次且只能用一次。


    示例 1：
    输入：tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
    输出：["JFK","MUC","LHR","SFO","SJC"]


    示例 2：
    输入：tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
    输出：["JFK","ATL","JFK","SFO","ATL","SFO"]
    解释：另一种有效的行程是 ["JFK","SFO","ATL","JFK","ATL","SFO"] ,但是它字典排序更大更靠后。


    提示：
    1 <= tickets.length <= 300
    tickets[i].length == 2
    fromi.length == 3
    toi.length == 3
    fromi 和 toi 由大写英文字母组成
    fromi != toi
*/
#include <unordered_map>
#include <map>

class Solution
{
public:
    vector<string> res;
    unordered_map<string, map<string, int>> targets;
    bool backtracking(int tickNum)
    {
        if (res.size() == tickNum + 1)
        {
            return true;
        }

        for (auto &target : targets[res.back()])
        {
            if (target.second > 0)
            {
                res.push_back(target.first);
                --target.second;
                if (backtracking(tickNum))
                {
                    return true;
                }
                ++target.second;
                res.pop_back();
            }
        }
        return false;
    }
    vector<string> findItinerary(vector<vector<string>> &tickets)
    {
        targets.clear();
        res.clear();
        for (const vector<string> &vec : tickets)
        {
            ++targets[vec[0]][vec[1]]; // 记录映射关系
        }
        res.push_back("JFK");
        backtracking(tickets.size());
        return res;
    }
};

/*
37.解数独 https://leetcode.cn/problems/sudoku-solver/description/
    编写一个程序,通过填充空格来解决数独问题(9 X 9棋盘)。
    数独的解法需 遵循如下规则：
    数字 1-9 在每一行只能出现一次。
    数字 1-9 在每一列只能出现一次。
    数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
    数独部分空格内已填入了数字,空白格用 '.' 表示。

    提示：
    board.length == 9
    board[i].length == 9
    board[i][j] 是一位数字或者 '.'
    题目数据 保证 输入数独仅有一个解
*/

class Solution
{
private:
    // 单层递归确定一个数的值(1~9) 然后进入下一层递归 确定下一个数
    bool backtracking(vector<vector<char>> &board)
    {
        for (int i = 0; i < board.size(); ++i)
        { // 遍历行
            for (int j = 0; j < board[0].size(); ++j)
            { // 遍历列
                if (board[i][j] == '.')
                {
                    for (char k = '1'; k <= '9'; ++k)
                    { // (i, j) 这个位置放k是否合适
                        if (isValid(i, j, k, board))
                        {
                            board[i][j] = k; // 放置k
                            if (backtracking(board))
                                return true;   // 如果找到合适一组立刻返回
                            board[i][j] = '.'; // 回溯,撤销k
                        }
                    }
                    return false; // 9个数都试完了,都不行,那么就返回false
                }
            }
        }
        return true; // 遍历完没有返回false,说明找到了合适棋盘位置了
    }
    bool isValid(int row, int col, char val, vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
        { // 判断行里是否重复
            if (board[row][i] == val)
            {
                return false;
            }
        }
        for (int j = 0; j < 9; j++)
        { // 判断列里是否重复
            if (board[j][col] == val)
            {
                return false;
            }
        }
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; ++i)
        { // 判断9方格里是否重复
            for (int j = startCol; j < startCol + 3; ++j)
            {
                if (board[i][j] == val)
                {
                    return false;
                }
            }
        }
        return true;
    }

public:
    void solveSudoku(vector<vector<char>> &board)
    {
        backtracking(board);
    }
};
