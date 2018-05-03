#ifndef __STACK_QUEUE_HPP
#define __STACK_QUEUE_HPP

class StackQueue {
	public:
		int size() { return this->elementCount; };
		bool isEmpty() { return (this->elementCount == 0) ? true : false; };

	protected:
		StackQueue() { this->elementCount = 0; }
	
		void increaseElementCount() { ++this->elementCount; }
		void decreaseElementCount() { --this->elementCount; }
		
	private:
		int elementCount;
};

#endif