#include "sparseMatrix.hpp"

SparseMatrix::SparseMatrix(size_t r, size_t c) : MatrixType(r, c){
}
//---------------------------------------------------------------------------------------
double SparseMatrix::getValue(size_t i, size_t j) const{
  const auto & it = data.find(std::make_pair(i, j)); 
  if(it == data.end())
    return 0;
  return it->second;
}
//---------------------------------------------------------------------------------------
void SparseMatrix::setValue(size_t i, size_t j, double x){
  if(x == 0){
    const auto & it = data.find(std::make_pair(i, j));
    if(it != data.end())
      data.erase(it);
  }
  else
    data[std::make_pair(i, j)] = x;
}
