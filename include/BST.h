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

  /** Unique pointer to the root node */
	std::unique_ptr<Node> root;

  /**
    * \brief Recursive function for making a deep copy of a subtree.
    * \param n root of the subtree to be copied.
    *
    * Private auxiliary function, used in the implementation of the copy semantics for the binary search tree.
    */
  void copy(const std::unique_ptr<Node>& n);

  /**
   * \brief Private utility function which inserts a new node in the tree.
   * \param x<T> Pair key-value to be inserted in the tree.
   * \return std::pair<Itarator,bool> Pair formed by an iterator to the new node, and a bool which is
   * true if the node has been inserted in the tree, false if the input key was alredy in the tree.
   */
  template<class T>
  std::pair<Iterator, bool> insertPrivate(T&& x);

  /**
   * \brief Private function that returns an iterator pointing to the node with a given key, if any.
   * \param x Key to be found.
   * \return Iterator Iterator pointing to the node with the input key, if any.
   *
   * The function starts searching for the input key from the root. If the key is present it returns
   * an iterator pointing to the node containing that key if the key is not present it returns
   * an iterator pointing to the node in which the key should be inserted, if the tree is empty,
   * it returns a nullptr.
   */
	Iterator findnode(const Tk& x) const;

  /**
   * \brief Recursive utility function which builds a tree from a vector of pairs.
   * \param values Vector containing the key-value pairs of the current tree.
   * \param start First element of the input vector, useful for recursion.
   * \param end Last element of the input vector, useful for recursion.
   */
  void rebuildtree (std::vector<pair>>& values, int start, int end);

  /**
   * \brief Private auxiliary function which stores all the pairs key-value contained
   * in the nodes of the tree in a vector.
   * \return std::vector<pair> Vector containing pairs key-value.
   */
  std::vector<pair> BalancePrivate();

  /**
   * \brief Function that removes the root of the tree and properly sets a new one.
   */
  void RemoveRootMach();

  /**
   * \brief Function that delete a non-root node and reassemble the tree following the rules of the binary tree.
   * \param parent Parent node of the node to delete.
   * \param match Node to be deleted.
   * \param left Boolean which is true if the node to be deleted is the left child of its parent, false otherwise.
   */
  void RemoveMatch(Node* parent, Node* match, bool left);

	#ifdef PRINT
  /**
   * \brief Private function used to print the pair key-value contained in the input node.
   * \param n Node of which the function prints the stored data.
   * \param os Stream to which the nodes are sent.
   */
  void printNode(const std::unique_ptr<Node>& n, std::ostream& os) const;

  /**
   * \brief Private function used to print the structure of the tree.
   * \param prefix String for specifying the indentation of the node to print.
   * \param n Node to be printed.
   * \param nleft Boolean specifying if the input node is left child.
   * \param os Stream to which the nodes are sent.
   */
	void printBST(const std::string& prefix, const std::unique_ptr<Node>& n, bool nleft, std::ostream& os) const;
  #endif

