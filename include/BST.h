/**
 * \file BST.h
 * \authors Giovanni Pinna, Milton Plasencia, Gaia Saveri
 * \brief Class implementing a binary search tree.
 */




#include<memory> //unique_ptr
#include<utility> //pair
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

#include"node.h"
#include"iterators.h"

/**
 * \tparam Tk Type of node keys.
 * \tparam Tv Type of node values.
 * \tparam Tc Type of the comparison operator. Default is std::less<Tk>.
 */
template<class Tk, class Tv, class Tc=std::less<Tk>>
class BST
{
private:

  using pair = std::pair<const Tk,Tv>;
  using Node = node<pair>;
  using Iterator = iterator<Node, typename Node::value_type>;
  using Const_iterator = iterator<Node, const typename Node::value_type>;

        /** Unique pointer to the root */
	std::unique_ptr<Node> root;

	//private find
	Iterator findnode(const Tk& x) const;

  //find leftmost nodes
  //Node* findSmallest () const;

	template<class T>
	std::pair<Iterator, bool> insertPrivate(T&& x);


        /**
         * \brief Recursive function for deleting a subtree.
         * \param n root of the subtree to be deleted.
         *
         * Private auxiliary function. Called inside the function clear().
         */
	//void deleteNode(std::unique_ptr<Node>& n);

	/**
         * \brief Recursive function for making a deep copy of a subtree.
         * \param n root of the subtree to be copied.
         *
         * Private auxiliary function, used in the implementation of the
         * copy semantics for the binary search tree.
         */
	void copy(const std::unique_ptr<Node>& n);

  void RemoveRootMach();
  void RemoveMatch(Node* parent, Node* match, bool left);
  void RemoveSubtree(Node* ptr);
  void RemoveNodePrivate(const Tk& data, Node* parent);

	//private methods to visualize the treee
	#ifdef PRINT
  void printNode(const std::unique_ptr<Node>& n, std::ostream& os) const;
	void printBST(const std::string& prefix, const std::unique_ptr<Node>& n, bool nleft, std::ostream& os) const;
        #endif
	//std::ostream& PrintinOrderPrivate(std::unique_ptr<Node>& ptr, std::ostream& os);

	void rebuildtree (std::vector<std::pair<Tk,Tv>>& values, int start, int end);
  std::vector<std::pair<Tk,Tv>> BalancePrivate();
  //void RemoveSubtree(Node* ptr);
	//void RemoveMatch(Node* parent, Node* match, bool left);


public:

<<<<<<< HEAD
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

                //emplace
                template<typename.. Types>
                void emplace(Types&&.. args)
                {
                  #ifdef TEST
                  std::cout<<"Emplace"<<std::endl;
                  #endif
                  insert(std::make_pair{std::forward<Types>(args)...});
                }

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
=======
	/**comparison operator */
	Tc comp;
>>>>>>> 35a796f146e6db6a12e1e9117e89023461c47995

	/**
	 * \brief default constructor.
	 */
	BST()
	{
	  #ifdef TEST
	  std::cout<<"default ctor"<<std::endl;
	  #endif
	}

	/**
	 * \brief Custom custroctor .
	 *
	 * Constructs a binary search tree given the root node data.
	 */
	BST(pair newRoot, Tc cmp=Tc{})
	: root{new Node{newRoot}}, comp{cmp}
	{
	  #ifdef TEST
	  std::cout<<"custom ctor"<<std::endl;
	  #endif
	}

	/**
	 * \brief Copy constructor.
	 * \param tree binary search tree to be copied.
  	 *
	 * This constructor creates a binary search tree copying the content of
	 * the tree in input, taking advantage of the private recursive copy
	 * function.
	 */
	 BST(const BST& tree)
	{
	  copy(tree.root);
	  #ifdef TEST
	  std::cout<<"copy ctor"<<std::endl;
	  #endif

	}

	/**
         * \brief Copy assignment.
         * \param tree binary search tree to be copied.
         * \return BST& modified binary search tree
         */
	BST& operator=(const BST& tree);

	/**
	 * \brief Move constructor.
	 * \param tree binary search tree to be moved.
	 */

         // This constructor creates a binary search tree moving the
         // content of the tree in input.

	BST(BST&& tree) : root{std::move(tree.root)}
	{
	  #ifdef TEST
          std::cout<<"move ctor"<<std::endl;
	  #endif
	}

	/**
         * \brief Move assignment
         * \param tree binary search tree to be moved
         * \return BST& modified binary search tree
         */
	BST& operator=(BST&& tree);

	//function insert
	std::pair<Iterator, bool> insert(const pair& x);

	//function insert with rvalue
	std::pair<Iterator, bool> insert(pair&& x);

	//function find
	Iterator find(const Tk& x);

	//function find with const iter
	Const_iterator find(const Tk& x) const;

	/**
          * \brief Overload of the subscript operator []
          * \param k node key to be accessed
          * \return Tv& node value associated with k
         */
          //It is a find-or-add operator. It tries to find an element with the input key inside the tree. If it exists, it returns a reference to the associated value. If it doesn't, it creates and inserts a new node containing the input key and a default constructed value, and returns a reference to the value as well.

	Tv& operator[] (const Tk& k);

	/**
          * \brief Overload of the subscript operator [] for moves
          * \param k node key to be accessed
          * \return Tv& node value associated with k
          *
          */
	Tv& operator[] (Tk&& k);


	//begins and ends
	Iterator begin();
	Iterator end() { return Iterator{nullptr}; }

	Const_iterator begin() const;
	Const_iterator cbegin() const;
	Const_iterator end() const
		{ return Const_iterator{nullptr};}
	Const_iterator cend() const
		{ return Const_iterator{nullptr};}

  //emplace
  template<typename... Types>
  std::pair<Iterator, bool> emplace(Types&&... args)
  {
    #ifdef TEST
    std::cout<<"Emplace"<<std::endl;
    #endif
    return insert(std::make_pair<const Tk,Tv>(std::forward<Types>(args)...));
  }


	/**
	  * \brief Function to clear the content of the tree
	  *
	  * Recursively remove the nodes starting from the root.
	  */
	void clear()
	{
	  #ifdef TEST
	  std::cout<<"deleting the tree"<<std::endl;
	  #endif
	  root.reset();
	}

	/** Destructor */
	~BST()=default;

	void Balance();
/**
*Call: User
*\param new pair key value
*\brief call RemoveNodePrivate setting the starting point as root
*\return void
*/	
void erase(const Tk& data);

//void erase(const std::pair<Tk,Tv>& data);
#ifdef PRINT
//print the structure of the tree
std::ostream& printTree(std::ostream& os) const;
#endif
//print pairs key-value ordered by key
std::ostream& printOrderedList(std::ostream& os) const;
friend std::ostream& operator<<(std::ostream& os, const BST& tree)
{
#ifdef PRINT
return tree.printTree(os);
#endif
return tree.printOrderedList(os);
}

};

#include"methods.h"
