#pragma once

#include <memory>


#include "../object/klass.hpp"
#include "../object/hiObject.hpp"
#include "../code/codeObject.hpp"
#include "../object/hiString.hpp"


class FunctionKlass: public Klass {
private:
  FunctionKlass(){
    shared_ptr<HiString> x = std::make_shared<HiString>("Function");
    this->set_name(x);
  }
  static shared_ptr<FunctionKlass> instance;

public:
  virtual ~FunctionKlass(){};


public:
  static shared_ptr<FunctionKlass> get_instance(){
    if(FunctionKlass::instance == nullptr){
      FunctionKlass::instance = shared_ptr<FunctionKlass>(new FunctionKlass());
    }
    return FunctionKlass::instance;
  }

  virtual void print(shared_ptr<HiObject> obj) override;
  virtual void print_type(shared_ptr<HiObject> obj) override;

};


class FunctionObject: public HiObject {

  friend class FunctionKlass;
  friend class FrameObject;

private:
  shared_ptr<CodeObject>   _func_code;
  shared_ptr<HiString>     _func_name;


  unsigned int             _flags;

public:
  FunctionObject(shared_ptr<HiObject> code_object){
    shared_ptr<CodeObject> co = dynamic_pointer_cast<CodeObject>(code_object);

    this->_func_code = co;
    this->_func_name = co->_co_name;
    this->_flags     = co->_flag;

    this->set_klass(FunctionKlass::get_instance());
  }
  FunctionObject(shared_ptr<Klass> klass){
    this->_func_code = nullptr;
    this->_func_name = nullptr;
    this->_flags     = 0;

    this->set_klass(klass);
  }

  shared_ptr<HiString> func_name() { return this->_func_name; }

  int flags(){return this->_flags;}

};

void FunctionKlass::print(shared_ptr<HiObject> obj) {
  printf("<function :");

  shared_ptr<FunctionObject> fo = dynamic_pointer_cast<FunctionObject>(obj);

  assert(fo && fo->klass() == dynamic_pointer_cast<Klass>(FunctionKlass::instance));

  fo->func_name()->get_ptr();

  printf(">");
}

void FunctionKlass::print_type(shared_ptr<HiObject> obj){
  printf("Function");
}

shared_ptr<FunctionKlass> FunctionKlass::instance = nullptr;
