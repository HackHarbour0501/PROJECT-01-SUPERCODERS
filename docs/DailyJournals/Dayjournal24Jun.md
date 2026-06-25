# Daily Development Journal

**Date:** 24 June 2026

## What I Worked On Today

Today I started implementing a generic `HashMap<Key, Value>` from scratch. The goal was to build a fully custom hash table without using STL containers and to understand how key-value storage actually works internally.

Before starting, I knew that a hash map provides fast lookups, insertions, and deletions. However, while designing it, I realized that most of the complexity comes from collision handling, hashing different data types, resizing buckets, and maintaining performance as the map grows.

Since I already completed `DynamicArray<T>` and `LinkedList<T>`, I decided to use them as building blocks for the HashMap implementation.

---

## Work Completed

### Initial HashMap Design

Designed:

* Generic `HashMap<Key, Value>`
* Bucket array architecture
* Node structure for key-value pairs
* Collision handling using Separate Chaining
* Basic hash function framework
* Insert operation planning
* Find operation planning
* Remove operation planning
* Load factor calculation design

---

## Overall Architecture

Current design:

```cpp
HashMap<Key, Value>
```

contains:

```cpp
Bucket Array
       ↓

+-----+-----+-----+-----+-----+
|  *  |  *  |NULL |  *  |NULL |
+-----+-----+-----+-----+-----+
```

Each bucket stores a linked list.

Example:

```text
Bucket[0]
 ↓
("John",10) -> ("Mike",20)

Bucket[1]
 ↓
("Alex",30)

Bucket[2]
 ↓
NULL
```

---

## Understanding Hashing

A hash function converts a key into an array index.

Example:

```cpp
hash("John")
```

returns:

```text
173829
```

Then:

```cpp
index = hash % bucketCount
```

Suppose:

```text
bucketCount = 10
```

Then:

```text
173829 % 10 = 9
```

Store data in:

```text
Bucket[9]
```

Visualization:

```text
"John"
   ↓

Hash Function

   ↓

173829

   ↓

173829 % 10

   ↓

Bucket[9]
```

---

## Major Problems Faced

### 1. Supporting Different Key Types

Initially I assumed hashing integers would be enough.

Example:

```cpp
hash(100)
```

Easy.

But then:

```cpp
hash(std::string)
hash(CustomClass)
```

became a problem.

Different types require different hashing logic.

Solution:

Designed a generic Hasher structure:

```cpp
template<typename Key>
struct Hasher;
```

Specializations can be provided for:

```cpp
int
long
std::string
char*
```

and users can create their own hashers.

Example:

```cpp
Hasher<Student>
```

for custom classes.

This makes HashMap extensible.

---

### 2. Collision Handling

Biggest challenge today.

Different keys can generate same bucket index.

Example:

```text
Hash("John") % 10 = 4

Hash("Mike") % 10 = 4
```

Both want Bucket[4].

Without collision handling:

```text
John overwritten by Mike
```

Data loss occurs.

Solution:

Separate Chaining.

Memory:

```text
Bucket[4]
 ↓

("John",10)
      ↓

("Mike",20)
      ↓

("Alex",30)
      ↓

NULL
```

All entries survive.

---

### 3. Bucket Array Design

Initially I considered:

```cpp
Node<Key,Value>* buckets;
```

But this quickly became difficult to manage.

Instead:

```cpp
LinkedList<Entry>* buckets;
```

where:

```cpp
Entry
{
    Key key;
    Value value;
}
```

This made collision handling much cleaner.

Memory layout:

```text
Buckets

+-----+-----+-----+
| LL  | LL  | LL  |
+-----+-----+-----+

Each LL stores Entries
```

---

### 4. Key Comparison

Hash collision handling requires comparing keys.

Example:

```text
Find("John")
```

Hash leads to Bucket[4].

Inside bucket:

```text
("Mike",20)
("John",10)
("Alex",30)
```

Need:

```cpp
entry.key == searchKey
```

to locate correct element.

Realized hashing alone is not enough.

Hash narrows search area.

Equality comparison finds exact key.

---

### 5. Duplicate Keys

Problem:

```cpp
map.insert("John",10);
map.insert("John",50);
```

What should happen?

Options:

```text
Reject duplicate
```

or

```text
Update existing value
```

Decision:

Follow STL-like behavior.

Update existing value.

Result:

```text
Before

John -> 10

After

John -> 50
```

No duplicate entries.

---

