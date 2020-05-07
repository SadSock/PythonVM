#pragma once


#include <cstring>

#include "hiObject.hpp"

class HiString : public HiObject{
private:
  char* _value;
  int   _length;


public:
  HiString(const char* x){
    this->_length = strlen(x);
    this->_value = new char[this->_length];
    strcpy(this->_value,x);
  }
  HiString(const char* x, const int length){
    this->_length = length;
    this->_value = new char[length];
    for(int i = 0; i < length; i++){
      this->_value[i] = x[i];
    }
  }
  const char* value(){return this->_value;}
  int length(){return this->_length;}
};
