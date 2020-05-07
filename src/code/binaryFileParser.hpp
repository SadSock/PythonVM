#pragma once

#include "../object/hiString.hpp"
#include "../object/hiInteger.hpp"
#include "../util/arrayList.hpp"
#include "../util/bufferedInputStream.hpp"
#include "../code/codeObject.hpp"
#include "../object/hiObject.hpp"


#include <cstdio>
#include <cassert>
#include <type_traits>
#include <iostream>
#include <memory>
#include <optional>


using std::cout;
using std::endl;
using std::shared_ptr;
using std::optional;
using std::nullopt;
using std::make_shared;
using std::dynamic_pointer_cast;


class BinaryFileParser {
private:
  shared_ptr<BufferedInputStream> file_stream;

public:
  BinaryFileParser(shared_ptr<BufferedInputStream> stream):file_stream(stream){}

  optional<shared_ptr<CodeObject>> parse(){
    int magic_number = this->file_stream->read_int();
    printf("magic number is 0x %x\n",magic_number);

    int moddate = this->file_stream->read_int();
    printf("moddate is 0x %x\n",moddate);


    char object_type = this->file_stream->read();

    if(object_type == 'c'){
      optional<shared_ptr<CodeObject>> result = nullopt;
      result = this->get_code_object();
      printf("parse OK! \n");
      return result;
    }

    return nullopt;
  }



  shared_ptr<HiString> get_byte_codes(){
    assert(this->file_stream->read()=='s');
    return this->get_string();
  }

  shared_ptr<HiString> get_string(){
    int length = this->file_stream->read_int();
    char* str_value = new char[length];

    //shared_ptr<string> str_value = std::make_sh

    //shared_ptr<char> str_value = std::make_shared<char>(char[length]);

    for(int i = 0; i < length; i++){
      str_value[i] = this->file_stream->read();
    }

    shared_ptr<HiString> s = make_shared<HiString>(str_value,length);
    delete [] str_value;

    return s;
  }

  shared_ptr<ArrayList<shared_ptr<HiObject>>> get_tuple() {
    int length = this->file_stream->read_int();
    shared_ptr<HiString> str = make_shared<HiString>("");

    shared_ptr<ArrayList<shared_ptr<HiObject>>> list = make_shared<ArrayList<shared_ptr<HiObject>>>(length);

    for(int i = 0; i < length; i++){
      char obj_type = this->file_stream->read();

      switch(obj_type){
      case 'c':
        printf("got a code object.\n");
        list->add(this->get_code_object().value());
        break;
      case 'i':
        list->add(make_shared<HiInteger>(this->file_stream->read_int()));
        break;
      case 'N':
        list->add(NULL);
        break;
        //case 't':
        //str = this->get_string();
        //list->add(str);
      }
    }

    return list;
  }

  optional<shared_ptr<ArrayList<shared_ptr<HiObject>>>> get_consts(){
    if(this->file_stream->read()=='('){
      return this->get_tuple();
    }

    this->file_stream->unread();
    return nullopt;
  }

  shared_ptr<ArrayList<shared_ptr<HiObject>>> get_names(){
    shared_ptr<ArrayList<shared_ptr<HiObject>>> list = make_shared<ArrayList<shared_ptr<HiObject>>>();
    return list;
  }

  shared_ptr<ArrayList<shared_ptr<HiObject>>> get_var_names() {
    shared_ptr<ArrayList<shared_ptr<HiObject>>> list =
        make_shared<ArrayList<shared_ptr<HiObject>>>();
    return list;
  }

  shared_ptr<ArrayList<shared_ptr<HiObject>>> get_free_vars(){
    shared_ptr<ArrayList<shared_ptr<HiObject>>> list = make_shared<ArrayList<shared_ptr<HiObject>>>();
    return list;
  }
  shared_ptr<ArrayList<shared_ptr<HiObject>>> get_cell_vars(){
    shared_ptr<ArrayList<shared_ptr<HiObject>>> list = make_shared<ArrayList<shared_ptr<HiObject>>>();
    return list;
  }
  shared_ptr<HiString> get_file_name(){
    shared_ptr<HiString> str = make_shared<HiString>("");
    return str;
  }
  shared_ptr<HiString> get_name(){
     shared_ptr<HiString> str =  make_shared<HiString>("");
    return str;
  }
  shared_ptr<HiString> get_no_table(){
    shared_ptr<HiString> str = make_shared<HiString>("");
    return str;
  }

  optional<shared_ptr<CodeObject>> get_code_object() {
    int argcount         = this->file_stream->read_int();
    printf("%d",argcount);
    int nlocals          = this->file_stream->read_int();
    int stacksize        = this->file_stream->read_int();
    int flag             = this->file_stream->read_int();
    printf("%d",flag);

    shared_ptr<HiString> byte_codes                                = this->get_byte_codes();
    shared_ptr<ArrayList<shared_ptr<HiObject>>>  consts            = this->get_consts().value();
    shared_ptr<ArrayList<shared_ptr<HiObject>>>  names             = this->get_names();
    shared_ptr<ArrayList<shared_ptr<HiObject>>>  var_names         = this->get_var_names();
    shared_ptr<ArrayList<shared_ptr<HiObject>>>  free_vars         = this->get_free_vars();
    shared_ptr<ArrayList<shared_ptr<HiObject>>>  cell_vars         = this->get_cell_vars();
    shared_ptr<HiString>                         file_name         = this->get_file_name();
    shared_ptr<HiString>                         module_name       = this->get_name();
    int                                          begin_line_no     = this->file_stream->read_int();
    shared_ptr<HiString>                         lnotab            = this->get_no_table();

    shared_ptr<CodeObject> ret = make_shared<CodeObject>(
               argcount,
               nlocals,
               stacksize,
               flag,
               byte_codes,
               consts,
               names,
               var_names,
               free_vars,
               cell_vars,
               file_name,
               module_name,
               begin_line_no,
               lnotab);
    return ret;
  }
};


