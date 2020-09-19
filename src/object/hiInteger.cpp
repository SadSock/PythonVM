#include "hiInteger.hpp"


const HiInteger& HiInteger::operator =(const HiInteger& x){
  this->_value = x._value;

  auto tmp = IntegerKlass::get_instance();
  this->set_klass(tmp);

  return *this;
}


HiInteger::HiInteger(const HiInteger& x){
  this->_value = x._value;

  auto tmp = IntegerKlass::get_instance();
  this->set_klass(tmp);
}

HiInteger::HiInteger(int x){
  this->_value = x;
//
  auto tmp = IntegerKlass::get_instance();
  this->set_klass(tmp);
}

HiInteger::~HiInteger(){
}

shared_ptr<IntegerKlass> IntegerKlass::instance = nullptr;
