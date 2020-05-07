#pragma once


#include <memory>

#include "hiObject.hpp"


using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;

class HiInteger : public HiObject{
private:
  int _value;

public:
  HiInteger(int x):_value(x){}
  int value(){return this->_value;}
  void print() override {
    printf(" %d",this->_value);
  }

  shared_ptr<HiObject> add(shared_ptr<HiObject> x) override {
    auto ret = make_shared<HiInteger>(this->_value +  dynamic_pointer_cast<HiInteger>(x)->_value);
    return dynamic_pointer_cast<HiObject>(ret);
  }
};
