#ifndef Linked_List_Node_h
#define Linked_List_Node_h

#include <iostream>
#include <memory>


namespace dsc {
namespace lists {

template<typename T>
struct Node {
	Node(T data)
		: data(data)
		, next(nullptr)
	{
	}

	T data;
	std::shared_ptr<Node<T>> next;
};

template<typename T>
Node<T> node(T data)
{
	return Node<T>(data);
}

}  // namespace lists
}  // namespace dsc

#endif  // Linked_List_Node_h
