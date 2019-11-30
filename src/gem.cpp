#include "gem.hpp"

using namespace std;

Gem::Gem(size_t r, size_t c, MatrixType * & matrix, gemStates print) : r(r), c(c), m(matrix), print(print){
}
//---------------------------------------------------------------------------------------
void Gem::gem(){
  size_t k = 0, l = 0;
  if(print == gemStates::DETAILS)
    cout << "Starting Gaussian elimination..." << endl << *m;
  while(findNext(k, l)){
    eliminate(k, l);
    ++k;
    ++l;
  }
  makeReduced();
}
//---------------------------------------------------------------------------------------
bool Gem::findNext(size_t & k, size_t & l){
  bool isZero = true;
  if(l == c)
    return false;
  do{
    for(size_t i = k; i < r; ++i)
      if(m->getValue(i, l) != 0){
        isZero = false;
        if(i != k){
          m->swapRows(i, k);
          det *= -1;
          if(print == gemStates::DETAILS)
            cout << "Swapping rows " << i + 1 << " and " << k + 1 << endl << *m;
        }
        break;
      }
  }while(isZero && ++l < c);
  return isZero ? false : true;
}
//---------------------------------------------------------------------------------------
void Gem::eliminate(size_t row, size_t col){
  double val = m->getValue(row, col);
  if(1 / val != 1){
    m->multiplyRow(row, 1 / val);
    det *= val;
    if(print == gemStates::DETAILS)
      cout << "Multiplying row " << row + 1 << " by " << 1 / val << endl << *m;
  }
  for(size_t k = row + 1; k < r; ++k){
    if(m->getValue(k, col) != 0){
      m->addRow(k, row, -1 * m->getValue(k, col));
      if(print == gemStates::DETAILS)
        cout << "Adding a multiple of row " << row + 1 << " to row " << k + 1 << endl << *m;
    }
  }
}
//---------------------------------------------------------------------------------------
void Gem::makeReduced(){
  if(print == gemStates::DETAILS)
    cout << "Reducing..." << endl;
  for(size_t i = r - 1; i > 0; --i){
    for(size_t j = 0; j < c; ++j){
      if(m->getValue(i, j) == 1){
        for(size_t k = i - 1;; --k){
          m->addRow(k, i, -1 * m->getValue(k, j));
          if(print == gemStates::DETAILS)
            cout << *m << endl;
          if(k == 0) break;
        }
        break;
      }
    }
  }
  if(print == gemStates::DETAILS)
    cout << "Gaussian elimination done!" << endl;
}
//---------------------------------------------------------------------------------------
double Gem::getDeterminant() const{
  return det;
}
