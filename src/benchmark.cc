#include<iostream>
#include<fstream>
#include<map> //std::map
#include<unordered_map> //std::unordered_map
#include<memory>
#include<utility>
#include<algorithm> //std::random_shuffle
#include<chrono>
#include<vector>

#include"BST.h"

int N = 20000;

//function used to time spent to search nsearch element in a container of type B
template<class T, class V>
void test(std::ofstream& file, T& B, std::vector<V>& v)
{
  for(int nsearch=50; nsearch<N; nsearch+=50)
    {
      auto begin =std::chrono::high_resolution_clock::now();
      for (int i=0u; i<nsearch; ++i)
	B.find(v[i]);
      auto end = std::chrono::high_resolution_clock::now();
      auto total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
      file << total/double(nsearch) << "\n";
    }
}


int main()
{
  /** comparison of the time to find some elements */
  /** in the case of the bst both balanced and non-balanced */
  /** with different data type */

  //timing for the bst

  //key is int
  BST<int,int> bst_int; //non balanced random tree
  BST<int,int> bst_int_b; //balanced tree

  std::vector<int> ordered_int(N);
  for(int i=0; i<N; ++i)
    ordered_int.at(i)=i;

  std::vector<int> random_int = ordered_int;
  std::random_shuffle(random_int.begin(), random_int.end());

  for(auto x: random_int)
    bst_int.insert({x,x});
    
  

  //timing int bst
  std::ofstream file;

  for(int i=1; i<=5; ++i)
  {file.open("test/random_int_"+std::to_string(i)+".txt");
  test(file, bst_int, random_int);
  file.close();}

  bst_int.Balance();
  
  for(int i=1; i<=5; ++i) 
  {file.open("test/balanced_int_"+std::to_string(i)+".txt");
  test(file, bst_int_b, random_int);
  file.close();}

  //key is double
  BST<double,int> bst_d; //non balanced random tree
  BST<double,int> bst_d_b; //balanced tree

  std::vector<double> ordered_d(N);
  for(int i=0; i<N; ++i)
    ordered_d.at(i)=i*0.42+1.3;

  std::vector<double> random_d = ordered_d;
  std::random_shuffle(random_d.begin(), random_d.end());
    
  for(auto x: random_d)
    bst_d.insert({x,2});

 

  //timing double bst

  for(int i=1; i<=5; ++i)
  {file.open("test/random_double_"+std::to_string(i)+".txt");
  test(file, bst_d, random_d);
  file.close();}

  bst_d.Balance();

  for(int i=1; i<=5; ++i)
  {file.open("test/balanced_double_"+std::to_string(i)+".txt");
  test(file, bst_d_b, random_d);
  file.close();}

  //maps
  std::map<int,int> map;
  std::unordered_map<int,int> umap;
  for(auto x:ordered_int)
    {
      map.insert({x,x});
      umap.insert({x,x});
    }

  //timing map
  for(int i=1; i<=5; ++i)
  {file.open("test/map_"+std::to_string(i)+".txt");
  test(file, map, ordered_int);
  file.close();}

  for(int i=1; i<=5; ++i)
  {file.open("test/umap_"+std::to_string(i)+".txt");
  test(file, umap, ordered_int);
  file.close();}
  
}
