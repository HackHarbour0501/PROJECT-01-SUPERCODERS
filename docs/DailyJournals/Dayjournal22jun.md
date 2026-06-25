# Daily Development Journal

**Date:** 24 June 2026

## What I Worked On Today

Today I spent most of my time building a generic `DynamicArray<T>` from scratch. The main goal was to understand how dynamic arrays actually work internally instead of relying on STL containers.

Initially I thought implementing a dynamic array would mostly be about resizing memory, but while working on it I realized that handling object construction, destruction, and exception safety is equally important, especially when supporting both primitive and user-defined data types.

---

## Work Completed

### DynamicArray Structure

Implemented:

* Default constructor
* Destructor
* Dynamic memory allocation
* Automatic resizing
* `push_back()`
* `pop_back()`
* Bounds checked `operator[]`
* Helper cleanup functions
* Initial Rule of Three preparation

---

### Resizing Logic

Implemented automatic growth when array becomes full.

Example:

Before resize:

Capacity = 4

```
data
 ↓
+----+----+----+----+
| 10 | 20 | 30 | 40 |
+----+----+----+----+
```

After inserting another element:

Capacity becomes 8

```
newData
 ↓
+----+----+----+----+----+----+----+----+
| 10 | 20 | 30 | 40 | 50 |    |    |    |
+----+----+----+----+----+----+----+----+
```

Old memory gets destroyed and released.

---

## Major Problems Faced

### 1. Using malloc() with Objects

At first I was allocating memory using:

```cpp
malloc(sizeof(T) * capacity);
```

Then I realized this only allocates raw memory.

For primitive types:

```cpp
int
double
char
```

it looks like everything works.

But for classes:

```cpp
std::string
CustomClass
```

constructors never run.

Example memory:

```
malloc()

+----------------------+
| raw bytes only       |
| no constructor call  |
+----------------------+
```

Solution:

Used Placement New:

```cpp
new (&data[i]) T(value);
```

Now object construction happens correctly.

```
Raw Memory
     ↓

+---------+
| bytes   |
+---------+

Placement New

new (&data[0]) T(value);

+----------------+
| Constructed T  |
+----------------+
```

This was probably the biggest thing I learned today.

---

### 2. Exception Safety During Construction

Suppose we are copying elements into a newly allocated block.

```
Construct element 0 ✓
Construct element 1 ✓
Construct element 2 ✗ throws exception
```

Without cleanup:

```
Memory Leak
```

Already constructed objects remain alive.

To fix this I added:

```cpp
try
{
   ...
}
catch(...)
{
   ...
}
```

and manually destroyed successfully created objects before releasing memory.

Memory view:

Before failure:

```
+-----+-----+-----+
| Obj | Obj | ??? |
+-----+-----+-----+
```

After cleanup:

```
All constructed objects destroyed
Memory released
```

---

### 3. Destructor Handling

Another thing I learned:

Not every type needs destructor calls.

Example:

```cpp
int
double
char
```

No cleanup required.

But:

```cpp
std::string
std::vector
CustomClass
```

need destructor execution.

Used:

```cpp
if constexpr(std::is_trivially_destructible_v<T>)
```

to decide at compile time.

Flow:

```
           Type T
              |
              v

 Is trivially destructible?

      /        \
    Yes        No
     |          |
 Skip dtor   Call dtor
```

This avoids unnecessary work for primitive types.

---

### 4. Safe Array Access

Initially:

```cpp
arr[index]
```

could access invalid memory.

Example:

Array Size = 5

Valid:

```
0 1 2 3 4
```

Invalid:

```
5
6
100
```

Added:

```cpp
throw std::out_of_range(...)
```

Now invalid access is detected immediately.

---

### 5. pop_back() Edge Case

Found another issue:

```cpp
DynamicArray<int> arr;
arr.pop_back();
```

Size was already 0.

Without checks:

```
size becomes -1
undefined behaviour
```

Added:

```cpp
throw std::underflow_error(...)
```

Now empty removals are prevented.

---

### 6. Extra Copies During Insertion

Originally:

```cpp
push_back(T value);
```

Flow:

```
Object
  ↓
Copy #1 into parameter
  ↓
Copy #2 into array
```

Too many copies.

Changed to:

```cpp
push_back(const T& value);
```

Now:

```
Object
  ↓
Reference
  ↓
Single construction in array
```

Much better.

---

## Concepts I Understood Better Today

* Placement New
* Raw memory vs constructed objects
* Object lifetime
* Manual destruction
* Exception safety
* Deep copy
* Shallow copy
* Rule of Three
* `std::bad_alloc`
* `std::out_of_range`
* `std::underflow_error`
* `if constexpr`
* `std::is_trivially_destructible_v<T>`
* Difference between memory release and object destruction

---

## Internal Memory Picture of Current DynamicArray

Example:

```cpp
DynamicArray<int> arr;

arr.push_back(10);
arr.push_back(20);
arr.push_back(30);
```

Memory:

```
size = 3
capacity = 4

data
 ↓

+----+----+----+----+
| 10 | 20 | 30 | ?? |
+----+----+----+----+
```

After another insertion:

```cpp
arr.push_back(40);
arr.push_back(50);
```

Resize occurs:

```
Old Capacity = 4
New Capacity = 8
```

```
+----+----+----+----+----+----+----+----+
| 10 | 20 | 30 | 40 | 50 |    |    |    |
+----+----+----+----+----+----+----+----+
```

---

## Next Tasks

### High Priority

* Complete Copy Constructor
* Complete Copy Assignment Operator
* Verify Deep Copy Logic

### Medium Priority

* Implement insert(index, value)
* Implement remove(index)
* Implement clear()

### Future Improvements

* Move Constructor
* Move Assignment Operator
* Iterator Support
* Emplace Functions
* STL-like Interface
* Full Rule of Five

---

## End of Day Notes

Today was one of the most educational days so far in this project. I started with the idea of simply creating a resizable array, but ended up learning much more about memory management, object lifetime, constructors, destructors, and exception safety.

The biggest takeaway is that allocating memory and creating objects are two completely different operations. Understanding that distinction made placement new, manual destruction, and exception-safe cleanup finally make sense.

Tomorrow I plan to finish the copy constructor and copy assignment operator so the DynamicArray follows the Rule of Three properly.
