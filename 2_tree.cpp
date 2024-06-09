#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// 树结构
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode *left, TreeNode *right) : val(val), left(left), right(right) {}
};

// 递归前序遍历
void preorderTraversal(TreeNode *root, vector<int> &vec)
{
    if (root == nullptr)
        return;
    vec.push_back(root->val);
    preorderTraversal(root->left, vec);
    preorderTraversal(root->right, vec);
}

// 递归中序遍历
void inorderTraversal(TreeNode *root, vector<int> &vec)
{
    if (root == nullptr)
        return;
    inorderTraversal(root->left, vec);
    vec.push_back(root->val);
    inorderTraversal(root->right, vec);
}

// 递归后序遍历
void postorderTraversal(TreeNode *root, vector<int> &vec)
{
    if (root == nullptr)
        return;
    postorderTraversal(root->left, vec);
    postorderTraversal(root->right, vec);
    vec.push_back(root->val);
}

vector<int> traversal(TreeNode *root)
{
    vector<int> result;
    preorderTraversal(root, result); // 前序遍历
    return result;
}

//144. 二叉树的前序遍历  https://leetcode.cn/problems/binary-tree-preorder-traversal/description/
// 迭代法前序遍历
vector<int> preorderTraversal(TreeNode *root)
{
    vector<int> result;
    stack<TreeNode *> st;
    if (root != nullptr)
        st.push(root);
    while (!st.empty())
    {
        TreeNode *node = st.top();
        st.pop();
        if (node != nullptr)
        {
            if (node->right)
                st.push(node->right);
            if (node->left)
                st.push(node->left);
            st.push(node);
            st.push(nullptr);
        }
        else
        {
            node = st.top();
            st.pop();
            result.push_back(node->val);
        }
    }
    return result;
}
// 迭代法中序遍历
vector<int> inorderTraversal(TreeNode *root)
{
    vector<int> result;
    stack<TreeNode *> st;
    if (root != nullptr)
        st.push(root);
    while (!st.empty())
    {
        TreeNode *node = st.top();
        st.pop();
        if (node != nullptr)
        {
            if (node->right)
                st.push(node->right);
            st.push(node);
            st.push(nullptr);
            if (node->left)
                st.push(node->left);
        }
        else
        {
            node = st.top();
            st.pop();
            result.push_back(node->val);
        }
    }
    return result;
}
// 迭代法后序遍历
vector<int> postorderTraversal(TreeNode *root)
{
    vector<int> result;
    stack<TreeNode *> st;
    if (root != nullptr)
        st.push(root);
    while (!st.empty())
    {
        TreeNode *node = st.top();
        st.pop();
        if (node != nullptr)
        {
            st.push(node);
            st.push(nullptr);
            if (node->right)
                st.push(node->right);
            if (node->left)
                st.push(node->left);
        }
        else
        {
            node = st.top();
            st.pop();
            result.push_back(node->val);
        }
    }
    return result;
}
// 102. 二叉树的层序遍历 https://leetcode.cn/problems/binary-tree-level-order-traversal/
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> result;
    queue<TreeNode *> que;
    if (root != nullptr)
        que.push(root);
    while (!que.empty())
    {
        int size = que.size();
        vector<int> vec;
        for (int i = 0; i < size; i++)
        {
            TreeNode *node = que.front();
            que.pop();
            vec.push_back(node->val);
            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
        result.push_back(vec);
    }
    return result;
}
// 层序遍历递归法
class Solution
{
public:
    void order(TreeNode *cur, vector<vector<int>> &result, int depth)
    {
        if (cur == nullptr)
            return;
        if (result.size() == depth)
            result.push_back(vector<int>());
        result[depth].push_back(cur->val);
        order(cur->left, result, depth + 1);
        order(cur->right, result, depth + 1);
    }
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> result;
        int depth = 0;
        order(root, result, depth);
        return result;
    }
};

