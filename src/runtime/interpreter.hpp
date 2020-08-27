#pragma once

#include "../code/codeObject.hpp"
#include "../code/byteCode.hpp"
#include "../object/hiInteger.hpp"
#include "../util/map.hpp"
#include "block.hpp"
#include "frameObject.hpp"
#include "functionObject.hpp"

#include <QDebug>
#include <cstdio>
#include <memory>

#define PUSH(x)                      this->_frame->_stack->add((x))
#define POP()                        this->_frame->_stack->pop()
#define STACK_LEVEL()                this->_frame->_stack->size()


using std::shared_ptr;
using std::make_shared;


class Interpreter{
private:

  shared_ptr<FrameObject>                                      _frame;
  shared_ptr<HiObject>                                         _ret_value;
  shared_ptr<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>>  _buildins;
public:

  Interpreter(){
    this->_buildins = make_shared<Map<shared_ptr<HiObject>, shared_ptr<HiObject>>>();


    this->_buildins->put(make_shared<HiString>("True"),  Universe::HiTrue);
    this->_buildins->put(make_shared<HiString>("False"), Universe::HiFalse);
    this->_buildins->put(make_shared<HiString>("None"),  Universe::HiNone);
  }


  void build_frame(shared_ptr<HiObject> callable, shared_ptr<ArrayList<shared_ptr<HiObject>>> args){

    auto tmp = dynamic_pointer_cast<FunctionObject>(callable);

    shared_ptr<FrameObject>  frame = make_shared<FrameObject>(tmp,args);
    frame->set_sender(this->_frame);
    this->_frame = frame;
  }

  void run(shared_ptr<CodeObject> codes) {
    this->_frame = make_shared<FrameObject>(codes);
    this->eval_frame();
    this->destroy_frame();
  }

  void destroy_frame(){
    this->_frame = this->_frame->sender();
  }

  void leave_frame(){
    this->destroy_frame();
    PUSH(this->_ret_value);
  }


