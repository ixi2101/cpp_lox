#include "lox/Lox.h"
#include "lyra/help.hpp"
#include "lyra/lyra.hpp"
#include "lyra/opt.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>

int main(int argc, char *argv[]) {
  std::string file_path;
  bool show_help;
 
  auto cli =
      lyra::cli() |
      lyra::opt(file_path, "filePath")["-f"]["--filepath"]("file to execute") |
      lyra::help(show_help);

  auto result = cli.parse({argc, argv});
  if (!result) {
    std::cerr << "Fatal error parsing cli args" << std::endl;
    exit(-1);
  }
  // if (show_help) {
  //   std::cout << cli << std::endl;
  //   exit(0);
  // }
  Lox lox;
  if (file_path != "") {
    std::string dbg = "test.lox";
    lox.runFile(dbg);
  } else {
    lox.runPrompt();
  }
}