// 从中序与后序遍历序列构造二叉树
TreeNode *inorderAndPostorderTraversal(vector<int> &inorder, vector<int> &postorder)
{
    // 第一步
    if (postorder.size() == 0)
        return nullptr;
    // 第二步：后序遍历数组的最后一个元素,即当前的中间节点
    int rootValue = postorder[postorder.size() - 1];
    TreeNode *root = new TreeNode(rootValue);
    // 叶子节点
    if (postorder.size() == 1)
        return root;
    // 第三步：查找切割点
    int delimiterIndex = 0;
    for (; delimiterIndex < inorder.size(); ++delimiterIndex)
    {
        if (inorder[delimiterIndex] == rootValue)
            break;
    }
    // 切割中序数组,得到中序左数组和中序右数组
    // 左闭右开
    vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
    vector<int> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());
    // 切割后序数组,得到后序左数组和后序右数组
    // postorder舍弃末尾元素,因为这个元素是中间节点,已经用过了
    postorder.resize(postorder.size() - 1);
    // 左闭右开
    vector<int> leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
    vector<int> rightPostorder(postorder.begin() + leftInorder.size(), postorder.end());

    // 第六步：
    root->left = inorderAndPostorderTraversal(leftInorder, leftPostorder);
    root->right = inorderAndPostorderTraversal(rightInorder, rightPostorder);

    // 返回当前节点
    return root;
}
TreeNode *inorderAndPostorderBuildTree(vector<int> &inorder, vector<int> &postorder)
{
    if (inorder.size() == 0 || postorder.size() == 0)
        return nullptr;
    return inorderAndPostorderTraversal(inorder, postorder);
}



//106. 从中序与后序遍历序列构造二叉树 https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/
/*从中序与后序遍历序列构造二叉树(索引版本)*/
class Solution
{
private:
    // 中序区间：[inorderBegin, inorderEnd),后序区间[postorderBegin, postorderEnd)
    TreeNode *traversal(vector<int> &inorder, int inorderBegin, int inorderEnd, vector<int> &postorder, int postorderBegin, int postorderEnd)
    {
        if (postorderBegin == postorderEnd)
            return NULL;

        int rootValue = postorder[postorderEnd - 1];
        TreeNode *root = new TreeNode(rootValue);

        if (postorderEnd - postorderBegin == 1)
            return root;

        int delimiterIndex;
        for (delimiterIndex = inorderBegin; delimiterIndex < inorderEnd; delimiterIndex++)
        {
            if (inorder[delimiterIndex] == rootValue)
                break;
        }
        // 切割中序数组
        // 左中序区间,左闭右开[leftInorderBegin, leftInorderEnd)
        int leftInorderBegin = inorderBegin;
        int leftInorderEnd = delimiterIndex;
        // 右中序区间,左闭右开[rightInorderBegin, rightInorderEnd)
        int rightInorderBegin = delimiterIndex + 1;
        int rightInorderEnd = inorderEnd;

        // 切割后序数组
        // 左后序区间,左闭右开[leftPostorderBegin, leftPostorderEnd)
        int leftPostorderBegin = postorderBegin;
        int leftPostorderEnd = postorderBegin + delimiterIndex - inorderBegin; // 终止位置是 需要加上 中序区间的大小size
        // 右后序区间,左闭右开[rightPostorderBegin, rightPostorderEnd)
        int rightPostorderBegin = postorderBegin + (delimiterIndex - inorderBegin);
        int rightPostorderEnd = postorderEnd - 1; // 排除最后一个元素,已经作为节点了

        root->left = traversal(inorder, leftInorderBegin, leftInorderEnd, postorder, leftPostorderBegin, leftPostorderEnd);
        root->right = traversal(inorder, rightInorderBegin, rightInorderEnd, postorder, rightPostorderBegin, rightPostorderEnd);

        return root;
    }

public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        if (inorder.size() == 0 || postorder.size() == 0)
            return NULL;
        // 左闭右开的原则
        return traversal(inorder, 0, inorder.size(), postorder, 0, postorder.size());
    }
};
// 序列化和反序列化暂时先不用写了
/*
序列化和反序列化二叉树:
    题目描述：请实现两个函数,分别用来序列化和反序列化二叉树。
    你需要设计一个算法来实现二叉树的序列化与反序列化。
    这里不限定你的序列 / 反序列化算法执行逻辑,
    你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
*/

