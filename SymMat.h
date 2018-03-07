/**
    Faster Matrix Algebra for ATLAS: Evaluation Test (GSoC 2018)
    Eigen_Triangular.cpp
    Purpose: To make a class, SymMat, accomodating symmetric matrices with
    Eigen Matrices. Operations to be defined-
    a) SymMat + & - SymMat
    b) SymMat + & - Eigen::Matrix
    c) SymMat * SymMat
    d) SymMat * Eigen::Matrix

    @author Adarsh Pal Singh
*/
#ifndef SYMMAT_H
#define SYMMAT_H

#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace std;

/**
    Templated Class SymMat
*/
template <typename T>
class SymMat
{
  vector<T> V;     //To store the upper triangular part of the Eigen Matrix.
  int rows, cols;  //To store the number of rows, columns in the Eigen Matrix.

public:

  /**
      Non-parametrized constructor which is invoked when no Eigen Matrix is
      passed as an argument. Sets the number of rows and columns to 0.

      @param None
      @return NA
  */
  SymMat();

  /**
      Parametrized constructor that accepts an arbitrary Eigen Matrix and
      converts it into a linear array consisting of upper triangular elements.

      @param Eigen Matrix.
      @return NA
  */
  template <typename D>
  SymMat(Eigen::MatrixBase<D>&);

  /**
      Returns the element in (row, column) position of a SymMat. Note that for a
      symmetric matrix, element at (i,j) = element at (j,i).

      @param Row and column position.
      @return Element at specified row and position.
  */
  T Access(int, int);

  /**
      Operator '+' overloaded to account for addition of two symmetric matrices.

      @param SymMat object.
      @return The sum of SymMat and SymMat.
  */
  SymMat<T> operator + (const SymMat<T>&);

  /**
      Operator '-' overloaded to account for subtraction of two symmetric matrices.

      @param SymMat object.
      @return The difference of SymMat and SymMat.
  */
  SymMat<T> operator - (const SymMat<T> &Obj);

  /**
      Operator '+' overloaded to account for addition of a SymMat and Eigen Matrix.

      @param Eigen Matrix.
      @return The sum of SymMat and Eigen Matrix.
  */
  template <typename D>
  SymMat<T> operator + (const Eigen::MatrixBase<D>&);

  /**
      Operator '-' overloaded to account for sutraction of a SymMat and Eigen
      Matrix.

      @param Eigen Matrix.
      @return The difference of SymMat and Eigen Matrix.
  */
  template <typename D>
  SymMat<T> operator - (const Eigen::MatrixBase<D>&);

  /**
      Operator '*' overloaded to account for multiplication between a SymMat and
      SymMat.

      @param SymMat object.
      @return The product of SymMat and SymMat.
  */
  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> operator * (SymMat<T>&);

  /**
      Operator '*' overloaded to account for multiplication between a SymMat and
      an Eigen Matrix.

      @param Eigen Matrix.
      @return The product of SymMat and Eigen Matrix.
  */
  template <typename D>
  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> operator * (const Eigen::MatrixBase<D>&);

  /**
      Operator '<<' overloaded to display the contents of SymMat.

      @param Reference to ostream object, SymMat object to be displayed.
      @return ostream object
  */
  template <typename U>
  friend ostream & operator << (ostream&, const SymMat<U>&);

};

template <typename T>
SymMat<T>::SymMat()
{
  rows=cols=0;
}

template <typename T>
template <typename D>
SymMat<T>::SymMat(Eigen::MatrixBase<D>& M)
{
  rows = M.rows();
  cols = M.cols();
  try
  {
    if(rows!=cols)
      throw "\nError: Input Matrix is not a square matrix!";
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(0);
  }

  //Visit only the upper triangular positions
  for(int i=0; i<cols; i++)
  {
    for(int j=i; j<rows; j++)
    {
      V.push_back(M(i,j));
    }
  }
}

