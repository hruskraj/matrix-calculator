#include "handler.hpp"

using namespace std;

const string Handler::NO_VARS = "No variables stored!";
const string Handler::ILLEGAL_NAME = "Illegal name for variable!";
const string Handler::UNKNOWN = "Unknown command!";
//---------------------------------------------------------------------------------------
bool Handler::execute(const string & input){
  istringstream iss(input);
  istringstream iss2(input);
  Matrix tmp;
  string first = getNextWord(iss);
  transform(first.begin(), first.end(), first.begin(), ::tolower);
  if(first == "") return true;
  else if(first == "exit") return false;
  else if(first == "print") printVariable(iss);
  else if(first == "delete") deleteVariable(iss);
  else if(first == "scan") scanVariable(iss);
  else if(first == "list") listVariables();
  else if(first == "determinant") determinant(iss);
  else if(first == "rank") rank(iss);
  else if(first == "help") printHelp();
  else parse(iss2, tmp);
  return true;
}
//---------------------------------------------------------------------------------------
void Handler::printHelp() const{
  cout << "LIST - print names of all variables" << endl;
  cout << "PRINT var - print matirx var" << endl;
  cout << "SCAN var rows cols - scan matrix var with dimensions rows x cols" << endl;
  cout << "DELETE var - delete matrix var" << endl;
  cout << "MERGE var1 var2 - merge matrices var1 and var2" << endl;
  cout << "SPLIT var rows cols posR posC - split matrix from var with dimensions rows x cols starting at position [posR;posC]" << endl;
  cout << "GEM var [-v] - do Gaussian elimination method to matrix var" << endl;
  cout << "DETERMINANT var - calculate determinant of matrix var" << endl;
  cout << "RANK var - calculate rank of matrix var" << endl;
  cout << "TRANSPOSE var - transpose matrix var" << endl;
  cout << "INVERSE var - inverse matrix var" << endl; 
  cout << "var rows cols [val] - make matrix var with dimensions rows x cols and diagonal value val" << endl;
  cout << "var1 + var2 - sum of matrices var1 and var2" << endl;
  cout << "var1 - var2 - difference of matrices var1 and var2" << endl;
  cout << "var1 * var2 - product of matrices var1 and var2" << endl;
  cout << "var = ... - save result of right side to variable var" << endl;
}
//---------------------------------------------------------------------------------------
bool Handler::parse(istringstream & iss, Matrix & m){
  string first = getNextWord(iss);
  string tmp = first;
  transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
  if(tmp == "merge") return merge(iss, m);
  else if(tmp == "split") return split(iss, m);
  else if(tmp == "transpose") return transpose(iss, m);
  else if(tmp == "inverse") return inverse(iss, m);
  else if(tmp == "gem") return gem(iss, m);
  else if(isDouble(first)) return scalarMultiple(first, iss, m);
  else return variableOperation(first, iss, m);
}
//---------------------------------------------------------------------------------------
string Handler::getNextWord(istringstream & iss) const{
  string tmp;
  iss >> tmp;
  return tmp;
}
//---------------------------------------------------------------------------------------
bool Handler::isDouble(const string & s) const{
  if((s.at(0) != '+' || s.at(0) != '-') && (s.at(0) < '0' || s.at(0) > '9'))
    return false;
  bool decimalPoint = false;

  for(size_t i = 0; i < s.size(); ++i){
    if(s.at(i) == '.' && !decimalPoint){
      decimalPoint = true;
      continue;
    }
    if(s.at(i) < '0' || s.at(i) > '9')
      return false;
  }
  return true;
}
//---------------------------------------------------------------------------------------
bool Handler::isValidVariableName(const string & var) const{
  string str = var;
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  if(isDouble(var) || str == "exit" || str == "print" || str == "scan" || str == "list"
     || str == "merge" || str == "rank" || str == "determinant" || str == "split"
     || str == "gem" || str == "transpose" || str == "inverse" || str == "delete")
    return false;
  return true;
}
//---------------------------------------------------------------------------------------
void Handler::listVariables() const{
  if(vars.size() == 0){
    cout << NO_VARS << endl;
    return;
  }
  for(const auto & x : vars)
    cout << x.first << " ";
  cout << endl;
}
//---------------------------------------------------------------------------------------
bool Handler::getVariable(istringstream & iss, Matrix const * & m) const{
  string var;
  iss >> var;
  if(!iss.eof() || iss.fail() || iss.bad()){
    cout << UNKNOWN << endl;
    return false;
  }
  const auto & it = vars.find(var);
  if(it == vars.cend())
    cout << "Variable '" << var << "' not found!" << endl;
  else{
    m = &(it->second);
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------------------
void Handler::printVariable(istringstream & iss) const{
  Matrix const * tmp;
  if(getVariable(iss, tmp))
    cout << *tmp;
}
//---------------------------------------------------------------------------------------
void Handler::scanVariable(istringstream & iss){
  string var;
  size_t rows, cols;
  iss >> var >> rows >> cols;
  if(!iss.eof() || iss.fail() || iss.bad()){
    cout << UNKNOWN << endl;
    return;
  }
  if(!isValidVariableName(var)){
    cout << ILLEGAL_NAME << endl;
    return;
  }
  map<string, Matrix>::iterator it;
  if((it = vars.find(var)) == vars.end())
    vars[var] = Matrix(rows, cols);
  else
    it->second = Matrix(rows, cols);
  try{
    cin >> vars.find(var)->second;
    cout << "Scanning done!" << endl;
  }
  catch(const exception & e){
    cout << e.what() << endl;
    cin.clear();
    vars.erase(var);
  }
}
//---------------------------------------------------------------------------------------
void Handler::deleteVariable(istringstream & iss){
  string var = getNextWord(iss);
  if(!iss.eof() || iss.fail() || iss.bad()){
    cout << UNKNOWN << endl;
    return;
  }
  const auto & it = vars.find(var);
  if(it == vars.cend())
    cout << "Variable '" << var << "' not found!" << endl;
  else{
    vars.erase(var);
    cout << "Variable '" << var << "' deleted!" << endl;
  }
}
//---------------------------------------------------------------------------------------
bool Handler::merge(istringstream & iss, Matrix & m) const{
  string var1, var2;
  iss >> var1 >> var2;
  if(!iss.eof() || iss.fail() || iss.bad()){
    cout << UNKNOWN << endl;
    return false;
  }
  const auto & it1 = vars.find(var1);
  const auto & it2 = vars.find(var2);
  if(it1 == vars.cend())
    cout << "Variable '" << var1 << "' not found!" << endl;
  else if(it2 == vars.cend())
    cout << "Variable '" << var2 << "' not found!" << endl;
  else{
    m = it1->second.merge(it2->second);
    cout << m;
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------------------
bool Handler::split(istringstream & iss, Matrix & m) const{
  string var;
  size_t rows, cols, posR, posC;
  iss >> var >> rows >> cols >> posR >> posC;
  if(!iss.eof() || iss.fail() || iss.bad()){
    cout << UNKNOWN << endl;
    return false;
  }
  const auto & it = vars.find(var);
  if(it == vars.cend())
    cout << "Variable '" << var << "' not found!" << endl;
  else{
    m = it->second.split(rows, cols, posR, posC);
    cout << m;
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------------------
void Handler::determinant(istringstream & iss) const{
  Matrix const * tmp;
  if(getVariable(iss, tmp))
    cout << tmp->determinant() << endl; 
}
//---------------------------------------------------------------------------------------
void Handler::rank(istringstream & iss) const{
  Matrix const * tmp;
  if(getVariable(iss, tmp))
    cout << tmp->rank() << endl;
}
//---------------------------------------------------------------------------------------
bool Handler::transpose(istringstream & iss, Matrix & m) const{
  Matrix const * tmp;
  if(getVariable(iss, tmp)){
    m = tmp->transpose();
    cout << m;
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------------------
bool Handler::inverse(istringstream & iss, Matrix & m) const{
  Matrix const * tmp;
  if(getVariable(iss, tmp)){
    m = tmp->inverse();
    cout << m;
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------------------
bool Handler::gem(istringstream & iss, Matrix & m) const{
  string var, detail;
  iss >> var;
  if(!iss.eof()){
    iss >> detail;
    if(detail != "-v"){
      cout << UNKNOWN << endl;
      return false;
    }
  }
  if(!iss.eof() || iss.fail() || iss.bad()){
    cout << UNKNOWN << endl;
    return false;
  }
  const auto & it = vars.find(var);
  if(it == vars.cend())
    cout << "Variable '" << var << "' not found!" << endl;
  else{
    m = (detail == "-v" ? it->second.gem(gemStates::DETAILS) : it->second.gem());
    cout << m;
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------------------
bool Handler::scalarMultiple(const string & x, istringstream & iss, Matrix & m) const{
  string op, var;
  double sc;
  istringstream tmp (x);
  tmp >> sc;
  iss >> op >> var;
  if(!iss.eof() || iss.fail() || iss.bad() || op != "*"){
    cout << UNKNOWN << endl;
    return false;
  }
  const auto & it = vars.find(var);
  if(it == vars.cend())
    cout << "Variable '" << var << "' not found!" << endl;
  else{
    m = sc * it->second;
    cout << m;
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------------------
bool Handler::binaryOperation(const string & var1, const string & op, istringstream & iss, Matrix & m) const{
  string var2;
  iss >> var2;
  if(!iss.eof() || iss.fail() || iss.bad()){
    cout << UNKNOWN << endl;
    return false;
  }
  const auto & it1 = vars.find(var1);
  const auto & it2 = vars.find(var2);
  if(it1 == vars.cend())
    cout << "Variable '" << var1 << "' not found!" << endl;
  else if(it2 == vars.cend())
    cout << "Variable '" << var2 << "' not found!" << endl;
  else{
    if(op == "+")
      m = it1->second + it2->second;
    else if(op == "-")
      m = it1->second - it2->second;
    else
      m = it1->second * it2->second;
    cout << m;
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------------------
bool Handler::equalToVariable(istringstream & iss){
  string var1, var2, op;
  iss >> var1 >> op >> var2;
  return (vars.find(var2) != vars.end() && iss.eof() && !iss.bad() && !iss.fail());
}
//---------------------------------------------------------------------------------------
bool Handler::addNewMatrix(const string & var, const string & rows, istringstream & iss){
  stringstream tmp(rows);
  size_t r, c;
  double diag = 0;
  tmp >> r;
  iss >> c;
  if(!iss.eof())
    iss >> diag;
  if(!iss.eof() || iss.fail() || iss.bad()){
    cout << UNKNOWN << endl;
    return false;
  }
  vars[var] = Matrix(r, c);
  vars[var] = diag; 
  return true;
}
//---------------------------------------------------------------------------------------
bool Handler::variableOperation(const string & var, istringstream & iss, Matrix & m){
  string next = getNextWord(iss);
  if(!iss.good())
    cout << UNKNOWN << endl;
  else if(next == "+" || next == "-" || next == "*")
    return binaryOperation(var, next, iss, m);
  else if(isDouble(next))
    return addNewMatrix(var, next, iss);
  else if(next == "="){
    istringstream iss2(iss.str());
    if(equalToVariable(iss2)){
      iss >> next;
      vars[var] = vars[next];
      return true;
    }
    if(parse(iss, m)){
      vars[var] = m;
      return true;
    }
    return false;
  }
  else
    cout << UNKNOWN << endl;
  return false;
}
