#pragma once


#include "../code/codeObject.hpp"
#include "../code/byteCode.hpp"
#include "../object/hiInteger.hpp"
#include "../util/map.hpp"


#include <cstdio>
#include <memory>



#define PUSH(x)                    _stack->add((x))
#define POP()                      _stack->pop()
#define STACK_LEVEL()              _stack->size()


using std::shared_ptr;
using std::make_shared;

class Block{
public:
  unsigned char    _type;
  unsigned int     _target;
  int              _level;

  Block();
  Block(unsigned char b_type, unsigned int b_target, int b_level)
    :_type(b_type),_target(b_target),_level(b_level) {}

  Block& operator =(const Block& b){
    _type       = b._type;
    _target     = b._target;
    _level      = b._level;
    return *this;
  }
};



class Interpreter{
private:

  shared_ptr<ArrayList<shared_ptr<Block>>>                   _loop_stack;

  shared_ptr<ArrayList<shared_ptr<HiObject>>>                _stack;
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                _const;
  shared_ptr<ArrayList<shared_ptr<HiObject>>>                _co_names;
  shared_ptr<Map<shared_ptr<HiObject>,shared_ptr<HiObject>>> _vars;
public:
  void run(shared_ptr<CodeObject> codes) {
    int pc               = 0;
    int code_length      = codes->_bytecodes->length();
    _stack               = make_shared<ArrayList<shared_ptr<HiObject>>>(codes->_stack_size);
    _const               = codes->_consts;
    _co_names            = codes->_names;
    _vars                = make_shared <Map<shared_ptr<HiObject>, shared_ptr<HiObject>>>();
    _loop_stack          = make_shared<ArrayList<shared_ptr<Block>>>();


    while (pc < code_length) {

      unsigned char op_code           = codes->_bytecodes->value()[pc++];
      bool has_argument               = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

      int op_arg     =  -1;
      if(has_argument){
        int byte1    = (codes->_bytecodes->value()[pc++] & 0xFF);
        op_arg       = ((codes->_bytecodes->value()[pc++] & 0xFF) << 8) | byte1;
      }

      shared_ptr<HiInteger> lhs,rhs;
      shared_ptr<HiObject>  v,w,u,attr;
      shared_ptr<Block>     b;

      switch(op_code){
      case ByteCode::BINARY_ADD: // 23
        v = _stack->pop();
        w = _stack->pop();
        _stack->add(w->add(v));
        break;
      case ByteCode::PRINT_ITEM://71
        v = _stack->pop();
        v->print();
        break;
      case ByteCode::PRINT_NEWLINE://72
        printf("\n");
        break;
      case ByteCode::BREAK_LOOP://80
        b = _loop_stack->pop();
        while(STACK_LEVEL() > b->_level){
          POP();
        }
        pc = b->_target;
        break;
      case ByteCode::RETURN_VALUE://83
        _stack->pop();
        break;

      case ByteCode::POP_BLOCK://87
        b = _loop_stack->pop();
        while (STACK_LEVEL() > b->_level) {
          POP();
        }
        break;
      case ByteCode::STORE_NAME://90
        v = _co_names->get(op_arg);
        w = POP();
        _vars->put(v, w);
        break;
      case ByteCode::LOAD_CONST: // 100
        _stack->add(_const->get(op_arg));
        break;
      case ByteCode::LOAD_NAME: //101
        v = _co_names->get(op_arg);
        w = _vars->get(v);
        PUSH(w);
        break;
      case ByteCode::COMPARE_OP://107
        w = POP();
        v = POP();

        switch(op_arg){
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
        default:
          printf("Error: Unrecognized compare op %d\n",op_arg);
        }
        break;
      case ByteCode::JUMP_FORWARD://110
        pc = pc + op_arg;
        break;
      case ByteCode::JUMP_ABSOLUTE://113
        pc = op_arg;
        break;
      case ByteCode::POP_JUMP_IF_FALSE://114
        v = POP();
        if(v==Universe::HiFalse)
          pc = op_arg;
        break;

      case ByteCode::SETUP_LOOP://120
        _loop_stack->add(
            make_shared<Block>(op_code, pc + op_arg, STACK_LEVEL()));
        break;

      default:
        printf("Error:Unrecognized byte code %d\n",op_code);
      }
    }
  }
};
