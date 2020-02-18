## Binary Search Tree project 
Advanced Programming exam 2019-2020



Group composed by: Pinna Giovanni, Plasencia Milton and Saveri Gaia

# Structure of the repository

This repository contains the following folders:

* `include` which contains the headers `BST.h` (containg the interface for the Binary Search Tree), `methods.h` (containing the implementation of the methods of the Binary Search Tree), `iterators.h` (containing the implementation of the class iterator) and `node.h` (containing the implementation of the class node).

* `src` which contains the codes `main.cc`, used to test our `BST`, and `benchmark.cc`, used to benchmark the performances of the `BST`.

* `test` which contains the results of the benchmark we performed, along with the corresponding graphs contained in the Report. 

* `Doxygen` containing the `doxy.in` file, used to produced the Doxygen style documentation.

The `Makefile` is used to compile the codes inside the `src` folder and generate the documentation. By typing `make` in the terminal the executables `main.o` and `benchmark.o` are produced. By typing `make documentation` the Doxygen style documentation is produced, and two folders `latex` and `html` are created.

The `Report.md` contains a summary of our work, briefly explaining all the classes and functions we implemented and the results of our benchmark. 
