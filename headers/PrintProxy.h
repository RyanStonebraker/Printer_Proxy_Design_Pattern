// PrintProxy.h
// Header for the PrintProxy proxy class

#ifndef PRINTPROXY_H
#define PRINTPROXY_H

#include "Printer.h"
#include <sstream>
#include <string>

class PrintProxy {
public:
  PrintProxy(const std::string & print_folder = "");
  ~PrintProxy();
public:
  friend PrintProxy & operator<<(PrintProxy & ps, const std::string & content);
public:
  void print(const std::string & content);
  void flush();
  void setMaxCharactersPerPage(size_t pageSize);
  size_t getMaxCharactersPerPage() const;
  void setPrintDirectory(const std::string & print_dir);
  std::string getPrintDirectory() const;
private:
  std::string _printCache;
  size_t _maxCharactersPerPage;
  Printer _destPrinter;
  std::string _printDirectory;
};

#endif
