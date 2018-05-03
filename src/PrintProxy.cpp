// PrintProxy.cpp
// Implementation for the Print proxy class

#include "PrintProxy.h"
#include "Printer.h"

PrintProxy::PrintProxy(const std::string & print_folder) : _printCache(""),
                       _maxCharactersPerPage(100),
                       _destPrinter(Printer(print_folder)),
                       _printDirectory(print_folder) {}

PrintProxy::~PrintProxy() {
  flush();
  _destPrinter.stopWatchingJobs();
}

PrintProxy & operator<<(PrintProxy & ps, const std::string & content) {
  ps.print(content);
  return ps;
}

void PrintProxy::flush() {
  _destPrinter.startWatchingJobs();
  if (_printCache.size() > 0) {
    _destPrinter.printJob(_printCache);
    _printCache.clear();
  }
  _destPrinter.stopWatchingJobs();
}

void PrintProxy::print(const std::string & content) {
  auto overSheetOfPaper = content.size() + _printCache.size() > _maxCharactersPerPage;
  if (overSheetOfPaper) {
    flush();
    _printCache = content;
  }
  else {
    _printCache += content + "\n";
  }
}

void PrintProxy::setMaxCharactersPerPage(size_t pageSize) {
  _maxCharactersPerPage = pageSize;
}

size_t PrintProxy::getMaxCharactersPerPage() const {
  return _maxCharactersPerPage;
}

void PrintProxy::setPrintDirectory(const std::string & print_dir) {
  _destPrinter.stopWatchingJobs();
  Printer newDirPrinter(print_dir);
  _destPrinter = std::move(newDirPrinter);
  _printDirectory = print_dir;
}
std::string PrintProxy::getPrintDirectory() const {
  return _printDirectory;
}
