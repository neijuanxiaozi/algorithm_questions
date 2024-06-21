#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <climits>
#include <ctime>
#include <string>
#include <algorithm>
#include <set>
#include <list>
#include <memory>
using namespace std;

int func1()
{
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;

    vector<vector<int>> dp(weight.size(), vector<int>(bagWeight + 1, 0));

    for (int j = weight[0]; j <= bagWeight; ++j)
    {
        dp[0][j] = value[0];
    }

    for (int i = 1; i < weight.size(); ++i)
    {
        for (int j = 0; j <= bagWeight; ++j)
        {
            if (j < weight[i])
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
            }
        }
    }
    return dp[weight.size() - 1][bagWeight];
}

int func2()
{
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;

    vector<int> dp(bagWeight + 1, 0);

    for (int i = 0; i < weight.size(); ++i)
    {
        for (int j = bagWeight; j >= weight[i]; --j)
        {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[bagWeight];
}
int func3()
{
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;

    vector<int> dp(bagWeight + 1, 0);

    for (int i = 0; i < weight.size(); ++i)
    {
        for (int j = weight[i]; j <= bagWeight; ++j)
        {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[bagWeight];
}

int func4()
{
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;

    vector<int> dp(bagWeight + 1, 0);

    for (int j = 0; j <= bagWeight; ++j)
    {
        for (int i = 0; i < weight.size(); ++i)
        {
            if (j - weight[i] >= 0)
                dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[bagWeight];
}
