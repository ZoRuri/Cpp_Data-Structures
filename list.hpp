#ifndef __LIST_HPP_
#define __LIST_HPP_

#include <iostream>

class List {
	
	public:
		int size() { return this->elementCount; }
	
	protected:
		class Execption {
			
			private:
				int errorCode;	
			
			protected:
				Execption(int ae) : errorCode(ae) {}
			
				void errorReport() {
					switch(this->errorCode)
					{
						case 1:
							std::cout << "" << std::endl;
					}
					
					exit(1);
				}
		};
	
		List() { this->elementCount = 0; }
	
		void increaseElementCount() { ++this->elementCount; }
		void decreaseElementCount() { --this->elementCount; }
			
	private:
		int elementCount;

};

#endif