#include <iostream>
#include <fstream>
#include "parsing.hpp"

void exit_print_usage()
{
  std::cout << "USAGE: mdtest.exe <INPUT FILE>"
            << std::endl;
  std::exit(-1);
}

int main(int argc, char const *argv[])
{
  using namespace gmb::utils::markdown;

  if(argc != 2) {
    exit_print_usage();
  }

  std::ifstream f(argv[1]);
  if(!f) {
    std::cerr << "Couldn't open '" << argv[1]
              << "' for reading" << std::endl;
    exit_print_usage();
  }

  std::cout << "<!DOCTYPE html><html><head /><body>";
  char buffer[256];
  auto hdrlvl = 0;

  initialize_state();

  do {
    f.read(&buffer[0], sizeof(buffer));

    auto first = &buffer[0],
         last = &buffer[f.gcount()];

    for(;first != last; ++first) {

      if(!decode(*first, std::cout)) {
        std::cout.put(*first);
      }
    }
  }
  while(f);

  std::cout << "</body></html>";

  return 0;
}

