#include "Node.h"
#pragma once
template <typename T>
class LinkedList
{
private:
	Node<T>* Head;

public:

	LinkedList()
	{
		Head = nullptr;
	}

	~LinkedList()
	{
		DeleteAll();
	}

	// Prints the linked list in the required format
	// DON'T CHANGE ANYTHING INSIDE THIS FUNCTION *********
	// BECAUSE THE AUTOMATIC JUDGE COMPARES FOR THIS FORMAT
	void PrintList()	const
	{
		Node<T>* p = Head;
		while (p)
		{
			cout << p->getItem() << " ";
			p = p->getNext();
		}
		cout << endl;
	}

	// DO NOT CHANGE ANYTHING IN THIS FUNCTION *********
	void ReadList()
	{
		int val;
		cin >> val;
		while (val != -1)
		{
			this->InsertEnd(val);
			cin >> val;
		}
	}

	// you should NOT change this function
	void InsertEnd(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		if (!Head)
		{
			Head = R;
			return;
		}
		Node<T>* p = Head;
		while (p->getNext())
			p = p->getNext();
		p->setNext(R);
	}

	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

};

