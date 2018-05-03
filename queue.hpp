#ifndef __QUEUE_HPP
#define __QUEUE_HPP

#include <iostream>
#include "stackQueue.hpp"

template <typename T>
class Queue;

template <typename NodeType>
class Node {
	friend class Queue<NodeType>;
	private:
		NodeType data;
		Node<NodeType> *next;
};

template <typename T>
class Queue : public StackQueue {
	public:
		Queue(){ 
			this->frontNode = nullptr;
			this->rearNode = nullptr;
		};
		
		void enqueue(T data);
		T dequeue();
		T peek() {return this->frontNode->data; };	
	
		void clear() 
		{
			while(!isEmpty())
			{
				Node<T> *delNode = this->frontNode;

				this->frontNode = delNode->next;
				delNode->next = nullptr;
				delete delNode;

				decreaseElementCount();

				if (isEmpty()) {
					this->rearNode = nullptr;
					this->frontNode = nullptr;
				}
			}
		}
	
		~Queue(){ };
	
	private:
		Node<T> *frontNode;
		Node<T> *rearNode;
};


// Output << Front::Rear << input
template <typename T>
void Queue<T>::enqueue(T data) {
	Node<T> *newNode = new Node<T>;
	
	/* First element */
	if (size() == 0) {
		this->frontNode = newNode;
		this->rearNode = newNode;
	}
	else {
		this->rearNode->next = newNode;
		this->rearNode = newNode;
	}
	
	newNode->data = data;
	increaseElementCount();
}

template <typename T>
T Queue<T>::dequeue() {
	if (isEmpty()) {
		std::cout << "Underflow Error: queue is empty" << std::endl;
		exit(1);
	}
	
	Node<T> *delNode = this->frontNode;
	T returnValue = delNode->data;
	
	this->frontNode = delNode->next;
	delNode->next = nullptr;
	delete delNode;
	
	decreaseElementCount();
	
	if (isEmpty()) {
		this->rearNode = nullptr;
		this->frontNode = nullptr;
	}

	return returnValue;
}

/*
	int main() {
		Queue<int> queue;
		queue.enqueue(1);
		queue.enqueue(1);
		queue.enqueue(3);

		std::cout << "peek: " << queue.peek() << std::endl;

		std::cout << "[*] Clear" << std::endl;
		queue.clear();

		queue.enqueue(2);
		queue.enqueue(2);
		queue.enqueue(3);
		queue.enqueue(5);
		queue.enqueue(4);
		queue.enqueue(1);

		while(!queue.isEmpty())
			std::cout << "dequeue: " << queue.dequeue() << std::endl;
	}

	#Output
	peek: 1
	[*] Clear
	dequeue: 2
	dequeue: 2
	dequeue: 3
	dequeue: 5
	dequeue: 4
	dequeue: 1
*/

#endif
