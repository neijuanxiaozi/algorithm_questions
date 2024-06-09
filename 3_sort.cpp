#include <iostream>
#include <vector>
using namespace std;
//912. 排序数组 https://leetcode.cn/problems/sort-an-array/description/

void swap(vector<int> &arr, int i, int j); // 交换函数

void selectSort(vector<int> &arr); // 选择排序
void bubbleSort(vector<int> &arr); // 冒泡排序
void insertSort(vector<int> &arr); // 插入排序

// 归并排序
void mergeSort(vector<int> &arr); // 时间复杂度O(N*logN) 空间复杂度O(N)
void processMerge(vector<int> &arr, int left, int right);
void merge(vector<int> &arr, int left, int mid, int right);

// 快排
void quickSort(vector<int> &arr); // 由于选择的num不一样会影响时间复杂度，平均为O(N*logN) 平均空间复杂度O(logN) 最差空间复杂度O(N)
void processQuick(vector<int> &arr, int left, int right);
vector<int> partition(vector<int> &arr, int left, int right);

// 堆排序
void heapSort(vector<int> &arr);
void heapInsert(vector<int> &arr, int index);
void heapify(vector<int> &arr, int index, int heapSize);

void swap(vector<int> &arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
// 选择排序 从未排序系列中选择一个最小的放到最前面
void selectSort(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); ++j)
        {
            minIndex = arr[j] < arr[minIndex] ? j : minIndex;
        }
        swap(arr, i, minIndex);
    }
}
// 冒泡排序
void bubbleSort(vector<int> &arr)
{
    for (int end = arr.size() - 1; end > 0; --end)
    {
        for (int i = 0; i < end; ++i)
        {
            if (arr[i] > arr[i + 1])
                swap(arr[i], arr[i + 1]);
        }
    }
}
// 插入排序
void insertSort(vector<int> &arr)
{
    for (int i = 1; i < arr.size(); ++i)
    {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j)
        {
            swap(arr, j, j - 1);
        }
    }
}

void mergeSort(vector<int> &arr)
{
    processMerge(arr, 0, arr.size() - 1);
}

void processMerge(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        processMerge(arr, left, mid);
        processMerge(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(vector<int> &arr, int left, int mid, int right)
{
    vector<int> help(right - left + 1, 0);
    int helpIndex = 0; // help下标
    int p1 = left;     // 左边有序数组第一个下标
    int p2 = mid + 1;  // 右边有序数组第一个下标
    while (p1 <= mid && p2 <= right)
        help[helpIndex++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
    while (p1 <= mid)
        help[helpIndex++] = arr[p1++];
    while (p2 <= right)
        help[helpIndex++] = arr[p2++];
    for (int i = 0; i < help.size(); ++i)
    {
        arr[left + i] = help[i];
    }
}

void quickSort(vector<int> &arr)
{
    processQuick(arr, 0, arr.size() - 1);
}

void processQuick(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        auto temp = partition(arr, left, right);
        processQuick(arr, left, temp[0] - 1);  //<
        processQuick(arr, temp[1] + 1, right); //>
    }
}

vector<int> partition(vector<int> &arr, int left, int right)
{
    int less = left - 1; //<num区的右边界
    int more = right;    //>num区的左边界
    while (left < more)
    {                               // left表示当前值位置，arr[right]表示划分值num left<more表示 当前值没有和大于num区的边界重合时
        if (arr[left] < arr[right]) // 当前值小于划分值
            swap(arr, ++less, left++);
        else if (arr[left] > arr[right])
            swap(arr, left, --more);
        else
            ++left;
    }
    swap(arr, left, right); // 将放在最后的num元素和>num区的第一个元素进行交换
    return {less + 1, more}; // 返回等于num区元素的第一个和最后一个元素的下标
}

void heapSort(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        heapInsert(arr, i);
    }
    int heapSize = arr.size();
    swap(arr, 0, --heapSize);
    while (heapSize > 0)
    {
        heapify(arr, 0, heapSize);
        swap(arr, 0, --heapSize);
    }
}
void heapInsert(vector<int> &arr, int index)
{
    while (arr[index] > arr[(index - 1) / 2])
    {
        swap(arr, index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
}
void heapify(vector<int> &arr, int index, int heapSize)
{
    int leftChild = index * 2 + 1; // 左孩子下标
    while (leftChild < heapSize)
    { // left < heapSize 左孩子没越界(有左孩子)
        int largest = leftChild + 1 < heapSize && arr[leftChild + 1] > arr[leftChild] ? leftChild + 1 : leftChild;
        largest = arr[index] > arr[largest] ? index : largest;
        if (largest == index)
            return;
        swap(arr, index, largest);
        index = largest;
        leftChild = index * 2 + 1;
    }
}

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* 
148. 排序链表 https://leetcode.cn/problems/sort-list/description/
给你链表的头结点 head，请将其按升序排列并返回 排序后的链表
*/
// 链表归并排序
ListNode *mergeSort(ListNode *head)
{
    if (!head || !head->next)
        return head;
    ListNode *mid = findMid(head);
    ListNode *l1 = head;
    ListNode *l2 = mid->next;
    mid->next = nullptr;
    l1 = mergeSort(l1);
    l2 = mergeSort(l2);
    return merge(l1, l2);
}

ListNode *findMid(ListNode *head)
{
    ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode *merge(ListNode *l1, ListNode *l2)
{
    // l1 >= l2长度
    ListNode *dummyHead = new ListNode();
    ListNode *cur = dummyHead;
    while (l1 && l2)
    {
        if (l1->val <= l2->val)
        {
            cur->next = l1;
            l1 = l1->next;
        }
        else
        {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;
    ListNode *result = dummyHead->next;
    delete dummyHead;
    dummyHead = nullptr;
    return result;
}