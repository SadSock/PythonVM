#pragma once

#include <cstdio>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class HiObject {
public:
  virtual void print() {
    printf("HiObject\n");
  }
  virtual ~HiObject() {}

public:
  virtual shared_ptr<HiObject> add(shared_ptr<HiObject> x) {
    return shared_ptr<HiObject>();
  }
  virtual shared_ptr<HiObject> greater(shared_ptr<HiObject> x){
    return  shared_ptr<HiObject>();
  }
  virtual shared_ptr<HiObject> less(shared_ptr<HiObject> x) {
    return  shared_ptr<HiObject>();
  }
  virtual shared_ptr<HiObject> equal(shared_ptr<HiObject> x) {
    return  shared_ptr<HiObject>();
  }
  virtual shared_ptr<HiObject> not_equal(shared_ptr<HiObject> x) {
    return  shared_ptr<HiObject>();
  }
  virtual shared_ptr<HiObject> ge(shared_ptr<HiObject> x) {
    return  shared_ptr<HiObject>();
  }
  virtual shared_ptr<HiObject> le (shared_ptr<HiObject> x) {
    return  shared_ptr<HiObject>();
  }
};
