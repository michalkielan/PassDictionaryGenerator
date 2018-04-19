/**
 * @file OptionParser.cpp
 *
 * @brief
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#include "OptionParser.hpp"

#include "RandomCharactersGenerator.hpp"

#include <iostream>


OptionParser::OptionParser(const int argc, char** argv) :
  mVariableMap{},
  mDescription{"Options"}
{
  mDescription.add_options()
    (mParams.help.c_str(),                                   "Print help messages")
    (mParams.words.c_str(),        po::value<std::string>(), "Input file with random words")
    (mParams.characters.c_str(),   po::value<int>(),         "Number of characters in passwords");

  try
  {
    po::store(po::parse_command_line(argc, argv, mDescription), mVariableMap);
  }
  catch(...)
  {
  }
}

int OptionParser::run()
{
  if(mVariableMap.count(mParams.help))
  {
    std::cout << mDescription << std::endl;
    return 0;
  }

  std::string words{};
  int characters{};

  try
  {
    characters = mVariableMap[mParams.characters].as<int>();
  }
  catch(...)
  {
    std::cout << "Error \'characters\' parameter" << std::endl;
    return -1;
  }

  try
  {
    words = mVariableMap["words"].as<std::string>();
  }
  catch(...)
  {
    std::cout << "Error \'words\' parameter" << std::endl;
    return -1;
  }

  std::unique_ptr<PassphraseGenerator> passGenerator;

  const std::string passPath {"pass.txt"};

  passGenerator = std::make_unique<RandomCharactersGenerator>(words, passPath, characters);
  passGenerator->generate();

  po::notify(mVariableMap);

  return 0;
}

