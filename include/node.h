/**
 * @file node.h
 * @author Giovanni Pinna, Milton Plasencia, Gaia Saveri 
 * @brief implementation of the class Node.
 */

#ifndef	__NODE_
#define __NODE_

#include<memory> //unique_ptr
#include<utility> //pair


template<class N>
struct node
{ 
	N data; 
	using value_type = N;
	//every node has to contain a pair key-value

	std::unique_ptr<node> left;
	std::unique_ptr<node> right;
//parent is not smart pointer because more than one node can have
//the same parent
	node* parent; //usefull for iterators

	//default constructor
	node();

	//constructor that takes a pair as argument
	//and initializes without the parent
	//usefull for the class iterator
	node(N n) 
	 : data{n}, left{nullptr}, right{nullptr}, parent{nullptr} {}

	//constructor that takes a pair and a parent
	node(N n, node* p)
	 : data{n}, left{nullptr}, right{nullptr}, parent{p} {}

	//copy constroctor
	node(const node& n) 
	 : data{n.data}, left{nullptr}, right{nullptr}, parent{n.parent} {}

	//destructor (non sono sicura che sia necessario)
	~node() = default; 
	

};

#endif
