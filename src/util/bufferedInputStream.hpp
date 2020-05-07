#pragma once


#include <cstdio>
#include <memory>


using std::shared_ptr;

const int BUFFER_LEN = 256;

class BufferedInputStream{
private:
  FILE *fp;
  char szBuffer[BUFFER_LEN];
  unsigned short index;


public:

  BufferedInputStream(char const * filename){
    fp = fopen(filename,"rb");
    fread(this->szBuffer,BUFFER_LEN*sizeof(char),1,this->fp);
    this->index = 0;
  }

  ~BufferedInputStream(){
    this->close();
  }

  char read(){
    if(index < BUFFER_LEN)
      return this->szBuffer[index++];
    else{
      this->index = 0;
      fread(this->szBuffer,BUFFER_LEN*sizeof(char),1,fp);
      return this->szBuffer[this->index++];
    }
  }

  int read_int(){
    int b1 = this->read() & 0xff;
    int b2 = this->read() & 0xff;
    int b3 = this->read() & 0xff;
    int b4 = this->read() & 0xff;

    return b4<<24|b3<<16|b2<<8|b1;
  }

  void unread(){
    this->index--;
  }

  void close(){
    if(fp!=NULL){
      fclose(fp);
      fp=NULL;
    }
  };

};
