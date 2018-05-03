// Printer.cpp
// Implementation of the example "expensive operation" Printer class

#include "Printer.h"
#include <thread>
#include <mutex>
#include <fstream>
#include <iostream>

// The below macro makes usleep cross-platform compatible with Windows
// and systems supporting unistd
#ifdef _WIN32
	#include <windows.h>
	#define usleep(tm) Sleep(tm * 0.001)
#endif
#ifndef _WIN32
	#include <unistd.h>
#endif

Printer::Printer(const std::string & file_dir) : _printDest(file_dir),
                                                 _printNumber(0)
{
  watchPrintJobs();
}

Printer::~Printer() {
  _printJobWatcher.join();
}

void Printer::printJob(const std::string & contents) {
  _printJobs.push(contents);
}

std::string Printer::getPrintLocation() {
  ++_printNumber;
  std::string printLocation = (_printDest.size() == 0
                              || _printDest[_printDest.size() - 1] == '/')
                              ? _printDest : _printDest + "/";
  printLocation += "print_" + std::to_string(_printNumber) + ".txt";
  std::cout << "Printing To: " << printLocation << std::endl;
  return printLocation;
}

void Printer::watchPrintJobs() {
  _printJobWatcher = std::thread([&]() {
    while (true) {
      // std::cout << "Print Queue Size: " << _printJobs.size() << std::endl;
      if (_printJobs.size() > 0) {
        std::ofstream printWriter(getPrintLocation());
        printWriter << _printJobs.front();
        _printJobs.pop();

        // This is done to intentionally make slower for demo purposes
        usleep(1000000);
      }
      else {
        // This is done to intentionally make slower for demo purposes
        usleep(1000000);
      }
    }
  });
}
