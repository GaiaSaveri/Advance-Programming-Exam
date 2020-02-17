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

//remove root
template <class Tk, class Tv, class Tc>
void BST<Tk,Tv,Tc>::RemoveRootMach(){
				//case 0 root have not a chldren
				if(!(root->left) && !(root->right))
        {
					root.reset(); //clear the tree
				}
				//case 1 root has one child --> right child
				else if (!(BST<Tk,Tv,Tc>::root->left.get()) && BST<Tk,Tv,Tc>::root->right.get())
        {
					root->right->parent = nullptr;
					root.reset(root->right.release());
          #ifdef TEST
					std::cout<<"The new root contains data " << root->data.first <<std::endl;
          #endif
        }
				//case 1 root has one child --> left child
				else if ((root->left) && !(root->right))
        {
					root->left->parent = nullptr;
					//root point to the left child (left child = current root)
					root.reset(root->left.release());
          #ifdef TEST
					std::cout<<"The new root contains data " << root->data.first <<std::endl;
          #endif
        }
				//case 2 the root has 2 children
				else
        {
					Node* temp = (root->right.get())->findSmallest();
					if(comp(temp->data.first,temp->parent->data.first))
          {
            if(temp->right) temp->right->parent = temp->parent;
					  
            temp->parent->left.release();
					}
					else
          {
					  temp->parent->right.release();
					  temp->parent = nullptr;
					}
					if(root->left)
          {
						root->left->parent = temp;
						temp->left.reset(root->left.release());
					}
					if(root->right)
          {
            Node * tempright = root->right.release();
					  root->right->parent = temp;
            temp->parent->left.reset(temp->right.release());
					  temp->right.reset(tempright);
            temp->parent = nullptr;
            delete tempright;
					}
					root.reset(temp);
          #ifdef TEST
					std::cout << "the root was overwitten with key "<< root->data.first<<std::endl;	//allert of the change
          #endif
        }
			}

//remove node
template <class Tk, class Tv, class Tc>
void BST<Tk,Tv,Tc>::RemoveMatch(typename BST<Tk,Tv,Tc>::Node* parent,typename BST<Tk,Tv,Tc>::Node* match, bool left)
{
			//case 0 no children
			if(!(match->left) && !(match->right))
      {
				left == true ?							//the node that we want delete is the left child of its parent?
					parent->left.reset() :			//if yes put the parent's left pointer to nullptr
					parent->right.reset();			//esle no put the parent's right pointr to nullptr
        #ifdef TEST
				cout<<"the node containing the data " << matchdata<< " was removed"<<endl;
        #endif
			}
			//case 1 one child --> right
			else if(!(match->left) && (match->right))
      {
				if(left == true)
        {							//the node that we want delete is the left child of its parent?
					parent->left.release();
          match->right->parent = parent;
					parent->left.reset(match->right.release());		//if yes put the parent's left pointer to the left pointr of the node that we want delete
					delete match;
					}
				else
        {
          parent->right.release();
					parent->right.reset(match->right.release());
			    parent->right->parent = parent;
					delete match; //delete the node
				}
        #ifdef TEST
				std::cout<<"the node containing the data " << match->data.first<< " was removed"<<std::endl;
        #endif
			}
			//case 1 one child --> left
			else if((match->left) && !(match->right))
      {
				if(left == true)
        {	//is the node that we want delete the left child of its parent?
          parent->left.release();
					parent->left.reset(match->left.release());		//if yes put the parent's left ptr to the left ptr of the node that we want delete
					parent->left->parent = parent;
					delete match;
					}
				else
        {
          parent->right.release();
					parent->right.reset(match->left.release());
					parent->right->parent = parent;
					delete match;
				}
        #ifdef TEST
				cout<<"the node containing the data " << match->data.fisrt<< " was removed"<<endl;
        #endif
				}
			//case 2 have both children
				else
        {
					Node* temp = (match->right.get())->findSmallest();
					if(comp(temp->data.first, temp->parent->data.first))
          {
					temp->parent->left.release();
				  temp->right->parent = temp->parent;
          if(!(temp->right)) temp->parent->left.reset(temp->right.release());
					}
					else
          {
					temp->parent->right.release();
					temp->parent = nullptr;
					}
					if(left == true){
						parent->left.release();
						parent->left.reset(temp);
						temp->parent = parent;
					}
					else
          {
					  parent->right.release();
						parent->right.reset(temp);
						temp->parent = parent;
					}
					if (match->left)
          {
						match->left->parent = temp;
						temp->left.reset(match->left.release());
					}
					if (match->right)
          {
						match->right->parent = temp;
            temp->right.reset(match->right.release());
					}
					delete match;
							}
            }

