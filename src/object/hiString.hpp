#pragma once

#include <cassert>
#include <cstdio>
#include <cstring>
#include <memory>

#include "klass.hpp"
#include "hiObject.hpp"
#include "../runtime/universe.hpp"


using std::dynamic_pointer_cast;

class HiString : public HiObject {
private:
  char *_value;
  int _length;

public:
  HiString(const char *x);
  HiString(const char *x, const int length);
  ~HiString();
  const char *value();
  int length();

};



class StringKlass : public Klass{
private:
  static shared_ptr<StringKlass> instance;
  StringKlass(){}

public:
  virtual ~StringKlass(){};
  static shared_ptr<StringKlass> get_instance(){
    if(!StringKlass::instance){
      StringKlass::instance = shared_ptr<StringKlass>(new StringKlass());
    }
    return StringKlass::instance;
  }


  shared_ptr<HiObject> equal(shared_ptr<HiObject> x, shared_ptr<HiObject> y) override{
    if(x->klass() != y->klass())
      return Universe::HiNone;


    shared_ptr<HiString> sx = dynamic_pointer_cast<HiString>(x);
    shared_ptr<HiString> sy = dynamic_pointer_cast<HiString>(y);

    assert(x && (x->klass() == shared_ptr<Klass>(StringKlass::get_instance())));
    assert(y && (y->klass() == shared_ptr<Klass>(StringKlass::get_instance())));


    if(sx->length()!=sy->length())
      return Universe::HiFalse;

    for(int i = 0; i < sx->length(); i++){
      if(sx->value()[i] != sy->value()[i])
        return Universe::HiFalse;
    }

    return Universe::HiTrue;
  }


  void print(shared_ptr<HiObject> obj) override{

    assert(obj && (obj->klass() == shared_ptr<Klass>(StringKlass::get_instance())));
    shared_ptr<HiString> str_obj = dynamic_pointer_cast<HiString>(obj);

    for(int i = 0; i < str_obj->length(); i++){
      printf("%c",str_obj->value()[i]);
    }
  }

};



