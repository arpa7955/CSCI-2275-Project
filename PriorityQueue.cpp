#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;

void swap(ReviewInfo **a, ReviewInfo **b)
{
    ReviewInfo *temp = *a;
    *a = *b;
    *b = temp;
}

PriorityQ::PriorityQ(int cap)
{
    capacity = cap;
    currentSize = 0;
    heapArr = new ReviewInfo[capacity];
}

PriorityQ::~PriorityQ()
{
    delete[] heapArr; //knows to delete the whole size 50 bc it's 50 contiguous spaces
}

int PriorityQ::parent(int index)
{
    if (index == 0)
    {
        return -1;
    }
    else
    {
        return (index - 1) / 2;
    }
}

int PriorityQ::leftChild(int index)
{
    return (2*index) + 1;
}

int PriorityQ::rightChild(int index)
{
    return (2*index) + 2;
}

void PriorityQ::peek()
{
    if (currentSize == 0)
    {
        cout << "no record found" << endl;
    }
    else
    {
        ReviewInfo rw = heapArr[0];
        cout << "Restaurant: " << rw.restaurantName << endl;
        cout << "Customer:" << rw.customer << endl;
        cout << "Review:" << rw.review << endl;
        cout << "Time:" << rw.time << endl;
    }
}

void PriorityQ::heapify(int i)
{ //mainly for pop
    int max = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < currentSize && heapArr[left].time > heapArr[max].time)
        max = left;

    if (right < currentSize && heapArr[right].time > heapArr[max].time)
        max = right;

    if (max != i)
    {
        swap(heapArr[i], heapArr[max]);
        heapify(max);
    }
}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    if (currentSize == capacity)
    {
        cout << "Maximum heap size reached. Cannot insert anymore." << endl;
    }
    else
    {
        heapArr[currentSize] = restaurant;
        currentSize++;
        int index = currentSize - 1;
        while (index > 0 && heapArr[index].time > heapArr[parent(index)].time)
        {
            swap(heapArr[index], heapArr[parent(index)]);
            index = parent(index);
        }
    }
}

void PriorityQ::print()
{
    for (int i = 0; i < currentSize; i++)
    {
        cout << "\t"
             << "Customer: " << heapArr[i].customer << endl;
        cout << "\t"
             << "Review: " << heapArr[i].review << endl;
        cout << "\t"
             << "Time: " << heapArr[i].time << endl;
        cout << "\t"
             << "=====" << endl;
    }
}

void PriorityQ::pop()
{
    if (currentSize <= 0)
    {
        return;
    }

    heapArr[0] = heapArr[currentSize - 1];
    currentSize--;

    heapify(0);
}
