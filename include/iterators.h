/**
 * \file iterators.h
 * \authors Giovanni Pinna, Milton Plasencia, Gaia Saveri
 * \brief header containing the implementation of the class iterator.
 */

#ifndef __ITERATORS_
#define __ITERATORS_

#include<utility> //pair
#include<memory>

#include"node.h"

template<class N, class I>
class iterator
{

  //BST has to use node()
  template<class Tk, class Tv, class Tc> friend class BST;

  /** Raw pointer to a node of type N */
  N* current; //an iterator is basically a pointer to a node

public:

	/**
	 * \brief Default contructor for the class iterator.
	 */
	iterator() = default;

	/**
	 * \brief Custom constructor for the class iterator.
	 * \param n pointer to a node.
	 *
	 * This constructor creates an iterator pointing to the input node.
	 *
	 */
	explicit iterator(N* n) noexcept : current{n} {};

	/**
	 * \brief Destructor for the class iterator.
	 */
	~iterator() = default;

	using value_type = I;
	using reference  = value_type&;
	using pointer = value_type*;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;

       /**
	 * \brief Overload of the pre-increment operator ++.
	 * \return iterator& Incremented iterator.
	 *
	 * This operator is used to traverse the tree from leftmost node to the rightmost one.
	 */
	iterator& operator++();

	/**
	 * \brief Overload of the post-increment operator ++.
	 * \return iterator& Iterator before advancing to the next node.
	 */
	iterator operator++(int)
	{ iterator tmp {*this};
	  ++(*this);
	  return tmp;
	}

	/**
	 * \brief Overload of the operator ==.
	 * \param x Iterator that is going to be on the left hand side of the operator.
	 * \param y Iterator that is going to be on the right hand side of the operator.
	 * \return bool True if and only if the input iterators point to the same node.
	 *
	 * The function is declared friend beacuase we need access to private members of the class.
	 */
	friend bool operator==(const iterator& x, const iterator& y)
	{ return x.current==y.current; }

	/**
	 * \brief Overload of the operator !=.
	 * \param x Iterator that is going to be on the left hand side of the operator.
	 * \param y Iterator that is going to be on the right hand side of the operator.
	 * \return bool True if and only if input iterators point to different nodes.
	 *
	 * The function is declared friend because we need access to private members of the class.
	 */
	friend bool operator!=(const iterator& x, const iterator& y) 
	{ return x.current!=y.current; }

	/**
	 * \brief Overload of the dereference operator *.
	 * \return reference Data of the node the current iterator is pointing to.
	 */
	reference operator*() const noexcept
		{ return current->data; }

	/**
	 * \brief Overload of the arrow operator ->.
	 * \return pointer Current node tterator is pointing to.
	 */
	pointer operator->() const noexcept
		{ return &(*(*this)); }

	/**
	 * \brief Utility function that returns a pointer to the node pointed to by the iterator.
	 * \retunr N* Pointer to the node the iterator is pointing to.
	 */
	N* node() { return current; }


};

template<class N, class I>
iterator<N, I>& iterator<N,I>::operator++()
{
	if(current)
  {
    if(current->right)
     current = current->right->findSmallest();
    else
     current = current->findBigger();
   }
 return *this;
}

#endif
