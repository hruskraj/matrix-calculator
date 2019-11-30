#ifndef MATRIXEXCEPTION_HPP
#define MATRIXEXCEPTION_HPP

#include <exception>
#include <string>

/**
  * @brief Simple class for matrix exceptions.
  */
class MatrixException : public std::exception{
  private:
    const char * error; ///< Error message.
  public:
    /**
      * @brief Constructor.
      * @param error error message
      */
    MatrixException(const char * error);
    /**
      * @brief Returns error message.
      * @return error message
      */
    const char * what() const noexcept;
};

#endif /* MATRIXEXCEPTION_HPP */
