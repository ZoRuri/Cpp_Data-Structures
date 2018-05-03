#include <iostream>
#include <chrono>

#include "stack.hpp"

int moved = 0;

void move(int count, std::string from, std::string to) {
	//std::cout << ++moved << " Moved | " << count  << " Disk: "   << from << " -> " << to << std::endl;
    return;
}


//--------------------------------------------------------------------
/* For understanding tower of hanoi algorithm before implementation */
//--------------------------------------------------------------------

// * Recursion progress

// moveTower_1 -> moveTower_2 -> moveTower_3
//                            -> moveTower_3
//             -> moveTower_2 -> moveTower_3
//                            -> moveTower_3

/* Move 1 Disk From -> To */
void moveTower_3(int count, std::string from, std::string temp, std::string to) {
	move(count, from, to);	// Just move From -> To
}

/* Move 2 Disks From -> To */
void moveTower_2(int count, std::string from, std::string temp, std::string to) {
	moveTower_3(count - 1, from, to, temp);	// Move From(left) -> Temp(middle) that except last Disk 
	
	move(count, from, to);					// Move From(left) -> to(right) last Disk
	
	moveTower_3(count - 1, temp, from, to);	// Move Temp(middle) -> to(right) remaining(1) Disk 
}

/* Move 3 Disks From -> To */
void moveTower_1(int count, std::string from, std::string temp, std::string to) {
	moveTower_2(count - 1, from, to, temp); // Move From(left) -> Temp(middle) that except last Disk 
	
	move(count, from, to);					// Move From(left) -> to(right)	last Disk
	
	moveTower_2(count - 1, temp, from, to);	// Move Temp(middle) -> to(right) remaining(2) Disks 
}

void towerOfHanoi_Understand(int count, std::string from, std::string temp, std::string to) {
	moveTower_1(count, from, temp, to);
}

//--------------------------------------------------------------------

/* implament using recursion */
void towerOfHanoi(int count, std::string from, std::string temp, std::string to) {
	
	if ( count == 1 ) {
		move(count, from, to);
		return ;
	}
	
	towerOfHanoi(count - 1, from, to, temp);
	move(count, from, to);
	towerOfHanoi(count - 1, temp, from, to);
}

/* implament using none recursion */
void none_recursion_towerOfHanoi(int count, std::string from, std::string temp, std::string to) {
	Stack<std::string> stack;
    Stack<int> cntStack;
   
    while(1) 
    {
        while ( 1 < count )
        {
            stack.push( to );
            stack.push( temp );
            stack.push( from );

            cntStack.push(count);

            --count;

            stack.push( to );
            to = temp;
            temp = stack.pop();
        }

        move(count, from, to);

        if(!stack.isEmpty())
        {
            from = stack.pop();
            temp = stack.pop();
            to = stack.pop();
            count = cntStack.pop();

            move(count, from, to);
            --count;

            stack.push( from );
            from = temp;
            temp = stack.pop();
        }
        else
            break;
        
    }
    

}

int main() {

    
	//towerOfHanoi_Understand(3, "left", "middle", "right");
	moved = 0;
    
    std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();
	towerOfHanoi(25, "left", "middle", "right");
    std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();
    std::chrono::duration<double> recursion = EndTime - StartTime;
    std::chrono::milliseconds mill1 = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime);
	moved = 0;
    
    StartTime = std::chrono::system_clock::now();
	none_recursion_towerOfHanoi(25, "left", "middle", "right");
    EndTime = std::chrono::system_clock::now();
    
    std::chrono::duration<double> DefaultSec = EndTime - StartTime;
    std::chrono::milliseconds mill2  = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime);
    
    std::cout << "recursion: " << mill1.count() << std::endl;
    std::cout << "loop: " << mill2.count() << std::endl;
	
}