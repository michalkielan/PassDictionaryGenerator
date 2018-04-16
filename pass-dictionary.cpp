//============================================================================
// Name        : pass-dictionary.cpp
// Author      : Michal Kielan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "AnuRandom.hpp"
#include "PassDictionary.hpp"

#include <memory>
#include <iostream>
#include <boost/program_options.hpp>


void generateDictionary(const std::size_t len)
{
  PassDictionary passDictionary{"words.txt", "pass.txt",
    std::make_shared<AnuRandom<char>>(len), len};

  passDictionary.generate();
}

/**
 * ./pass-dictionary -
 *
 *  -i file.txt
 *  -o file.txt
 *
 *  -engine=anu
 *  -engine=local
 *  -engine=cpu
 *
 */

namespace po = boost::program_options;

int main(int argc, const char** argv)
{

  const std::string help {"help"};
  const std::string input {"i"};
  const std::string output {"o"};
  const std::string engine {"engine"};

  po::options_description desc("Options");
  desc.add_options()
    (help.c_str(),   "Print help messages")
    (input.c_str(),  "input file with words")
    (output.c_str(), "output file with words and passwords")
    (engine.c_str(), "choose random engine");

  po::variables_map vm;

  po::store(po::parse_command_line(argc, argv, desc), vm);

  if(vm.count(help))
  {
    std::cout << "Help messages" << std::endl
              << desc << std::endl;
    return 0;
  }

  po::notify(vm); // throws on error, so do after help in case
                  // there are any problems

 // generateDictionary(8);
}

