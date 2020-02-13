/** 
 * @file BST.h
 * @author Giovanni Pinna, Milton Plasencia, Gaia Saveri 
 * @brief class implementing a binary search tree
 */




#include<memory> //unique_ptr
#include<utility> //pair
#include<iostream>
#include<vector>
/**
 * @tparam Tk Type of node keys
 * @tparam Tv Type of node values
 * @tparam Tc Type of the comparison operator. Default is std::less<Tk>.
 */
template<class Tk, class Tv, class Tc=std::less<Tk>>
class BST
{

private:
		
	struct Node;

public:
	class Iterator;
	class Const_iterator;

private:
		
        /** Unique pointer to the root */
	std::unique_ptr<Node> root;

	//private find
	Iterator findPrivate(const Tk& x) const;

	/**
         *delete the subtree having n as root
	 */
	void deleteNode(std::unique_ptr<Node>& n);
	
	//perform the deep copy of a tree starting from node n
	void copy(const std::unique_ptr<Node>& n);
	
	void PrintinOrderPrivate(Node* ptr);
	
	void RemoveRootMach();
	
	void RemoveMatch(Node& parent, Node& match, bool left);
	
	void RemoveSubtree(Node& ptr);
			
			
	std::vector<std::pair<Tk,Tv>> BalancePrivate(Node & ptr);
		
	void rebuildtree (std::vector<std::pair<Tk,Tv>>& values, int start, int end);
	
	void RemoveNodePrivate(const std::pair<Tk,Tv>& data, Node& parent);
	
public:

		/**comparison operator */
		Tc comp; 

		
		/** default constructor */ 		
		BST()
		{ 
		  #ifdef TEST
		  std::cout<<"default ctor"<<std::endl;
		  #endif 
		}

		/** custom custroctor */
		//constructs a bst given the root
		BST(std::pair<Tk, Tv> newRoot, Tc cmp=Tc{})
		: root{new Node{newRoot}}, comp{cmp}
		{
		  #ifdef TEST
		  std::cout<<"custom ctor"<<std::endl;
		  #endif
		}
		
		
		/** copy constructor */
		//deep copy of the bst in input
		//input: bst to be copied 
	 	BST(const BST& tree) 
		{ 
		  copy(tree.root);
		  #ifdef TEST
		  std::cout<<"copy ctor"<<std::endl;
		  #endif
		   
		}

		//copy assignment
		//input: bst to be copied
		//output: current tree
		BST& operator=(const BST& tree);

		/** move constructor */
		//input: bst to be moved
		BST(BST&& tree) : root{std::move(tree.root)} 
		{
		  #ifdef TEST
		  std::cout<<"move ctor"<<std::endl;
		  #endif
		} 

		//move assignment
		//input: bst to be moved
		//output: current tree
		BST& operator=(BST&& tree);

		/**
 		* \brief This function inserts a new node into the BST.
 		* \param It needs as argument a pair composed by a key and a value.
 		* \return It returns a pair: an iterator that points to the node and a bool value which is true if the function insert the node, false if the node is already in the BST.
 		*/		
		std::pair<Iterator, bool> insert(const std::pair<Tk, Tv>& x);

		/**
 		* \brief This function inserts a new node into the BST.
 		* \param It needs as arument a pair composed by a key and a value, it is passed to the function as an rvalue.
 		* \return It returns a pair : an iterator that points to the node and a bool value which is true if the function insert the node, false if the node is already in the BST.
 		*/
		std::pair<Iterator, bool> insert(std::pair<Tk, Tv>&& x);

		/**
 		* \brief This function finds a key of a node inside the BST.
 		* \param It needs as argument a key.
 		* \return It returns an iterator thet points to the node with that key, otherwise it returns an iterator that points to "nullptr".
 		*/
		Iterator find(const Tk& x);	

		/**
 		* \brief This function finds a key of a node inside the BST.
 		* \param It needs as argument a key.
 		* \return It returns an iterator thet points to the node with that key, otherwise it returns an iterator that points to "nullptr".
 		*/
		Const_iterator find(const Tk& x) const;

		/**
 		* \brief This function finds a key of a node inside the BST.
 		* \param It needs as argument a key, it is passed to the function as an rvalue.
 		* \return It returns a pointer to the node with that key.
 		*/
		Node* findnode(Tk&& k); //it is needed?

		/**
 		* \brief This function inserts a new element into the container constructed in-place.
 		* \param It needs a pair as argument.
 		* \return It returns a pair: an iterator that points to the node and a bool value which is true if the function insert the node, false if the node is already in the BST. 
 		*/
		template<class...Args>
		std::pair<Iterator, bool> emplace (Args&&... args);
					
		//subscripting operators
		//used to access, or insert, a node given the key
		//and return the value associated with the input key
		Tv& operator[] (const Tk& k);
		Tv& operator[] (Tk&& k);

		/**
 		* \brief This function gives us the starting point of our container.
 		* \return It return an iterator that points to the leftmost node of the tree.
 		*/
		Iterator begin();

		/**
 		* \brief This function gives us the starting point of our container.
 		* \return It return an iterator that points to the leftmost node of the tree.
 		*/
		Const_iterator begin() const;
		
		/**
                 * @brief This function gives us the starting point of our container.
                 * @return It return an iterator that points to the leftmost node of the tree.
                 */
                Const_iterator cbegin() const;


		//ends
		Iterator end() { return Iterator{nullptr}; }
		Const_iterator end() const 
			{ return Const_iterator{nullptr};} 
		Const_iterator cend() const
			{ return Const_iterator{nullptr};}		



		//clear the content of the tree
		//recursively remove the nodes
		void clear() 
		{ 
		  #ifdef TEST
		  std::cout<<"deleting the tree"<<std::endl;
		  #endif
		  deleteNode(this->root); 
		} 
		
		//destructor
		~BST()=default;

		void PrintinOrder();
		
		void PrintChildren(std::pair<Tk,Tv>& data);

		void Balance();

		void erase(const std::pair<Tk,Tv>& data);
};

#include"node.h"
#include"iterators.h"
#include"myfunc.h"


