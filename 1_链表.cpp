#include <map>
#include <vector>
#include <queue>
using namespace std;

/*
25. K个一组反转链表  https://leetcode.cn/problems/reverse-nodes-in-k-group/description/?envType=study-plan-v2&envId=top-interview-150
    给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
    k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
    你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
*/
struct ListNode
{    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// 递归法
class Solution
{
public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        if (!head)
        {
            return head;
        }
        int num = k;
        ListNode *last = head;
        while (num--)
        {
            if (!last)
            {
                return head;
            }
            last = last->next;
        }
        ListNode *cur = head->next;
        head->next = reverseKGroup(last, k);
        while (--k)
        {
            ListNode *temp = cur->next;
            cur->next = head;
            head = cur;
            cur = temp;
        }
        return head;
    }
};
// 迭代法
class Solution
{
public:
    pair<ListNode *, ListNode *> myReverse(ListNode *head, ListNode *tail)
    {
        ListNode *prev = tail->next, *p = head;
        while (prev != tail)
        {
            ListNode *nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return {tail, head};
    }
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *hair = new ListNode();
        hair->next = head;
        ListNode *pre = hair;
        while (head)
        {
            ListNode *tail = pre;
            // 查看剩余部分长度是否大于等于k
            for (int i = 0; i < k; ++i)
            {
                tail = tail->next;
                if (!tail)
                {
                    return hair->next;
                }
            }
            ListNode *next = tail->next;
            // 翻转链表
            auto res = myReverse(head, tail);
            head = res.first, tail = res.second;
            // 子链表接回原链表
            pre->next = head;
            tail->next = next;
            pre = tail;
            head = tail->next;
        }
        return hair->next;
    }
};

/*
23. 合并k个升序链表 https://leetcode.cn/problems/merge-k-sorted-lists/description/
    给你一个链表数组，每个链表都已经按升序排列。
    请你将所有链表合并到一个升序链表中，返回合并后的链表。
*/
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// chenboyu
class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (lists.empty())
        {
            return nullptr;
        }
        ListNode *vHead = new ListNode(-1);
        ListNode *curNode = vHead;
        while (true)
        {
            int minIndex = 0;
            bool tip = false;
            for (int i = 0; i < lists.size(); ++i)
            {
                if (lists[i] != nullptr)
                {
                    tip = true;
                    if (lists[minIndex] == nullptr)
                    {
                        minIndex = i;
                    }
                    else if (lists[i]->val <= lists[minIndex]->val)
                    {
                        minIndex = i;
                    }
                }
            }
            if (tip == false)
            {
                return vHead->next;
            }
            else
            {
                curNode->next = lists[minIndex];
                lists[minIndex] = lists[minIndex]->next;
                curNode = curNode->next;
            }
        }
        return vHead->next;
    }
};


// 宫水三叶评论区答案  用优先级队列小根堆
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    struct comparsion {
        bool operator()(const ListNode *node1, const ListNode *node2) {
            return node1->val > node2->val;
        }
    };
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, comparsion> heap;
        ListNode *dummyHead = new ListNode();
        for (int i = 0; i < lists.size(); ++i) {
            if (lists[i]) {
                heap.push(lists[i]);
            }
        }
        ListNode *cur = dummyHead;
        while (!heap.empty()) {
            auto node = heap.top();
            heap.pop();
            cur->next = node;
            cur = cur->next;
            if (node->next) {
                heap.push(node->next);
            }
        }
        return dummyHead->next;
    }
};

/*
92. 反转链表 II  https://leetcode.cn/problems/reverse-linked-list-ii/description/?envType=study-plan-v2&envId=top-interview-150
*/

class Solution {
public:
    //宫水三叶 评论区答案
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* h = dummyHead;
        //拿到要反转的第一个节点的前一个节点h
        for (int i = 1; i <= left - 1; ++i) {
            h = h->next;
        }
        //要反转的第一个节点 这个节点不用动的
        ListNode *p = h->next;
        //把要反转的第一个节点后面的所有节点插到h后面
        for (int i = 1; i <= right - left; ++i) {
            ListNode* q = p->next;
            p->next = q->next;
            q->next = h->next;
            h->next = q;
        }
        return dummyHead->next;
    }
};