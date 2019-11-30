#ifndef MATRIXTYPE_HPP
#define MATRIXTYPE_HPP

#include <iostream>
#include <iomanip>
#include <map>
#include "matrixException.hpp"

/**
  * @brief Base class for matrix implementations.
  * Matrix can either be dense or sparse. This class unifies different implementations.
  */
class MatrixType{
  protected:
    size_t r, ///< Number of rows.
           c; ///< Number of columns.
  public:
    /**
      * @brief Constructs matrix with dimensions r x c.
      * @param r number of rows
      * @param c number of columns
      */
    MatrixType(size_t r, size_t c);
    /**
      * @brief Default destructor.
      */           
    virtual ~MatrixType() = default;
    
    /**
      * @brief Computes ratio of elements equal to zero.
      * Ratio is computed as count of all zero elements divided by count of all elements.
      * @return ratio
      */
    double getRatioOfZeros() const;
    /**
      * @brief Returns value of the element in <i>i</i>-th row and <i>j</i>-th column.
      * @param i row
        @param j column
      * @return value
      */
    virtual double getValue(size_t i, size_t j) const = 0;
    /**
      * @brief Inserts <i>x</i> in <i>i</i>-th row and <i>j</i>-th column.
      * @param i row
      * @param j column
      * @param x value of inserted element
      */
    virtual void setValue(size_t i, size_t j, double x) = 0;

    /**
      * @brief Swaps <i>i</i>-th and <i>j</i>-th row.
      * If non-existing row is selected then nothing happens.
      * @param i row
      * @param j row
      * @sa Gem
      */
    void swapRows(size_t i, size_t j);
    /**
      * @brief Multiplies <i>i</i>-th row by <i>x</i>.
      * Every element in the <i>i</i>-th row is multiplied by <i>x</i>. If <i>x</i> is
      * equal to zero or non-existing row is selected then nothing happens.
      * @param i row
      * @param x multiplier
      * @sa Gem
      */ 
    void multiplyRow(size_t i, double x);
    /**
      * @brief Adds <i>j</i>-th row multiplied by x to <i>i</i>-th row.
      * If <i>x</i> is equal to zero or non-existing row is selected then nothing happens.
      * @param i row
      * @param j row
      * @param x multiplier
      * @sa Gem
      */
    void addRow(size_t i, size_t j, double x);
    /**
      * @brief Counts zero rows.
      * Zero rows are the rows where every element of that row is equal to zero.
      * @return number of non-zero rows
      */
    unsigned int countZeroRows() const;

    /**
      * @brief Prints matrix.
      * Elements are printed with the width 6. There is a newline after the last row.
      * @param os output stream
      * @param x matrix
      * @return os output stream
      */
    friend std::ostream & operator <<(std::ostream & os, const MatrixType & x);
    /**
      * @brief Scans matrix.
      * 
      * @param is input stream
      * @param x matrix
      * @return is input stream
      */
    friend std::istream & operator >>(std::istream & is, MatrixType & x);
};

#endif /* MATRIXTYPE_HPP */
