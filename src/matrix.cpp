#include "matrix.hpp"

using namespace std;

const char * Matrix::DIMENSION = "Wrong dimensions!";
const char * Matrix::SINGULAR = "Singular matrix!"; 
const double Matrix::DENSITY_TRESHOLD = 0.6;

void Matrix::copyMatrix(MatrixType * const & src, MatrixType * & out) const{
  for(size_t i = 0; i < r; ++i)
    for(size_t j = 0; j < c; ++j)
      out->setValue(i, j, src->getValue(i, j));
}
//---------------------------------------------------------------------------------------
Matrix::Matrix(size_t r, size_t c, MatrixType * data) : r(r), c(c), matrix(data){
  if(r == 0 || c == 0)
    throw MatrixException(DIMENSION);
  if(matrix == NULL){
    matrix = new SparseMatrix(r, c);
    return;
  }
  checkCountOfZeros();
}
//---------------------------------------------------------------------------------------
Matrix::Matrix(const Matrix & other) : r(other.r), c(other.c), isDense(other.isDense){
  if(isDense)
    matrix = new DenseMatrix(r, c);
  else
    matrix = new SparseMatrix(r, c);
  copyMatrix(other.matrix, matrix);
  checkCountOfZeros();
}
//---------------------------------------------------------------------------------------
Matrix & Matrix::operator =(const Matrix & other){
  if(this == &other)
    return *this;
  delete matrix;
  r = other.r;
  c = other.c;
  isDense = other.isDense;
  if(isDense)
    matrix = new DenseMatrix(r, c);
  else
    matrix = new SparseMatrix(r, c);
  copyMatrix(other.matrix, matrix);
  checkCountOfZeros();
  return *this;
}
//---------------------------------------------------------------------------------------
Matrix::~Matrix(){
  delete matrix;
}
//---------------------------------------------------------------------------------------
void Matrix::checkCountOfZeros(){
  double tmp = matrix->getRatioOfZeros();
  if((isDense && tmp >= DENSITY_TRESHOLD) || (!isDense && tmp <= DENSITY_TRESHOLD))
    useOtherTypeOfMatrix();
}
//---------------------------------------------------------------------------------------
void Matrix::useOtherTypeOfMatrix(){
  MatrixType * tmp;  
  if(isDense)
    tmp = new SparseMatrix(r, c);
  else
    tmp = new DenseMatrix(r, c);
  copyMatrix(matrix, tmp);
  delete matrix;
  isDense = !isDense;
  matrix = tmp; 
}
//---------------------------------------------------------------------------------------
Matrix Matrix::operator +(const Matrix & other) const{
  if(r != other.r || c != other.c)
    throw MatrixException(DIMENSION);
  MatrixType * tmp = new SparseMatrix(r, c);
  for(size_t i = 0; i < r; ++i)
    for(size_t j = 0; j < c; ++j)
      tmp->setValue(i, j, matrix->getValue(i, j) + other.matrix->getValue(i, j));
  return Matrix(r, c, tmp);
}
//---------------------------------------------------------------------------------------
Matrix Matrix::operator *(const Matrix & other) const{
  if(c != other.r)
    throw MatrixException(DIMENSION);
  MatrixType * tmp = new SparseMatrix(r, other.c);
  for(size_t i = 0; i < r; ++i)
    for(size_t j = 0; j < other.c; ++j){
      double val = 0;
      for(size_t k = 0; k < c; ++k)
        val += matrix->getValue(i, k) * other.matrix->getValue(k, j);
      tmp->setValue(i, j, val);
    }
  return Matrix(r, other.c, tmp);
}
//---------------------------------------------------------------------------------------
Matrix operator *(double x, const Matrix & m){
  MatrixType * tmp = new SparseMatrix(m.r, m.c);
  for(size_t i = 0; i < m.r; ++i)
    for(size_t j = 0; j < m.c; ++j)
      tmp->setValue(i, j, x * m.matrix->getValue(i, j));
  return Matrix(m.r, m.c, tmp);
}
//---------------------------------------------------------------------------------------
Matrix Matrix::operator -(const Matrix & other) const{
  return *this + (-1 * other);
}
//---------------------------------------------------------------------------------------
Matrix & Matrix::operator =(double x){
  for(size_t i = 0; i < r; ++i)
    matrix->setValue(i, i, x);
  checkCountOfZeros();
  return *this;
}
//---------------------------------------------------------------------------------------
Matrix & Matrix::operator +=(const Matrix & other){
  return (*this = *this + other);
}
//---------------------------------------------------------------------------------------
Matrix & Matrix::operator -=(const Matrix & other){
  return (*this = *this - other);
}
//---------------------------------------------------------------------------------------
Matrix & Matrix::operator *=(const Matrix & other){
  return (*this = *this * other);
}
//---------------------------------------------------------------------------------------
Matrix & operator *=(Matrix & m, double x){
  return (m = x * m);
}
//---------------------------------------------------------------------------------------
Matrix Matrix::merge(const Matrix & other) const{
  if(r != other.r)
    throw MatrixException(DIMENSION);
  MatrixType * tmp = new SparseMatrix(r, c + other.c);
  for(size_t i = 0; i < r; ++i){
    for(size_t j = 0; j < c; ++j)
      tmp->setValue(i, j, matrix->getValue(i, j));
    for(size_t j = 0; j < other.c; ++j)
      tmp->setValue(i, j + c, other.matrix->getValue(i, j));
  }
  return Matrix(r, c + other.c, tmp);
}
//---------------------------------------------------------------------------------------
Matrix Matrix::split(size_t newR, size_t newC, size_t posR, size_t posC) const{
  if(posR + newR - 1 > r || posC + newC - 1 > c)
    throw MatrixException(DIMENSION);
  MatrixType * tmp = new SparseMatrix(newR, newC);
  for(size_t i = 0; i < newR; ++i)
    for(size_t j = 0; j < newC; ++j)
      tmp->setValue(i, j, matrix->getValue(posR + i, posC + j));
  return Matrix(newR, newC, tmp);
}
//---------------------------------------------------------------------------------------
Matrix Matrix::gem(gemStates printDetail, double & out) const{
  MatrixType * tmp = new SparseMatrix(r, c);
  copyMatrix(matrix, tmp);
  Gem g(r, c, tmp, printDetail);
  g.gem();
  out = g.getDeterminant();
  return Matrix(r, c, tmp);
}
//---------------------------------------------------------------------------------------
Matrix Matrix::gem(gemStates printDetail) const{
  double tmp = 0;
  return gem(printDetail, tmp);
}
//---------------------------------------------------------------------------------------
unsigned int Matrix::rank() const{
  Matrix tmp = gem();
  return tmp.matrix->countZeroRows();
}
//---------------------------------------------------------------------------------------
Matrix Matrix::transpose() const{
  MatrixType * tmp = new SparseMatrix(c, r);
  for(size_t i = 0; i < c; ++i)
    for(size_t j = 0; j < r; ++j)
      tmp->setValue(i, j, matrix->getValue(j, i));
  return Matrix(c, r, tmp);
}
//---------------------------------------------------------------------------------------
Matrix Matrix::inverse() const{
  if(r != c)
    throw MatrixException(DIMENSION);
  if(rank() != r)
    throw MatrixException(SINGULAR);
  Matrix e(r, c);
  e = 1;
  Matrix tmp = *this;
  tmp = tmp.merge(e).gem().split(r, c, 0, c);
  return tmp;
}
//---------------------------------------------------------------------------------------
double Matrix::determinant() const{
  if(r != c)
    throw MatrixException(DIMENSION);
  if(rank() != r)
    return 0;
  double out = 1;
  Matrix tmp = gem(gemStates::NO_DETAILS, out);
  return out;
}
//---------------------------------------------------------------------------------------
ostream & operator <<(ostream & os, const Matrix & x){
  return os << *(x.matrix);
}
//---------------------------------------------------------------------------------------
istream & operator >>(istream & is, Matrix & x){
  is >> *(x.matrix);
  x.checkCountOfZeros();
  return is;
}
