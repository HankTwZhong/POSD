#ifndef NUMBER_H
#define NUMBER_H

#include <string>
using std::string;
#include "atom.h"
#include<sstream>

class Number : public Term{
public:
  Number (double s) {
    std::ostringstream doubleConvertsStr;
    doubleConvertsStr << s;
    _symbol = doubleConvertsStr.str();
  }
  string symbol() const{
    return _symbol;
  }
private:
  string _symbol;
};
#endif