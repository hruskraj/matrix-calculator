#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "matrixType.hpp"
#include "denseMatrix.hpp"
#include "sparseMatrix.hpp"
#include "gem.hpp"
#include "matrixException.hpp"

/**
  * @brief Main class which handles matrix functions.
  */
class Matrix{
  private:
    size_t r, ///< Number of rows.
           c; ///< Number of columns.
    bool isDense = false; ///< Density.
    MatrixType * matrix; ///< Matrix.
    
    ///Error message for wrong dimensions.
    static const char * DIMENSION;
    ///Error message for singular matrix.
    static const char * SINGULAR;
    /**
      * @brief Treshold of density.
      * If ratio of zeros is greater than this treshold then sparse matrix is used.
      */
    static const double DENSITY_TRESHOLD;
    
    /**
      * @brief Checks ratio of zeros in matrix.
      * If another type of matrix is more suitable then this type is used.
      * @sa useOtherTypeOfMatrix, DENSITY_TRESHOLD, MatrixType::getRatioOfZeros
      */
    void checkCountOfZeros();
    /**
      * @brief Uses another type of matrix implementation.
      * If sparse matrix was used then new type would be dense matrix and vice versa.
      * @sa copyMatrix
      */
    void useOtherTypeOfMatrix();
    /**
      * @brief Makes copy of matrix.
      * @param src source
      * @param[out] out destination
      */
    void copyMatrix(MatrixType * const & src, MatrixType *& out) const;
    /**
      * @brief Performs Gaussian elimination method and computes determinant.
      * @param printDetails print details
      * @param[out] out determinant
      * @return reduced matrix
      * @sa Gem
      */
    Matrix gem(gemStates printDetails, double & out) const;
  public:

    /**
      * @brief Constructor.
      * If no matrix type is specified (data == NULL) then sparse matrix type is used and
      * all elements are equal to zero. Ratio of zero elements is checked. If no dimensions
      * are set then 3x3 matrix is created.
      * @param r rows
      * @param c columns
      * @param data matrix
      * @sa checkCountOfZeros
      */
    Matrix(size_t r = 3, size_t c = 3, MatrixType * data = NULL);
    /**
      * @brief Copy constructor.
      * Ratio of zero elements is checked.
      * @param other source
      */
    Matrix(const Matrix & other);
    /**
      * @brief Operator =
      * @param other source
      * @return this
      */
    Matrix & operator =(const Matrix & other);
    /**
      * @brief Destructor.
      */
    ~Matrix();

    /**
      * @brief Makes matrix which is sum of this matrix and other matrix.
      * @throw MatrixException
      * @param other other
      * @return Matrix sum
      */
    Matrix operator +(const Matrix & other) const;
    /**
      * @brief Makes matrix which is difference of this matrix and other matrix.
      * @throw MatrixException
      * @param other other
      * @return Matrix difference
      */
    Matrix operator -(const Matrix & other) const;
    /**
      * @brief Makes matrix which is multiplication of this matrix and other matrix.
      * @throw MatrixException
      * @param other other
      * @return Matrix multiplication
      */
    Matrix operator *(const Matrix & other) const;
    /**
      * @brief Makes matrix which is a scalar multiplication of a matrix.
      * @param x scalar
      * @param m matrix
      * @return Matrix
      */
    friend Matrix operator *(double x, const Matrix & m);

    /**
      * @brief Sets every element on main diagonal to x.
      * @param x value
      * @return this
      */
    Matrix & operator =(double x);

    /**
      * @brief Adds to this matrix another matrix.
      * @throw MatrixException
      * @param other other matrix
      * @return this
      */
    Matrix & operator +=(const Matrix & other);
    /**
      * @brief Substracts from this matrix another matrix.
      * @throw MatrixException
      * @param other other matrix
      * @return this
      */
    Matrix & operator -=(const Matrix & other);
    /**
      * @brief Multiplies this matrix by another matrix.
      * @throw MatrixException
      * @param other other matrix
      * @return this
      */
    Matrix & operator *=(const Matrix & other);
    /**
      * @brief Scalar multiplication of matrix <i>m</i>.
      * @param m matrix
      * @param x scalar
      * @return this
      */
    friend Matrix & operator *=(Matrix & m, double x);

    /**
      * @brief Makes matrix which is concatenation of this matrix and other matrix.
      * Matrices must have the same number of rows. Number of rows of the new matrix is
      * the sum of the numbers of columns of original matrices. 
      * @throw MatrixException
      * @param other other matrix
      * @return merged matrix
      */
    Matrix merge(const Matrix & other) const;
    /**
      * @brief Makes matrix from this matrix.
      * New matrix has dimensions newR x newC and the top left element of the new matrix
      * is in the <i>posR</i>-th row and <i>posC</i>-th column.
      * @throw MatrixException
      * @param newR number of rows of new matrix
      * @param newC number of columns of new matrix
      * @param posR row where the top left element is located
      * @param posC column where the top left element is located
      * @return new matrix
      */
    Matrix split(size_t newR, size_t newC, size_t posR, size_t posC) const;
    /**
      * @brief Makes matrix which is this matrix after Gaussian elimination method.
      * @param printDetail print details
      * @return reduced matrix
      * @sa Gem
      */
    Matrix gem(gemStates printDetails = gemStates::NO_DETAILS) const;
    /**
      * @brief Returns rank of this matrix.
      * Rank can be obtained as number of non-zero rows after the GEM.
      * @return rank
      */
    unsigned int rank() const;

    /**
      * @brief Returns transposed matrix.
      * Transposed matrix is formed by turning rows of original matrix to colums and vice
      * versa.
      * @return transposed matrix
      */
    Matrix transpose() const;
    /**
      * @brief Returns inverse of this matrix.
      * Inversion can be computed by merging original matrix and identity matrix,
      * performing reduced GEM and then splitting matrix. If inverse does not exist then
      * exception is thrown. 
      * @throw MatrixException
      */
    Matrix inverse() const;
    /**
      * @brief Returns determinant of this matrix.
      * Determinant is calculated by GEM.
      * @throw MatrixException
      * @return determinant
      * @sa Gem
      */
    double determinant() const;

    /**
      * @brief Prints matrix.
      * @param os output stream
      * @param x matrix
      * @return output stream
      * @sa MatrixType::operator <<
      */
    friend std::ostream & operator <<(std::ostream & os, const Matrix & x);
    /**
      * @brief Scans matrix.
      * @param is input stream
      * @param x matrix
      * @return input stream
      * @sa MatrixType::operator >>
      */
    friend std::istream & operator >>(std::istream & is, Matrix & x);
};

#endif /* MATRIX_HPP */
