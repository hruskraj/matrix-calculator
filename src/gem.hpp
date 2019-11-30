#ifndef GEM_HPP
#define GEM_HPP

#include "matrixType.hpp"
#include <iostream>

enum class gemStates{DETAILS, NO_DETAILS}; ///<Whether to print details or not.

/**
  * @brief Makes Gaussian elimination method.
  */
class Gem{
  private:
    size_t r, ///< Number of rows.
           c; ///< Number of columns.
    MatrixType * m; ///< Matrix.
    double det = 1; ///< Determinant.
    gemStates print; ///< Print details.

    /**
      * @brief Finds next element which eliminates rows.
      *
      * For a given column <i>l</i> finds row <i>i</i> (<i>i</i> >= <i>k</i>) such that
      * element in <i>i</i>-th row and <i>l</i>-th column is not equal to zero. If
      * there is not any row like that then next column is selected. If there are none
      * columns left then function returns false. If row <i>i</i> was found then
      * function swaps rows <i>i</i> and <i>k</i>. Finally, in <i>k</i>-th row and
      * <i>l</i>-th column is a  non-zero element which can eliminate rows below it.
      *
      * @param[in, out] k row 
      * @param[in, out] l column
      * @return true if element was found and false otherwise.
      */
    bool findNext(size_t & k, size_t & l);
    /** 
      * @brief Eliminates rows below given row.
      *
      * First of all, <i>k</i>-th row is divided by element in <i>k</i>-th row and
      * <i>l</i>-th column. Then, multiple of this row is added to rows which are below
      * such that in <i>l</i>-th column of those rows is zero.
      *  
      * @param row row
      * @param col column
      */
    void eliminate(size_t row, size_t col);
    /**
      * @brief Eliminates rows above every 1.
      */
    void makeReduced();
  public:
    /**
      * @brief Initializes GEM.
      * @param r number of rows
      * @param c number of columns
      * @param matrix matrix
      * @param print print details
      */
    Gem(size_t r, size_t c, MatrixType * & matrix, gemStates print = gemStates::NO_DETAILS);
    /**
      * @brief Performs Gaussian elimination method.
      */
    void gem();
    /**
      * @brief Returns determinant.
      * Determinant is computed during GEM even when it is not a square matrix.
      */
    double getDeterminant() const;
};

#endif /* GEM_HPP */
