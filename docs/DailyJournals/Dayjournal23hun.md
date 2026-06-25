# Daily Development Journal

**Date:** 23 June 2026

## What I Worked On Today

Today I focused on implementing a generic `LinkedList<T>` from scratch. The goal was to understand how dynamic node-based data structures work internally and how memory is managed when elements are inserted or removed.

At first it looked much simpler than DynamicArray because there is no resizing logic involved. But while implementing it, I realized that pointer handling, node ownership, and proper cleanup are extremely important.

Most of the time went into understanding node creation, traversal, insertion logic, and preventing memory leaks.

---

## Work Completed

### LinkedList Structure

Implemented:

* Generic `Node<T>` structure
* LinkedList constructor
* LinkedList destructor
* `push_back()`
* `push_front()`
* `pop_back()`
* `pop_front()`
* `clear()`
* `size()`
* `empty()`
* `front()`
* `back()`
* Initial traversal support

---

## Node Design

Created a generic node structure:

```cpp
template<typename T>
struct Node
{
    T data;
    Node<T>* next;
};
```

Each node stores:

* Actual data
* Pointer to next node

Memory representation:

```text
+---------+---------+
|  Data   |  Next   |
+---------+---------+
```

---

## Understanding Linked Structure

Example:

```cpp
list.push_back(10);
list.push_back(20);
list.push_back(30);
```

Memory:

```text
head
 ↓

+----+------+    +----+------+    +----+------+
| 10 |  *---|--->| 20 |  *---|--->| 30 | NULL |
+----+------+    +----+------+    +----+------+

                                          ↑
                                         tail
```

Unlike DynamicArray:

```text
DynamicArray
[10][20][30]
```

LinkedList elements can live anywhere in memory.

```text
Node 1 -> Address 1000
Node 2 -> Address 5000
Node 3 -> Address 2000
```

Connections are maintained through pointers.

---

## Major Problems Faced

### 1. Losing Nodes During Insertion

Initially while inserting nodes I accidentally overwrote pointers.

Example:

```cpp
newNode->next = head;
head = newNode;
```

If done incorrectly:

```cpp
head = newNode;
```

before saving old head,

the old list becomes inaccessible.

Example:

Before:

```text
head
 ↓

10 -> 20 -> 30
```

Wrong update:

```text
head
 ↓

40

10 -> 20 -> 30
```

Now nodes:

```text
10 -> 20 -> 30
```

are leaked forever.

Lesson learned:

Always preserve existing links before modifying pointers.

---

### 2. Traversing the List

To access elements I needed to move node by node.

Used:

```cpp
Node<T>* current = head;
```

Then:

```cpp
while(current)
{
    current = current->next;
}
```

Visualization:

```text
head
 ↓

10 -> 20 -> 30 -> NULL
 ↑
current
```

After one iteration:

```text
10 -> 20 -> 30 -> NULL
       ↑
    current
```

Understanding traversal made almost every operation easier.

---

### 3. pop_front() Memory Leak

Initially:

```cpp
head = head->next;
```

worked logically.

But old node memory was never released.

Example:

Before:

```text
head
 ↓

10 -> 20 -> 30
```

After update:

```text
20 -> 30
```

Node containing 10 still exists somewhere in memory.

Memory leak.

Fixed using:

```cpp
Node<T>* temp = head;
head = head->next;
delete temp;
```

Now memory is properly reclaimed.

---

### 4. Handling Empty Lists

Several functions crashed when list was empty.

Example:

```cpp
head->data
```

when:

```text
head = nullptr
```

caused invalid access.

Added checks:

```cpp
if(head == nullptr)
```

before operations.

Also added exceptions where required.

---

### 5. Implementing pop_back()

This turned out to be harder than expected.

For:

```text
10 -> 20 -> 30
```

to remove 30:

Need access to node 20.

Problem:

Singly Linked List only knows next node.

Cannot move backwards.

Traversal required:

```text
10 -> 20 -> 30
       ↑
 previous node needed
```

Solution:

Traverse until:

```cpp
current->next == tail
```

Then update:

```cpp
tail = current;
tail->next = nullptr;
```

Finally delete old tail.

---

### 6. Destructor Design

Biggest concern:

Every node is allocated individually.

Example:

```text
Node A
Node B
Node C
Node D
```

If destructor only deletes head:

```cpp
delete head;
```

Remaining nodes leak.

Needed full traversal:

```cpp
while(head)
{
    Node<T>* temp = head;
    head = head->next;
    delete temp;
}
```

Memory cleanup process:

```text
10 -> 20 -> 30 -> 40

Delete 10
Delete 20
Delete 30
Delete 40
```

All nodes released safely.

---

## Concepts Learned Today

* Dynamic node allocation
* Pointer ownership
* Singly linked list architecture
* Traversal techniques
* Head pointer management
* Tail pointer management
* Memory leaks
* Node deletion
* Exception handling
* List destruction
* Difference between contiguous and non-contiguous storage
* Importance of preserving links before pointer updates

---

## Internal Memory Picture

After:

```cpp
list.push_back(100);
list.push_back(200);
list.push_back(300);
```

Memory:

```text
size = 3

head
 ↓

+-----+------+    +-----+------+    +-----+------+
| 100 |  *---|--->| 200 |  *---|--->| 300 | NULL |
+-----+------+    +-----+------+    +-----+------+

                                             ↑
                                            tail
```

Addresses may look like:

```text
Node 100 -> 0x1000
Node 200 -> 0x5000
Node 300 -> 0x3000
```

Nodes are not stored together.

Pointers connect them.

---

## Debugging Exercises Performed

Tested:

* Insert at beginning
* Insert at end
* Multiple insertions
* Single node list
* Empty list operations
* Repeated pop_front()
* Repeated pop_back()
* Destructor cleanup
* Traversal correctness

Created intentional bugs:

### Bug 1

Forgot:

```cpp
delete temp;
```

Result:

Memory leak.

---

### Bug 2

Forgot:

```cpp
tail = nullptr;
```

after deleting last node.

Result:

Dangling pointer.

---

### Bug 3

Used:

```cpp
head->next
```

without checking:

```cpp
head == nullptr
```

Result:

Segmentation fault.

---

## Comparison With DynamicArray

### DynamicArray

Pros:

* Fast indexing O(1)
* Cache friendly
* Contiguous memory

Cons:

* Resizing cost
* Expensive middle insertions

---

### LinkedList

Pros:

* Easy insertions
* No resizing
* Flexible memory usage

Cons:

* No random access
* Extra memory for pointers
* Poor cache locality

---

## Next Tasks

### High Priority

* Implement find()
* Implement findIf()
* Implement insert(index)
* Implement remove(index)

### Medium Priority

* Copy Constructor
* Copy Assignment Operator

### Future Improvements

* Iterator Support
* Reverse Function
* Doubly Linked List Version
* STL-like Interface
* Rule of Three Compliance

---

## End of Day Notes

Today helped me understand pointers much better than before. The biggest lesson was that linked lists are less about storing data and more about maintaining connections between nodes. A single wrong pointer update can disconnect an entire chain of nodes and create memory leaks.

The most challenging part was implementing deletion operations correctly while keeping head and tail valid. By the end of the day I was comfortable with node creation, traversal, insertion, and cleanup.

Tomorrow I plan to implement searching operations and start preparing the LinkedList for integration into the HashMap project.
