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
                                                 _printNumber(0),
                                                 _keepWatchingJobs(true)
{
  watchPrintJobs();
}

Printer::Printer(Printer && rhs)  {
  _printJobs = std::move(rhs._printJobs);
  _printDest = std::move(rhs._printDest);
  _printNumber = std::move(rhs._printNumber);
  rhs.stopWatchingJobs();
  _keepWatchingJobs = true;
}

Printer Printer::operator=(Printer && rhs) {
  _printJobs = std::move(rhs._printJobs);
  _printDest = std::move(rhs._printDest);
  _printNumber = std::move(rhs._printNumber);
  rhs.stopWatchingJobs();
  _keepWatchingJobs = true;

  return std::move(*this);
}


Printer::~Printer() {
  if (_printJobWatcher.joinable())
    _printJobWatcher.join();
}

void Printer::printJob(const std::string & contents) {
  _printJobs.push(contents);
}

std::string Printer::getPrintLocation() {
  ++_printNumber;
  auto printLocation = (_printDest.size() == 0
                              || _printDest[_printDest.size() - 1] == '/')
                              ? _printDest : _printDest + "/";
  printLocation += "print_" + std::to_string(_printNumber) + ".txt";
  std::cout << "Printing To: " << printLocation << std::endl;
  return printLocation;
}

void Printer::watchPrintJobs() {
  _printJobWatcher = std::thread([&]() {
    while (true) {
      if (_printJobs.size() > 0) {
        std::ofstream printWriter(getPrintLocation());
        printWriter << _printJobs.front();

        // This is done to intentionally make slower for demo purposes
        usleep(1000000);

        _printJobs.pop();
      }
      else {
        if (_keepWatchingJobs == false)
          break;
        // This is done to intentionally make slower for demo purposes
        usleep(1000000);
      }
    }
  });
}

void Printer::stopWatchingJobs() {
  if (_keepWatchingJobs) {
    _keepWatchingJobs = false;
    if (_printJobWatcher.joinable())
      _printJobWatcher.join();
  }
}

void Printer::startWatchingJobs() {
  if (!_keepWatchingJobs) {
    _keepWatchingJobs = true;
    watchPrintJobs();
  }
}

bool Printer::allJobsDone() {
  return _printJobs.size() == 0;
}
