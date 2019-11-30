#ifndef SPARSEMATRIX_HPP
#define SPARSEMATRIX_HPP

#include "matrixType.hpp"

/**
  * @brief Implementation of matrix as map.
  * 
  * This implementation is used for sparse matrices. Sparse matrix is a matrix where only  
  * a few elements are not equal to zero.
  */
class SparseMatrix : public MatrixType{
  private:
    std::map<std::pair<size_t, size_t>, double> data; ///< Map where elements are stored.
  public:
    /**
      * @brief Constructs matrix with dimensions r x c.
      * @param r number of rows
      * @param c number of columns
      */
    SparseMatrix(size_t r, size_t c);

    virtual double getValue(size_t i, size_t j) const;
    virtual void setValue(size_t i, size_t j, double x);
};

#endif /* SPARSEMATRIX_HPP */
