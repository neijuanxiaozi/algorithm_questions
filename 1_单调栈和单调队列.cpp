/*
42. 接雨水: https://leetcode.cn/problems/trapping-rain-water/description/
    单调栈 接雨水  height = [0,1,0,2,1,0,1,3,2,1,2,1] 算出能接雨水的面积，结果等于6
    思想：求每个元素的左右两边的第一个大的元素，然后这两个元素之间的间隔为宽度，这两个元素之间的最小值减去中间元素为高
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution1
{
public:
    int trap(vector<int> &height)
    {
        if (height.size() <= 2)
            return 0; // 可以不加

        stack<int> st; // 存着下标，计算的时候用下标对应的柱子高度
        st.push(0);
        int sum = 0;

        for (int i = 1; i < height.size(); ++i)
        {
            if (height[i] < height[st.top()])
            { // 情况一 小于栈顶直接加入形成单调递增栈
                st.push(i);
            }
            else if (height[i] == height[st.top()])
            {             // 情况二
                st.pop(); // 其实这一句可以不加，效果是一样的，但处理相同的情况的思路却变了。
                st.push(i);
            }
            else
            { // 情况三
                while (!st.empty() && height[i] > height[st.top()])
                {                       // 注意这里是while 把每一个小于当前元素的栈中元素都要处理
                    int mid = st.top(); // 要处理的中间元素
                    st.pop();           // 弹出要处理的元素

                    if (!st.empty())
                    {                                                           // 此时栈中还有元素
                        int h = min(height[st.top()], height[i]) - height[mid]; // 计算高度
                        int w = i - st.top() - 1;                               // 注意减一，只求中间宽度 不包括left 和right
                        sum += h * w;                                           // 计算雨水
                    }
                }
                st.push(i);
            }
        }
        return sum;
    }
};

/*
84. 柱状图中最大的矩形  https://leetcode.cn/problems/largest-rectangle-in-histogram/description/
    给定 n 个非负整数，用来表示柱状图中各个柱子的高度。
    每个柱子彼此相邻，且宽度为 1 。
    求在该柱状图中，能够勾勒出来的矩形的最大面积。

    输入：heights = [2,1,5,6,2,3]
    输出：10
    解释：最大的矩形为图中红色区域，面积为 10
*/
class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int res = 0;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        stack<int> st;
        st.push(0);
        for (int i = 1; i < heights.size(); ++i)
        {
            if (heights[i] > heights[st.top()])
                st.push(i);
            else if (heights[i] == heights[st.top()])
            {
                st.pop();
                st.push(i);
            }
            else
            {
                // 找到左右两边第一个小于当前柱子的下标
                while (!st.empty() && heights[i] < heights[st.top()])
                {
                    int mid = st.top();
                    st.pop();
                    if (!st.empty())
                    {
                        int left = st.top();
                        int h = heights[mid];
                        int w = i - left - 1;
                        res = max(res, (h * w));
                    }
                }
                st.push(i);
            }
        }
        return res;
    }
};

// 单调队列：
/*

239. 滑动窗口的最大值 https://leetcode.cn/problems/sliding-window-maximum/description/
    给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
    你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
    返回滑动窗口中的最大值 。

    示例 1：
    输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
    输出：[3,3,5,5,6,7]
    解释：
    滑动窗口的位置                最大值
    ---------------               -----
    [1  3  -1] -3  5  3  6  7      3
    1 [3  -1  -3] 5  3  6  7       3
    1  3 [-1  -3  5] 3  6  7       5
    1  3  -1 [-3  5  3] 6  7       5
    1  3  -1  -3 [5  3  6] 7       6
    1  3  -1  -3  5 [3  6  7]      7



    示例 2：
    输入：nums = [1], k = 1
    输出：[1]


    提示：
    1 <= nums.length <= 105
    -104 <= nums[i] <= 104
    1 <= k <= nums.length
*/

class Solution3
{
private:
    class MyQueue
    { // 单调队列（从大到小）
    public:
        deque<int> que; // 使用deque来实现单调队列
        // 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出。
        // 同时pop之前判断队列当前是否为空。
        void pop(int value)
        {
            if (!que.empty() && value == que.front())
            {
                que.pop_front();
            }
        }
        // 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
        // 这样就保持了队列里的数值是单调从大到小的了。
        void push(int value)
        {
            while (!que.empty() && value > que.back())
            {
                que.pop_back();
            }
            que.push_back(value);
        }
        // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
        int front()
        {
            return que.front();
        }
    };

public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        MyQueue que;
        vector<int> result;
        for (int i = 0; i < k; ++i)
        { // 先将前k的元素放进队列
            que.push(nums[i]);
        }
        result.push_back(que.front()); // result 记录前k的元素的最大值
        for (int i = k; i < nums.size(); ++i)
        {
            que.pop(nums[i - k]);          // 滑动窗口移除最前面元素
            que.push(nums[i]);             // 滑动窗口前加入最后面的元素
            result.push_back(que.front()); // 记录对应的最大值
        }
        return result;
    }
};

/*
347. 前k个高频元素 https://leetcode.cn/problems/top-k-frequent-elements/description/
    给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。
    你可以按任意顺序返回答案。

    示例 1:
    输入: nums = [1,1,1,2,2,3], k = 2
    输出: [1,2]


    示例 2:
    输入: nums = [1], k = 1
    输出: [1]


    提示：
    1 <= nums.length <= 105
    k 的取值范围是 [1, 数组中不相同的元素的个数]
    题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的
*/
#include <iostream>
#include <unordered_map>
#include <queue>

