#ifndef Trees_Bst_Node_h
#define Trees_Bst_Node_h

#include <iostream>
#include <memory>


namespace dsc {
namespace trees {
namespace bst {

template<typename Tkey, typename Tdata>
struct Node {
	Node(Tkey key, Tdata data)
		: key(key)
		, data(data)
		, left(nullptr)
		, right(nullptr)
	{
	}

	Tkey key;
	Tdata data;
	std::shared_ptr<Node<Tkey, Tdata>> left;
	std::shared_ptr<Node<Tkey, Tdata>> right;
};

template<typename Tkey, typename Tdata>
Node<Tkey, Tdata> node(Tkey key, Tdata data)
{
	return Node<Tkey, Tdata>(key, data);
}

}  // namespace bst
}  // namespace trees
}  // namespace dsc

#include "bst.cpp"

#endif  // Trees_Bst_Node_h
