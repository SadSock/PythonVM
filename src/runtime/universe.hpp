#pragma once

#include "../object/hiObject.hpp"

#include <memory>


using std::shared_ptr;
using std::unique_ptr;
using std::make_unique;

class Universe{
public:
  static shared_ptr<HiObject> HiTrue;
  static shared_ptr<HiObject> HiFalse;
  static shared_ptr<HiObject> HiNone;


  static void genesis(){
    Universe::HiTrue       = make_shared<HiObject>();
    Universe::HiFalse      = make_shared<HiObject>();
    Universe::HiNone       = make_shared<HiObject>();
  }
  static void destroy(){
  }
};
