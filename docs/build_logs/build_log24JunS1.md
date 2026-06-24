-Date:24 Jun 2026 (Session 1)
Duration: 2 Hours 30 mins 
Goal():
Implementation of some functions for the linked list and thouroughly testing them for the memory leaks and its generic implementation.

What I Tried():
Firstly i created the structure for the node then i and then i tried creating the structure and the template implementation for the linked list.
 I have listed all the functions which I will be implementing in the linked list now i will be moving to implement the constructor and destructor.

PROBLEM():
**Error 1**:
In file included from main.cpp:3:0:
LinkedList.hpp: In constructor 'LinkedList<T>::LinkedList()':
LinkedList.hpp:44:1: error: expected '{' before 'template'
 template<typename T>
 ^~~~~~~~
LinkedList.hpp: In instantiation of 'LinkedList<T>::~LinkedList() [with T = int]':
main.cpp:6:21:   required from here
LinkedList.hpp:51:27: error: request for member 'next' in 'current', which is of pointer type 'Node<int>*' (maybe you meant to use '->' ?)
         current = current.next;
                   ~~~~~~~~^~~~
PS D:\GITN\PROJECT-01-SUPERCODERS\src\LinkedList>

This error has occured just because insted of the pointer i used the dot.
I updated the function and test it once again and now it ran sucessfully.

MemoryLeak Report:
annmol@LAPTOP-B59SBVHT:/mnt/d/GITN/PROJECT-01-SUPERCODERS/src/LinkedList$ valgrind --leak-check=full ./main.cpp
==1057== Memcheck, a memory error detector
==1057== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==1057== Using Valgrind-3.26.0 and LibVEX; rerun with -h for copyright info
==1057== Command: ./main.cpp
==1057==
./main.cpp: 2: //: Permission denied
==1058==
==1058== HEAP SUMMARY:
==1058==     in use at exit: 2,296 bytes in 37 blocks
==1058==   total heap usage: 41 allocs, 4 frees, 3,342 bytes allocated
==1058==
==1058== LEAK SUMMARY:
==1058==    definitely lost: 0 bytes in 0 blocks
==1058==    indirectly lost: 0 bytes in 0 blocks
==1058==      possibly lost: 0 bytes in 0 blocks
==1058==    still reachable: 2,296 bytes in 37 blocks
==1058==         suppressed: 0 bytes in 0 blocks
==1058== Reachable blocks (those to which a pointer was found) are not shown.
==1058== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==1058==
==1058== For lists of detected and suppressed errors, rerun with: -s
==1058== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
: not found 4:
./main.cpp: 5: Syntax error: "(" unexpected
==1057==
==1057== HEAP SUMMARY:
==1057==     in use at exit: 1,256 bytes in 34 blocks
==1057==   total heap usage: 42 allocs, 8 frees, 4,360 bytes allocated
==1057==
==1057== LEAK SUMMARY:
==1057==    definitely lost: 0 bytes in 0 blocks
==1057==    indirectly lost: 0 bytes in 0 blocks
==1057==      possibly lost: 0 bytes in 0 blocks
==1057==    still reachable: 1,256 bytes in 34 blocks
==1057==         suppressed: 0 bytes in 0 blocks
==1057== Reachable blocks (those to which a pointer was found) are not shown.
==1057== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==1057==
==1057== For lists of detected and suppressed errors, rerun with: -s
==1057== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Outcome():
Basic implementation of the linked list constructors destructors copy constructor and assignment operator have been completed.
