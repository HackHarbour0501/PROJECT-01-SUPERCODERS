- Date 24 June 2026 (Session 4)
Duration- 3 hours
Goal():
The objective of this session is to design and implement the generic hashmap from scratch wiithout using any STL containers. The hashmap is been built upon the Dynamic array and the linked list which have been built in the earlier session.

What I tried():
1. Created a hash.hpp header file:
This file  contains the implementation of the defaulthasher and also added hashhin for the string float integral types etc.
2. Designed Hashmap Template:
i have designed the hashmap template which is been given below as 
template<
    typename Key,
    typename Value,
    typename Hasher = DefaultHasher<Key>
>
class HashMap;
3. Implemented core operations such as Constructor(),insert(),contains(),at(),erase() etc.

4. Added the rehashing logic for the same whenever the loadfactor hits 0.75
5. Also added some exceptions whenver the requested key do no texist such as key out of range etc.
6. Tested the basic working of the hash functions.

Problems():
Error 1:
In file included from main.cpp:3:0:
HashMap.hpp: In instantiation of 'HashMap<Key, Value, Hasher>::HashMap(size_t) [with Key = int; Value = std::__cxx11::basic_string<char>; Hasher = DefaultHasher<int, void>; size_t = unsigned int]':
main.cpp:16:26:   required from here
HashMap.hpp:88:21: error: 'class DynamicArray<LinkedList<HashMap<int, std::__cxx11::basic_string<char> >::Entry> >' has no member named 'push_back'; did you mean 'pop_back'?
             buckets.push_back(LinkedList<Entry>());
             ~~~~~~~~^~~~~~~~~
HashMap.hpp: In instantiation of 'void HashMap<Key, Value, Hasher>::insert(const Key&, const Value&) [with Key = int; Value = std::__cxx11::basic_string<char>; Hasher = DefaultHasher<int, void>]':
main.cpp:27:24:   required from here
HashMap.hpp:121:24: error: 'class LinkedList<HashMap<int, std::__cxx11::basic_string<char> >::Entry>' has no member named 'push_back'
         buckets[index].push_back(Entry(key,value));
         ~~~~~~~~~~~~~~~^~~~~~~~~
HashMap.hpp: In instantiation of 'void HashMap<Key, Value, Hasher>::rehash(size_t) [with Key = int; Value = std::__cxx11::basic_string<char>; Hasher = DefaultHasher<int, void>; size_t = unsigned int]':
HashMap.hpp:104:19:   required from 'void HashMap<Key, Value, Hasher>::insert(const Key&, const Value&) [with Key = int; Value = std::__cxx11::basic_string<char>; Hasher = DefaultHasher<int, void>]'
main.cpp:27:24:   required from here
HashMap.hpp:57:24: error: 'class DynamicArray<LinkedList<HashMap<int, std::__cxx11::basic_string<char> >::Entry> >' has no member named 'push_back'; did you mean 'pop_back'?
             newBuckets.push_back(LinkedList<Entry>());
             ~~~~~~~~~~~^~~~~~~~~
HashMap.hpp:69:35: error: 'class LinkedList<HashMap<int, std::__cxx11::basic_string<char> >::Entry>' has no member named 'push_back'
                 newBuckets[index].push_back(entry);
                 ~~~~~~~~~~~~~~~~~~^~~~~~~~~

I have added the functions such as pushback which have not been declared in the linked list. I have gone to the linked list checked forthe metrods updated the pushback with append and insertback operation.
In case of Dynamic array also the same case has happened and therefore did the same and updated in dynamic array too.

BuG 2:
Code duplication during Contains(),at(),insert() all performed the mannual traversal which made large amount of the suplicated traversal logic. 
I have solved this problem by createing a findif() function which helps in reusing the implementation from the linked list 
 
Valgrind Report for the memory leak:

annmol@LAPTOP-B59SBVHT:/mnt/d/GITN/PROJECT-01-SUPERCODERS/src$ valgrind --leak-check=full ./main.cpp
==495== Memcheck, a memory error detector
==495== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==495== Using Valgrind-3.26.0 and LibVEX; rerun with -h for copyright info
==495== Command: ./main.cpp
==495==
: not found 4:
./main.cpp: 5: using: not found
: not found 5:
: not found 6:
./main.cpp: 7: Syntax error: "(" unexpected
==495==
==495== HEAP SUMMARY:
==495==     in use at exit: 1,042 bytes in 32 blocks
==495==   total heap usage: 46 allocs, 14 frees, 6,226 bytes allocated
==495==
==495== LEAK SUMMARY:
==495==    definitely lost: 0 bytes in 0 blocks
==495==    indirectly lost: 0 bytes in 0 blocks
==495==      possibly lost: 0 bytes in 0 blocks
==495==    still reachable: 1,042 bytes in 32 blocks
==495==         suppressed: 0 bytes in 0 blocks
==495== Reachable blocks (those to which a pointer was found) are not shown.
==495== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==495==
==495== For lists of detected and suppressed errors, rerun with: -s
==495== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Outcome():
Implemented the hash function and hashmap now moving to the next session for the redislite implementation.