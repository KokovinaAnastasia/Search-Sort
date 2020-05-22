#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <stack>
#include <chrono>
#include "MyStack.h"

using namespace std;

const int searchArraySize = 10000;
const int minSearchValue = -1000;
const int maxSearchValue = 1000;

const int valueForSearch = 5;
const int countOutputArray = 50;

const int binSearchArraySize = 100;
const int minBinSearchValue = -10;
const int maxBinSearchValue = 10;

int Search(int* array, int arraySize, int value)
{
	for (int i = 0; i < arraySize; ++i)
		if (array[i] == value)
			return i;
	return -1;
};

void QuickSortWithRecursion(int *numbers, int left, int right)
{
	int pivot;
	int l_hold = left; 
	int r_hold = right;
	pivot = numbers[left];
	while (left < right)
	{
		while ((numbers[right] >= pivot) && (left < right))
			right--; 
		if (left != right)
		{
			numbers[left] = numbers[right];
			left++; 
		}
		while ((numbers[left] <= pivot) && (left < right))
			left++;
		if (left != right) 
		{
			numbers[right] = numbers[left]; 
			right--;
		}
	}
	numbers[left] = pivot; 
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) 
		QuickSortWithRecursion(numbers, left, pivot - 1);
	if (right > pivot)
		QuickSortWithRecursion(numbers, pivot + 1, right);
}

void QuickSortWithoutRecursion(int* numbers, int left, int right)
{
	MyStack lefts;
	MyStack rights;
 	lefts.Push(left);
	rights.Push(right);
	while (!lefts.isEmpty() && !rights.isEmpty())
	{
		left = lefts.top->data;
		right = rights.top->data;
		int indx = left;
		int pivot = numbers[right];
		for (int i = left; i < right; i++)
			if (numbers[i] <= pivot)
			{
				int temp = numbers[i];
				numbers[i] = numbers[indx];
				numbers[indx] = temp;
				indx++;
			}
		numbers[right] = numbers[indx];
		numbers[indx] = pivot;
		lefts.Pop();
		rights.Pop();
		if (indx > left)
		{
			lefts.Push(left);
			rights.Push(indx - 1);
		}
		if (indx < right)
		{
			lefts.Push(indx + 1);
			rights.Push(right);
		}
	}
}

int BSearchWithoutRecursion(int *numbers, int left, int right, int value)
{
	int middle;
	bool flag = false;
	while ((left < right) && !flag)
	{
		middle = (left + right) / 2;
		if (numbers[middle] == value) flag = true;
		if (numbers[middle] > value) right = middle;
		else left = middle + 1;
	}
	if (flag) return middle;
	else return -1;
}

int BSearchWithRecursion(int *numbers, int left, int right, int value)
{
	if (left < right)
	{
		int middle = (right + left) / 2;
		if (value <= numbers[middle])
			return BSearchWithRecursion (numbers, left, middle, value);
		else
			return BSearchWithRecursion( numbers, middle + 1, right, value);
	}
	else
	{
		if (numbers[right] == value)
			return right;
		return -1;
	}
}

void SetRandomArray(int* array, int N, int minVal, int maxVal)
{
	for(int i=0; i < N; i++)
		array[i] = rand() % (maxVal - minVal) + minVal;
}

void PrintArray(int* array)
{
	for (int i = 0; i < countOutputArray; i++)
		cout << array[i] << " ";
	cout << endl;
}

int main()
{
	int numbers[searchArraySize];
	SetRandomArray(numbers, searchArraySize, minSearchValue, maxSearchValue);
	cout << "Array:" << endl;
	PrintArray(numbers);
	cout << "Index of " << valueForSearch << " is ";
	auto start1 = chrono::steady_clock::now();
	int index1 = Search(numbers, searchArraySize, valueForSearch);
	auto stop1 = chrono::steady_clock::now();
	auto time1 = chrono::duration_cast<chrono::microseconds>(stop1 - start1);
	cout << index1 << endl;
	cout << "Time of search in array with " << searchArraySize 
		<< " elements is " << time1.count() << " mcrs" << endl;
	cout << endl << endl;

	int numbers2[searchArraySize];
	SetRandomArray(numbers2, binSearchArraySize, minBinSearchValue, maxBinSearchValue);
	cout << "Array before sorting:" << endl; 
	PrintArray(numbers2);
	QuickSortWithRecursion(numbers2, 0, binSearchArraySize - 1);
	cout << "Array after sorting with recursion:" << endl;
	PrintArray(numbers2);
	cout << endl;


	auto start2 = chrono::steady_clock::now();
	cout << "Index of " << valueForSearch << " with recursion is ";
	int index2 = BSearchWithRecursion(numbers2, 0, binSearchArraySize - 1, valueForSearch);
	auto stop2 = chrono::steady_clock::now();
	auto time2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
	cout << index2 << endl;
	cout << "Time of binary search in array with " << binSearchArraySize
		<< " elements and with recursion is " << time2.count() << " mcrs" << endl;
	cout << endl;

	auto start3 = chrono::steady_clock::now();
	cout << "Index of " << valueForSearch << " without recursion is ";
	int index3 = BSearchWithoutRecursion(numbers2, 0, binSearchArraySize - 1, valueForSearch);
	auto stop3 = chrono::steady_clock::now();
	auto time3 = chrono::duration_cast<chrono::microseconds>(stop3 - start3);
	cout << index3 << endl;
	cout << "Time of binary search in array with " << binSearchArraySize
		<< " elements and without recursion is " << time3.count() << " mcrs" << endl;
	cout << endl << endl;

	int numbers3[searchArraySize];
	SetRandomArray(numbers3, binSearchArraySize, minBinSearchValue, maxBinSearchValue);
	cout << "Array before sorting:" << endl;
	PrintArray(numbers3);
	QuickSortWithoutRecursion(numbers3, 0, binSearchArraySize - 1);
	cout << "Array after sorting without recursion:" << endl;
	PrintArray(numbers3);

	system("pause");
	return 0;
}
