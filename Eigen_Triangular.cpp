#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace std;

template <typename T>
class SymMat
{
  vector<T> V;
  int rows, cols;
public:
  SymMat()    //Non-para Constructor
  {
    rows=cols=0;
  }
  template <typename D>
  SymMat(Eigen::MatrixBase<D>& M)    //Para Constructor
  {
    rows = M.rows();
    cols = M.cols();
    for(int i=0; i<cols; i++)
    {
      for(int j=i; j<rows; j++)
      {
        V.push_back(M(i,j));
      }
    }
  }

  SymMat<T> operator + (const SymMat<T> &Obj)   //Overload + for Sym
  {
    SymMat<T> S;
    S.rows = rows;
    S.cols = cols;
    for(int i=0; i<V.size(); i++)
    {
      S.V.push_back(V[i]+Obj.V[i]);
    }
    return S;
  }

  template <typename D>
  SymMat<T> operator + (const Eigen::MatrixBase<D> &Obj)   //Overload + for Eigen
  {
    //SymMat<T> S_1(Obj);
    SymMat<T> S_2;
    S_2.rows = rows;
    S_2.cols = cols;
    /*
    for(int i=0; i<V.size(); i++)
    {
      S_2.V.push_back(V[i]+S_1.V[i]);
    }
    */
    int k=0;
    for(int i=0; i<cols; i++)
    {
      for(int j=i; j<rows; j++)
      {
        S_2.V.push_back(V[k]+Obj(i,j));
        k++;
      }
    }
    return S_2;
  }

  T Access(int r, int c)      //Access specific Position
  {
    int k=0;
    int flag=0;
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

  friend ostream & operator << (ostream &out, const SymMat<T> &S)
  {
    for(int i=0; i<S.V.size(); i++)
    {
      out<<S.V[i];
      out<<" ";
    }
  }
};

int main()
{
  Eigen::MatrixXi M1(3,3);
  M1 << 1,2,3,4,5,6,7,8,9;
  Eigen::MatrixXi M2(3,3);
  M2 << 1,1,1,1,1,1,1,1,1;
  Eigen::MatrixXi M3(3,3);
  M3 << 1,1,1,1,1,1,1,1,1;
  SymMat<int> S1(M1);
  SymMat<int> S2(M2);
  SymMat<int> S3;
  cout<<"\nSymMat 1: ";
  cout<<S1;
  cout<<"\nSymMat 2: ";
  cout<<S2;
  S3 = S1 + S2;
  cout<<"\nSymMat 3: ";
  cout<<S3;
  S3 = S1 + M3;
  cout<<"\nSymMat 3: ";
  cout<<S3;
  cout<<endl;
  return 0;
}
