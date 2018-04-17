/**
 * @file NumberGenerator.cpp
 *
 * @brief
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#include "NumberGenerator.hpp"

#include <iostream>


NumberGenerator::NumberGenerator(const std::string wordsPath, const std::string passPath, std::size_t characters) :
  mWords{wordsPath, std::ios::in},
  mPass{passPath, std::ios::out},
  mLen{characters}
{

}

size_t NumberGenerator::getLines()
{
  std::string line;
  size_t lines{};
  while(std::getline(mWords, line))
  {
    ++lines;
  }
  return lines;
}

void NumberGenerator::generate()
{
  if(mWords)
  {
    std::string word;
//    const auto lines = getLines();
//    const auto digits {mLen};
//    const auto maxNumber = (lines < digits) ? lines : digits;
//
//    std::cout << "Generating passphrase..." << std::endl;
    size_t counter {};

    while(std::getline(mWords, word))
    {
      mPass << std::to_string(counter++) << " " << word << std::endl;
    }
    std::cout << "Generating passphrase done" << std::endl;
  }
  else
  {
    std::cerr << "Error open file" << std::endl;
    throw;
  }
}

NumberGenerator::~NumberGenerator()
{

}