  void eval_frame(){

    while (this->_frame->has_more_codes()) {

      unsigned char op_code           = this->_frame->get_op_code();
      bool has_argument               = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

      qInfo()<<"execute op_code"<<op_code;

      shared_ptr<FunctionObject> fo   = nullptr;

      int op_arg     =  -1;
      if(has_argument){
        op_arg = this->_frame->get_op_arg();
      }

      shared_ptr<HiInteger> lhs,rhs;
      shared_ptr<HiObject>  v,w,u,attr;
      shared_ptr<Block>     b;
      shared_ptr<ArrayList<shared_ptr<HiObject>>> args;

      switch (op_code) {

      case ByteCode::POP_TOP:
        POP();
        break;
      case ByteCode::RETURN_VALUE:
        this->_ret_value = POP();
        if(this->_frame->is_first_frame())
          return;
        leave_frame();
        break;
      case ByteCode::CALL_FUNCTION:
        if(op_arg > 0){
          args = make_shared<ArrayList<shared_ptr<HiObject>>>(op_arg);
          while(op_arg--){
            args->set(op_arg, POP());
          }
        }
        build_frame(POP(),args);
        break;
      case ByteCode::MAKE_FUNCTION:
        v  = POP();
        fo = make_shared<FunctionObject>(v);
        fo->set_globals(_frame->globals());              //函数对象的全局变量表就是当前上下文的全局变量表

        if(op_arg > 0){
          args = make_shared<ArrayList<shared_ptr<HiObject>>>(op_arg);
          while(op_arg--){
            args->set(op_arg, POP());
          }
        }

        fo->set_defaults(args);

        if(args != nullptr)
          args = nullptr;
        PUSH(fo);
        break;
      case ByteCode::BINARY_ADD: // 23
        v = this->_frame->stack()->pop();
        w = this->_frame->stack()->pop();
        this->_frame->stack()->add(w->add(v));
        break;
      case ByteCode::BINARY_MULTIPLY://20
        v = this->_frame->stack()->pop();
        w = this->_frame->stack()->pop();
        this->_frame->stack()->add(w->mul(v));
        break;
      case ByteCode::PRINT_ITEM://71
        v = this->_frame->stack()->pop();
        v->print();
        break;
      case ByteCode::PRINT_NEWLINE://72
        printf("\n");
        break;
      case ByteCode::BREAK_LOOP://80
        b = this->_frame->_loop_stack->pop();
        while(STACK_LEVEL() > b->_level){
          POP();
        }
        this->_frame->set_pc(b->_target);
        break;

      // case ByteCode::RETURN_VALUE://83
      // this->_frame->stack()->pop();
      // break;

      case ByteCode::POP_BLOCK://87
        b = this->_frame->_loop_stack->pop();
        while (STACK_LEVEL() > b->_level) {
          POP();
        }
        break;
      case ByteCode::STORE_NAME://90
        v = this->_frame->_names->get(op_arg);
        w = POP();
        this->_frame->_locals->put(v, w);
        break;
      case ByteCode::STORE_GLOBAL:
        v = this->_frame->_names->get(op_arg);
        w = POP();
        this->_frame->_globals->put(v, w);
        break;
      case ByteCode::LOAD_CONST: // 100
        this->_frame->stack()->add(this->_frame->_consts->get(op_arg));
        break;

      case ByteCode::LOAD_GLOBAL://
        v = this->_frame->_names->get(op_arg);
        w = this->_frame->globals()->get(v);

        //qInfo() << "LOAD_GLOBAL:" << "op_arg=";
        printf("LOAD_GLOBAL: op_arg=");
        v->print();
        printf("%d\n", this->_frame->globals()->size());
        this->_frame->globals()->get_key(0)->print();

        if (w != Universe::HiNone) {
          PUSH(w);
          break;
        }

        PUSH(Universe::HiNone);
        break;

      case ByteCode::LOAD_NAME: //101

        v = this->_frame->_names->get(op_arg);

        w = this->_frame->_locals->get(v);
        if (w != Universe::HiNone) {
          PUSH(w);
          break;
        }


        w = _frame->globals()->get(v);
        if(w != Universe::HiNone){
          PUSH(w);
          break;
        }

        w = this->_buildins->get(v);
        if(w != Universe::HiNone) {
          PUSH(w);
          break;
        }
          PUSH(Universe::HiNone);
          break;

        case ByteCode::COMPARE_OP: // 107
          w = POP();
          v = POP();

          switch (op_arg) {
          case ByteCode::GREATER:
            PUSH(v->greater(w));
            break;
          case ByteCode::LESS:
            PUSH(v->less(w));
            break;
          case ByteCode::EQUAL:
            PUSH(v->equal(w));
            break;
          case ByteCode::NOT_EQUAL:
            PUSH(v->not_equal(w));
            break;
          case ByteCode::GREATER_EQUAL:
            PUSH(v->ge(w));
            break;
          case ByteCode::LESS_EQUAL:
            PUSH(v->le(w));
            break;
          case ByteCode::IS:
            if (v == w)
              PUSH(HI_TRUE);
            else
              PUSH(HI_FALSE);
            break;
          case ByteCode::IS_NOT:
            if (v == w)
              PUSH(HI_FALSE);
            else
              PUSH(HI_TRUE);
            break;
          default:
            printf("Error: Unrecognized compare op %x\n", op_arg);
          }
          break;
      case ByteCode::JUMP_FORWARD: // 110
        this->_frame->set_pc(this->_frame->get_pc() + op_arg);
        break;
      case ByteCode::JUMP_ABSOLUTE: // 113
        this->_frame->set_pc(op_arg);
        break;
      case ByteCode::POP_JUMP_IF_FALSE: // 114
        v = POP();
        if (v == Universe::HiFalse)
          this->_frame->set_pc(op_arg);
        break;

      case ByteCode::SETUP_LOOP: // 120
          this->_frame->_loop_stack->add(make_shared<Block>(
              op_code, this->_frame->get_pc() + op_arg, STACK_LEVEL()));
          break;

      case ByteCode::LOAD_FAST: //124
        PUSH(this->_frame->fast_locals()->get(op_arg));
        break;

      case ByteCode::STORE_FAST: //125
        this->_frame->fast_locals()->set(op_arg,POP());
        break;

        default:
          printf("Error:Unrecognized byte code %d\n", op_code);
        }
    }
  }


};
