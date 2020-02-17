/**
 * \file methods.h
 * \authors Giovanni Pinna, Milton Plasencia, Gaia Saveri
 * \brief Class implementing a binary search tree.
 */


#include<memory>
#include<utility>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

//it begin
template<class Tk, class Tv, class Tc>
typename BST<Tk,Tv,Tc>::Iterator BST<Tk,Tv,Tc>::begin() noexcept
{
  if(root)
  {
  Node* n = root->findSmallest();
  return Iterator{n};
  }
  return Iterator{nullptr};
}

//const begin
template<class Tk, class Tv, class Tc>
typename BST<Tk,Tv,Tc>::Const_iterator BST<Tk,Tv,Tc>::begin() const noexcept
{
  if(!root) return Const_iterator{nullptr};
  Node* n = root->findSmallest();
  return Const_iterator{n};
}

//const cbegin
template<class Tk, class Tv, class Tc>
typename BST<Tk,Tv,Tc>::Const_iterator BST<Tk,Tv,Tc>::cbegin() const noexcept
{
  if(!root) return Const_iterator{nullptr};
  Node* n = root->findSmallest();
  return Const_iterator{n};
}


template<class Tk, class Tv, class Tc>
typename BST<Tk,Tv,Tc>::Iterator BST<Tk,Tv,Tc>::findnode(const Tk& x) const
{
  Node* current=root.get(); //starting from the root
  while(current)
    {
      //the key of the current node is smaller than k
      if(comp(current->data.first, x))
        {
          //have to search on the right child
          if(!(current->right.get())) //when there is no right child
            return Iterator{current};
          else //when there is the right child we go down to the right
              current=current->right.get();
        }
      //the key of the current node is bigger than k
      else if (comp(x, current->data.first))
        {
          //heve to search on the left child
          if(!(current->left.get())) //when there is no left child
            return Iterator{current};
          else //when there is the left child we go down to the left
            current = current->left.get();
        }
      else //equality case --> the key of the node is equal to key
        return Iterator{current};

    }
  //if the root was nullptr-->empty tree
  return Iterator{nullptr}; //iterator pointing to nullptr
}

//insert
template<class Tk, class Tv, class Tc>
std::pair<typename BST<Tk,Tv,Tc>::Iterator, bool> BST<Tk,Tv,Tc>::insert(const pair& x)
{
  #ifdef TEST
  std::cout<<std::endl;
  std::cout<<"lvalue insert"<<std::endl;
  #endif
  return insertPrivate(x);
}

//rvalue insert
template<class Tk, class Tv, class Tc>
std::pair<typename BST<Tk,Tv,Tc>::Iterator, bool> BST<Tk,Tv,Tc>::insert(pair&& x)
{
  #ifdef TEST
  std::cout<<std::endl;
  std::cout<<"rvalue insert"<<std::endl;
  #endif
  return insertPrivate(std::move(x));
}

template<class Tk, class Tv, class Tc>
template<class T>
std::pair<typename BST<Tk,Tv,Tc>::Iterator, bool> BST<Tk,Tv,Tc>::insertPrivate(T&& x)
{
  #ifdef TEST
  std::cout<<std::endl;
  std::cout<<"forward insert"<<std::endl;
  #endif
    Node* current = root.get();
    //Node* newnode=new Node(std::forward<T>(x),current);
    while(current)
    { //we have a node
      if(comp(x.first, current->data.first))
      {
         if(current->left)
         current = current->left.get();
         else
         {
         current->left.reset(new Node(std::forward<T>(x),current));
         return std::make_pair(Iterator{current->left.get()}, true);
          }
      }
      else if(comp(current->data.first, x.first))
      {
          if(current->right)
           current=current->right.get();
          else
          {
           current->right.reset(new Node(std::forward<T>(x),current));
           return std::make_pair(Iterator{current->right.get()}, true);
          }
       }
    else
    {
      return std::make_pair(Iterator{current}, false);
    }
}
    //root was empty
    root.reset(new Node(std::forward<T>(x),nullptr));
    return std::make_pair(Iterator{root.get()}, true);

}

//find
//non-const version
template<class Tk, class Tv, class Tc>
typename BST<Tk,Tv,Tc>::Iterator BST<Tk,Tv,Tc>::find(const Tk& x)
{
  #ifdef TEST
  std::cout<<"non-const find"<<std::endl;
  #endif
  Iterator it{this->findnode(x)};
  if(it!=end())
    return (((*it).first == x )? it : end());
  else //tree is empty
    return end();
}

//const version
typename BST<Tk,Tv,Tc>::Const_iterator BST<Tk,Tv,Tc>::find(const Tk& x) const
{
  #ifdef TEST
  std::cout<<"const find"<<std::endl;
  #endif
  Const_iterator it{this->findnode(x)};
  //if the key is not present findPrivate returns end()
  if(it!=end())
    return (*it).first == x ? it : cend();
  else
    return cend();
}

//erase
template<class Tk, class Tv, class Tc>
void BST<Tk,Tv,Tc>::erase(const Tk& data)
{
  if(!root) {std::cout<<"Empty tree"<<std::endl;}
  else //tree is not empty
  {
    Iterator it{find(data)};
    if(it == end()) {std::cout<<"key is not in the tree"<<std::endl;}
    else
    {
      if(it.node()==root.get()) //need to remove the root
      { RemoveRootMach();}
      else
      {
        Node* match = it.node();
        Node* parent = match->parent;
        //need to decide if it is left or right child
        if(parent->left.get() == match)
        {RemoveMatch(parent, match, true);}
        else {RemoveMatch(parent, match, false);}
      }
    }
  }
}
