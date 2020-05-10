#pragma once


#include <cstdio>
#include <cstring>

#include "hiInteger.hpp"
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

  void print() override{
    for(int i = 0; i < this->_length; i++){
      printf("%c",_value[i]);
    }
  }

  shared_ptr<HiObject> equal(shared_ptr<HiObject> x) override{
    auto tmp = dynamic_pointer_cast<HiString>(x);
    if(this->_length != tmp->length())
      return Universe::HiFalse;
    for(int i = 0 ; i < this->_length; i++){
      if(this->_value[i] != tmp->value()[i] )
        return Universe::HiFalse;
    }
    return Universe::HiTrue;
  }
};
