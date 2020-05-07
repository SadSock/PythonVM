#pragma once

#include "../object/hiObject.hpp"
#include "../object/hiString.hpp"
#include "../util/arrayList.hpp"

#include <memory>

using std::shared_ptr;

class CodeObject : public HiObject {
public:
  int _argcount;
  int _nlocals;
  int _stack_size;
  int _flag;
  shared_ptr<HiString> _bytecodes;

  shared_ptr<ArrayList<shared_ptr<HiObject>>> _consts;
  shared_ptr<ArrayList<shared_ptr<HiObject>>> _names;
  shared_ptr<ArrayList<shared_ptr<HiObject>>> _varnames;
  shared_ptr<ArrayList<shared_ptr<HiObject>>> _freevars;
  shared_ptr<ArrayList<shared_ptr<HiObject>>> _cellvars;
  shared_ptr<HiString> _file_name;
  shared_ptr<HiString> _co_name;
  int _lineno;
  shared_ptr<HiString> _notable;

  CodeObject(int argcount, int nlocals, int stacksize, int flag,
             shared_ptr<HiString> bytecodes,
             shared_ptr<ArrayList<shared_ptr<HiObject>>> consts,
             shared_ptr<ArrayList<shared_ptr<HiObject>>> names,
             shared_ptr<ArrayList<shared_ptr<HiObject>>> varnames,
             shared_ptr<ArrayList<shared_ptr<HiObject>>> freevars,
             shared_ptr<ArrayList<shared_ptr<HiObject>>> cellvars,
             shared_ptr<HiString> file_name, shared_ptr<HiString> co_name,
             int lineno, shared_ptr<HiString> notable)
      : _argcount(argcount), _nlocals(nlocals), _stack_size(stacksize),
        _flag(flag), _bytecodes(bytecodes), _consts(consts), _names(names),
        _varnames(varnames), _freevars(freevars), _cellvars(cellvars),
        _file_name(file_name), _co_name(co_name), _lineno(lineno),
        _notable(notable) {}
};
