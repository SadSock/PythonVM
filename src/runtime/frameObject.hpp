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
  FrameObject(shared_ptr<CodeObject>codes) {                                                       //从code_object初始化FrameObject，
                                                                                                   //用来创建主函数对应的栈帧，即创建栈帧头结点

    this->_pc       = 0;
    this->_codes    = codes;


    this->_consts     = codes->_consts;
    this->_names      = codes->_names;


    this->_locals     = make_shared<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>>();
    this->_globals    = this->_locals;                                                             //主函数的全局变量表与局部变量相同
    this->_stack      = make_shared<ArrayList<shared_ptr<HiObject>>>();
    this->_loop_stack = make_shared<ArrayList<shared_ptr<Block>>>();
  }


  FrameObject(shared_ptr<FunctionObject>func, shared_ptr<ArrayList<shared_ptr<HiObject>>> args) {  //从FunctionObject初始化FrameObject，
                                                                                                   //用来创建主函数之外的函数对应的栈帧
    this->_codes        = func->_func_code;
    this->_consts       = this->_codes->_consts;
    this->_names        = this->_codes->_names;

    this->_locals       = make_shared<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>>();
    this->_globals      = func->globals();
    this->_stack        = make_shared<ArrayList<shared_ptr<HiObject>>>();
    this->_fast_locals  = nullptr;
    this->_loop_stack   = make_shared<ArrayList<shared_ptr<Block>>>();

    this->_pc           = 0;
    this->_sender       = nullptr;

    this->_fast_locals = make_shared<ArrayList<shared_ptr<HiObject>>>();

    if(func->_defaults){
      int dft_cnt = func->_defaults->length();
      int argcnt  = this->_codes->_argcount;

      while(dft_cnt--){
        this->_fast_locals->set(--argcnt, func->_defaults->get(dft_cnt));
      }
    }

    if(args != nullptr){
      for(int i = 0; i < args->length(); i++){
        this->_fast_locals->set(i,args->get(i));
      }
    }
  }

public:
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                   _stack;
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                   _fast_locals;   //函数参数栈
  shared_ptr<ArrayList<shared_ptr<Block>>>                      _loop_stack;
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                   _consts;
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                   _names;
  shared_ptr<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>>   _locals;        //局部变量表
  shared_ptr<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>>   _globals;       //全局变量表

  shared_ptr<FrameObject>                                       _sender;



  shared_ptr<CodeObject>                                        _codes;
  int                                                           _pc;



public:
  void set_pc(int x){this->_pc = x;}
  int  get_pc()     {return this->_pc;}


  shared_ptr<ArrayList<shared_ptr<HiObject>>>                 stack()           {return this->_stack;}
  shared_ptr<ArrayList<shared_ptr<Block>>>                    loop_stack()      {return this->_loop_stack;}
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                 consts()          {return this->_consts;}
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                 names()           {return this->_names;}
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                 fast_locals()     {return this->_fast_locals;}
  shared_ptr<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>> locals()          {return this->_locals;}
  shared_ptr<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>> globals()         {return this->_globals;}
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
