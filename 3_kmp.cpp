#include <iostream>
#include <vector>
using namespace std;
// KMP算法

/*
28. 找出字符串中第一个匹配项的下标  https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
求next数组
    前缀: 指不包含最后一个字符的所有以第一个字符开头的连续子串
    后缀: 指不包含第一个字符的所有以最后一个字符结尾的连续子串

    next[i]表示从0到i(包含i)的字符串的最长相等前后缀

    比较细节: 如果当前i + 1这个下标的字符不匹配了 那么i + 1这个字符肯定不能要了 回退到哪?
    回退到不包含i + 1的字符串(从0~i)的最长相等前后缀的下一个位置 最长相等前后缀保证了这部分是相等的 不用重新比较
    所以从下一个位置开始比较即可 因为next[i]里面存的是长度 数组索引是从0开始 所以next[i] 直接就是要跳回的位置

    例子: aabaaf
*/
void getNext(vector<int> &next, const string &s)
{
    next[0] = 0; // 只包含第一个字符的字符串 没有前后缀的概念 所以最长相等前后缀初始化为0

    int j = 0; // j表示前缀末尾位置(j同时也表示i之前(包括i)的最长相等前后缀的长度) i表示后缀末尾位置
    for (int i = 1; i < s.size(); ++i)
    {
        while (j > 0 && s[i] != s[j]) // 当前缀末尾和后缀末尾不相等时 前缀回退到前一个位置的下标
        {
            j = next[j - 1];
        }

        if (s[i] == s[j])
        {
            ++j;
        }
        next[i] = j;
    }
}
int strStr(string haystack, string needle)
{
    if (needle.size() == 0)
    {
        return 0;
    }

    vector<int> next(needle.size());
    getNext(next, needle);

    int j = 0;                                // 索引j遍历needle
    for (int i = 0; i < haystack.size(); ++i) // 索引i遍历haystack
    {
        while (j > 0 && haystack[i] != needle[j]) // 匹配失败needle回退
        {
            j = next[j - 1];
        }
        if (haystack[i] == needle[j]) // 匹配成功  i和j都后移
        {
            ++j;
        }
        if (j == needle.size())
        {
            return (i - needle.size() + 1);
        }
    }
    return -1;
}

/*
459. 重复的子字符串  https://leetcode.cn/problems/repeated-substring-pattern/description/
    题目描述:给定一个非空的字符串 s ，检查是否可以通过由它的一个子串重复多次构成。

    示例 1:
    输入: s = "abab"
    输出: true
    解释: 可由子串 "ab" 重复两次构成。


    示例 2:
    输入: s = "aba"
    输出: false


    示例 3:
    输入: s = "abcabcabcabc"
    输出: true
    解释: 可由子串 "abc" 重复四次构成。 (或子串 "abcabc" 重复两次构成。)


    提示：
    1 <= s.length <= 104
    s 由小写英文字母组成
*/
/*
    题解的主要思想是将s的变成s+s  如果满足题意要求 那么s+s中间一定会出现s
    但是查找过程 如果中间有s 算上头尾的一共三个 所以把s+s的头尾字母去掉一个 这样就只保留了中间的s
    然后利用kmp去找
*/
#include <vector>

class Solution
{
public:
    void getNext(vector<int> &next, string const &s)
    {
        next[0] = 0;
        int j = 0;
        for (int i = 1; i < s.size(); ++i)
        {
            while (j > 0 && s[i] != s[j])
                j = next[j - 1];
            if (s[i] == s[j])
                ++j;
            next[i] = j;
        }
    }
    bool repeatedSubstringPattern(string s)
    {
        if (s.size() <= 1)
            return false;
        string double_s = s + s;
        vector<int> next(s.size());
        getNext(next, s);
        int j = 0;
        for (int i = 1; i < double_s.size() - 1; ++i)
        {
            while (j > 0 && double_s[i] != s[j])
                j = next[j - 1];
            if (double_s[i] == s[j])
                ++j;
            if (j == s.size())
                return true;
        }
        return false;
    }
};
