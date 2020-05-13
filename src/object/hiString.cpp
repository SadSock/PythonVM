#include "hiString.hpp"
#include <memory>

HiString::HiString(const char *x) {
  this->_length = strlen(x);
  this->_value = new char[this->_length];
  strcpy(this->_value, x);

  this->set_klass(StringKlass::get_instance());
}
HiString::HiString(const char *x, const int length) {
  this->_length = length;
  this->_value = new char[length];
  for (int i = 0; i < length; i++) {
    this->_value[i] = x[i];
  }
  this->set_klass(StringKlass::get_instance());
}
const char *HiString::value() { return this->_value; }
int HiString::length() { return this->_length; }

HiString::~HiString(){
  delete [] this->_value;
}


std::shared_ptr<StringKlass> StringKlass::instance = 0;