class Solution4
{
public:
    class mycomparsion
    {
    public:
        bool operator()(pair<int, int> const &lhs, pair<int, int> const &rhs)
        {
            return lhs.second > rhs.second;
        }
    };
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> map;
        for (auto const &temp : nums)
        {
            ++map[temp];
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparsion> pri_que;
        for (auto &temp : map)
        {
            pri_que.push(temp);
            if (pri_que.size() > k)
                pri_que.pop();
        }

        vector<int> res(k);
        for (int i = k - 1; i >= 0; --i)
        {
            res[i] = pri_que.top().first;
            pri_que.pop();
        }
        return res;
    }
};

/*
224. 基本计算器 https://leetcode.cn/problems/basic-calculator/description/?envType=study-plan-v2&envId=top-interview-150
    给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。
    注意:不允许使用任何将字符串作为数学表达式计算的内置函数，比如 eval() 。

    示例 1：
    输入：s = "1 + 1"
    输出：2

    示例 2：
    输入：s = " 2-1 + 2 "
    输出：3

    示例 3：
    输入：s = "(1+(4+5+2)-3)+(6+8)"
    输出：23

    提示：
    1 <= s.length <= 3 * 105
    s 由数字、'+'、'-'、'('、')'、和 ' ' 组成
    s 表示一个有效的表达式
    '+' 不能用作一元运算(例如， "+1" 和 "+(2 + 3)" 无效)
    '-' 可以用作一元运算(即 "-1" 和 "-(2 + 3)" 是有效的)
    输入中不存在两个连续的操作符
    每个数字和运行的计算将适合于一个有符号的 32位 整数
*/

// 宫水三叶
class Solution
{
public:
    void replace(string &s)
    {
        int pos = s.find(" ");
        while (pos != -1)
        {
            s.replace(pos, 1, "");
            pos = s.find(" ");
        }
    }
    int calculate(string s)
    {
        // 存放所有的数字
        stack<int> nums;
        // 为了防止第一个数为负数，先往 nums 加个 0
        nums.push(0);
        // 将所有的空格去掉
        replace(s);
        // 存放所有的操作，包括 +/-
        stack<char> ops;
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            char c = s[i];
            if (c == '(')
                ops.push(c);
            else if (c == ')')
            {
                // 计算到最近一个左括号为止
                while (!ops.empty())
                {
                    char op = ops.top();
                    if (op != '(')
                        calc(nums, ops);
                    else
                    {
                        ops.pop();
                        break;
                    }
                }
            }
            else
            {
                if (isdigit(c))
                {
                    int cur_num = 0;
                    int j = i;
                    // 将从 i 位置开始后面的连续数字整体取出，加入 nums
                    while (j < n && isdigit(s[j]))
                        cur_num = cur_num * 10 + (s[j++] - '0');
                    // 注意上面的计算一定要有括号，否则有可能会溢出
                    nums.push(cur_num);
                    i = j - 1;
                }
                else
                {
                    if (i > 0 && (s[i - 1] == '(' || s[i - 1] == '+' || s[i - 1] == '-'))
                    {
                        nums.push(0);
                    }
                    // 有一个新操作要入栈时，先把栈内可以算的都算了
                    while (!ops.empty() && ops.top() != '(')
                        calc(nums, ops);
                    ops.push(c);
                }
            }
        }
        while (!ops.empty())
            calc(nums, ops);
        return nums.top();
    }
    void calc(stack<int> &nums, stack<char> &ops)
    {
        if (nums.size() < 2 || ops.empty())
            return;
        int b = nums.top();
        nums.pop();
        int a = nums.top();
        nums.pop();
        char op = ops.top();
        ops.pop();
        nums.push(op == '+' ? a + b : a - b);
    }
};

// 带* / 版本
class Solution
{
public:
    unordered_map<char, int> oper_pri = {
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2},
        {'%', 2},
        {'^', 3}};
    stack<char> opers;
    stack<long long> nums;
    int calculate(string s)
    {
        nums.push(0);
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            if (s[i] == ' ')
                continue;
            else if (s[i] == '(')
            {
                opers.push('(');
                if (s[i + 1] == '-')
                {
                    i++;
                    nums.push(0);
                    opers.push('-');
                }
            }
            else if (s[i] == ')')
            {
                while (opers.top() != '(')
                {
                    cal();
                }
                opers.pop();
            }
            else if ('0' <= s[i] && s[i] <= '9')
            {
                int l = i;
                while (i + 1 < n && '0' <= s[i + 1] && s[i + 1] <= '9')
                    i++;
                nums.push(stoll(s.substr(l, i - l + 1)));
            }
            else
            {
                while (!opers.empty() && opers.top() != '(' && oper_pri[opers.top()] >= oper_pri[s[i]])
                {
                    cal();
                }
                opers.push(s[i]);
            }
        }
        while (!opers.empty() && opers.top() != '(')
        {
            cal();
        }
        return nums.top();
    }
    void cal()
    {
        long long b = nums.top();
        nums.pop();
        long long a = nums.top();
        nums.pop();
        char oper = opers.top();
        opers.pop();
        long long res;
        switch (oper)
        {
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            res = a / b;
            break;
        case '%':
            res = a % b;
            break;
        case '^':
            res = pow(a, b);
            break;
        }
        nums.push(res);
    }
};