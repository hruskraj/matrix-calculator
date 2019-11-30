#ifndef DENSEMATRIX_HPP
#define DENSEMATRIX_HPP

#include "matrixType.hpp"

/**
  * @brief Implementation of matrix as 2D array.
  * 
  * This implementation is used for dense matrices. Dense matrix is a matrix where only  
  * a few elements are equal to zero.
  */
class DenseMatrix : public MatrixType{
  private:
    double ** data; ///< 2D array where elements are stored.
  public:
    /**
      * @brief Constructs matrix with dimensions r x c.
      * @param r number of rows
      * @param c number of columns
      */
    DenseMatrix(size_t r, size_t c);
    /**
      * @brief Frees allocated memory.
      */ 
    ~DenseMatrix();
    
    virtual double getValue(size_t i, size_t j) const;
    virtual void setValue(size_t i, size_t j, double x);
};

#endif /* DENSEMATRIX_HPP */
