#pragma once

#include <memory>

#include "../runtime/universe.hpp"
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
  virtual shared_ptr<HiObject> greater(shared_ptr<HiObject> x) override {
    if(this->_value > dynamic_pointer_cast<HiInteger>(x)->_value)
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }
  virtual shared_ptr<HiObject> less(shared_ptr<HiObject> x) override {
    if (this->_value < dynamic_pointer_cast<HiInteger>(x)->_value)
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }
  virtual shared_ptr<HiObject> equal(shared_ptr<HiObject> x) override {
    if (this->_value == dynamic_pointer_cast<HiInteger>(x)->_value)
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }
  virtual shared_ptr<HiObject> not_equal(shared_ptr<HiObject> x) override {
    if (this->_value != dynamic_pointer_cast<HiInteger>(x)->_value)
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }
  virtual shared_ptr<HiObject> ge(shared_ptr<HiObject> x) override {
    if (this->_value >= dynamic_pointer_cast<HiInteger>(x)->_value)
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }
  virtual shared_ptr<HiObject> le(shared_ptr<HiObject> x) override {
    if (this->_value <= dynamic_pointer_cast<HiInteger>(x)->_value)
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }
};