// 只写了层序序列化
// 层序序列化
//  Encodes a tree to a single string.
string serialize(TreeNode *root)
{ // 把一颗树以层序遍历输出成一个字符串,用,隔开,空节点就输出null。 例如 2,3,null,8,4,null,10,null
    if (root == nullptr)
        return "";
    string result = "";
    queue<TreeNode *> que;
    que.push(root);
    while (!que.empty())
    {
        TreeNode *node = que.front();
        que.pop();
        if (node)
        {
            result += (to_string(node->val) + ',');
            que.push(node->left);
            que.push(node->right);
        }
        else
        {
            result += ("null,");
        }
    }
    result.pop_back(); // 删除最后一个
    return result;
}

// Decodes your encoded data to tree.
TreeNode *deserialize(string data)
{ // 反序列化,用上一个函数生成的字符串反序列化成一棵树
    if (data == "")
        return nullptr;
    vector<string> s = split(data);
    queue<TreeNode *> que;
    TreeNode *root = new TreeNode(stoi(s[0]));
    que.push(root);
    int i = 1;
    while (!que.empty() && i < s.size())
    {
        TreeNode *node = que.front();
        que.pop();
        if (s[i] != "null")
        {
            node->left = new TreeNode(stoi(s[i]));
            que.push(node->left);
        }
        ++i;
        if (s[i] != "null")
        {
            node->right = new TreeNode(stoi(s[i]));
            que.push(node->right);
        }
        ++i;
    }
    return root;
}
vector<string> split(string &s)
{ // 将字符串以,分割成多个小字符串
    vector<string> res;
    int n = s.size();
    int i = 0;
    while (i < n)
    {
        int j = i + 1;
        while (j < n && s[j] != ',')
            ++j;
        res.push_back(s.substr(i, j - i));
        i = j + 1;
    }
    return res;
}

/*
LCR 152. 验证二叉搜索树的后序遍历序列 https://leetcode.cn/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/description/
    请实现一个函数来判断整数数组 postorder 是否为二叉搜索树的后序遍历结果。

    递归分治
    根据二叉搜索树的定义,可以通过递归,判断所有子树的正确性（即其后序遍历是否满足二叉搜索树的定义）,
    若所有子树都正确,则此序列为二叉搜索树的后序遍历。
    递归解析：
    终止条件:当i≥j,说明此子树节点数量≤1,无需判别正确性,因此直接返回true;
    递推工作:
            划分左右子树:遍历后序遍历的[i,j]区间元素,寻找第一个大于根节点的节点,索引记为m。
            此时,可划分出左子树区间[i,m−1],右子树区间[m,j−1],根节点索引j。
            判断是否为二叉搜索树:
            左子树区间[i,m−1]内的所有节点都应<postorder[j],
            然而划分左右子树步骤已经保证左子树区间的正确性,因此只需要判断右子树区间即可。
            右子树区间[m,j−1]内的所有节点都应>postorder[j]。
            实现方式为遍历,当遇到≤postorder[j]的节点则跳出;
            则可通过p=j(在判断右子区间时,是否走到了根节点,走到说明都大于根节点)判断是否为二叉搜索树。
    返回值: 所有子树都需正确才可判定正确,因此使用与逻辑符&&连接。
    p=j： 判断此树是否正确。
    recur(i,m−1)：判断此树的左子树是否正确。
    recur(m,j−1)：判断此树的右子树是否正确。
*/

