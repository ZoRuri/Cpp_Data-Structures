#ifndef __DEQUE_HPP
#define __DEQUE_HPP

#include <iostream>
#include "stackQueue.hpp"

template <typename T>
class Deque;

template <typename NodeType>
class Node {
	public:
		friend class Deque<NodeType>;
	private:
		NodeType data;
		Node<NodeType> *next;
		Node<NodeType> *prev;
};

/* Double-Ended queue */
template <typename T>
class Deque : public StackQueue {
	public:
		class iterator {
			public:
				typedef T	value_type;
				typedef T&	reference;
				typedef T*	pointer;
			
				typedef std::forward_iterator_tag iterator_category;
				typedef std::ptrdiff_t difference_type;
			
				/* internal class & default constructor */
				iterator(Node<T> *ptr = nullptr) : currentNode(ptr) { }
				
				/* operator overloading */
				iterator& operator++() { 
					currentNode = currentNode->prev; 
					return *this; 
				}
			
				iterator operator++(int) { 
					iterator tmp( *this ); 
					++currentNode; 
					return tmp; 
				}
			
				reference operator*() { return currentNode->data; }
				//pointer operator->() { return _ptr; }
			
				bool operator==(const iterator& rhs) { return currentNode == rhs.currentNode; }
				bool operator!=(const iterator& rhs) { return currentNode != rhs.currentNode; }
			
			private:
				Node<T>* currentNode;
		};
		
		iterator begin() {
			return iterator(this->frontNode);
		}
	
		iterator end() {
			return iterator(nullptr);
		}
	
		Deque() {
			this->frontNode = nullptr;
			this->rearNode = nullptr;
		};
		void push_front(T data);
		T pop_front();
		void push_back(T data);
		T pop_back();
		void print();
		~Deque() {};
	
	private:
		Node<T> *frontNode;
		Node<T> *rearNode;
};

template <typename T>
void Deque<T>::push_front(T data) {
	Node<T> *newNode = new Node<T>;
	
	newNode->next = nullptr;
	newNode->prev = nullptr;
	
	if (isEmpty()) {
		this->frontNode = newNode;
		this->rearNode = newNode;
	}
	else {
		Node<T>	*frontNode = this->frontNode;
		
		frontNode->next = newNode;
		newNode->prev = frontNode;
		newNode->next = nullptr;
		
		this->frontNode = newNode;
	}
	
	newNode->data = data;
	increaseElementCount();
}

template <typename T>
void Deque<T>::push_back(T data) {
	Node<T> *newNode = new Node<T>;
	
	newNode->next = nullptr;
	newNode->prev = nullptr;
	
	if (isEmpty()) {
		this->frontNode = newNode;
		this->rearNode = newNode;
	}
	else {
		Node<T> *rearNode = this->rearNode;
		
		rearNode->prev = newNode;
		newNode->next = rearNode;
		newNode->prev = nullptr;
		
		this->rearNode = newNode;
	}
	
	newNode->data = data;
	increaseElementCount();
}

template <typename T>
T Deque<T>::pop_front() {
	if(isEmpty()) {
		std::cout << "Underflow Error: deque is empty" << std::endl;
		exit(1);
	}
	
	Node<T> *delNode = this->frontNode;	
	T returnValue = delNode->data;
	
	if(size() == 1) {
		delNode->prev = nullptr;
		this->frontNode = nullptr;
		this->rearNode = nullptr;
	}
	else {
		delNode->prev->next = nullptr;
		this->frontNode = delNode->prev;
		delNode->prev = nullptr;
	}
	
	delete delNode;
	
	decreaseElementCount();
	return returnValue;
}

template <typename T>
T Deque<T>::pop_back() {
	if (isEmpty()) {
		std::cout << "Underflow Error: deque is empty" << std::endl;
		exit(1);
	}
	
	Node<T> *delNode = this->rearNode;	
	T returnValue = delNode->data;
	
	if(size() == 1) {
		delNode->next = nullptr;
		this->frontNode = nullptr;
		this->rearNode = nullptr;
	}
	else {
		delNode->next->prev = nullptr;
		this->rearNode = delNode->next;
		delNode->next = nullptr;
	}
	
	delete delNode;
	
	decreaseElementCount();
	return returnValue;
}

template <typename T>
void Deque<T>::print() {
	std::cout << "Front <-> ";
	
	for(auto i = this->begin(); i != this->end(); ++i)
	{
		std::cout << *i << " <-> ";
	}
	
	std::cout << " Rear" << std::endl;
}

int main() {
	Deque<int> deque;
	
	deque.push_front(1);
	deque.print();
	deque.push_back(4);
	deque.print();
	deque.push_front(3);
	deque.print();
	deque.push_back(2);
	deque.print();
	deque.pop_front();
	deque.print();
	deque.pop_back();
	deque.print();
	deque.push_front(20);	
	deque.push_back(40);
	deque.push_back(50);
	deque.print();
}

#endif