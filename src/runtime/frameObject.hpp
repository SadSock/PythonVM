#pragma once

#include <memory>



#include "../code/codeObject.hpp"
#include "../util/arrayList.hpp"
#include "../util/map.hpp"
#include "../object/hiObject.hpp"
#include "block.hpp"
#include "functionObject.hpp"



using std::shared_ptr;


class FrameObject{

public:
  FrameObject();
  FrameObject(shared_ptr<CodeObject> codes){

    this->_pc       = 0;
    this->_codes    = codes;


    this->_consts     = codes->_consts;
    this->_names      = codes->_names;


    this->_locals     = make_shared<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>>();
    this->_stack      = make_shared<ArrayList<shared_ptr<HiObject>>>();
    this->_loop_stack = make_shared<ArrayList<shared_ptr<Block>>>();
  }

  FrameObject(shared_ptr<FunctionObject> func){
    this->_codes        = func->_func_code;
    this->_consts       = this->_codes->_consts;
    this->_names        = this->_codes->_names;
    this->_locals       = make_shared<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>>();
    this->_stack        = make_shared<ArrayList<shared_ptr<HiObject>>>();
    this->_loop_stack   = make_shared<ArrayList<shared_ptr<Block>>>();

    this->_pc           = 0;
    this->_sender       = nullptr;
  }


public:
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                   _stack;
  shared_ptr<ArrayList<shared_ptr<Block>>>                      _loop_stack;
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                   _consts;
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                   _names;
  shared_ptr<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>>   _locals;
  shared_ptr<FrameObject>                                       _sender;



  shared_ptr<CodeObject>                            _codes;
  int                                               _pc;



public:
  void set_pc(int x){this->_pc = x;}
  int  get_pc()     {return this->_pc;}


  shared_ptr<ArrayList<shared_ptr<HiObject>>>                 stack()           {return this->_stack;}
  shared_ptr<ArrayList<shared_ptr<Block>>>                    loop_stack()      {return this->_loop_stack;}
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                 consts()          {return this->_consts;}
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                 names()           {return this->_names;}
  shared_ptr<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>> locals()          {return this->_locals;}
  shared_ptr<FrameObject>                                     sender()          {return this->_sender;}

  bool            is_first_frame(){
    return this->_sender == nullptr;
  }

  bool            has_more_codes(){
    return this->_pc < this->_codes->_bytecodes->length();
  }
  unsigned char   get_op_code(){
    return this->_codes->_bytecodes->value()[this->_pc++];
  }
  int             get_op_arg(){

    int byte1 = (this->_codes->_bytecodes->value()[this->_pc++] & 0xFF);
    int byte2 = (this->_codes->_bytecodes->value()[this->_pc++] & 0xFF);
    int op_arg    =  (byte2 << 8) | byte1;

    return op_arg;
  }
  void           set_sender(shared_ptr<FrameObject> x){
    this->_sender = x;
  }


};