public:

	/**comparison operator */
	Tc comp;

	/**
	 * \brief Default constructor for the class BST.
	 */
	BST()
	{
	  #ifdef TEST
	  std::cout<<"default ctor"<<std::endl;
	  #endif
	}

	/**
	 * \brief Custom custroctor.
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
   *
   * This constructor creates a binary search tree moving the content of the tree in input.
   */
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

   /**
    * \brief Function to clear the content of the tree.
    *
    * This function resets the root of the tree, so that the whole tree is destroyed without any memory leak.
    */
    void clear()
    {
     	#ifdef TEST
     	std::cout<<"deleting the tree"<<std::endl;
     	#endif
     	root.reset();
     }

  	/**
     * \brief Function used to start iterations on the tree.
     * \return Iterator An iterator pointing to the leftmost node of the tree, the one with the smallest key.
     */
  	Iterator begin() noexcept;

    /**
     * \brief Function used to finish an iteration on the tree.
     * \return Iterator An iterator pointing to one past the last element of the tree.
     */
  	Iterator end() noexcept { return Iterator{nullptr}; }

    /**
     * \brief Function used to start iterations on the tree.
     * \return Const_iterator A constant iterator pointing to the leftmost node of the tree, the one with the smallest key.
     */
  	Const_iterator begin() const noexcept;

    /**
     * \brief Function used to start iterations on the tree.
     * \return Const_iterator A constant iterator pointing to the leftmost node of the tree,
     * the one with the smallest key.
     */
  	Const_iterator cbegin() const noexcept;

    /**
     * \brief Function used to finish an iteration on the tree.
     * \return Const_iterator A constant iterator pointing to one past
     * the last element of the tree.
     */
  	Const_iterator end() const noexcept
  		{ return Const_iterator{nullptr};}

    /**
     * \brief Function used to finish an iteration on the tree.
     * \return Const_iterator A constant iterator pointing to one past
     * the last element of the tree.
     */
  	Const_iterator cend() const noexcept
  		{ return Const_iterator{nullptr};}

    /**
 		 * \brief This function inserts a new node into the BST.
 		 * \param x Pair composed by a key and a value.
 		 * \return std::pair<Iterator,bool> It returns a pair:
     * an iterator that points to the node containing the input pair
     * and a bool value which is true if the function inserts the node, false if the node is already in the BST.
 		 */
	  std::pair<Iterator, bool> insert(const pair& x);

    /**
     * \brief This function inserts a new node into the BST.
     * \param x Pair composed by a key and a value.
     * \return std::pair<Iterator,bool> It returns a pair:
     * an iterator that points to the node containing the input pair
     * and a bool value which is true if the function inserts the node, false if the node is already in the BST.
     */
	  std::pair<Iterator, bool> insert(pair&& x);

    /**
     * \brief This function inserts a new element into the container constructed in-place.
     * \param args A key-value pair.
     * \return std::pair<Itearator, bool> It returns a pair: an iterator that points to the node
     * and a bool value which is true if the function insert the node, false if the node is already in the BST.
     */
    template<typename... Types>
    std::pair<Iterator, bool> emplace(Types&&... args)
    {
      #ifdef TEST
      std::cout<<"Emplace"<<std::endl;
      #endif
      return insert(std::make_pair<const Tk,Tv>(std::forward<Types>(args)...));
    }


		/**
 		 * \brief This function finds a key of a node inside the BST.
 		 * \param x It needs as argument a key.
 		 * \return Iterator It returns an iterator thet points to the node with that key, if any.
     * Otherwise it returns an iterator that points to "nullptr".
 		 */
	  Iterator find(const Tk& x);

    /**
     * \brief This function finds a key of a node inside the BST.
     * \param x It needs as argument a key.
     * \return Const_iterator It returns a constant iterator thet points to the node with that key, if any.
     * Otherwise it returns a constant iterator that points to "nullptr".
     */
	  Const_iterator find(const Tk& x) const;

	  /**
     * \brief Overload of the subscript operator [].
     * \param k Node key to be accessed.
     * \return Tv& Node value associated with k.
     *
     * It is a find-or-add operator. It tries to find an element with the input key inside the tree. If it exists, it returns a reference to the associated value. If it doesn't, it creates and inserts a new node containing the input key and a default constructed value, and returns a reference to the value as well.
     */
  	Tv& operator[] (const Tk& k);

	  /**
     * \brief Overload of the subscript operator [] for moves.
     * \param k Node key to be accessed
     * \return Tv& Node value associated with k
     *
     */
	  Tv& operator[] (Tk&& k);

	  void Balance();

    void erase(const Tk& k);

    #ifdef PRINT
	  /**
     * \brief Function that prints the structure of the tree.
     * \param os Stream to which the tree should be printed.
     */
	  std::ostream& printTree(std::ostream& os) const;
    #endif

    void PrintChildren(Tk a);

    /**
     * \brief Functions that prints the node in acending order.
     * \param os Stream to which the nodes are sent.
     */
    std::ostream& printOrderedList(std::ostream& os) const;

    /**
     * \brief Operator << to print the tree in ascending key order.
     * \param os Stream to which nodes are sent.
     * \param tree BST to be printed.
     * \return std::ostream Strem to which nodes have been sent.
     */
	  friend std::ostream& operator<<(std::ostream& os, const BST& tree)
    {
     #ifdef PRINT
     return tree.printTree(os);
     #else
     return tree.printOrderedList(os);
     #endif
    }

  	 /**
      *\brief Destructor for the binary search tree.
      */
  	 ~BST() noexcept = default;
};

#include"methods.h"
