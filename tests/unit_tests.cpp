// client_test.cpp
// tests that make sure the print proxy class is working correctly

#include "catch.hpp"

#include "Printer.h"
#include "PrintProxy.h"
#include <fstream>
#include <stdio.h>

SCENARIO ("Printing without the print proxy", "[Printer]") {
  std::string printFolder = "tests";
  WHEN ("There are no print jobs.") {
    Printer emptyPrinter(printFolder);
    emptyPrinter.stopWatchingJobs();
    THEN ("No print files should be created.") {
      std::ifstream emptyReader("tests/print_1.txt");
      REQUIRE(!emptyReader);
    }
  }

  WHEN ("There is one print job.") {
    Printer somePrinter(printFolder);
    std::string sentContent = "some text.";
    somePrinter.printJob(sentContent);
    somePrinter.stopWatchingJobs();

    while(!somePrinter.allJobsDone()){}

    std::ifstream someReader("tests/print_1.txt");

    THEN ("The print file should exist.") {
      REQUIRE(!!someReader);
    }

    THEN ("The print file should contain the correct text.") {
      std::string actualPrintContent;
      std::getline(someReader, actualPrintContent);
      REQUIRE(actualPrintContent == sentContent);
    }

    system("make clean_tests");
  }

  WHEN ("There are multiple print jobs.") {
    Printer multiplePrinter(printFolder);
    std::string print1Text = "first print text.";
    std::string print2Text = "second print text.";
    std::string print3Text = "third print text.";

    multiplePrinter.printJob(print1Text);
    multiplePrinter.printJob(print2Text);
    multiplePrinter.printJob(print3Text);
    multiplePrinter.stopWatchingJobs();

    while(!multiplePrinter.allJobsDone()){}

    std::ifstream reader1("tests/print_1.txt");
    std::ifstream reader2("tests/print_2.txt");
    std::ifstream reader3("tests/print_3.txt");

    THEN ("All print files should exist.") {
      REQUIRE(!!reader1);
      REQUIRE(!!reader2);
      REQUIRE(!!reader3);
    }

    THEN ("All print files should contain the correct text.") {
      std::string actualText;

      std::getline(reader1, actualText);
      REQUIRE(actualText == print1Text);

      std::getline(reader2, actualText);
      REQUIRE(actualText == print2Text);

      std::getline(reader3, actualText);
      REQUIRE(actualText == print3Text);
    }

    system("make clean_tests");
  }
}
