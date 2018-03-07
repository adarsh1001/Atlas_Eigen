# Faster Matrix Algebra for ATLAS (GSoC-18' Evaluation Test)

In this project, a standalone C++ class was built which can work with Symmetric Matrices on top of the Eigen Library. Working only with the upper/lower triangular part of a symmetric matrix reduces the storage space as well as the complexity for different matrix operations considerably. The following operations were implemented-
1. SymMat +&- SymMat
2. SymMat +&- Eigen::Matrix
3. SymMat * SymMat
4. SymMat * Eigen::Matrix

Eval Link: https://github.com/StewMH/GSoC2018/blob/master/evaluation_test.pdf

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

1. Install the latest Eigen library (http://eigen.tuxfamily.org/index.php?title=Main_Page). Make sure that the Eigen folder is in your include path (/usr/local/include).

2. Latest g++ compiler.

## Running the tests

The Test.cpp file shows a few examples of addition and multiplication cases. Follow the following points to get the Test file up and running-

1. Clone the repository.

```
git clone https://github.com/adarsh1001/Atlas_Eigen.git
```

2. Compile the Test.cpp with g++.

```
g++ Test.cpp -o Test
```

3. Execute the run file

```
./Test
```

