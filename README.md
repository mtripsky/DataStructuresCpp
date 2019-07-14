# Abstract data structures

This project shows examples of implementation of some abstract data structures in *C++11*. 

### Heap

A heap is a tree-based data structure [1](https://en.wikipedia.org/wiki/Heap_(data_structure)). Heap data structure can be used to sort an array, because the root node of the tree contains the maximum or minimum element depending on the implementation. My version of the heap has the maximum element in the root and therefore when dequing this tree we get an array in descending order. The implementation is generic with a constructor taking only maximum size of a container as an argument:

`Heap<T>(size_t maxSize)`

It has these public methods:

1.  `bool push(const T& element)`

   ​	to push an element into the data structure.

   ​	it returns false when `Heap` is full.

2. `bool push(Iterator start, Iterator end)`

   ​	to push elements from some container using generic `Iterator`.

3. `bool pop()`

   ​	to pop out a root element out of the tree.

4. `const T& top()`

   ​	to get a root element (the maximum element).

5. `const size_t size()`

   ​	to get number of nodes in the tree.



### Queue

A queue is a FIFO data structure [2](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)). The implementation is generic with a constructor taking only maximum size of a container as an argument.

​	`Queue<T>(size_t maxSize)`

It has these public methods:

1.  `bool enqueue(const T& element)`

   ​	to enqueue an element into the data structure.

   ​	it returns false when `Queue` is full.

2. `bool dequeue()`

   ​	to dequeue a first element in the queue.

3. `const T& front()`

   ​	to get a first element in the queue.

4. `const size_t size()`

   ​	to get number of elements in the tree.

5. `const bool isEmpty()`

   ​	true if the queue does not contain any elements.

6. `const bool isFull()`

   ​	true if the queue is full.

7. `void print()`

   ​	print the queue in the order how the elements were pushed into the queue.

