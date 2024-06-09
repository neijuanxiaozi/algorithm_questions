cin 输入接触到第一个非空格字符时开始阅读，当遇到下一个空格字符（空格、制表符、换行符）时就会停止读取。如果`cin>>a>>b`结束后按空格和制表符没用， 必须按回车。因此可以放在while中作为输入bool类型的输入结束判断符。

getline函数可以读取整行，包括前导和嵌入式的空格，并将其存储在字符串对象中。

C++有两种getline函数：

**第一种：**在头文件`#include<istream>`中，是iostream类的成员函数，有两种重载形式：

```c++
istream& getline(char* s, streamsize n);
istream& getline(char* s, streamsize n, char delim);
//以输入遇到回车换行符'\n'作为结束, 或着满10个字符结束，或者遇到设定的字符a = 'a'结束字符流读取。
char buf[20];
char a = 'q';
//cin.getline(buf, 10)
std::cin.getline(buf, 10 ,a)
```

**第二种：**在头文件`#include<string>`中，是普通函数，有四种重载形式。

```c++
istream& getline(istream& is, string& str, char delim);
istream& getline(istream&& is, string& str, char delim);
istream& getline(istream& is, string& str); 
istream& getline(istream&& is, string& str);
```

用法和第一种类似，但是读取的`istream`是作为参数 is 传进函数的，读取的字符串保存在`string`类型的`str`中。`is` : 表示一个输入流，例如`cin`。其中 `str` : 为`string`类型的引用，用来存储输入流中的流信息。`delim` ：为`char`类型的变量，截断字符。不定义的情况下，默认遇到 ‘`\n`'代表一行的输入结束。

```c++
//会一直输入，遇到换行'\n' 符则（执行一次while循环体），循环继续，再进入输入状态。直到EOF事件发生，如ctrl+z 则跳出while循环，结束。
string str;
while(getline(cin, str)){
    cout<<str;
}
//会一直循环输入，遇到'\n' 时也不影响，直到遇到 'q' 字符则（执行一次while循环体）既此处为输出打印一次，然后循环继续，再进入输入状态。直到EOF事件发生，如ctrl+z 则跳出while循环，结束。
string str;
while(getline(cin, str, 'q')){
    cout<<str;
}
```

输入描述:第一行是一个整数N，表示后面会有N行a和b，通过空格隔开。

```cpp
int main() {
    int n, a, b;
    while (cin >> n) {
        while (n--) {
            cin >> a >> b;
        }
    }
}
```

输入描述:输入中每行是一对a和b。其中会有一对是0和0标志着输入结束，且这一对不要计算。

```cpp
int main() {
    int a, b;
    while (cin >> a >> b) {
        if (a == 0 && b == 0) break;
    }
}
```

输入描述:每行的第一个数N，表示本行后面有N个数。如果N=0时，表示输入结束，且这一行不要计算。

```cpp
int main() {
    int n, a;
    while (cin >> n) {
        if (n == 0) break;
        while (n--) {
            cin >> a;
        }
    }
}
```

输入描述:输入的第一行为一个整数N，接下来N行每行先输入一个整数M，然后在同一行内输入M个整数。

```c++
int main() {
    int n, m, a;
    while (cin >> n) {
        while (n--) {
            cin >> m;
            while (m--) {
                cin >> a;
            }
        }
    }
}
```

输入描述:有多组测试样例。每组输入数据占一行，由一个或多个大写字母组成，字母之间由空格分隔。

```cpp
int main() {
    string s;
    while (getline(cin, s)) { // 接受一整行字符串
        float sum = 0;
        int count = 0;
        int flag = 1;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'A') {sum += 4; count++;}
            else if (s[i] == 'B') {sum += 3; count++;}
            else if (s[i] == 'C') {sum += 2; count++;}
            else if (s[i] == 'D') {sum += 1; count++;}
            else if (s[i] == 'F') {sum += 0; count++;}
            else if (s[i] == ' ') continue;
            else {
                flag = 0;
                cout << "Unknown" << endl;
                break;
            }
        }
        if (flag) printf("%.2f\n", sum / count);
    }
    return 0;
}
```

输入描述:输入包含多组测试样例。每组测试样例包含一个正整数n，表示小明已经堆好的积木堆的个数。
接着下一行是n个正整数，表示每一个积木堆的高度h，每块积木高度为1。其中1<=n<=50,1<=h<=100。
测试数据保证积木总数能被积木堆数整除。
当n=0时，输入结束。

```c++
int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        vector<int> nums = vector<int>(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
    }
}
```

输入描述:输入的第一行是一个整数n，表示一共有n组测试数据。（输入只有一个n，没有多组n的输入）
接下来有n行，每组测试数据占一行，每行有一个词组，每个词组由一个或多个单词组成；每组的单词个数不超过10个，每个单词有一个或多个大写或小写字母组成；
单词长度不超过10，由一个或多个空格分隔这些单词。

```c++
//输入示例
//1
//ad dfa     fgs
int main() {
    int n;
    string result, s;
    cin >> n;
/*
当你使用 cin 来读取一个整数时，例如 cin >> n;，用户输入的整数会被读取到变量 n 中。然而，当用户按下回车键确认输入后，除了输入的整数之外，还会输入一个换行符 \n。这是因为用户按下回车键会触发输入的终止，并且换行符会被放置在输入缓冲区中。

在C++中，cin的输入操作符 >> 只会读取输入直到遇到空白字符（包括空格、换行符、制表符等）。而且，这些空白字符会在缓冲区中留下。因此，如果之后你使用 getline() 来读取一行字符串，它会读取到这个留在缓冲区中的换行符，导致似乎直接跳过了输入。

为了避免这种情况，你可以使用 getchar() 来读取并丢弃输入缓冲区中的换行符。这样做确保了之后的输入操作不受之前换行符的影响，从而得到正确的输入。
*/
    getchar(); // 吸收一个回车，因为输入n之后，要输入一个回车
    while (n--) {
        result = "";
        getline(cin, s);
        result += changeChar(s[0]);
        for (int i = 1; i < s.size() - 1; i++) { // 单词之间可能有多个空格
            if (s[i] == ' ' && s[i + 1] != ' ') result += changeChar(s[i + 1]);
        }
        cout << result << endl;
    }
}
```

