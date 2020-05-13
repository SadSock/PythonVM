#pragma once


#include "../runtime/universe.hpp"
#include "hiObject.hpp"

#include <memory>
#include <cstdio>

class HiString;

class Klass{
private:
  shared_ptr<HiString> _name;
public:
  Klass(){};
  void set_name(shared_ptr<HiString> x){this->_name = x;};
  shared_ptr<HiString> name();

  virtual void print(shared_ptr<HiObject> obj){};

  virtual shared_ptr<HiObject> greater     (shared_ptr<HiObject> x, shared_ptr<HiObject> y){return Universe::HiNone;}
  virtual shared_ptr<HiObject> less        (shared_ptr<HiObject> x, shared_ptr<HiObject> y){return Universe::HiNone;}
  virtual shared_ptr<HiObject> equal       (shared_ptr<HiObject> x, shared_ptr<HiObject> y){return Universe::HiNone;}
  virtual shared_ptr<HiObject> not_equal   (shared_ptr<HiObject> x, shared_ptr<HiObject> y){return Universe::HiNone;}
  virtual shared_ptr<HiObject> ge          (shared_ptr<HiObject> x, shared_ptr<HiObject> y){return Universe::HiNone;}
  virtual shared_ptr<HiObject> le          (shared_ptr<HiObject> x, shared_ptr<HiObject> y){return Universe::HiNone;}

  virtual shared_ptr<HiObject> add         (shared_ptr<HiObject> x, shared_ptr<HiObject> y) {
    return Universe::HiNone;
  }
  virtual shared_ptr<HiObject> sub         (shared_ptr<HiObject> x, shared_ptr<HiObject> y) {
    return Universe::HiNone;
  }
  virtual shared_ptr<HiObject> mul         (shared_ptr<HiObject> x, shared_ptr<HiObject> y) {
    return Universe::HiNone;
  }
  virtual shared_ptr<HiObject> div         (shared_ptr<HiObject> x, shared_ptr<HiObject> y) {
    return Universe::HiNone;
  }
  virtual shared_ptr<HiObject> mod         (shared_ptr<HiObject> x, shared_ptr<HiObject> y) {
    return Universe::HiNone;
  }
};
