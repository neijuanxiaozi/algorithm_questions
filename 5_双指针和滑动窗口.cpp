// A~Z 65~90    a~z  97~122

/*
hard
30. 串联所有单词的子串 https://leetcode.cn/problems/substring-with-concatenation-of-all-words/description/?envType=study-plan-v2&envId=top-interview-150
    给定一个字符串 s 和一个字符串数组 words。 words 中所有字符串 长度相同。
    s 中的 串联子串 是指一个包含  words 中所有字符串以任意顺序排列连接起来的子串。
    例如，如果 words = ["ab","cd","ef"]， 那么 "abcdef"， "abefcd"，"cdabef"， "cdefab"，"efabcd"， 和 "efcdab" 都是串联子串。 "acdbef" 不是串联子串，因为他不是任何 words 排列的连接。
    返回所有串联子串在 s 中的开始索引。你可以以 任意顺序 返回答案。

    示例 1：
        输入：s = "barfoothefoobarman", words = ["foo","bar"]
        输出：[0,9]
        解释：因为 words.length == 2 同时 words[i].length == 3，连接的子字符串的长度必须为 6。
        子串 "barfoo" 开始位置是 0。它是 words 中以 ["bar","foo"] 顺序排列的连接。
        子串 "foobar" 开始位置是 9。它是 words 中以 ["foo","bar"] 顺序排列的连接。
        输出顺序无关紧要。返回 [9,0] 也是可以的。

    示例 2：
        输入：s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
        输出：[]
        解释：因为 words.length == 4 并且 words[i].length == 4，所以串联子串的长度必须为 16。
        s 中没有子串长度为 16 并且等于 words 的任何顺序排列的连接。
        所以我们返回一个空数组。

    示例 3：
        输入：s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
        输出：[6,9,12]
        解释：因为 words.length == 3 并且 words[i].length == 3，所以串联子串的长度必须为 9。
        子串 "foobarthe" 开始位置是 6。它是 words 中以 ["foo","bar","the"] 顺序排列的连接。
        子串 "barthefoo" 开始位置是 9。它是 words 中以 ["bar","the","foo"] 顺序排列的连接。
        子串 "thefoobar" 开始位置是 12。它是 words 中以 ["the","foo","bar"] 顺序排列的连接。

    提示：
        1 <= s.length <= 104
        1 <= words.length <= 5000
        1 <= words[i].length <= 30
        words[i] 和 s 由小写英文字母组成
*/
class Solution
{
public:
    vector<int> findSubstring(string s, vector<string> &words)
    {
        vector<int> res;
        int s_len = s.size(), word_len = words[0].size();
        int window_len = word_len * words.size(); // 窗口长度
        unordered_map<string, int> words_freq;          // 记录words中单词出现的频次
        // 算出窗口长度以及words中单词出现的频次
        for (auto &word : words)
        {
            ++words_freq[word];
        }

        // 一共有d(单词长度)个滑动窗口,将这d个滑动窗口初始化单词频率
        // 然后和words的单词频率um比较,如果相同,加入结果集
        // 意思就是先看看d个窗口的初始位置有没有结果,有就放入结果集
        vector<unordered_map<string, int>> windows_freq(word_len);
        // 遍历每个初始窗口
        for (int i = 0; i < word_len && i + window_len <= s_len; ++i)
        {
            // 按照word_length长度分割初始窗口里的单词,然后加入窗口频次的map中
            for (int j = i; j < i + window_len; j += word_len)
            {
                string temp = s.substr(j, word_len);
                ++windows_freq[i][temp];
            }
            if (windows_freq[i] == words_freq)
            {
                res.push_back(i);
            }
        }
        // 滑动窗口,每次移动d(一个单词的长度)个位置
        // i的值是对应窗口将要移动到的起始位置
        for (int i = word_len; i + window_len <= s_len; ++i)
        {
            // 得到当前要操作的窗口,第几个窗口
            int index = i % word_len;
            // 得到要左边要删除的单词
            string left = s.substr(i - word_len, word_len);
            // 得到右边要加入的单词
            string right = s.substr(i - word_len + window_len, word_len);
            --windows_freq[index][left];
            if (windows_freq[index][left] == 0)
            {
                windows_freq[index].erase(left);
            }
            ++windows_freq[index][right];
            if (windows_freq[index] == words_freq)
            {
                res.push_back(i);
            }
        }
        return res;
    }
};
/*
209. 长度最小的子数组: https://leetcode.cn/problems/minimum-size-subarray-sum/description/
    给定一个含有 n 个正整数的数组和一个正整数 target 。
    找出该数组中满足其总和大于等于 target 的长度最小的连续子数组 [numsl, numsl+1, ..., numsr-1, numsr]
    并返回其长度。如果不存在符合条件的子数组，返回 0 。

    示例 1：
    输入：target = 7, nums = [2,3,1,2,4,3]
    输出：2
    解释：子数组 [4,3] 是该条件下的长度最小的子数组。


    示例 2：
    输入：target = 4, nums = [1,4,4]
    输出：1


    示例 3：
    输入：target = 11, nums = [1,1,1,1,1,1,1,1]
    输出：0
*/
#include <vector>
#include <climits>
using namespace std;

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int res = INT_MAX, left = 0, right = 0, sum = 0; // left和right分别表示窗口的左右边界 sum表示窗口内数字和
        for (; right < nums.size(); ++right)             // 遍历窗口的右边界
        {
            sum += nums[right];   // 将新加入窗口内右边界的数字 加入sum中
            while (sum >= target) // 收缩左边界 每移动一次就记录一次答案
            {
                res = res > (right - left + 1) ? (right - left + 1) : res;
                sum -= nums[left++];
            }
        }
        return res == INT_MAX ? 0 : res;
    }
};

