#include "code/binaryFileParser.hpp"
#include "code/codeObject.hpp"
#include "runtime/interpreter.hpp"
#include "stoneConfig.h"
#include "util/bufferedInputStream.hpp"

#include <QDateTime>
#include <QFile>
#include <QString>
#include <QtCore>
#include <QtMessageHandler>
#include <codecvt>
#include <cstdio>
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

void LogMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {

  FILE* fileLog  = fopen("log.txt", "a+");

  QByteArray localMsg = msg.toLocal8Bit();
  const char *file = context.file ? context.file : "";
  const char *function = context.function ? context.function : "";
  switch (type) {
  case QtDebugMsg:
    fprintf(fileLog, "[%s] [Debug]: %s (%s:%u, %s)\n",
            QDateTime::currentDateTime()
                .toString("yyyy-MM-dd hh:mm:ss.zzz")
                .toLocal8Bit()
                .data(),
            localMsg.constData(), file, context.line, function);
    break;
  case QtInfoMsg:
    fprintf(fileLog, "[%s] [Info]: %s (%s:%u, %s)\n",
            QDateTime::currentDateTime()
                .toString("yyyy-MM-dd hh:mm:ss.zzz")
                .toLocal8Bit()
                .data(),
            localMsg.constData(), file, context.line, function);
    break;
  case QtWarningMsg:
    fprintf(fileLog, "[%s] [Warning]: %s (%s:%u, %s)\n",
            QDateTime::currentDateTime()
                .toString("yyyy-MM-dd hh:mm:ss.zzz")
                .toLocal8Bit()
                .data(),
            localMsg.constData(), file, context.line, function);
    break;
  case QtCriticalMsg:
    fprintf(fileLog, "[%s] [Critical]: %s (%s:%u, %s)\n",
            QDateTime::currentDateTime()
                .toString("yyyy-MM-dd hh:mm:ss.zzz")
                .toLocal8Bit()
                .data(),
            localMsg.constData(), file, context.line, function);
    break;
  case QtFatalMsg:
    fprintf(fileLog, "[%s] [Fatal]: %s (%s:%u, %s)\n",
            QDateTime::currentDateTime()
                .toString("yyyy-MM-dd hh:mm:ss.zzz")
                .toLocal8Bit()
                .data(),
            localMsg.constData(), file, context.line, function);
    break;
  }
  if (fileLog) {
    fclose(fileLog);
  }
}


int main(int argc, char **argv) {

  if (argc <= 1) {
    printf("vm need a parameter:filename\n");
    exit(1);
  }

  qInstallMessageHandler(LogMessageOutput);
  // shared_ptr<BufferedInputStream> stream =
  // make_shared<BufferedInputStream>(argv[1]);
  shared_ptr<BufferedInputStream> stream = make_shared<BufferedInputStream>(argv[1]);
  // printf("magic number is 0x%x\n",stream->read_int());

  shared_ptr<BinaryFileParser> parser = make_shared<BinaryFileParser>(stream);

  shared_ptr<CodeObject> main_code = parser->parse().value();

  Interpreter interpreter;

  interpreter.run(main_code);

  return 0;
}
