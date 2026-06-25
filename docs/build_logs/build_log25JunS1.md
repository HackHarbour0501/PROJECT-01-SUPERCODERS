Date : 25 June 2026(Session 1)
Duration: 3 Hours 30 Mins
Goal():
Implemention and complete testing of the hashmap in all userdefined objects.

Problem():
My hash map was working nice with the primitives but when it came to the user defined classes and the random objects the hasmap crashed.

Understanding the requirements how to hash for the user defined functions and how to build the logic for the same.

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
This error told me i have used a pushback function in my hashmap but it not been in either dynamic array or linkedlist due to which this error occured i checked on it and changed the methods been called in it.

What I DID():
I tested some basic features such as:
Empty Hashmap 
Basic insertion 
Access values 
updating the existing key etc

Outcome():
Basic Functions and hashmap was succesfully tested for primitive string and float datatypes.
