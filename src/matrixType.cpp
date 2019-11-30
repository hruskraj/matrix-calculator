#include "matrixType.hpp"

MatrixType::MatrixType(size_t r, size_t c) : r(r), c(c){
}
//---------------------------------------------------------------------------------------
double MatrixType::getRatioOfZeros() const{
  double count = 0;
  for(size_t i = 0; i < r; ++i)
    for(size_t j = 0; j < c; ++j)
      if(getValue(i, j) == 0)
        ++count;
  return count / (double) (r * c);
}
//---------------------------------------------------------------------------------------
void MatrixType::swapRows(size_t i, size_t j){
  if(i >= r || j >= r)
    return;
  for(size_t k = 0; k < c; ++k){
    double tmp = getValue(i, k);
    setValue(i, k, getValue(j, k));
    setValue(j, k, tmp);
  }
}
//---------------------------------------------------------------------------------------
void MatrixType::multiplyRow(size_t i, double x){
  if(i >= r || x == 0)
    return;
  for(size_t k = 0; k < c; ++k)
    setValue(i, k, getValue(i, k) * x);
}
//---------------------------------------------------------------------------------------
void MatrixType::addRow(size_t i, size_t j, double x){
  if(i >= r || j >= r || x == 0)
    return;
  for(size_t k = 0; k < c; ++k)
    setValue(i, k, getValue(i, k) + getValue(j, k) * x);
}
//---------------------------------------------------------------------------------------
unsigned int MatrixType::countZeroRows() const{
  //set count as maximum
  unsigned int count = r;
  for(size_t i = 0; i < r; ++i){
    //assume this is zero row
    bool zero = true;
    for(size_t j = 0; j < c; ++j)
      //if non-zero element is found then this is not a zero row
      if(getValue(i, j) != 0){
        zero = false;
        break;
      }
    //if this is zero row then decrement number of non-zero rows 
    if(zero) 
      --count;
  }
  return count;
}
//---------------------------------------------------------------------------------------
std::ostream & operator <<(std::ostream & os, const MatrixType & x){
  for(size_t i = 0; i < x.r; ++i){
    for(size_t j = 0; j < x.c; ++j){
      double val = x.getValue(i, j);
      os << std::setw(6) << ((val == -0) ? 0 : val) << ((j != x.c - 1) ? " " : "");
    }
    os << std::endl;
  }
  return os;
}
//---------------------------------------------------------------------------------------
std::istream & operator >>(std::istream & is, MatrixType & x){
  double tmp;
  for(size_t i = 0; i < x.r; ++i){
    for(size_t j = 0; j < x.c; ++j){
      is >> tmp;
      if(!is.good())
        throw MatrixException("Illegal value!");
      x.setValue(i, j, tmp);
    }
  }
  return is;
}