bool verifyPostorder(vector<int> &postorder)
{
    return recur(postorder, 0, postorder.size() - 1);
}
bool recur(vector<int> &postorder, int left, int right)
{
    if (left >= right)
        return true;
    int temp = left;
    while (postorder[temp] < postorder[right])
        ++temp;
    int mid = temp;
    while (postorder[temp] > postorder[right])
        ++temp;
    return temp == right && recur(postorder, left, mid - 1) && recur(postorder, mid, right - 1);
}

/*

111. 二叉树的最小深度 https://leetcode.cn/problems/minimum-depth-of-binary-tree/description/
    给定一个二叉树,找出其最小深度。
    最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
    说明：叶子节点是指没有子节点的节点。


    示例 1：
    输入：root = [3,9,20,null,null,15,7]
    输出：2

    示例 2：
    输入：root = [2,null,3,null,4,null,5,null,6]
    输出：5

    提示：
    树中节点数的范围在 [0, 105] 内
    -1000 <= Node.val <= 1000
*/
// 迭代法用层序遍历即可 碰到叶子节点直接返回层数即可

// 递归法
/*
    如果左子树为空,右子树不为空,说明最小深度是 1 + 右子树的深度。
    如果右子树为空,左子树不为空,最小深度是 1 + 左子树的深度。
    最后如果左右子树都不为空(或者都为空),返回左右子树深度最小值 + 1。
*/
int minDepth(TreeNode *root)
{
    if (!root)
        return 0;
    if (root->left && !root->right)
        return minDepth(root->left) + 1;
    else if (!root->left && root->right)
        return minDepth(root->right) + 1;
    return min(minDepth(root->left), minDepth(root->right)) + 1;
}

/*
501. 二叉搜索树中的众数 https://leetcode.cn/problems/find-mode-in-binary-search-tree/description/
    给你一个含重复值的二叉搜索树（BST）的根节点 root ,
    找出并返回 BST 中的所有众数（即出现频率最高的元素）。
    如果树中有不止一个众数,可以按任意顺序返回。

    假定 BST 满足如下定义：
        结点左子树中所含节点的值 小于等于当前节点的值
        结点右子树中所含节点的值 大于等于当前节点的值
        左子树和右子树都是二叉搜索树

    示例 1：
    输入：root = [1,null,2,2]
    输出：[2]


    示例 2：
    输入：root = [0]
    输出：[0]

    树中节点的数目在范围 [1, 104] 内
    -105 <= Node.val <= 105
*/

class Solution
{
private:
    int maxCount = 0; // 最大频率
    int count = 0;    // 统计频率
    TreeNode *pre = nullptr;
    vector<int> result;
    void searchBST(TreeNode *cur)
    {
        if (cur == NULL)
            return;
        // 左
        searchBST(cur->left); 
        // 中                      
        if (pre == nullptr)
        { // 第一个节点
            count = 1;
        }
        else if (pre->val == cur->val)
        { // 与前一个节点数值相同
            count++;
        }
        else
        { // 与前一个节点数值不同
            count = 1;
        }
        pre = cur; // 更新上一个节点

        if (count == maxCount)
        { // 如果和最大值相同,放进result中
            result.push_back(cur->val);
        }

        if (count > maxCount)
        {                     // 如果计数大于最大值频率
            maxCount = count; // 更新最大频率
            result.clear();   // 很关键的一步,不要忘记清空result,之前result里的元素都失效了
            result.push_back(cur->val);
        }
        // 右
        searchBST(cur->right); 
        return;
    }

public:
    vector<int> findMode(TreeNode *root)
    {
        count = 0;
        maxCount = 0;
        pre = nullptr; // 记录前一个节点
        result.clear();
        searchBST(root);
        return result;
    }
};