### 6. Load Factor Understanding

Learned about load factor today.

Formula:

```cpp
loadFactor = size / bucketCount
```

Example:

```text
size = 8
bucketCount = 10

loadFactor = 0.8
```

As load factor increases:

```text
More collisions
↓
Longer linked lists
↓
Slower lookups
```

Visualization:

Good:

```text
Bucket0 -> A

Bucket1 -> B

Bucket2 -> C
```

Bad:

```text
Bucket0

A -> B -> C -> D -> E -> F
```

Performance drops significantly.

---

### 7. Rehashing Design

Once load factor exceeds threshold:

```text
0.75
```

Need larger bucket array.

Example:

```text
Old Buckets = 8

New Buckets = 16
```

Process:

```text
Create new bucket array

Recalculate every hash

Move all entries

Destroy old buckets
```

Diagram:

Before:

```text
8 Buckets

A -> Bucket 2
B -> Bucket 3
C -> Bucket 2
```

After:

```text
16 Buckets

A -> Bucket 10
B -> Bucket 7
C -> Bucket 4
```

Entries may move to completely different buckets.

---

## Internal Memory Picture

After:

```cpp
map.insert("John",100);
map.insert("Mike",200);
map.insert("Alex",300);
```

Memory:

```text
Bucket Array

+-----+-----+-----+-----+-----+
|  *  |NULL |  *  |NULL |  *  |
+-----+-----+-----+-----+-----+

Bucket[0]
 ↓
("John",100)

Bucket[2]
 ↓
("Mike",200)

Bucket[4]
 ↓
("Alex",300)
```

Collision Example:

```text
Bucket[2]
 ↓

("John",100)
      ↓

("Mike",200)
      ↓

("David",300)
      ↓

NULL
```

---

## Concepts Learned Today

* Hash Tables
* Hash Functions
* Key-Value Storage
* Bucket Arrays
* Collision Handling
* Separate Chaining
* Load Factor
* Rehashing
* Generic Programming
* Custom Hashers
* Equality Comparison
* Average O(1) Operations
* Worst Case O(n) Operations

---

## Debugging Exercises Performed

### Bug 1

Forgot modulo operation.

```cpp
index = hashValue;
```

Result:

```text
Array index out of bounds
```

Fixed:

```cpp
index = hashValue % bucketCount;
```

---

### Bug 2

Forgot collision handling.

Result:

```text
Existing data overwritten
```

Fixed using linked lists.

---

### Bug 3

Forgot key comparison.

Result:

```text
Wrong value returned
```

Fixed:

```cpp
entry.key == key
```

check before returning value.

---

### Bug 4

Forgot to update size.

Result:

```text
Load factor calculation wrong
```

Rehash never triggered correctly.

---

### Bug 5

Forgot to delete old bucket array after rehash.

Result:

```text
Memory leak
```

Fixed by releasing old buckets after migration.

---

## Complexity Analysis

### Average Case

```text
Insert  -> O(1)
Find    -> O(1)
Remove  -> O(1)
```

### Worst Case

When all keys collide:

```text
Insert  -> O(n)
Find    -> O(n)
Remove  -> O(n)
```

Essentially behaves like a linked list.

---

## Integration with Previous Data Structures

HashMap is now becoming a combination of everything built so far.

```text
HashMap
    |
    +---- DynamicArray (Buckets)
    |
    +---- LinkedList (Collision Chains)
    |
    +---- Hasher
```

Project hierarchy:

```text
DynamicArray<T>
        ↓

LinkedList<T>
        ↓

HashMap<Key, Value>
```

For the first time, one custom data structure is being built using other custom data structures.

---

## Next Tasks

### High Priority

* Implement insert()
* Implement find()
* Implement remove()
* Implement contains()

### Medium Priority

* Implement operator[]
* Implement rehash()
* Implement clear()

### Future Improvements

* Iterator Support
* Custom Allocator Support
* Move Semantics
* Rule of Five
* STL-like API
* UnorderedMap-level Features

---

## End of Day Notes

Today was mostly about understanding architecture rather than writing large amounts of code. The biggest realization was that a HashMap is not just a big array. It is a combination of hashing, collision handling, bucket management, and careful memory ownership.

The most interesting part was seeing how DynamicArray and LinkedList can now work together to build a much larger data structure. This feels like the first real step toward creating a mini STL from scratch.

Tomorrow I plan to start implementing insertion and lookup operations and verify that collision handling works correctly under heavy testing.
