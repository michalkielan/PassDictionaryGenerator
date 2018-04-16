#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <array>

#include "RandomEngine.hpp"
#include "PassDictionary.hpp"
#include "AnuRandom.hpp"

#include <boost/program_options.hpp>



class PassGenerator
{
public:

  PassGenerator(const std::string words, const int characters)
  {
  }

  virtual void generate() = 0;

  virtual ~PassGenerator() = default;
};

class RandomCharactersGenerator : public PassGenerator
{
public:

  RandomCharactersGenerator(const std::string words, const int characters)
  {
  }

  void generate() override
  {

  }

  virtual ~RandomCharactersGenerator() = default;
};

class NumberGenerator : public PassGenerator
{
public:

  NumberGenerator(const std::string words, const int characters)
  {
  }

  void generate() override
  {
  }

  virtual ~NumberGenerator() = default;
};

namespace po = boost::program_options;

class OptionParser
{

  po::variables_map       mVariableMap;
  po::options_description mDescription;

  const struct
  {
    const std::string help {"help"};
    const std::string words {"words"};
    const std::string numbersOnly {"numbers-only"};
    const std::string characters {"characters"};
  } mParams;

public:

  OptionParser(const int argc, char** argv) :
    mVariableMap{},
    mDescription{"Options"}
  {
    mDescription.add_options()
      (mParams.help.c_str(),                                   "Print help messages")
      (mParams.words.c_str(),        po::value<std::string>(), "Input file with random words")
      (mParams.numbersOnly.c_str(),                            "Passwords is only numbers, sorted from 0 to N")
      (mParams.characters.c_str(),   po::value<int>(),         "Number of characters in passwords");

    try
    {
      po::store(po::parse_command_line(argc, argv, mDescription), mVariableMap);
    }
    catch(...)
    {
    }
  }

  int run()
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

    std::unique_ptr<PassGenerator> passGenerator;

    if(mVariableMap.count(mParams.numbersOnly))
    {
      passGenerator = std::make_unique<NumberGenerator>(words, characters);
    }

    else
    {
      passGenerator = std::make_unique<RandomCharactersGenerator>(words, characters);
    }

    passGenerator->generate();

    po::notify(mVariableMap);

    return 0;
  }

};

int main(int argc, char** argv)
{

  OptionParser parser{argc, argv};
  return parser.run();

} // main
