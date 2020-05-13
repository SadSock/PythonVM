#include "../runtime/universe.hpp"
#include "../object/klass.hpp"
#include "hiObject.hpp"


#include <cstdio>
#include <memory>
#include <cstdlib>
#include <cassert>


HiObject::HiObject(){};
HiObject::HiObject(const HiObject &x) {
  printf("copy HiObject\n");
  this->_klass = x._klass;
}
HiObject& HiObject::operator=(const HiObject &x){
  printf("assginment HiObject\n");
  this->_klass = x._klass;
  return *this;
}


shared_ptr<Klass> HiObject::klass(){
  assert(this->_klass);
  return this->_klass;
}

void HiObject::set_klass(shared_ptr<Klass> x) { this->_klass = x; }

shared_ptr<HiObject> HiObject::get_ptr(){ return this->shared_from_this();}

void HiObject::print() { this->klass()->print(this->get_ptr()); }

HiObject::~HiObject(){}

shared_ptr<HiObject> HiObject::greater(shared_ptr<HiObject> x){
  return this->klass()->greater(this->get_ptr(), x);
}
shared_ptr<HiObject> HiObject::less(shared_ptr<HiObject> x){
  return this->klass()->less(this->get_ptr(), x);
}
shared_ptr<HiObject> HiObject::equal(shared_ptr<HiObject> x){
  return this->klass()->equal(this->get_ptr(), x);
}
shared_ptr<HiObject> HiObject::not_equal(shared_ptr<HiObject> x){
  return this->klass()->not_equal(this->get_ptr(), x);
}
shared_ptr<HiObject> HiObject::ge(shared_ptr<HiObject> x){
  return this->klass()->ge(this->get_ptr(), x);
}
shared_ptr<HiObject> HiObject::le(shared_ptr<HiObject> x){
  return this->klass()->le(this->get_ptr(), x);
}



shared_ptr<HiObject> HiObject::add(shared_ptr<HiObject> x){
  return this->klass()->add(this->get_ptr(), x) ;
}
shared_ptr<HiObject> HiObject::sub(shared_ptr<HiObject> x){
  return this->klass()->sub(this->get_ptr(), x);
}
shared_ptr<HiObject> HiObject::mul(shared_ptr<HiObject> x){
  return this->klass()->mul(this->get_ptr(), x);
}
shared_ptr<HiObject> HiObject::div(shared_ptr<HiObject> x){
  return this->klass()->div(this->get_ptr(), x);
}
shared_ptr<HiObject> HiObject::mod(shared_ptr<HiObject> x){
  return this->klass()->mod(this->get_ptr(), x);
}
