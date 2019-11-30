#include <iostream>
#include <string>
#include <exception>
#include "matrix.hpp"
#include "handler.hpp"

using namespace std;

int main(){
  string input;
  Handler h;
  while(getline(cin, input)){
    try{
      if(!h.execute(input))
        break;
    }
    catch(const exception & e){
      cout << e.what() << endl;
    }
  }

  return 0;
}
