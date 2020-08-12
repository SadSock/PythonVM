#pragma once


#include "../runtime/universe.hpp"

#include <memory>
#include <vector>


using std::make_shared;
using std::shared_ptr;
using std::unique_ptr;
using std::make_unique;
using std::vector;


template <typename K, typename V>
class MapEntry{
public:
  K _k;
  V _v;

  MapEntry(const MapEntry<K,V>& entry){
    this->_k = entry._k;
    this->_v = entry._v;
  }

  MapEntry(K k,V v):_k(k),_v(v){}

  MapEntry():_k(0),_v(0){}
};


template <typename K, typename V>
class Map{
private:
  vector<MapEntry<K,V>> _entries;


public:
  Map(){
    this->_entries = vector<MapEntry<K,V>>();
  }
  int size(){return this->_entries.size();}
  void put(K k,V v){
    for(int i = 0; i < this->_entries.size(); i++){
      if(this->_entries[i]._k->equal(k) ==  Universe::HiTrue){
        this->_entries[i]._v = v;
        return;
      }
    }
    this->_entries.push_back(MapEntry<K,V>(k,v));
    return;
  }
  V get(K k){
    int i = this->index(k);
    if(i < 0)
      return Universe::HiNone;
    else
      return this->_entries[i]._v;
  }
  bool has_key(K k){
    int i = index(k);
    return i >= 0;
  }
  K get_key(int index){
    return this->_entries[index]._k;
  }
  int index(K k){
    for(int i = 0; i < this->_entries.size(); i++){
      if(this->_entries[i]._k->equal(k) == Universe::HiTrue){
        return i;
      }
    }
    return -1;
  }
  V remove(K k){
    int i = index(k);
    if(i < 0) return 0;
    V v = this->_entries[i]._v;
    this->_entries[i] = this->_entries[this->_entries.size()-1];
    this->_entries.erase(this->_entries.begin() + this->_entries.size() - 1 );
    return v;
  }
};

template class Map<shared_ptr<HiObject>,shared_ptr<HiObject>>;
