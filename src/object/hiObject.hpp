#pragma once

#include <memory>

using std::shared_ptr;
using std::make_shared;

class HiObject {
public:
  virtual void print() {}
  virtual shared_ptr<HiObject> add(shared_ptr<HiObject> x) {
    return make_shared<HiObject>();
  }
  virtual ~HiObject() {}
};
