#include <iostream>
#include <vector>
using namespace std;

/*
    #背包总结

    ##01背包
    在动态规划：关于01背包问题,你该了解这些！ (opens new window)中我们讲解二维dp数组01背包先遍历物品还是先遍历背包都是可以的,且第二层for循环是从小到大遍历。
    和动态规划：关于01背包问题,你该了解这些！（滚动数组） (opens new window)中,我们讲解一维dp数组01背包只能先遍历物品再遍历背包容量,且第二层for循环是从大到小遍历。
    一维dp数组的背包在遍历顺序上和二维dp数组实现的01背包其实是有很大差异的,大家需要注意！

    ##完全背包
    说完01背包,再看看完全背包。

    在动态规划：关于完全背包,你该了解这些！ (opens new window)中,讲解了纯完全背包的一维dp数组实现,先遍历物品还是先遍历背包都是可以的,且第二层for循环是从小到大遍历。

    但是仅仅是纯完全背包的遍历顺序是这样的,题目稍有变化,两个for循环的先后顺序就不一样了。
    如果求组合数就是外层for循环遍历物品,内层for遍历背包。
    如果求排列数就是外层for遍历背包,内层for循环遍历物品。

    相关题目如下：

    求组合数：动态规划：518.零钱兑换II(opens new window)
    求排列数：动态规划：377. 组合总和 Ⅳ (opens new window)、动态规划：70. 爬楼梯进阶版（完全背包）(opens new window)
    如果求最小数,那么两层for循环的先后顺序就无所谓了,相关题目如下：求最小数：动态规划：322. 零钱兑换 (opens new window)、动态规划：279.完全平方数(opens new window)
    对于背包问题,其实递推公式算是容易的,难是难在遍历顺序上,如果把遍历顺序搞透,才算是真正理解了。

*/

/*
01bag:
    物品不能重复添加
    题目描述：有N件物品和一个最多能承受重量W的背包,第i件物品的重量是weight[i],得到的价值是value[i],
    没见物品只能用一次,求解将哪些物品装入背包后物品价值的总和最大？
    -----------------------------------------------
                    重量                价值
    物品0           1                   15
    物品1           3                   20
    物品2           4                   30
    -----------------------------------------------

    答案：
                    背包重量j：
            0   1   2   3   4
    物品0:  0   15  15  15  15
    物品1:  0   15  15  20  35
    物品2:  0   15  15  20  35
*/

// 二维数组版
int func1()
{
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};

    int bagWeight = 4; // 背包容量为4

    // 二维数组
    vector<vector<int>> dp(weight.size(), vector<int>(bagWeight + 1, 0));

    // 初始化, 从第一行,从能装下最小物品的的那一列开始赋值为能装下第一个物品的价值
    for (int j = weight[0]; j <= bagWeight; ++j)
    {
        dp[0][j] = value[0];
    }

    // weight数组的长度就是物品的个数
    for (int i = 1; i < weight.size(); ++i) // 遍历物品
    {
        for (int j = 0; j <= bagWeight; ++j) // 遍历背包容量
        {
            if (j < weight[i])
                dp[i][j] = dp[i - 1][j]; // 背包总容量都放不下该物品
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]); // 取不放入该物品和减去该物品的背包容量放入该物品的最大值
        }
    }
    return dp[weight.size() - 1][bagWeight];
}

// 一维数组版
// 一维数组版先遍历物品后遍历背包,要从后往前遍历,因为j-weight[i]会用到前面的值
int func2()
{
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;

    // 初始化dp数组
    vector<int> dp(bagWeight + 1, 0);
    for (int i = 0; i < weight.size(); ++i) // 遍历物品
    {
        for (int j = bagWeight; j >= weight[i]; --j) // 遍历背包容量
        {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[bagWeight];
}

/*
完全bag:
    物品可重复添加
    题目描述：有N件物品和一个最多能背重量W的背包。第i件物品的重量是weight[i],得到的价值是value[i],
    每件物品都有无限个(也就是可以放入背包多次),求解将哪些物品装入背包中物品价值的总和最大

    -----------------------------------------------
                    重量                价值
    物品0           1                   15
    物品1           3                   20
    物品2           4                   30
    -----------------------------------------------

    在完全背包中,dp一维数组,先遍历背包和先遍历物品都可以,因为dp[j]是根据下标j之前所对应的dp[k](k<j)计算出来的,
    只要保证下标j之前的dp[k](k<j)都是经过计算的即可。
    完全背包要从前向后遍历,因为可以重复添加多遍
*/

// 先遍历物品
int func3()
{
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;
    vector<int> dp(bagWeight + 1, 0);

    for (int i = 0; i < weight.size(); ++i) // 遍历物品
    {
        for (int j = weight[i]; j <= bagWeight; ++j) // 遍历背包容量
        {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[bagWeight];
}

// 先遍历背包容量
int func4()
{
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;
    vector<int> dp(bagWeight + 1, 0);
    for (int j = 0; j <= bagWeight; ++j) // 遍历背包容量
    {
        for (int i = 0; i < weight.size(); ++i) // 遍历物品
        {
            if (j - weight[i] >= 0)
                dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[bagWeight];
}

/*
多步爬楼梯：
    假设正在爬楼梯,需要跨过n个台阶才能到达楼顶。
    每一步可以跨过1个台阶、2个台阶、3个台阶,...,直到m个台阶。
    问有多少种不同的方法可以爬到楼顶？ (先j后i)
*/

int climbStairs(int n, int m)
{
    if (n <= 2)
        return n;
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    // 求排列问题,所以一定先遍历背包,再遍历物品
    // 每个物品可重复使用(步数使用次数不限) 所以内层循环从前向后遍历
    for (int j = 1; j <= n; j++)
    { // 背包
        for (int i = 1; i <= m; i++)
        { // 物品
            if (j - i >= 0)
                dp[j] += dp[j - i];
        }
    }
    return dp[n];
}

/*
718. 最长重复子数组  https://leetcode.cn/problems/maximum-length-of-repeated-subarray/description/
    给两个整数数组nums1和nums2,返回两个数组中公共的、长度最长的子数组的长度 子数组要连续
    示例：
    输入：nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
    输出：3
    解释：长度最长的公共子数组是 [3,2,1]。

dp[i][j]表示 nums1以i-1为结尾的数组和nums2以j-1为结尾的最长公共子数组
dp数组推导：
        B:  3   2   1   4   7
    A:  0   0   0   0   0   0
    1   0   0   0   1   0   0
    2   0   0   1   0   0   0
    3   0   1   0   0   0   0
    2   0   0   2   0   0   0
    1   0   0   0   3   0   0
*/

int findLength(vector<int> &nums1, vector<int> &nums2)
{
    // dp[i][j]表示 nums1以i-1为结尾的数组和nums2以j-1为结尾的最长公共子数组
    vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
    int res = 0;

    for (int i = 1; i <= nums1.size(); ++i)
    {
        for (int j = 1; j <= nums2.size(); ++j)
        {
            if (nums1[i - 1] == nums2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            if (dp[i][j] > res)
                res = dp[i][j];
        }
    }
    return res;
}