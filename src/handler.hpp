#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <exception>
#include "matrix.hpp"

/**
  * @brief Handler of user input.
  */
class Handler{
  private:
    std::map<std::string, Matrix> vars; ///< All stored variables.

    /// Information for user that no variables are stored.
    static const std::string NO_VARS;
    /// Information for user that variable has illegal name.
    static const std::string ILLEGAL_NAME;
    /// Information for user about unknown command.
    static const std::string UNKNOWN;

    /**
      * @brief Returns next word.
      * @param iss input string stream
      * @return next word
      */
    std::string getNextWord(std::istringstream & iss) const;
    /**
      * @brief Tests whether string <i>s</i> can be transformed to double.
      * String can start with <b>+</b> or <b>-</b> and can have only one decimal point.
      * Apart from that, string must consists of digits.
      * @param s string to be tested
      * @return true if can be transformed and false otherwise
      */
    bool isDouble(const std::string & s) const;
    /**
      * @brief Tests whether string <i>var</i> can be variable name.
      * Variable name mustn't be key word nor real number.
      * @param var string to be tested
      * @return true if is valid name and false otherwise
      */
    bool isValidVariableName(const std::string & var) const;
    /**
      * @brief Prints help
      */
    void printHelp() const;
    /**
      * @brief Prints names of all variables.
      * If no variables are stored then function prints "No variables stored!".
      */
    void listVariables() const;
    /**
      * @brief Prints variable which name is in <i>iss</i>.
      * If there is not any variable with such a name then information is printed.
      * @param iss input string stream
      */
    void printVariable(std::istringstream & iss) const;
     /**
      * @brief Deletes variable which name is in <i>iss</i>.
      * If there is not any variable with such a name then information is printed.
      * @param iss input string stream
      */
    void deleteVariable(std::istringstream & iss);
     /**
      * @brief Scans variable which name and dimensions are in <i>iss</i>.
      * If there is a variable with this name then this variable is overwritten. 
      * @param iss input string stream
      */
    void scanVariable(std::istringstream & iss);

    /**
      * @brief Merges matrices and prints result.
      * @param iss input string stream
      * @param[out] m merged matrix
      * @return true if successful merging otherwise false
      * @sa Matrix::merge
      */
    bool merge(std::istringstream & iss, Matrix & m) const;
    /**
      * @brief Splits matrix from bigger matrix and prints result.
      * @param iss input string stream
      * @param[out] m split matrix
      * @return true if successful splitting otherwise false
      * @sa Matrix::split
      */
    bool split(std::istringstream & iss, Matrix & m) const;
    /**
      * @brief Calculates determinant of matrix.
      * @param iss input string stream
      * @sa Matrix::determinant
      */
    void determinant(std::istringstream & iss) const;
    /**
      * @brief Calculates rank of matrix.
      * @param iss input string stream
      * @sa Matrix::rank
      */
    void rank(std::istringstream & iss) const;
    /**
      * @brief Transposes matrix and prints result.
      * @param iss input string stream
      * @param[out] m transposed matrix
      * @return true if successful transpose otherwise false
      * @sa Matrix::transpose
      */
    bool transpose(std::istringstream & iss, Matrix & m) const;
    /**
      * @brief Inverts matrix and prints result.
      * @param iss input string stream
      * @param[out] m inverted matrix
      * @return true if successful inversion otherwise false
      * @sa Matrix::inverse
      */
    bool inverse(std::istringstream & iss, Matrix & m) const;
    /**
      * @brief Performs GEM on matrix and prints result.
      * @param iss input string stream
      * @param[out] m GEMed matrix
      * @return true if successful GEM otherwise false
      * @sa Matrix::gem
      */
    bool gem(std::istringstream & iss, Matrix & m) const;
    /**
      * @brief Scalar multiplication of matrix.
      * @param x scalar
      * @param iss input string stream
      * @param[out] m multiplied matrix
      * @return true if successful multiplication otherwise false
      */
    bool scalarMultiple(const std::string & x, std::istringstream & iss, Matrix & m) const;

     /**
      * @brief Binary operation between two variables.
      * Can be sum, difference or multiplication.
      * @param var1 first variable
      * @param op operator
      * @param iss input string stream
      * @param[out] m matrix
      * @return true if successful operation otherwise false
      */
    bool binaryOperation(const std::string & var1, const std::string & op, std::istringstream & iss, Matrix & m) const;
    /**
     * @brief Operator = for variables.
     * @param var first variable
     * @param iss input string stream
     * @param[out] m matrix
     * @return true if successful operation otherwise false
     */
    bool variableOperation(const std::string & var, std::istringstream & iss, Matrix & m);
     /**
      * @brief Adds new variable.
      * @param var variable name
      * @param rows rows
      * @param iss input string stream
      * @return true if successful operation otherwise false
      */
    bool addNewMatrix(const std::string & var, const std::string & rows, std::istringstream & iss);
    /**
      * @brief Tries operation which generate new matrix.
      * @param iss input string stream
      * @param[out] m new matrix
      */
    bool parse(std::istringstream & iss, Matrix & m);
    /**
      * @brief var1 = var2
      * @param iss input string stream
      * @return true if successful operation otherwise false
      */
    bool equalToVariable(std::istringstream & iss);
    /**
      * @brief Finds variable or prints not found.
      * @param iss input string stream
      * @param[out] m variable
      * @return true if found otherwise false
      */
    bool getVariable(std::istringstream & iss, Matrix const * & m) const;

  public:
    /**
      * @brief Default constructor.
      */
    Handler() = default;
    /**
      * @brief Handles new command.
      * @param input user input
      * @return false if exit was typed true otherwise
      */
    bool execute(const std::string & input);
};

#endif /* HANDLER_HPP */
