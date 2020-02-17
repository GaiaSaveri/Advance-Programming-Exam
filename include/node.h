/**
 * \file node.h
 * \author Giovanni Pinna, Milton Plasencia, Gaia Saveri
 * \brief header containing the implementation of the class node.
 */

#ifndef	__NODE_
#define __NODE_

#include<memory> //unique_ptr
#include<utility> //pair


template<class N>
struct node {

  //BST has to use findSmallest()
  template<class Tk, class Tv, class Tc> friend class BST;
	//iterator has to use findSmallest() and findBigger()
	template<class O, class I> friend class iterator;

  /** Data contained in the node */
	N data;
	using value_type = N;
	//every node has to contain a pair key-value

  /** Unique_ptr to the left child node*/
	std::unique_ptr<node> left;
  /** Unique_ptr to the right child node*/
	std::unique_ptr<node> right;
  /** Rae pointer to the parent node */
	node* parent;

	/**
   * \brief Default constructor for the class node.
   */
	node();

  /**
   * \brief Custom constructor for the class node.
   *
   * Initilizes a node only with its data.
   */
	node(N n)
	 : data{n}, left{nullptr}, right{nullptr}, parent{nullptr} {}

	/**
   * \brief Custom constructor for the class node.
   * \param n Data to be inserted in the new node.
   * \param p Parent of the new node.
   *
   * Initializes a node with data and parent node.
   */
	node(N n, node* p)
	 : data{n}, left{nullptr}, right{nullptr}, parent{p} {}

  /**
   * \brief Copy constructor for the class node.
   * \param n Const reference to the node to be copied.
   *
   * This constructor creates a node copying the content of another node.
   */
	node(const node& n)
	 : data{n.data}, left{nullptr}, right{nullptr}, parent{n.parent} {}

	/**
   *\brief Default destructor for the class node.
   */
	~node() noexcept = default;

	/**
   * \brief Recursive function that returns the leftmost node of the tree having as root the current node.
   * \return node* Pointer to the leftmost node.
   */
	node* findSmallest() noexcept
	{
	 if(left) return left->findSmallest();
	 return this;
	}

  /**
   * \brief Recursive function that returns the first right ancestor of the current node.
   * \return node* pointer to the first right ancestor of the current node, if any, nullptr otherwise.
   *
   * If the current node is the left child of its parent, it returns the parent of the current node.
   * Otherwise it recursively search in the ancestors of the current node until a left child found.
   */
  node* findBigger() const;
};

template<class N>
node<N>* node<N>::findBigger() const
{
	if(parent)

		if(parent->right.get()==this) //if it is a right child we continue going up
		return parent->findBigger();

	return parent; //if it is a left child we return
}

#endif
