#pragma once

#include "../object/hiInteger.hpp"
#include "../object/hiobject.hpp"

#include <memory>


using std::shared_ptr;
using std::unique_ptr;
using std::make_unique;


class Universe{
public:
  static shared_ptr<HiInteger> Hitrue;
  static shared_ptr<HiInteger> HiFalse;
  static shared_ptr<HiObject>  HiNone;


  static void genesis(){
    Universe::Hitrue       = make_shared<HiInteger>(1);
    Universe::HiFalse      = make_shared<HiInteger>(0);
    Universe::HiNone       = make_shared<HiObject>();
  }
  static void destroy(){
    
  }
};

shared_ptr<HiInteger> Universe::Hitrue     = make_shared<HiInteger>(1);
shared_ptr<HiInteger> Universe::HiFalse    = make_shared<HiInteger>(0);
shared_ptr<HiObject>  Universe::HiNone     = make_shared<HiObject>();
