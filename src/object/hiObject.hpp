#pragma once


#include <cstdio>
#include <memory>


using std::shared_ptr;
using std::make_shared;
using std::enable_shared_from_this;

class Klass;

class HiObject : public  enable_shared_from_this<HiObject> {

private:
  shared_ptr<Klass> _klass;

public:
  virtual ~HiObject();
  HiObject();
  HiObject(const HiObject& x);
  HiObject& operator =(const HiObject & x);

public:
  shared_ptr<Klass> klass();
  void set_klass(shared_ptr<Klass> x);
  shared_ptr<HiObject> get_ptr();
  void print();
  void print_type();

public:
  shared_ptr<HiObject> greater   (shared_ptr<HiObject> x);
  shared_ptr<HiObject> less      (shared_ptr<HiObject> x);
  shared_ptr<HiObject> equal     (shared_ptr<HiObject> x);
  shared_ptr<HiObject> not_equal (shared_ptr<HiObject> x);
  shared_ptr<HiObject> ge        (shared_ptr<HiObject> x);
  shared_ptr<HiObject> le        (shared_ptr<HiObject> x);


  shared_ptr<HiObject> add       (shared_ptr<HiObject> x) ;
  shared_ptr<HiObject> sub       (shared_ptr<HiObject> x) ;
  shared_ptr<HiObject> mul       (shared_ptr<HiObject> x) ;
  shared_ptr<HiObject> div       (shared_ptr<HiObject> x) ;
  shared_ptr<HiObject> mod       (shared_ptr<HiObject> x) ;
};
