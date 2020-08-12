#pragma once

#include <cstdio>
#include <memory>

#include "../runtime/universe.hpp"
#include "hiObject.hpp"
#include "../object/klass.hpp"
#include <cstdlib>
#include <cassert>


using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;


class HiInteger : public HiObject {
private:
  int _value;

public:
  HiInteger(int x);
  HiInteger(const HiInteger& x);
  const HiInteger& operator=(const HiInteger& x);
  ~HiInteger();
  int value() { return this->_value; }
};


class IntegerKlass : public Klass {
private:
  IntegerKlass() {}
  static shared_ptr<IntegerKlass> instance;

public:
  virtual ~IntegerKlass(){
    //printf("IntegerKlass: destruction\n");
  }

public:
  static shared_ptr<IntegerKlass> get_instance() {
    //if(IntegerKlass::instance){
    //  printf("fuck1\n");
    //}
    if (!IntegerKlass::instance) {
      IntegerKlass::instance = shared_ptr<IntegerKlass>(new IntegerKlass());
    }
    //assert(!IntegerKlass::get_instance());

    //if(IntegerKlass::instance){
    //  printf("fuck2\n");
    //}

    return IntegerKlass::instance;
  }

  virtual void print_type(shared_ptr<HiObject> x) override{
    printf("Integer");
  }

  virtual void print(shared_ptr<HiObject> x) override {
    assert(x && (x->klass() == dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);

    printf("%d",ix->value());
  }

  virtual shared_ptr<HiObject> greater         (shared_ptr<HiObject> x, shared_ptr<HiObject> y) override {
    if(x->klass() != y->klass())
      return Universe::HiFalse;

    assert(x && (x->klass() == dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));
    assert(y && (y->klass() == dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);
    shared_ptr<HiInteger> iy = dynamic_pointer_cast<HiInteger>(y);

    if(ix->value() > iy->value())
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }
  virtual shared_ptr<HiObject> less            (shared_ptr<HiObject> x, shared_ptr<HiObject> y) override {

    if (x->klass() != y->klass())
      return Universe::HiFalse;

    assert(x && (x->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));
    assert(y && (y->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);
    shared_ptr<HiInteger> iy = dynamic_pointer_cast<HiInteger>(y);

    if (ix->value() < iy->value())
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }
  virtual shared_ptr<HiObject> equal           (shared_ptr<HiObject> x, shared_ptr<HiObject> y) override {

    if (x->klass() != y->klass())
      return Universe::HiFalse;

    assert(x && (x->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));
    assert(y && (y->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);
    shared_ptr<HiInteger> iy = dynamic_pointer_cast<HiInteger>(y);

    if (ix->value() == iy->value())
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }
  virtual shared_ptr<HiObject> not_equal       (shared_ptr<HiObject> x, shared_ptr<HiObject> y) override {

    if (x->klass() != y->klass())
      return Universe::HiFalse;

    assert(x && (x->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));
    assert(y && (y->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);
    shared_ptr<HiInteger> iy = dynamic_pointer_cast<HiInteger>(y);

    if (ix->value() != iy->value())
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }
  virtual shared_ptr<HiObject> ge              (shared_ptr<HiObject> x, shared_ptr<HiObject> y) override {

    if (x->klass() != y->klass())
      return Universe::HiFalse;

    assert(x && (x->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));
    assert(y && (y->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);
    shared_ptr<HiInteger> iy = dynamic_pointer_cast<HiInteger>(y);

    if (ix->value() >= iy->value())
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }
  virtual shared_ptr<HiObject> le              (shared_ptr<HiObject> x, shared_ptr<HiObject> y) override {

    if (x->klass() != y->klass())
      return Universe::HiFalse;

    assert(x && (x->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));
    assert(y && (y->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);
    shared_ptr<HiInteger> iy = dynamic_pointer_cast<HiInteger>(y);

    if (ix->value() <= iy->value())
      return Universe::HiTrue;
    else
      return Universe::HiFalse;
  }

  virtual shared_ptr<HiObject> add             (shared_ptr<HiObject> x, shared_ptr<HiObject> y) override  {

    if (x->klass() != y->klass())
      return Universe::HiFalse;

    assert(x && (x->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));
    assert(y && (y->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);
    shared_ptr<HiInteger> iy = dynamic_pointer_cast<HiInteger>(y);

    return make_shared<HiInteger>(ix->value() + iy->value());
  }
  virtual shared_ptr<HiObject> sub             (shared_ptr<HiObject> x, shared_ptr<HiObject> y) override  {

    if (x->klass() != y->klass())
      return Universe::HiFalse;

    assert(x && (x->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));
    assert(y && (y->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);
    shared_ptr<HiInteger> iy = dynamic_pointer_cast<HiInteger>(y);

    return make_shared<HiInteger>(ix->value() - iy->value());
  }
  virtual shared_ptr<HiObject> mul             (shared_ptr<HiObject> x, shared_ptr<HiObject> y) override  {

    if (x->klass() != y->klass())
      return Universe::HiFalse;

    assert(x && (x->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));
    assert(y && (y->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);
    shared_ptr<HiInteger> iy = dynamic_pointer_cast<HiInteger>(y);
    return make_shared<HiInteger>(ix->value() * iy->value());
  }
  virtual shared_ptr<HiObject> div             (shared_ptr<HiObject> x, shared_ptr<HiObject> y) override  {

    if (x->klass() != y->klass())
      return Universe::HiFalse;

    assert(x && (x->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));
    assert(y && (y->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);
    shared_ptr<HiInteger> iy = dynamic_pointer_cast<HiInteger>(y);

    return make_shared<HiInteger>(ix->value() / iy->value());
  }
  virtual shared_ptr<HiObject> mod             (shared_ptr<HiObject> x, shared_ptr<HiObject> y) override  {

    if (x->klass() != y->klass())
      return Universe::HiFalse;

    assert(x && (x->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));
    assert(y && (y->klass() ==
                 dynamic_pointer_cast<Klass>(IntegerKlass::get_instance())));

    shared_ptr<HiInteger> ix = dynamic_pointer_cast<HiInteger>(x);
    shared_ptr<HiInteger> iy = dynamic_pointer_cast<HiInteger>(y);

    return  make_shared<HiInteger>(ix->value() % iy->value());
  }

};

shared_ptr<IntegerKlass> IntegerKlass::instance = NULL;

const HiInteger& HiInteger::operator =(const HiInteger& x){
  this->_value = x._value;
  //printf("HiInteger: assignment\n");

  auto tmp = IntegerKlass::get_instance();
  //if (tmp) {
  //  printf("Yes\n");
  //}
  this->set_klass(tmp);

  return *this;
}


HiInteger::HiInteger(const HiInteger& x){
  this->_value = x._value;
  //printf("HiInteger: copy\n");

  auto tmp = IntegerKlass::get_instance();
  //if (tmp) {
  //  printf("Yes\n");
  //:}
  this->set_klass(tmp);
}

HiInteger::HiInteger(int x){
  this->_value = x;
  //printf("HiInteger: construction\n");

  auto tmp = IntegerKlass::get_instance();
  //if (tmp) {
  //  printf("Yes\n");
  //}
  this->set_klass(tmp);

  //if(this->klass())
  //  printf("Yes\n");
}

HiInteger::~HiInteger(){
  //printf("HiInteger: destruction\n");
}
