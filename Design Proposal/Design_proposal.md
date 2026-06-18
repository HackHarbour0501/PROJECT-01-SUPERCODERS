# Project 1 Design Proposal 

##  Project Objective:- 
This project is to create an implementation of three data structures in c++ without using the standard libraries.The data structures are:
Dynamic Array
Linked List 
Hash Maps
We will then implement this data structures in redis lite and further use them for the different projects.
The objective of this project is to understand how memory actually works in the syste

##  Section 1- Public API 
- **Dynamic Arrays** :

| Methods          | Parameters | Return Type |
|------------------|----------|---------------|
| DynamicArray()   |   --     | Constructor  |
| ~DynamicArray()  |   --     | Destructor    |
|DynamicArray(const|  other   | Constructor  |
|  DynamicArray&)  |          |               |
| operator=()      | other         | Dynamic Array&  |
| append()  | const T& value   |  void  |
| insert()           | int index,const T& value   | bool  |
| operator[]   | int index   | T&   |
| set()          | int index,const T& value   | bool   |
| capacity()   | --  | int   |
| clear()           | --  | void   |
| size()          | --  | int  |

- **LinkedList**

| Method | Parameters | Return Type |
|----------|------------|-------------|
|linkedList() | -- | Constructor | 
| ~LinkedList()|-- | Destructor | 
| LinkedList(const LinkedList&) | other | Constructor |
| operator=() | other | LinkedList& |
| pushFront() | const T& value | void | 
| insert() | int pos, const T& value | bool | 
| remove() | const T& value | bool | 
| find() | const T& value | int |
| get()| int pos | T& | 
| size() | --| int | 
| clear() | -- | void|

- **Hash Map**

| Method | Parameters | Return Type |
|----------|------------|-------------|
| HashMap() | — | Constructor |
|~HashMap() | — | Destructor |
|HashMap(const HashMap&) | other | Constructor |
| operator=() | other | HashMap& |
|put() | const Key& , const Value& | void |
| remove() | const T& value | bool | 
| contains() | const Key& | bool |  
| get() | const Key& | Value*| 
| size() | — | int | 
| clear() | — | void | 

Justification: The hashmap api differs fron the list based containers because the structure stores key-value pairs instead of indexed data. The operations listed are therefore key oriented such as get,put,remove,contains instead of position oriented such as remove at,insert etc.

### Section 2- Internal representation
 **Memory Ownership**
   - Each container owns its allocated memory.

   - Constructors allocate memory.
   - Destructors release memory.

   - Copy constructor and assignment operator perform deep copies.

   - This prevents memory leaks, dangling pointers and double free errors.
## Section 3- Complexity Analysis

  | Operation | Best|Average|Worst | Space |
  |------------|-----|-------|-------|-------|
  | DynamicArray get | O(1)|O(1)|O(1) | O(1) |
  | DynamicArray append | O(1)|O(1)*|O(n) | O(1) |
  | DynamicArray insert | O(1)|O(n)|O(n) | O(1) |
  |LinkedList pushFront | O(1)|O(1)|O(1)|O(1) |
  | LinkedList insert | O(1)|O(n)|O(n) | O(1) | **
  | LinkedList remove | O(1)|O(n)|O(n) | O(1) | **
  | LinkedList find | O(1)|O(n)|O(n) | O(1) |
  | HashMap put | O(1)|O(1)|O(n) | O(1) |
  | HashMap get | O(1)|O(1)|O(n) | O(1) |
  | HashMap remove | O(1)|O(1)|O(n) | O(1) |

*Append is amortized O(1) because resizing occurs infrequently. Rehashing causes occasional O(n) operations but maintains constant average performance.
** insertion/removal at the head position takes the O(1) further in all other cases it takes O(n)

## Section 4- Design Decisions
In this given section l have selected some of the proposals and also listed the alternatives and reasons to reject them from my project.

### Decision 1- Dynamic Array Growth Stategy 
- Selected: Increase the growth capacity by 2x. Why? Doubling the capacity reduces the total number of reallocations to O(log n),
allowing append operations to achieve amortized O(1) complexity.
- Alternative: Growth by 1.5x, Growth by fixed no. of blocks. Why to reject? Because in 1.5x we will be having the fewer memory overhead but the reallocations will be more which will not let it optimize 
- Optimization Technique: Shrinking the capacity of the array. When the size of the array will be 25% of the capacity we will shrink the capacity by 50% which helps in efficient memory usage.

### Decision 2- Linked List Structure
- Selected: Singly Linked list: Why? I have selected this because it takes less memory and Insertion and deletion at the head are O(1). Operations at arbitrary positions require traversal and therefore take O(n).
- Alternative: Doubly Linked list: Why to reject? It takes almost 100% more memory head to store the previous pointers. 

### Decision 3- HashMap Collision Resolution Technique
- Selected: Seperate Chaining: Why? In this each bucket stores a seperate linked list which helps in better rehashing and also makes the performance constant under moderate collisions.
- Alternative: 1.Linear Probing: Why to reject? In this i creates a primary clusters in the table whichc reduces the performance as the table tends to get filled.
               2.Double Hashing: Why to reject? In this multiple hash functions increases the complexity in the implementation.
### Decision 4- Rehashing Strategy
- Selected: Rehasing to be done when the load factor >= 0.75 Why? It prevents the excessive collision chains.
- Alternative: Rehash at 50%- It wastes the memory but also provides good performance.
               Rehash at 100%- It increses the collisions occurence before the expansions happens.
### Decision 5- Copy Semantics
- Selected: Deep Copy: Why? the deep copy creates the copy of the given structure which recives it own memory allocations
- Alternative: Shallow Copy: It cannot be used because it creates a copy of the constructor but points to the same memory location whenever any changes will happen to the new constructuor it will be reflected to the original one also.
### Decision 6- Redis Lite Storage
- Selected: Hash map: why? it supports O(1) SET, GET,DEL operations and are easily scalable for the large datasets.
- Alternative: Dynamic Array: it takes O(n) for the same operations 
               Linked list: for all the lookups it needs traversal which agin takes O(n) time complexity.
## Summary
The proposed design sastisfies the project requirements and providing the foundation for the future enhancements. Many alternatives were not considered during the design process. The final choices majorly focuses on simplicity,Maintainablity and performance. The functions such as Seperate Chianing dynamic resizing and deep copy semantics hels in making the library reliable.