/*
水果成篮:
    题目描述:你正在探访一家农场，农场从左到右种植了一排果树。这些树用一个整数数组 fruits 表示，
    其中 fruits[i] 是第 i 棵树上的水果种类 。
    你想要尽可能多地收集水果。然而，农场的主人设定了一些严格的规矩，你必须按照要求采摘水果：
    你只有两个篮子，并且每个篮子只能装单一类型的水果。每个篮子能够装的水果总量没有限制。
    你可以选择任意一棵树开始采摘，你必须从每棵树（包括开始采摘的树）上恰好摘一个水果。
    采摘的水果应当符合篮子中的水果类型。每采摘一次，你将会向右移动到下一棵树，并继续采摘。
    一旦你走到某棵树前，但水果不符合篮子的水果类型，那么就必须停止采摘。
    给你一个整数数组 fruits ，返回你可以收集的水果的最大数目。


    示例 1：
    输入：fruits = [1,2,1]
    输出：3
    解释：可以采摘全部 3 棵树。


    示例 2：
    输入：fruits = [0,1,2,2]
    输出：3
    解释：可以采摘 [1,2,2] 这三棵树。
    如果从第一棵树开始采摘，则只能采摘 [0,1] 这两棵树。


    示例 3：
    输入：fruits = [1,2,3,2,2]
    输出：4
    解释：可以采摘 [2,3,2,2] 这四棵树。
    如果从第一棵树开始采摘，则只能采摘 [1,2] 这两棵树。


    示例 4：
    输入：fruits = [3,3,3,1,2,1,1,2,3,3,4]
    输出：5
    解释：可以采摘 [1,2,1,1,2] 这五棵树。
*/
#include <unordered_map>
class Solution
{
public:
    int totalFruit(vector<int> &fruits)
    {
        int res = 0;
        unordered_map<int, int> type_number; // 当前拿的水果种类
        int left = 0, right = 0;
        for (; right < fruits.size(); ++right)
        {
            ++type_number[fruits[right]];
            while (type_number.size() > 2)
            {
                --type_number[fruits[left]];
                if (type_number[fruits[left]] == 0)
                    type_number.erase(fruits[left]);
                ++left;
            }
            res = max(right - left + 1, res); // 每加入一个right的值都会记录答案，所以不会漏情况的 不管type_number.siz()是不是大于0
        }
        return res;
    }
};

