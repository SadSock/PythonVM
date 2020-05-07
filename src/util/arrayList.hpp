#pragma once


#include <cstdio>

template <typename T>

class ArrayList{
private:
  int _length;
  T* _array;
  int _size;

  void expand() {
    T *new_array = new T[this->_length << 1];
    for (int i = 0; i < this->_length; i++) {
      new_array[i] = this->_array[i];
    }

    delete[] this->_array;
    this->_array = new_array;
    this->_length = this->_length << 1;

    printf("expand an array to %d, size is %d\n", this->_length, this->_size);
  }

public:
  ArrayList(int n = 8) : _length(n), _array(new T[n]), _size(0) {}

  void add(T t) {
    if (this->_size >= this->_length)
      this->expand();

    this->_array[this->_size++] = t;
  }
  void insert(int index, T t) {

    this->add(nullptr);
    for (int i = this->_size; i > index; i--) {
      this->_array[i] = this->_array[i - 1];
    }

    this->_array[index] = t;
  }
  T get(int index) { return _array[index]; };
  void set(int index, T t) {
    if (this->_size <= index)
      this->_size = index + 1;

    while (this->_size > this->_length)
      this->expand();

    this->_array[index] = t;
  }
  int size() { return this->_size; };
  int length() { return this->_length; };
  T pop() { return this->_array[--this->_size]; }
  };
