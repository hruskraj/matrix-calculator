#include "matrixException.hpp"

MatrixException::MatrixException(const char * error) : error(error){
}
//---------------------------------------------------------------------------------------
const char * MatrixException::what() const noexcept{
  return error;
}
