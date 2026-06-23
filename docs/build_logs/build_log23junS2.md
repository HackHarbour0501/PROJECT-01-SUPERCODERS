
- Date: 23 June 2026 (Session 2)
Duration: 2 Hours 30 mins 
Goal():
Now Implementing the different functions using the malloc()and free in the dynamic array, Understanding the placment new and also researching for use of the string datatype.


Problem():
Error:
main.cpp: In function 'int main()':
main.cpp:6:22: error: 'size_t DynamicArray<int>::size' is private within this context
     std::cout << arr.size();
                      ^~~~
In file included from main.cpp:1:0:
DynamicArray.hpp:11:12: note: declared private here
     size_t size;
            ^~~~
main.cpp:6:27: error: expression cannot be used as a function
     std::cout << arr.size();
                           ^
main.cpp:7:22: error: 'class DynamicArray<int>' has no member named 'empty'
     std::cout << arr.empty();
                      ^~~~~


What I tried:
I reasearched about the error and i found that it was just due to the declaration mistake i have done in the creating to scope to the function. Also i have learnt how can i use the sting datatype in the memory allocations by creating a seperate class for the string datatype.

i have also researched on how the std::vector works. the flowchart is given below

Raw Memory
     ↓
Placement New
     ↓
Object Constructed
     ↓
Destructor
     ↓
Memory Released


Outcome:
Understood about the advantages and disadvantages of using malloc function for the mannual memory allocation.

