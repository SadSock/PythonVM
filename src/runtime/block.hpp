#pragma once


class Block {
public:
  unsigned char _type;
  unsigned int _target;
  int _level;

  Block();
  Block(unsigned char b_type, unsigned int b_target, int b_level)
      : _type(b_type), _target(b_target), _level(b_level) {}

  Block &operator=(const Block &b) {
    _type = b._type;
    _target = b._target;
    _level = b._level;
    return *this;
  }
};
