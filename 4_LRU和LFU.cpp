#include <unordered_map>
#include <list>
using namespace std;

/*
146.LRU缓存: https://leetcode.cn/problems/lru-cache/description/
    请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
    实现 LRUCache 类：
    LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
    int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
    void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
    函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
*/

// 用stl的链表
class LRUCache
{
public:
    int capacity_;
    unordered_map<int, list<pair<int, int>>::iterator> node_map;
    list<pair<int, int>> lst;
    LRUCache(int capacity) : capacity_(capacity)
    {
        node_map.clear();
        lst.clear();
    }

    int get(int key)
    {
        if (capacity_ == 0)
            return -1;
        if (node_map.find(key) == node_map.end())
            return -1;
        int value = node_map[key]->second;
        lst.erase(node_map[key]);
        addToHead(key, value);
        return value;
    }

    void put(int key, int value)
    {
        if (capacity_ == 0)
            return;
        if (node_map.find(key) == node_map.end()) // 不在链表中
        {
            if (node_map.size() == capacity_) // 链表是满的
            {
                node_map.erase(lst.back().first);
                lst.pop_back();
            }
            addToHead(key, value);
        }
        else // 在链表中
        {
            lst.erase(node_map[key]);
            addToHead(key, value);
        }
    }
    void addToHead(int key, int value)
    {
        lst.emplace_front(key, value);
        node_map[key] = lst.begin();
    }
};
// 自己实现链表
struct LinkNode
{
    int key;
    int value;
    LinkNode *prev;
    LinkNode *next;
    LinkNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    LinkNode(int key_, int value_) : key(key_), value(value_), prev(nullptr), next(nullptr) {}
};
class LRUCache
{
private:
    unordered_map<int, LinkNode *> cache;
    LinkNode *head;
    LinkNode *tail;
    int capacity;

public:
    LRUCache(int capacity) : capacity(capacity)
    {
        head = new LinkNode();
        tail = new LinkNode();
        head->next = tail;
        tail->prev = head;
    }
    ~LRUCache()
    {
        LinkNode *node = head;
        while (head)
        {
            LinkNode *temp = head->next;
            delete head;
            head = temp;
        }
    }
    int get(int key)
    {
        if (!cache.count(key))
            return -1;
        LinkNode *node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value)
    {
        if (cache.count(key))
        {
            LinkNode *node = cache[key];
            node->value = value;
            moveToHead(node);
        }
        else
        {
            LinkNode *node = new LinkNode(key, value);
            cache[key] = node;
            if (cache.size() > capacity)
            {
                LinkNode *node = tail->prev;
                if (node != head)
                {
                    removeNode(node);
                    cache.erase(node->key);
                    delete node;
                }
            }
            addToHead(node);
        }
    }
    void removeNode(LinkNode *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void addToHead(LinkNode *node)
    {
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        node->prev = head;
    }
    void moveToHead(LinkNode *node)
    {
        removeNode(node);
        addToHead(node);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

/*
460. LFU缓存  https://leetcode.cn/problems/lfu-cache/description/
    请你为 最不经常使用（LFU）缓存算法设计并实现数据结构。

    实现 LFUCache 类：

    LFUCache(int capacity) - 用数据结构的容量 capacity 初始化对象
    int get(int key) - 如果键 key 存在于缓存中，则获取键的值，否则返回 -1 。
    void put(int key, int value) - 如果键 key 已存在，则变更其值；如果键不存在，请插入键值对。当缓存达到其容量 capacity 时，则应该在插入新项之前，移除最不经常使用的项。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除 最久未使用 的键。
    为了确定最不常使用的键，可以为缓存中的每个键维护一个 使用计数器 。使用计数最小的键是最久未使用的键。

    当一个键首次插入到缓存中时，它的使用计数器被设置为 1 (由于 put 操作)。对缓存中的键执行 get 或 put 操作，使用计数器的值将会递增。

    函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
*/

// 根据项目里的改写的  能通过leetcode 但是代码太多 因为node list 都是自己写的
class DoubleList
{
private:
    int freq;
    LinkNode *head;
    LinkNode *tail;

public:
    DoubleList *prev;
    DoubleList *next;
    DoubleList(int freq_ = 0) : freq(freq_), prev(nullptr), next(nullptr)
    {
        head = new LinkNode();
        tail = head;
    }
    ~DoubleList() { destory(); }
    void destory()
    {
        while (head != nullptr)
        {
            LinkNode *temp = head;
            head = head->next;
            delete temp;
        }
    }
    int getFreq() { return freq; }
    bool isEmpty() { return head == tail; }
    LinkNode *getLast() { return tail; }
    void add(LinkNode *node)
    { // 将节点添加到链表头部
        if (!head->next)
            tail = node;
        else
            head->next->prev = node;
        node->next = head->next;
        head->next = node;
        node->prev = head;
    }
    void del(LinkNode *node)
    {
        node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
        else
            tail = node->prev;
    }
};
class LFUCache1
{
private:
    DoubleList *head;
    int capacity;
    unordered_map<int, LinkNode *> node_map;
    unordered_map<int, DoubleList *> list_map;

public:
    LFUCache1(int capacity) : capacity(capacity)
    {
        head = new DoubleList(); // 新建一个大连表的虚拟头节点  默认频度为0
    }
    ~LFUCache1()
    {
        while (head)
        {
            DoubleList *temp = head;
            head = head->next;
            temp->destory();
            delete temp;
        }
    }
    void delList(DoubleList *list)
    {
        list->prev->next = list->next;
        if (list->next)
        {
            list->next->prev = list->prev;
        }
        list->destory();
        delete list;
    }
    int get(int key)
    {
        if (!capacity)
            return -1;
        if (node_map.find(key) == node_map.end())
            return -1;
        LinkNode *node = node_map[key];
        DoubleList *list = list_map[key];
        addFreq(node, list);
        return node->value;
    }

    void put(int key, int value)
    {
        if (!capacity)
            return;
        if (node_map.find(key) != node_map.end())
        {
            LinkNode *node = node_map[key];
            node->value = value;
            addFreq(node, list_map[key]);
        }
        else
        {
            // 缓存已满 删除频度最小链表里的最后一个节点
            if (node_map.size() == capacity)
            {
                DoubleList *temp = head->next;
                LinkNode *last = temp->getLast();
                temp->del(last);
                node_map.erase(last->key);
                list_map.erase(last->key);
                delete last;
                if (temp->isEmpty())
                {
                    delList(temp);
                }
            }
            LinkNode *node = new LinkNode(key, value); // 新建节点
            addFreq(node, head);                       // 将节点加入到链表中
            node_map[key] = node;                      // 将新建节点的key映射到节点上
            list_map[key] = head->next;                // 将新建节点的key映射到所属链表上
        }
    }

    void addFreq(LinkNode *node, DoubleList *list)
    {
        DoubleList *temp = nullptr;
        // 后面没有链表了或者下一个链表的freq不等于当前链表的freq + 1
        if (!list->next || list->getFreq() + 1 != list->next->getFreq())
        {
            temp = new DoubleList(list->getFreq() + 1);
            // 后面有链表
            if (list->next)
                list->next->prev = temp;
            temp->next = list->next;
            list->next = temp;
            temp->prev = list;
        }
        else
        {
            temp = list->next;
        }
        list_map[node->key] = temp;
        if (list != head)
            list->del(node);
        temp->add(node);
        if (list != head && list->isEmpty())
            delList(list);
    }
};

// leetcode 官方题解
//  缓存的节点信息
class LFUCache
{
private:
    struct Node
    {
        int key;
        int value;
        int freq;
        Node(int key_, int value_, int freq_)
            : key(key_), value(value_), freq(freq_) {}
    };
    int minFreq;
    int capacity_;
    unordered_map<int, list<Node>> list_map;
    unordered_map<int, list<Node>::iterator> node_map;

public:
    LFUCache(int capacity) : capacity_(capacity), minFreq(0)
    {
        list_map.clear();
        node_map.clear();
    }

    int get(int key)
    {
        if (node_map.find(key) == node_map.end())
            return -1;
        int freq = node_map[key]->freq;
        int value = node_map[key]->value;
        list_map[freq].erase(node_map[key]);
        if (list_map[freq].empty())
        {
            if (minFreq == freq)
                minFreq += 1;
            list_map.erase(freq);
        }
        list_map[freq + 1].emplace_front(key, value, freq + 1);
        node_map[key] = list_map[freq + 1].begin();
        return value;
    }

    void put(int key, int value)
    {
        if (node_map.find(key) == node_map.end())
        {
            if (capacity_ == node_map.size())
            {
                node_map.erase(list_map[minFreq].back().key);
                list_map[minFreq].pop_back();
                if (list_map[minFreq].empty())
                {
                    list_map.erase(minFreq);
                }
            }
            list_map[1].emplace_front(key, value, 1);
            node_map[key] = list_map[1].begin();
            minFreq = 1;
        }
        else
        {
            int freq = node_map[key]->freq;
            list_map[freq].erase(node_map[key]);
            if (list_map[freq].empty())
            {
                if (minFreq == freq)
                    minFreq += 1;
                list_map.erase(freq);
            }
            list_map[freq + 1].emplace_front(key, value, freq + 1);
            node_map[key] = list_map[freq + 1].begin();
        }
    }
};