/*
76. 最小覆盖子串: https://leetcode.cn/problems/minimum-window-substring/description/
    题目描述:给你一个字符串 s 、一个字符串 t 。
    返回 s 中涵盖 t 所有字符的最小子串。
    如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串""。

    注意：
    对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
    如果 s 中存在这样的子串，我们保证它是唯一的答案。


    示例 1：
    输入：s = "ADOBECODEBANC", t = "ABC"
    输出："BANC"
    解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。


    示例 2：
    输入：s = "a", t = "a"
    输出："a"
    解释：整个字符串 s 是最小覆盖子串。


    示例 3:
    输入: s = "a", t = "aa"
    输出: ""
    解释: t 中两个字符 'a' 均应包含在 s 的子串中，
    因此没有符合条件的子字符串，返回空字符串。


    提示：
    m == s.length
    n == t.length
    1 <= m, n <= 105
    s 和 t 由英文字母组成
*/

class Solution
{
public:
    string minWindow(string s, string t)
    {
        int len = INT_MAX;
        int res_left = 0;
        int s_length = s.size();
        int left = 0, right = 0;
        unordered_map<char, int> t_frequency;
        for (auto const &temp : t)
        {
            ++t_frequency[temp];
        }
        for (; right < s_length; ++right)
        {
            if (t_frequency.find(s[right]) != t_frequency.end())
            {
                --t_frequency[s[right]];
            }
            while (check(t_frequency) && left <= right)
            {
                int temp = right - left + 1;
                if (temp < len)
                {
                    len = temp;
                    res_left = left;
                }
                if (t_frequency.find(s[left]) != t_frequency.end())
                    ++t_frequency[s[left]];
                ++left;
            }
        }
        return len == INT_MAX ? "" : s.substr(res_left, len);
    }
    bool check(unordered_map<char, int> &t_frequency)
    {
        for (auto const &temp : t_frequency)
        {
            if (temp.second > 0)
            {
                return false;
            }
        }
        return true;
    }
};

// 四数之和 用滑动窗口不好去重 所以双指针
/*
18. 四数之和: https://leetcode.cn/problems/4sum/description/
    给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。
    请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]]
    若两个四元组元素一一对应，则认为两个四元组重复）：
    0 <= a, b, c, d < n
    a、b、c 和 d 互不相同
    nums[a] + nums[b] + nums[c] + nums[d] == target
    你可以按任意顺序返回答案 。


    示例 1：
    输入：nums = [1,0,-1,0,-2,2], target = 0
    输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]


    示例 2：
    输入：nums = [2,2,2,2,2], target = 8
    输出：[[2,2,2,2]]


    提示：
    1 <= nums.length <= 200
    -109 <= nums[i] <= 109
    -109 <= target <= 109
*/
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int k = 0; k < nums.size(); ++k)
        {
            // 剪枝处理
            if (nums[k] > target && nums[k] >= 0)
            {
                break; // 这里使用break，统一通过最后的return返回
            }
            // 对nums[k]去重
            if (k > 0 && nums[k] == nums[k - 1])
            {
                continue;
            }
            for (int i = k + 1; i < nums.size(); ++i)
            {
                // 2级剪枝处理
                if (nums[k] + nums[i] > target && nums[k] + nums[i] >= 0)
                {
                    break;
                }
                // 对nums[i]去重
                if (i > k + 1 && nums[i] == nums[i - 1])
                {
                    continue;
                }
                int left = i + 1;
                int right = nums.size() - 1;
                while (right > left)
                {
                    // nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
                    if ((long)nums[k] + nums[i] + nums[left] + nums[right] > target)
                    {
                        --right;
                        // nums[k] + nums[i] + nums[left] + nums[right] < target 会溢出
                    }
                    else if ((long)nums[k] + nums[i] + nums[left] + nums[right] < target)
                    {
                        ++left;
                    }
                    else
                    {
                        result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
                        // 对nums[left]和nums[right]去重
                        while (right > left && nums[right] == nums[right - 1])
                            --right;
                        while (right > left && nums[left] == nums[left + 1])
                            ++left;

                        // 找到答案时，双指针同时收缩
                        --right;
                        ++left;
                    }
                }
            }
        }
        return result;
    }
};