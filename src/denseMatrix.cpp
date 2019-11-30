#include "denseMatrix.hpp"

DenseMatrix::DenseMatrix(size_t r, size_t c) : MatrixType(r, c){
  data = new double * [r];
  for(size_t i = 0; i < r; ++i){
    data[i] = new double [c];
    for(size_t j = 0; j < c; ++j)
      data[i][j] = 0;
  }
}
//---------------------------------------------------------------------------------------
DenseMatrix::~DenseMatrix(){
  for(size_t i = 0; i < r; ++i)
    delete [] data[i];
  delete [] data;
}
//---------------------------------------------------------------------------------------
double DenseMatrix::getValue(size_t i, size_t j) const{
  return data[i][j];
}
//---------------------------------------------------------------------------------------
void DenseMatrix::setValue(size_t i, size_t j, double x){
  data[i][j] = x;
}
