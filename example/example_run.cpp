// example_run.cpp
// An example of client code that writes to the proxy Print class that then
// passes the print job to the Printer class

#include "Printer.h"
#include "PrintProxy.h"
#include <string>
#include <unistd.h>
#include <iostream>

int main () {
  // Calling the Printer class directly many times is expensive and requires a
  // constant extra watcher thread to handle print requests. This watcher thread
  // also must be stopped in order to exit the program.
  Printer testPrinter;

  testPrinter.printJob("test1");
  testPrinter.printJob("test2");
  testPrinter.printJob("test3");
  testPrinter.stopWatchingJobs();


  // The PrintProxy class minimizes the amount of calls to the Printer class by
  // aggregating print jobs together while they are under the define word count
  // for a page (that can be changed). Furthermore, it automatically handles
  // the Printer watcher thread by starting and stopping it around the required
  // print operations. This frees up the thread for most of the time. Also, the
  // PrintProxy class allows for destination folder to be changed mid printing,
  // and allows the use of the stream operator.
  PrintProxy testPrint("bin");

  testPrint.print("test1");
  testPrint.print("test2");
  testPrint.print("test3");
  testPrint << "test4" << "test5";
}
