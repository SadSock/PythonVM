#pragma once

class ByteCode {

public:
  // static const unsigned char BINARY_ADD                     = 23;
  // static const unsigned char PRINT_ITEM                     = 71;
  // static const unsigned char PRINT_NEWLINE                  = 72;
  // static const unsigned char BREAK_LOOP                     = 80;
  // static const unsigned char RETURN_VALUE                   = 83;
  // static const unsigned char POP_BLOCK                      = 87;
  static const unsigned char HAVE_ARGUMENT                  = 90;
  // static const unsigned char STORE_NAME                     = 90;
  // // index in const list
  // static const unsigned char LOAD_CONST                     = 100;
  // static const unsigned char LOAD_NAME                      = 101;
  // //Comparison operator
  // static const unsigned char COMPARE_OP                     = 107;
  // //Number of bytes to skip
  // static const unsigned char JUMP_FORWARD                   = 110;
  // static const unsigned char JUMP_ABSOLUTE                  = 113;
  // static const unsigned char POP_JUMP_IF_FALSE              = 114;

  // static const unsigned char SETUP_LOOP                     = 120;

  static const unsigned char BINARY_ADD = 23;
  static const unsigned char BINARY_AND = 64;
  static const unsigned char BINARY_DIVIDE = 21;
  static const unsigned char BINARY_FLOOR_DIVIDE = 26;
  static const unsigned char BINARY_LSHIFT = 62;
  static const unsigned char BINARY_MODULO = 22;
  static const unsigned char BINARY_MULTIPLY = 20;
  static const unsigned char BINARY_OR = 66;
  static const unsigned char BINARY_POWER = 19;
  static const unsigned char BINARY_RSHIFT = 63;
  static const unsigned char BINARY_SUBSCR = 25;
  static const unsigned char BINARY_SUBTRACT = 24;
  static const unsigned char BINARY_TRUE_DIVIDE = 27;
  static const unsigned char BINARY_XOR = 65;
  static const unsigned char BREAK_LOOP = 80;
  static const unsigned char BUILD_CLASS = 89;
  static const unsigned char BUILD_LIST = 103;
  static const unsigned char BUILD_MAP = 105;
  static const unsigned char BUILD_SET = 104;
  static const unsigned char BUILD_SLICE = 133;
  static const unsigned char BUILD_TUPLE = 102;
  static const unsigned char CALL_FUNCTION = 131;
  static const unsigned char CALL_FUNCTION_KW = 141;
  static const unsigned char CALL_FUNCTION_VAR = 140;
  static const unsigned char CALL_FUNCTION_VAR_KW = 142;
  static const unsigned char COMPARE_OP = 107;
  static const unsigned char CONTINUE_LOOP = 119;
  static const unsigned char DELETE_ATTR = 96;
  static const unsigned char DELETE_FAST = 126;
  static const unsigned char DELETE_GLOBAL = 98;
  static const unsigned char DELETE_NAME = 91;
  //'DELETE_SLICE+0': 50,
  //'DELETE_SLICE+1': 51,
  //.'DELETE_SLICE+2': 52,
  //'DELETE_SLICE+3': 53,
  static const unsigned char DELETE_SUBSCR = 61;
  static const unsigned char DUP_TOP = 4;
  static const unsigned char DUP_TOPX = 99;
  static const unsigned char END_FINALLY = 88;
  static const unsigned char EXEC_STMT = 85;
  static const unsigned char EXTENDED_ARG = 145;
  static const unsigned char FOR_ITER = 93;
  static const unsigned char GET_ITER = 68;
  static const unsigned char IMPORT_FROM = 109;
  static const unsigned char IMPORT_NAME = 108;
  static const unsigned char IMPORT_STAR = 84;
  static const unsigned char INPLACE_ADD = 55;
  static const unsigned char INPLACE_AND = 77;
  static const unsigned char INPLACE_DIVIDE = 58;
  static const unsigned char INPLACE_FLOOR_DIVIDE = 28;
  static const unsigned char INPLACE_LSHIFT = 75;
  static const unsigned char INPLACE_MODULO = 59;
  static const unsigned char INPLACE_MULTIPLY = 57;
  static const unsigned char INPLACE_OR = 79;
  static const unsigned char INPLACE_POWER = 67;
  static const unsigned char INPLACE_RSHIFT = 76;
  static const unsigned char INPLACE_SUBTRACT = 56;
  static const unsigned char INPLACE_TRUE_DIVIDE = 29;
  static const unsigned char INPLACE_XOR = 78;
  static const unsigned char JUMP_ABSOLUTE = 113;
  static const unsigned char JUMP_FORWARD = 110;
  static const unsigned char JUMP_IF_FALSE_OR_POP = 111;
  static const unsigned char JUMP_IF_TRUE_OR_POP = 112;
  static const unsigned char LIST_APPEND = 94;
  static const unsigned char LOAD_ATTR = 106;
  static const unsigned char LOAD_CLOSURE = 135;
  static const unsigned char LOAD_CONST = 100;
  static const unsigned char LOAD_DEREF = 136;
  static const unsigned char LOAD_FAST = 124;
  static const unsigned char LOAD_GLOBAL = 116;
  static const unsigned char LOAD_LOCALS = 82;
  static const unsigned char LOAD_NAME = 101;
  static const unsigned char MAKE_CLOSURE = 134;
  static const unsigned char MAKE_FUNCTION = 132;
  static const unsigned char MAP_ADD = 147;
  static const unsigned char NOP = 9;
  static const unsigned char POP_BLOCK = 87;
  static const unsigned char POP_JUMP_IF_FALSE = 114;
  static const unsigned char POP_JUMP_IF_TRUE = 115;
  static const unsigned char POP_TOP = 1;
  static const unsigned char PRINT_EXPR = 70;
  static const unsigned char PRINT_ITEM = 71;
  static const unsigned char PRINT_ITEM_TO = 73;
  static const unsigned char PRINT_NEWLINE = 72;
  static const unsigned char PRINT_NEWLINE_TO = 74;
  static const unsigned char RAISE_VARARGS = 130;
  static const unsigned char RETURN_VALUE = 83;
  static const unsigned char ROT_FOUR = 5;
  static const unsigned char ROT_THREE = 3;
  static const unsigned char ROT_TWO = 2;
  static const unsigned char SETUP_EXCEPT = 121;
  static const unsigned char SETUP_FINALLY = 122;
  static const unsigned char SETUP_LOOP = 120;
  static const unsigned char SETUP_WITH = 143;
  static const unsigned char SET_ADD = 146;
  //'SLICE+0': 30,
  //'SLICE+1': 31,
  //'SLICE+2': 32,
  //'SLICE+3': 33,
  static const unsigned char STOP_CODE = 0;
  static const unsigned char STORE_ATTR = 95;
  static const unsigned char STORE_DEREF = 137;
  static const unsigned char STORE_FAST = 125;
  static const unsigned char STORE_GLOBAL = 97;
  static const unsigned char STORE_MAP = 54;
  static const unsigned char STORE_NAME = 90;
  //'STORE_SLICE+0': 40,
  //'STORE_SLICE+1': 41,
  //'STORE_SLICE+2': 42,
  //'STORE_SLICE+3': 43,
  static const unsigned char STORE_SUBSCR = 60;
  static const unsigned char UNARY_CONVERT = 13;
  static const unsigned char UNARY_INVERT = 15;
  static const unsigned char UNARY_NEGATIVE = 11;
  static const unsigned char UNARY_NOT = 12;
  static const unsigned char UNARY_POSITIVE = 10;
  static const unsigned char UNPACK_SEQUENCE = 92;
  static const unsigned char WITH_CLEANUP = 81;
  static const unsigned char YIELD_VALUE = 86;

  enum COMPARE {
    LESS               = 0,
    LESS_EQUAL,
    EQUAL,
    NOT_EQUAL,
    GREATER,
    GREATER_EQUAL,
    IS                 = 8,
    IS_NOT
  };
};
