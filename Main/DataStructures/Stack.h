#pragma once

template<typename T>
class Stack
{
private:
	T* items;
	int top;
	const int STACK_SIZE;

public:

	Stack(int MaxSize) : STACK_SIZE(MaxSize)
	{
		items = new T[STACK_SIZE];
		top = -1;
	}


	bool isEmpty() const
	{
		return top == -1;
	}

	bool push(const T& newEntry)
	{
		if (top == STACK_SIZE - 1) return false;

		top++;
		items[top] = newEntry;
		return true;
	}

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		top--;
		return true;
	}

	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		return true;
	}


	~Stack()
	{
		delete[]items;
	}


	Stack(const ArrayStack<T>& S) :STACK_SIZE(S.STACK_SIZE)
	{
		items = new T[STACK_SIZE];
		for (int i = 0; i <= S.top; i++)
			items[i] = S.items[i];
		top = S.top;
	}


};