//print the relation between a node and its children
template <class Tk, class Tv, class Tc>
void BST<Tk,Tv,Tc>::PrintChildren(Tk a)
{
            BST<Tk,Tv,Tc>::Node* ptr = BST<Tk,Tv,Tc>::find(a).node();	//create the pointer that will be use point the node with the data that we serch
            																			//the function retNode is equal to find (return the node with that value)
            			if (ptr){														//if ptr NOT point to null
                    std::cout<<std::endl;
                    if(ptr == root.get()) std::cout<<"Root ";
            				std::cout<<"Node = " << ptr->data.first << std::endl;		//parent node is the current node
            				ptr->left == nullptr ?										//ptr left child punt to null
            					std::cout<<"left child =NULL"<<std::endl:							//if yes cout null
            					std::cout<<"left child = "<<ptr->left->data.first<<std::endl;			//if no cout the value of the left child

            				ptr->right == nullptr ?										//ptr right child punt to null
            					std::cout<<"right child =NULL"<<std::endl:						//if yes cout null
            					std::cout<<"right child = "<<ptr->right->data.first<<std::endl;			//if no cout the value of the right child

                      std::cout << std::endl;
                        }
            			else{															//if the ptr point a null ptr
            				std::cout<<"not found"<<std::endl;
            			}
}

//Balance
template <class Tk, class Tv, class Tc>
	void BST<Tk,Tv,Tc>::Balance(){

		std::vector<std::pair<Tk,Tv>> v;					//create the vector for save all the values in the tree
		v = BalancePrivate(); //arg root		//call balanceprevate function for save the values. Remember that return a vector
		 clear(); //RemoveSubtree(root.get());								//delete ALL the tree (delete all unter the root = delete all the tree)
		std::sort( v.begin(), v.end() );					//order the vector in encrease order
		//root.reset();										//put the root to null pointer (the tree is emptry/not exist)
    #ifdef TEST
		for(int i = 0; i<v.size();i++) std::<<v[i].first<<" "<<v[i].second<<" \\"; std::cout<<std::endl;
    #endif
    rebuildtree(v, 0, v.size()-1);						/*create a new tree pefectly balance.
	//	 													  Here we pass the order vector that has insede all the couple key,value of the old tree*/
	}

//rebuild the tree in balance version
 template <class Tk, class Tv, class Tc>
  void BST<Tk,Tv,Tc>::rebuildtree (std::vector<std::pair<Tk,Tv>>& values, int start, int end){

  		if(start > end){						/*if the start point is equal to the end point.
  										  		  it means that all the value in the vector were been put inside the new balance tree*/
  			return;								//you put all value. Finish
  		}

  		int middle = (end+start)/2;				//calculate the middle point in the vector. In the middle there is the intermediate value
  		insert(values[middle]);					//insert in the tree the intermediate value

  		rebuildtree(values,start,middle-1);	//recall the function for repeat the procedure
      rebuildtree(values, middle+1, end);
  	}

//save nodes of before the balance
 template <class Tk, class Tv, class Tc>
    	std::vector<std::pair<Tk,Tv>> BST<Tk,Tv,Tc>::BalancePrivate(){
    		std::vector<std::pair<Tk,Tv>> values;					//vector for save the value in the left part of ptr
			  Iterator start{this->begin()};
        Iterator end{this->end()};
        if(start==end) //tree is Empty
         return values;
        else
        {
          for(; start!=end; ++start)
           {values.push_back(*start);}
          return values;
        }
     	}
