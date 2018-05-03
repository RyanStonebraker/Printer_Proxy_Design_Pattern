// Printer.h
// Header for the example "expensive operation" Printer class
// Instead of actually printing however, this class either prints to a file.

#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <queue>
#include <thread>

class Printer {
public:
  Printer(const std::string & file_dir="bin");
  ~Printer();
public:
  void printJob(const std::string & contents);
  void stopWatchingJobs();
  bool allJobsDone();
private:
  void watchPrintJobs();
  std::string getPrintLocation();
private:
  std::queue <std::string> _printJobs;
  std::thread _printJobWatcher;
  std::string _printDest;
  size_t _printNumber;
  bool _keepWatchingJobs;
};

#endif