/*
236. 二叉树的最近公共祖先 https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/
    给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

    百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q,
    最近公共祖先表示为一个节点 x,满足 x 是 p、q 的祖先且 x 的深度尽可能大
    （一个节点也可以是它自己的祖先）。”
*/
class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == q || root == p || root == nullptr)
            return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left != nullptr && right != nullptr)
            return root;
        if (left == nullptr && right != nullptr)
            return right;
        else if (left != nullptr && right == nullptr)
            return left;
        else
        { //  (left == nullptr && right == nullptr)
            return nullptr;
        }
    }
};

/*
208. 实现 Trie (前缀树) https://leetcode.cn/problems/implement-trie-prefix-tree/description/
    Trie(发音类似 "try")或者说 前缀树 是一种树形数据结构,用于高效地存储和检索字符串数据集中的键。
    这一数据结构有相当多的应用情景,例如自动补完和拼写检查。

    请你实现 Trie 类：
    Trie() 初始化前缀树对象。
    void insert(String word) 向前缀树中插入字符串 word 。
    boolean search(String word) 如果字符串 word 在前缀树中,返回 true（即,在检索之前已经插入）；否则,返回 false 。
    boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ,返回 true ；否则,返回 false。
*/

class Trie
{
private:
    vector<Trie *> children;
    bool isEnd;

    Trie *searchPrefix(string prefix)
    {
        Trie *node = this;
        for (char ch : prefix)
        {
            ch -= 'a';
            if (node->children[ch] == nullptr)
                return nullptr;
            node = node->children[ch];
        }
        return node;
    }

public:
    Trie() : children(26), isEnd(false) {}
    ~Trie()
    {
        for (auto &child : children)
        {
            if (child)
                delete child;
        }
    }
    void insert(string word)
    {
        Trie *node = this;   // 从当前节点开始遍历
        for (char ch : word) // 单词中每有一个字母 向下走一层
        {
            ch -= 'a';
            if (node->children[ch] == nullptr)
            {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    bool search(string word)
    {
        Trie *node = searchPrefix(word);
        return node != nullptr && node->isEnd;
    }

    bool startsWith(string prefix)
    {
        return searchPrefix(prefix) != nullptr;
    }
};

/*
543. 二叉树的直径 https://leetcode.cn/problems/diameter-of-binary-tree/description/
    给你一棵二叉树的根节点,返回该树的直径 。
    二叉树的直径是指树中任意两个节点之间最长路径的长度。
    这条路径可能经过也可能不经过根节点 root 。
    两节点之间路径的长度由它们之间边数表示。
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    int res;
    int traversal(TreeNode *root)
    {
        if (!root)
        {
            return 0;
        }
        // 获得左子树最大高度
        int left = traversal(root->left);
        // 获得右子树最大高度
        int right = traversal(root->right);

        // 以当前节点为根节点 的最大直径 等于左最大+右最大
        res = max(res, left + right);

        // 返回当前节点的高度
        return max(left, right) + 1;
    }
    int diameterOfBinaryTree(TreeNode *root)
    {
        res = 0;
        traversal(root);
        return res;
    }
};


/*
114. 二叉树展开为链表  https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/description/?envType=study-plan-v2&envId=top-interview-150
*/
class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root) {
            return;
        }
        flatten(root->right);
        flatten(root->left);
        TreeNode* right = root->right;
        root->right = root->left;
        root->left = nullptr;
        TreeNode* temp = root;
        while (temp->right)
            temp = temp->right;
        temp->right = right;
    }
};

/*
222. 完全二叉树的节点个数 https://leetcode.cn/problems/count-complete-tree-nodes/description/
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int left_depth = 0, right_depth = 0;
        TreeNode* temp = root;
        while (temp->left) {
            temp = temp->left;
            ++left_depth;
        }
        temp = root;
        while (temp->right) {
            temp = temp->right;
            ++right_depth;
        }
        if (left_depth == right_depth) {
            return (2 << left_depth) - 1;
        }
        return countNodes(root->left) + countNodes(root->right) + 1;
    }
};