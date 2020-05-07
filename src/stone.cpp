#include "code/binaryFileParser.hpp"
#include "code/codeObject.hpp"
#include "stoneConfig.h"
#include "util/bufferedInputStream.hpp"
#include "runtime/interpreter.hpp"


#include <QFile>
#include <Qstring>
#include <QtCore>
#include <codecvt>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <string>



using std::cerr;
using std::cout;
using std::getline;
using std::ifstream;
using std::ios;
using std::locale;
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::wcout;
using std::wifstream;
using std::wofstream;

int main(int argc, char **argv) {
  //if (argc <= 1) {
  //  printf("vm need a parameter:filename\n");
  //  exit(1);
  //}

  //shared_ptr<BufferedInputStream> stream = make_shared<BufferedInputStream>(argv[1]);
  shared_ptr<BufferedInputStream> stream = make_shared<BufferedInputStream>("hello.pyc");
  // printf("magic number is 0x%x\n",stream->read_int());

  shared_ptr<BinaryFileParser> parser = make_shared<BinaryFileParser>(stream);

  shared_ptr<CodeObject> main_code = parser->parse().value();

  Interpreter interpreter;
  interpreter.run(main_code);
  return 0;
}
