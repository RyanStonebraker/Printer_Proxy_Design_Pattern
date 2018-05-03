// example_run.cpp
// An example of client code that writes to the proxy Print class that then
// passes the print job to the Printer class

#include "Printer.h"
#include <string>
#include <unistd.h>
#include <iostream>

int main () {
  Printer testPrinter;
  // usleep(1000);
  testPrinter.printJob("testing");
  testPrinter.printJob("tasetsa");
  testPrinter.printJob("asfsdf");
  testPrinter.stopWatchingJobs();
}
