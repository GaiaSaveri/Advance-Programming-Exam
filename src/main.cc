#include"BST.h"


int main()
{
 try 
 {
  /** testing binary search tree constructors */
  BST<int,int> bst0{}; //default ctor
  std::cout << "Default constructed empty tree:" <<std::endl;
  std::cout << bst0; 
  std::cout<<std::endl;
  std::pair<int, int> pair0=std::make_pair(0, 1);
  BST<int,int> bst1{pair0}; //custom ctor
  std::cout << "Custom constructed tree with (0:1):"<<std::endl; 
  std::cout << bst1; 
  std::cout << std::endl;

  /** testing clear function */
  BST<int,int> bst3{pair0}; 
  bst3.clear();
  std::cout << "Cleared previous tree: "<<std::endl;
  std::cout << bst3; 
  std::cout << std::endl;

  /** testing copy semantics */
  BST<int,int> bst2{bst1}; //copy ctor
  bst0 = bst1; //copy assignment //test with some print possibly
  std::cout << "Testing copy semantics:"<<std::endl;
  std::cout << "Original tree:" <<std::endl;
  std::cout<< bst1; 
  std::cout << std::endl;
  std::cout << "Copied trees: "<< std::endl;
  std::cout << bst2; 
  std::cout << std::endl;
  std::cout << bst1; 
  std::cout << std::endl;
  std::cout << "Objects are identical: "<<std::endl;
  bool id = (*bst2.find(0) == *bst1.find(0));
  std::cout << id << " (expected 1)" <<std::endl;
  std::cout << "Copy is actually deep copy: " <<std::endl;
  bool ref = (&(*bst2.find(0)) == &(*bst1.find(0)));
  std::cout << ref << " (expected 0)" << std::endl;
  //testing also operators == and != of iterators
  
  

  /** testing move semantics */
  BST<int,int> bst4{std::move(bst0)}; //move ctor  
  std::cout << "Original trees are empty: "<<std::endl;
  std::cout << bst0;
  std::cout << std::endl;
  bst0 = std::move(bst1); //move assignment
  std::cout << bst1;
  std::cout << std::endl;
  std::cout << "Trees constructed by moving: "<<std::endl;
  std::cout << bst4; 
  std::cout << std::endl;
  std::cout << bst0; 
  std::cout << std::endl;
  

  /** testing the three methods to insert elements */
  BST<int,int> bst_int;
  std::pair<int,int> p8{8,8};
  std::pair<int,int> p6{6,6};
  std::pair<int,int> p10{10,10};
  std::pair<int,int> p3{3,3};
  std::pair<int,int> p7{7,7};
  std::pair<int,int> p2{2,2};
  std::pair<int,int> p15{15,15};
  std::pair<int,int> p4{4,4};
  std::pair<int,int> p12{12,12};
  
  /** testing insert */
  (void)bst_int.insert(p8); //purposely ignoring return value
  bool t = bst_int.insert(p10).second;
  std::cout<<"insert (expected 1): "<<t<<std::endl; //should return 1
  bool f = bst_int.insert({8,9}).second;
  std::cout<<"insert (expected 0): "<<f<<std::endl; //should return 0
  //testing also -> of iterators
  

  /** testing operator[] */
  std::cout<<"[8]: "<<bst_int[8]<<" (expected 8)"<<std::endl; //rv[] 
  std::cout<<"[3]: "<<bst_int[p3.first]<<" (expected 0)"<<std::endl; 
  //lv[]+i
  std::cout<<bst_int.insert(p3).second<<"      (expected 0)"<<std::endl; 
  std::cout<<"[2]: "<<bst_int[2]<<" (expected 0)"<<std::endl; //rv[]+i
  std::cout<<"[8]: "<<bst_int[p8.first]<<" (expected 8)"<<std::endl; 
  //lv[]

  
  /** testing find */
  auto it = bst_int.find(8);
  std::cout<<"("<<(*it).first<<","<<(*it).second<<")"<<"  (expected(8,8))"<<std::endl; 
  //tested also Iterator::operator*()
  auto it2 = bst_int.find(3);
  std::cout<<"("<<(*it2).first<<","<<(*it2).second<<")"<<"  (expected(3,0))"<<std::endl; 
  //tested also Iterator::operator*()
  auto it3 = bst_int.find(0);
  if(it3==bst_int.end()) std::cout<<"find is ok!"<<std::endl;


  BST<int,int> tree;
  tree.insert(p8);
  tree.insert(p6);
  tree.insert(p10);
  tree.insert(p3);
  tree.insert(p7);
  tree.insert(p2);
  tree.insert(p15);
  tree.insert(p4);
  tree.insert(p12);
  
  /** testing emplace */
  tree.emplace(1,1); 
  tree.emplace(9,9);
  
  /** testing print */
  std::cout << tree;
  std::cout<<std::endl;
  
  /** testing erase */
  tree.PrintChildren(1);
  tree.erase(1); 
  std::cout << tree;
  std::cout<<std::endl;
  tree.PrintChildren(12);
  tree.erase(12); 
  std::cout << tree;
  std::cout<<std::endl;
  tree.PrintChildren(6);
  tree.erase(6); 
  std::cout << tree;
  std::cout<<std::endl;
  tree.PrintChildren(9);
  tree.erase(9);
  std::cout << tree;
  std::cout<<std::endl;
  tree.PrintChildren(8);
  tree.erase(8);
  tree.PrintChildren(10);
  std::cout << tree;
  std::cout<<std::endl;
  tree.PrintChildren(7);
  tree.erase(7);
  std::cout << tree;
  std::cout<<std::endl;
   
  
  /** testing balance */
  #ifdef PRINT
  std::cout << "Non balanced tree:" << std::endl;
  std::cout << tree;
  std::cout<<"\n"<<"\n"<<"\n";
  std::cout << "Balanced tree: "<< std::endl;
  tree.Balance();
  std::cout << tree;
  #endif
   } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  
}