输入描述:

输入数据只有一组，第一行有n+1个整数，第一个整数是这行余下的整数数目n，后面是n个整数。

这一行整数是用来初始化列表的，并且输入的顺序与列表中的顺序相反，也就是说如果列表中是1、2、3那么输入的顺序是3、2、1。

第二行有一个整数m，代表下面还有m行。每行有一个字符串，字符串是“get”，“insert”，“delete”，“show”中的一种。

如果是“get”，代表获得第a个元素。（a从1开始计数）

如果是“delete”，代表删除第a个元素。（a从1开始计数）

如果是“insert”，则其后跟着两个整数a和e，代表在第a个位置前面插入e。（a从1开始计数）

“show”之后没有正数，直接打印链表全部内容。

```c++
int main() {
    int n, a, m, t, z;
    string s;
    cin >> n;
    LinkedNode* head = nullptr;
    while (n--) {
        cin >> a;
        addAtHead(a);
    }
    cin >> m;
    while (m--) {
        cin >> s;
        if (s == "show")  {
            if (printLinkedList() == -1) cout << "Link list is empty" << endl;
        }
        if (s == "delete") {
            cin >> t; 
            // 本题的删除索引是从1开始，函数实现是从0开始，所以这里是 t - 1
            if (deleteAtIndex(t - 1) == -1) cout << "delete fail" << endl; 
            else cout << "delete OK" << endl;
        }
        if (s == "insert") {
            cin >> t >> z; 
            if (addAtIndex(t - 1, z) == -1) cout << "insert fail" << endl;
            else cout << "insert OK" << endl;

        }
        if (s == "get") {
            cin >> t;
            int getValue = get(t - 1);
            if (getValue == -1) cout << "get fail" << endl;
            else cout << getValue << endl;
        }
    }
}
```

输入描述：输入包含多组测试数据。每组输入包含两个字符串，分别表示二叉树的前序遍历和中序遍历结果。每个字符串由不重复的大写字母组成。

```c++
int main() {

    string preorder;
    string inorder;
    while (cin >> preorder >> inorder) { // 接受一整行字符串
        // 开始构造二叉树
        TreeNode* root = buildTree(preorder, inorder);
        postorderTraversal(root);
        cout << endl;
    }
    return 0;
}
```

输入描述：   第一位一个整数n代表树中节点个数， 接下来n行 第1个表示左儿子序号，第2个代表右儿子序号，如果该序号为0表示没有。 (例如下面示例中，F序号为1，C序号为2，E序号为3，A序号为4，D序号为5，G序号为6，B序号为7)

```c++
TreeNode* buildTree(unordered_map<int, std::pair<int, int>>& nodeMap, vector<char> &index, int rootValueIndex) {
    if (rootValueIndex == 0) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(index[rootValueIndex]);
    root->left = buildTree(nodeMap, index, nodeMap[rootValueIndex].first);
    root->right = buildTree(nodeMap, index, nodeMap[rootValueIndex].second);
    return root;
}
int main() {
    int n;
    cin >> n;
	//记录一个节点的索引对应的左右儿子索引值
    unordered_map<int, std::pair<int, int>> nodeMap;
    // 记录每个节点的v时什么字母
    vector<char> index = vector<char>(n + 1, '0');
    //记录对应索引节点是否是某个节点的儿子节点
    vector<int> is_child = vector<int>(n + 1, 0);
    //	//记录一个节点的索引对应的左右儿子索引值
    vector<vector<int>> nums = vector<vector<int>>(n + 1, vector<int>(2, 0));
    for (int i = 1; i <= n; ++i) {
        cin >> index[i] >> nums[i][0] >> nums[i][1];
    }
    //build tree
    int rootValueIndex = -1;
    for (int i = 1; i <= n; ++i) {
        nodeMap[i] = std::make_pair(nums[i][0], nums[i][1]);
        count[nums[i][0]] += 1;
        count[nums[i][1]] += 1;
    }
    for (int i = 1; i <= n; ++i) {
        if (count[i] == 0) {
            rootValueIndex = i;
        }
    }
    TreeNode* root = buildTree(nodeMap, index, rootValueIndex);
    return 0;
}
```

输入描述:输入包含多组测试数据。
每组输入第一行为两个正整数n（n<=10）和m（m<=n*(n-1)/2），n表示城市个数，m表示线段个数。
接下来m行，每行输入三个整数a，b和l，表示a市与b市之间存在一条线段，线段长度为l。（a与b不同）
每组最后一行输入两个整数x和y，表示问题：x市与y市之间的最短距离是多少。（x与y不同）
城市标号为1~n，l<=20。

```c++
int main() {
    int n, m;//城市个数和线段个数
    while (cin >> n >> m) {
        //无向图
        unordered_map<int, vector<pair<int, int>>> graph;
        // 构建图
        while (m--) {
            int a, b, l;
            std::cin >> a >> b >> l;
            graph[a].emplace_back(b, l);
            graph[b].emplace_back(a, l);
        }
        int x, y;
        std::cin >> x >> y;
    }
    return 0;
}
```