template <typename T>
T SymMat<T>::Access(int r, int c)
{
  int k=0;
  int flag=0;
  try
  {
    if(r>=rows || c>=cols)
      throw "\nError: The specified element to access is beyond the matrix";
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(1);
  }
  if(r>c)  //If the element to return is in lower triangular part
  {
    int temp = r;
    r=c;
    c=temp;
  }
  for(int i=0; i<rows; i++)
  {
    for(int j=i; j<rows; j++)
    {
      if (i==r && j==c)
      {
        flag=1;
        break;
      }
      else
        k++;
    }
    if(flag==1)
      break;
  }
  return V[k];
}

template <typename T>
SymMat<T> SymMat<T>::operator + (const SymMat<T> &Obj)
{
  try
  {
    if(rows!=Obj.rows || cols!=Obj.cols)
      throw "\nError: Cannot Add matrices of different orders!";
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(2);
  }
  SymMat<T> S;
  S.rows = rows;
  S.cols = cols;
  for(int i=0; i<V.size(); i++)
  {
    S.V.push_back(V[i]+Obj.V[i]);
  }
  return S;
}

template <typename T>
SymMat<T> SymMat<T>::operator - (const SymMat<T> &Obj)
{
  try
  {
    if(rows!=Obj.rows || cols!=Obj.cols)
      throw "\nError: Cannot Subtract matrices of different orders!";
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(2);
  }
  SymMat<T> S;
  S.rows = rows;
  S.cols = cols;
  for(int i=0; i<V.size(); i++)
  {
    S.V.push_back(V[i]-Obj.V[i]);
  }
  return S;
}

template <typename T>
template <typename D>
SymMat<T> SymMat<T>::operator + (const Eigen::MatrixBase<D> &Obj)
{
  try
  {
    if(rows!=Obj.rows() || cols!=Obj.cols())
      throw "\nError: Cannot Add matrices of different orders!";
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(2);
  }
  SymMat<T> S;
  S.rows = rows;
  S.cols = cols;
  int k=0;

  for(int i=0; i<cols; i++)
  {
    for(int j=i; j<rows; j++)
    {
      S.V.push_back(V[k]+Obj(i,j));
      k++;
    }
  }
  return S;
}

template <typename T>
template <typename D>
SymMat<T> SymMat<T>::operator - (const Eigen::MatrixBase<D> &Obj)
{
  try
  {
    if(rows!=Obj.rows() || cols!=Obj.cols())
      throw "\nError: Cannot Subtract matrices of different orders!";
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(2);
  }
  SymMat<T> S;
  S.rows = rows;
  S.cols = cols;
  int k=0;
  for(int i=0; i<cols; i++)
  {
    for(int j=i; j<rows; j++)
    {
      S.V.push_back(V[k]-Obj(i,j));
      k++;
    }
  }
  return S;
}

template <typename T>
Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> SymMat<T>::operator * (SymMat<T> &Obj)
{
  try
  {
    if(cols!=Obj.rows)
      throw "\nError: The number of columns of Matrix 1 and the number of rows of Matrix 2 donot match!";
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(3);
  }
  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> M;
  M.resize(rows, Obj.cols);
  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < Obj.cols; j++)
    {
      M(i,j)=0;
      for(int k = 0; k < cols; k++)
        M(i,j) += ((this->Access(i,k)) * Obj.Access(k,j));
    }
  }
  return M;
}

template <typename T>
template <typename D>
Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> SymMat<T>::operator * (const Eigen::MatrixBase<D> &Obj)
{
  try
  {
    if(cols!=Obj.rows())
      throw "\nError: The number of columns of Matrix 1 and the number of rows of Matrix 2 donot match!";
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
    exit(3);
  }
  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> M;
  M.resize(rows, Obj.cols());
  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < Obj.cols(); j++)
    {
      M(i,j)=0;
      for(int k = 0; k < cols; k++)
        M(i,j) += ((this->Access(i,k)) * Obj(k,j));
    }
  }
  return M;
}

template <typename U>
ostream & operator << (ostream& out, const SymMat<U>& S)
{
  for(int i=0; i<S.V.size(); i++)
  {
    out<<S.V[i];
    out<<" ";
  }
}

#endif
