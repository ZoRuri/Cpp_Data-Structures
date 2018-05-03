#ifndef __SINGLY_LINKED_LIST_HPP
#define __SINGLY_LINKED_LIST_HPP

#include <iostream>
#include "list.hpp"

template <typename T>
class SinglyLinkedList;

template <typename NodeType>
class Node {
	friend class SinglyLinkedList<NodeType>;	// Using firend class for use private variable in SinglyLinkedList class
	private:
		NodeType data;
		Node<NodeType> *next;
};

template <typename T>
class SinglyLinkedList : public List {
	Node<T> *headNode = new Node<T>();
	
	public:
		SinglyLinkedList() {
			headNode->next = nullptr;
		};
	
		void insert(int pos, T data);
		void remove(int pos);
		void push_back(T data);
		void pop_back();
		void clear();
		void print();
	
		T operator[](int i); 
	
		~SinglyLinkedList() {
			while(this->size())
			{
				remove(0);
			}
			delete headNode;
		};
};

template <typename T>
void SinglyLinkedList<T>::insert(int pos, T data) {
	
	Node<T> *node = headNode;

	/* move to pos - 1 */
	for (int nodePos = 0; nodePos < pos; ++nodePos)
	{
		node = node->next;
	}
	
	Node<T> *newNode = new Node<T>;
	
	newNode->next = node->next;
	node->next = newNode;
	
	newNode->data = data;
	
	increaseElementCount();
};

template <typename T>
void SinglyLinkedList<T>::remove(int pos) {
	Node<T> *node = headNode;
	
	/* move to pos - 1 */
	for (int nodePos = 0; nodePos < pos; ++nodePos)
	{
		node = node->next;
	}
	
	Node<T> *delNode = node->next;
	
	node->next = delNode->next;
	delNode->next = nullptr;
	delete delNode;
	
	decreaseElementCount();
};

template <typename T>
void SinglyLinkedList<T>::push_back(T data) {
	
};

template <typename T>
void SinglyLinkedList<T>::pop_back() {
	
};

template <typename T>
void SinglyLinkedList<T>::clear() {
	while(this->size())
	{
		remove(0);
	}
}

template <typename T>
void SinglyLinkedList<T>::print() {
	Node<T> *node = headNode;

	for(int i = 0; i < this->size(); ++i){
		node = node->next;	
		std::cout << i << " : " << node->data << std::endl;
	}
}


template <typename T>
T SinglyLinkedList<T>::operator[](int pos) {
	Node<T> *node = headNode;
	
	/* move to pos */
	for (int nodePos = 0; nodePos <= pos; ++nodePos)
	{
		node = node->next;
	}
	
	return node->data;
}

/*
	int main() {
		SinglyLinkedList<int> a;
		SinglyLinkedList<char> b;

		b.insert(0, 'a');

		a.insert(0, 123);
		a.insert(0, 13);
		a.insert(0, 11223);

		a.remove(1);
		a.print();
		b.print();

		std::cout << a[1] << std::endl;

		std::cout << "[*] Clear" << std::endl;

		a.clear();
		std::cout << "Count: " << a.size() << std::endl;;
	}

	# Output
	0 : 11223
	1 : 123
	0 : a
	123
	[*] Clear
	Count: 0
*/

#endif