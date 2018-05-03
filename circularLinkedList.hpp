#ifndef __CIRCULAR_LINKED_LIST_HPP
#define __CIRCULAR_LINKED_LIST_HPP

#include <iostream>
#include "list.hpp"

template<typename T>
class CircularLinkedList;

template<typename NodeType>
class Node {
	friend class CircularLinkedList<NodeType>;
	private:
		NodeType data;
		Node<NodeType> *next;
};

template<typename T>
class CircularLinkedList : public List {
	Node<T> *headPointer;	/* Make CircularLinkedList with headPointer */
	
	public:
		CircularLinkedList(){ this->headPointer = nullptr; }

		void insert(int pos, T data);
		void remove(int pos);
		void clear();
		void print();
	
		T operator[](int i); 
};

template<typename T>
void CircularLinkedList<T>::insert(int pos, T data) {
	Node<T> *newNode = new Node<T>;
	
	if (this->size() == 0) {
		this->headPointer = newNode;
		newNode->next = this->headPointer;
	}
	else {
		Node<T> *node = this->headPointer;
		
		if (pos == 0) {
			newNode->next = this->headPointer;
			this->headPointer = newNode;
			
			for(int nodePos = 0; nodePos < this->size() - 1; ++nodePos) 
			{
				node = node->next;
			}
			
			node->next = this->headPointer;
		}
		else {
			for(int nodePos = 0; nodePos < pos - 1; ++nodePos) 
			{
				node = node->next;
			}
			
			newNode->next = node->next;
			node->next = newNode;
		}
	}
	
	newNode->data = data;
	this->increaseElementCount();
}

template<typename T>
void CircularLinkedList<T>::remove(int pos) {
	Node<T> *node = this->headPointer;
	
	if (this->size() == 1) {
		Node<T> *delNode = this->headPointer;
		
		delNode->next = nullptr;
		delete delNode;
		this->headPointer = nullptr;
	}
	else {
		if (pos == 0) {	
			while (node->next != this->headPointer)
			{
				node = node->next;
			}
			
			Node<T> *delNode = this->headPointer;
			this->headPointer = delNode->next;
			node->next = this->headPointer;
			
			delNode->next = nullptr;
			delete delNode;
		}
		else {
			for (int nodePos = 0; nodePos < pos - 1; ++nodePos)
			{
				node = node->next;
			}
			
			Node<T> *delNode = node->next;
			
			node->next = delNode->next;
			delNode->next = nullptr;
			delete delNode;
		}
	}
	
	this->decreaseElementCount();
}

template<typename T>
void CircularLinkedList<T>::clear() {
	while(this->size())
	{
		remove(0);
	}
}

template<typename T>
void CircularLinkedList<T>::print() {
	Node<T> *node = this->headPointer;

	for(int i = 0; i < this->size(); ++i){
		std::cout << i << " : " << node->data << std::endl;
		node = node->next;	
	}
}

template<typename T>
T CircularLinkedList<T>::operator[](int i) {
	
}


/*
	int main() {
		CircularLinkedList<int> a;

		a.insert(0, 123);
		a.insert(0, 13);
		a.insert(0, 1);
		a.insert(1, 2);
		a.insert(3, 1212312);

		a.print();
		std::cout << "Element Count: " << a.size() << std::endl;
		std::cout << "===============" << std::endl;

		a.remove(1);
		a.remove(0);
		a.remove(2);

		a.print();
		std::cout << "Element Count: " << a.size() << std::endl;
		std::cout << "===============" << std::endl;

		a.clear();

		std::cout << "[*] Clear" << std::endl;
		std::cout << "Element Count: " << a.size() << std::endl;

	}

	# Output
	0 : 1
	1 : 2
	2 : 13
	3 : 1212312
	4 : 123
	Element Count: 5
	===============
	0 : 13
	1 : 1212312
	Element Count: 2
	===============
	[*] Clear
	Element Count: 0
*/

#endif