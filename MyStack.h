#pragma once

class MyStack
{
public:

	MyStack() : top(nullptr) {};

	struct stackItem
	{
		int data;
		stackItem *next;
	};

	stackItem *top;

	void Push(int newItem)
	{
		stackItem *pNew = new stackItem;
		pNew->data = newItem;
		pNew->next = top;
		top = pNew;
	};

	int Pop()
	{
		if (top)
		{
			int temp = top->data;
			stackItem *pNew = top;
			top = top->next;
			delete pNew;
			return temp;
		}
	};

	bool isEmpty()
	{
		return (!top);
	};	
};
