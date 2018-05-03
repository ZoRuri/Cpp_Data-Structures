#ifndef __STACK_HPP
#define __STACK_HPP

#include <iostream>
#include "stackQueue.hpp"

template <typename T>
class Stack;

template <typename NodeType>
class Node {
	friend class Stack<NodeType>;
	private:
		NodeType data;
		Node<NodeType> *next;
};

template <typename T>
class Stack : public StackQueue {
	public:
		Stack() { 
			this->topNode = nullptr; 
		};
		void push(T data);
		T pop();
		T peek();
	
		void clear() {
			while(!isEmpty())
			{
				Node<T> *node = this->topNode;
				this->topNode = node->next;
	
				node->next = nullptr;

				delete node;	
				decreaseElementCount();
			}
		}
		~Stack() {};

	private:
		Node<T> *topNode;
};

template <typename T>
void Stack<T>::push(T data) {
	Node<T> *newNode = new Node<T>;
	
	newNode->next = this->topNode;
	this->topNode = newNode;
	
	newNode->data = data;
	increaseElementCount();
}

template <typename T>
T Stack<T>::pop() {
	if (isEmpty()) {
		std::cout << "Underflow Error: stack is empty" << std::endl;
		exit(1);
	}
	Node<T> *delNode = this->topNode;
	
	T returnValue = delNode->data;
	this->topNode = delNode->next;
	
	delNode->next = nullptr;

	delete delNode;	
	decreaseElementCount();
	
	return returnValue;
}

template <typename T>
T Stack<T>::peek() {
	return this->topNode->data;
}

/*
	int main() {
		Stack<int> stack;
		stack.push(1);
		stack.push(2);
		stack.push(3);

		std::cout << "peek: " << stack.peek() << std::endl;

		while(!stack.isEmpty())
			std::cout << "pop: " << stack.pop() << std::endl;
	}

	#Output
	peek: 3
	pop: 3
	pop: 2
	pop: 1
*/

#endif