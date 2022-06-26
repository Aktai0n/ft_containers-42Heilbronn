# ft_containers

The goal of ft_containers is to recode some of the containers of the [C++ STL](https://www.geeksforgeeks.org/the-c-standard-template-library-stl/) (namely the vector, stack, map and set) as they were implemented in the C++98 standart while maintaining a performance that is comparable to the original implementation.

1. [Usage](#usage)
2. [Overview](#overview)
3. [Resources](#resources)


## Usage:

clone the repository:
```bash
git clone https://github.com/Aktai0n/ft_containers-42Heilbronn.git &&
cd ft_containers-42Heilbronn
```

build the project with:
```bash
make
```

run the benchmark:
```bash
./benchmark.sh all
```

to run individual container benchmarks use:
```bash
./benchmark.sh [container_name]
```

modify the include paths inside config.hpp to test your own containers:
```c
#include "./inc/vector.hpp"
#include "./inc/stack.hpp"
#include "./inc/map.hpp"
#include "./inc/set.hpp"
```


## Overview:

### vector:
A vector container is an array that dynamically increases or shrinks in size when you add or remove elements from it.
All elements of a vector are stored in a contiguous block of memory and sorted by insertion order.

:+1: element access in constant time \
:+1: contiguous memory leads to few cache misses when iterating over the container \
:+1: usually constant insertion and deletion time on the end of the container \
:+1: preallocates memory to avoid copies

:-1: has to copy all its elements when running out of memory \
:-1: linear insertion and deletion time at the beginning of the container \
:-1: allocates potentially unused memory

### stack:
The stack container is a wrapper for a different container (usually a deque) to offer the functionalities of a LIFO stack, where elements are pushed and popped only at the end.
My self-written stack uses my vector as underlying container by default.

### map:
A map container stores its elements as pairs of keys and values. Searching for elements is done by providing a key to retrive the associated value. Maps use a binary search tree, which is usually implemented as a red-black tree, as their underlying data structure. More information about red-black trees can be found [here](https://github.com/Aktai0n/ft_containers-42Heilbronn/blob/master/inc/utils/RBtree.hpp).

:+1: fast insertion, deletion and search times in O(log n) \
:+1: keys can be any data type that is comparable using the < operator \
:+1: elements are sorted in ascending order \
:+1: only allocates as much memory as it currently needs

:-1: all elements are stored in destinct blocks of memory. This leads to cache misses which increases the time it takes to iterate over the container \
:-1: every element has to allocate additional storage to store the pointers and node color \
:-1: insertion and deletion may cause rotations to keep the tree (somewhat) balanced

### set:
The set container is similar to the map as it also stores its elements in a binary search tree. The major difference is that the stored value is also used as the key to access it.
Due to that, the set shares almost the same advantages and disadvantages as the map.


## Resources:

**vector:** \
[vector in the stdlib](https://www.cplusplus.com/reference/vector/vector/) \
[how does a vector work](https://www.youtube.com/watch?v=PocJ5jXv8No) \
[writing a vector](https://www.youtube.com/watch?v=ryRf4Jh_YC0)

**stack:** \
[stack in the stdlib](https://www.cplusplus.com/reference/stack/stack/)

**map:** \
[map in the stdlib](https://www.cplusplus.com/reference/map/map/) \
[how do maps work](https://www.youtube.com/watch?v=KiB0vRi2wlc)

**set:** \
[set in the stdlib](https://www.cplusplus.com/reference/set/set/)

**red-black tree:** \
[introduction to red-black trees](https://www.youtube.com/watch?v=3RQtq7PDHog) \
[red-black tree insertion](https://www.youtube.com/watch?v=qA02XWRTBdw) \
[red-black tree deletion](https://www.youtube.com/watch?v=w5cvkTXY0vQ)

**iterators:** \
[iterator in the stdlib](https://www.cplusplus.com/reference/iterator/) \
[what are iterators](https://www.youtube.com/watch?v=SgcHcbQ0RCQ) \
[writing an iterator yourself](https://www.youtube.com/watch?v=F9eDv-YIOQ0)

**enable_if (SFINAE):** \
[overview of enable_if](https://en.cppreference.com/w/cpp/types/enable_if) \
[what is SFINAE](https://en.cppreference.com/w/cpp/language/sfinae)