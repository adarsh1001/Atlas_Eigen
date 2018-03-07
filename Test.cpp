#include <iostream>
#include <Eigen/Dense>

#include "SymMat.h"

using namespace std;

int main()
{
  Eigen::MatrixXi M1(3,3);              //3x3 Integer Eigen Matrix M1
  M1 << 1,2,3,4,5,6,7,8,9;              //Initialize M1
  SymMat<int> S1(M1);                   //Make SymMat S1 from M1
  cout<<"Eigen Matrix M1-\n"<<M1;
  cout<<"\nSymMat S1-\n";
  cout<<S1;

  Eigen::MatrixXi M2(3,3);              //3x3 Integer Eigen Matrix M2
  M2 << 9,8,7,6,5,4,3,2,1;              //Initialize M2
  SymMat<int> S2(M2);                   //Make SymMat S2 from M2
  cout<<"\n\nEigen Matrix M2-\n"<<M2;
  cout<<"\nSymMat S2-\n";
  cout<<S2;

  Eigen::MatrixXi M3(3,3);

  SymMat<int> S3;

  S3 = S1 + S2;                         //SymMat + SymMat
  cout<<"\n\nSymMat S3=S1+S2-\n";
  cout<<S3;

  S3 = S1 + M2;                         //SymMat + Eigen::Matrix
  cout<<"\n\nSymMat S3=S1+M2-\n";
  cout<<S3;

  M3 = S1 * S2;                         //SymMat * SymMat
  cout<<"\n\nEigen Matrix M3=S1*S2-\n";
  cout<<M3;

  M3 = S1 * M2;                         //SymMat * Eigen::Matrix
  cout<<"\n\nEigen Matrix M3=S1*M2-\n";
  cout<<M3;
  cout<<endl;
  return 0;
}
