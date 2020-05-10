#pragma once

class ByteCode{

public:
  static const unsigned char BINARY_ADD                     = 23;
  static const unsigned char PRINT_ITEM                     = 71;
  static const unsigned char PRINT_NEWLINE                  = 72;
  static const unsigned char BREAK_LOOP                     = 80;
  static const unsigned char RETURN_VALUE                   = 83;
  static const unsigned char POP_BLOCK                      = 87;
  static const unsigned char HAVE_ARGUMENT                  = 90;
  static const unsigned char STORE_NAME                     = 90;
  // index in const list
  static const unsigned char LOAD_CONST                     = 100;
  static const unsigned char LOAD_NAME                      = 101;
  //Comparison operator
  static const unsigned char COMPARE_OP                     = 107;
  //Number of bytes to skip
  static const unsigned char JUMP_FORWARD                   = 110;
  static const unsigned char JUMP_ABSOLUTE                  = 113;
  static const unsigned char POP_JUMP_IF_FALSE              = 114;

  static const unsigned char SETUP_LOOP                     = 120;

      enum COMPARE {
        LESS = 0,
        LESS_EQUAL,
        EQUAL,
        NOT_EQUAL,
        GREATER,
        GREATER_EQUAL
      };
};


