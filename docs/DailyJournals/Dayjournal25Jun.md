# Daily Development Journal

**Date:** 25 June 2026

## What I Worked On Today

Today I shifted my focus from the core data structures to making the `HashMap` more generic and usable for real-world objects. Till now, hashing primitive data types like integers and strings was working fine, but the next challenge was supporting user-defined classes.

Along with that, I also started writing the initial structure for **Redis Lite**, where the custom `HashMap` will be used as the primary storage engine.

Most of the day went into understanding how custom hashing works, designing a reusable `combineValue()` helper, and testing whether my `HashMap` could correctly store and retrieve user-defined objects.

---

## Work Completed

### User Defined Hashing

Implemented support for hashing custom objects.

Created a helper function:

```cpp
combineValue(...)
```

which combines multiple field hashes into one final hash value.

Instead of writing an entirely new hash algorithm for every class, each field's hash is generated first and then combined together.

This makes writing custom hashers much cleaner.

---

### Example

Created a sample class:

```cpp
class Student
{
    int rollNo;
    std::string name;
};
```

Hash function:

```cpp
size_t operator()(const Student& s)
{
    size_t hash = 0;

    combineValue(hash, s.rollNo);
    combineValue(hash, s.name);

    return hash;
}
```

Now the entire object can be used directly as a key inside HashMap.

---

## Understanding combineValue()

Initially I thought hashing multiple fields simply meant adding them together.

Example:

```text
roll hash + name hash
```

But this creates many collisions.

Instead, `combineValue()` mixes the existing hash with the new field's hash using bit operations.

Flow:

```text
Current Hash
      │
      ▼

Hash(Field)

      │

Bit Mixing

      │

Updated Hash
```

Every field contributes to the final hash value.

---

## Memory Representation

Student Object

```text
+-------------------------+
| Roll = 101              |
| Name = "Anmol"          |
+-------------------------+
```

Individual hashes

```text
Roll Hash
     │

Name Hash
```

Combined

```text
combineValue()

      │

Final Hash

      │

Bucket Index
```

Finally stored inside HashMap.

---

## Testing User Defined Objects

Created multiple Student objects.

```cpp
Student s1;
Student s2;
Student s3;
```

Inserted them into HashMap.

Memory after insertion:

```text
Bucket Array

+-----+-----+-----+-----+-----+
|  *  |NULL |  *  |NULL |  *  |
+-----+-----+-----+-----+-----+

Bucket[0]

(Student 1)

Bucket[2]

(Student 2)

Bucket[4]

(Student 3)
```

Lookup was also tested.

```cpp
find(student)
```

returned the expected value successfully.

---

## Testing Collision Handling

Created different objects that intentionally produced the same bucket.

Result:

```text
Bucket[3]

Student A
      │
      ▼

Student B
      │
      ▼

Student C
      │
      ▼

NULL
```

The linked list handled collisions correctly.

No existing entries were overwritten.

---

## Redis Lite Implementation

Today I also started the basic implementation of Redis Lite.

Current structure:

```text
RedisLite

      │

HashMap

      │

Key -> Value
```

For now only basic operations are being planned.

Commands under implementation:

```text
SET

GET

DEL

EXISTS
```

Example flow:

```text
SET name Anmol

       │

HashMap.insert()

       │

Stored
```

Later

```text
GET name

       │

HashMap.find()

       │

Returns

Anmol
```

The goal is to make Redis Lite work exactly like a lightweight in-memory key-value database.

---

## Current Architecture

```text
Application

      │

RedisLite

      │

HashMap

      │

LinkedList

      │

DynamicArray
```

Everything built during the previous sessions is finally starting to connect together.

---

## Problems Faced

### 1. Hashing User Defined Objects

Initially only primitive types were supported.

Example:

```cpp
hash(100)
```

worked.

But

```cpp
hash(Student)
```

generated compilation errors.

Solution:

Created a custom hasher using `combineValue()`.

Now every field contributes to one final hash.

---

### 2. Different Objects Producing Similar Hashes

While testing, I noticed that simple addition of hashes produced many collisions.

Example:

```text
Hash(A)

+

Hash(B)
```

wasn't reliable.

Solution:

Used proper hash combining with bit shifting and mixing.

Distribution improved significantly.

---

### 3. Testing Generic HashMap

Until now most testing used:

```cpp
HashMap<int,int>
```

Today I tested:

```cpp
HashMap<Student,std::string>
```

This helped verify that templates were working correctly for non-primitive objects as well.

---

### 4. Designing Redis Commands

Initially I was directly accessing the HashMap.

Later I realized Redis Lite should expose simple commands instead.

Example:

```text
SET

GET

DEL
```

Internally these commands call the HashMap methods.

This keeps the implementation modular.

---

## Concepts Learned Today

* Custom Hash Functions
* User Defined Hashing
* Hash Combination
* `combineValue()`
* Generic Templates
* Custom Objects as Keys
* Collision Testing
* HashMap Validation
* Initial Redis Architecture
* Key-Value Storage
* Layered Design
* Reusability of Generic Components

---

## Internal Flow

Example:

```text
Student Object

      │

Hasher<Student>

      │

combineValue()

      │

Final Hash

      │

Bucket Number

      │

Linked List

      │

Stored Entry
```

Redis Flow:

```text
SET Name "Anmol"

        │

RedisLite

        │

HashMap

        │

Bucket

        │

Stored Successfully
```

---

## Testing Summary

Today's testing covered:

* HashMap with primitive types
* HashMap with custom classes
* Collision handling
* Lookup operations
* Duplicate key updates
* Custom hash generation
* Redis Lite SET flow
* Redis Lite GET flow
* Basic integration between Redis Lite and HashMap

Everything worked as expected after fixing the custom hash implementation.

---

## Next Tasks

### High Priority

* Complete Redis Lite command parser
* Implement SET command completely
* Implement GET command
* Implement DEL command
* Improve error handling

### Medium Priority

* Add support for more user-defined classes
* Improve HashMap testing
* Verify rehashing with custom objects

### Future Improvements

* TTL (Expiry)
* Multiple Redis data types
* Persistence
* Command-line interface
* Serialization
* Networking support

---

## End of Day Notes

Today's work felt like an important milestone because the project is slowly moving from building individual data structures to actually using them in a real application. Supporting user-defined objects inside the `HashMap` made the implementation much more flexible, and the `combineValue()` helper simplified writing custom hash functions.

It was also satisfying to see the first pieces of Redis Lite come together. Even though only the basic architecture and command flow are ready for now, the foundation is in place. The next step will be expanding the command set and using the custom `HashMap` as the complete in-memory storage engine.
