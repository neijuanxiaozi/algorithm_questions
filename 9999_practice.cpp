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

class find_and_sort
{
private:
    vector<int> father;
    int n = 1005;

public:
    void init()
    {
        father = vector<int>(n);
        for (int i = 0; i < n; ++i)
        {
            father[i] = i;
        }
    }

    int find(int u)
    {
        return father[u] == u ? u : father[u] = find(father[u]);
    }

    bool isSame(int u, int v)
    {
        u = find(u);
        v = find(v);
        return v == u;
    }

    void join(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u != v)
        {
            father[v] = u;
        }
    }
};

void merge(vector<int> &arr)
{
    processMerge(arr, 0, arr.size() - 1);
}

void processMerge(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        processMerge(arr, left, right);
        processMerge(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(vector<int> &arr, int left, int mid, int right)
{
    vector<int> help(right - left + 1);
    int helpIndex = 0, p1 = left, p2 = mid + 1;

    while (p1 <= mid && p2 <= right)
    {
        help[helpIndex++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
    }
    while (p1 <= mid)
    {
        help[helpIndex++] = arr[p1++];
    }

    while (p2 <= mid)
    {
        help[helpIndex++] = arr[p2++];
    }

    for (int i = 0; i < help.size(); ++i)
    {
        arr[left + i] = help[i];
    }
}

void quickSort(vector<int> &arr)
{
    processQuick(arr, 0, arr.size() - 1);
}
void swap(vector<int> &arr, int left, int right)
{
    int temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;
}
vector<int> partition(vector<int> &arr, int left, int right)
{
    int less = left - 1, more = right;
    while (left < more)
    {
        if (arr[left] < arr[right])
        {
            swap(arr, ++less, left++);
        }
        else if (arr[left] > arr[right])
        {
            swap(arr, --more, left);
        }
        else
        {
            ++left;
        }
    }
    swap(arr, left, right);
    return {less + 1, more};
}
void processQuick(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        auto temp = partition(arr, left, right);
        processQuick(arr, left, temp[0] - 1);
        processQuick(arr, temp[1] + 1, right);
    }
}

void heapSort(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); ++i)
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
    while (arr[(index - 1) / 2] < arr[index])
    {
        swap(arr[(index - 1) / 2], arr[index]);
        index = (index - 1) / 2;
    }
}

void heapify(vector<int> &arr, int index, int heapSize)
{
    int left = index * 2 + 1;
    while (left < heapSize)
    {
        int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;
        largest = arr[largest] > arr[index] ? largest : index;
        if (largest == index)
        {
            return;
        }
        swap(arr[largest], arr[index]);
        index = largest;
        left = index * 2 + 1;
    }
}