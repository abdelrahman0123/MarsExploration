#pragma once
template <typename T>
class PriNode
{
private:
	T item;
	PriNode<T>* next;
	int priority;
public:
	PriNode(int p = 0)
	{
		next = nullptr;
		priority = p;
	}

	PriNode(T newItem, int p = 0)
	{
		item = newItem;
		next = nullptr;
		priority = p;
	}
	
	void setItem(T newItem)
	{
		item = newItem;
	}

	void setNext(Node<T>* nextPtr)
	{
		next = nextPtr;
	}

	T getItem() const
	{
		return item;
	}

	PriNode<T>* getNext() const
	{
		return next;
	}

	int getPriority() const
	{
		return priority;
	}
};