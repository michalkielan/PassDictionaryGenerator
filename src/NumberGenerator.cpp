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
#include <sstream>
#include <iomanip>
#include <cassert>

NumberGenerator::NumberGenerator(const std::string wordsPath, const std::string passPath) :
  mWords{wordsPath, std::ios::in},
  mPass{passPath, std::ios::out}
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

template<typename T>
static inline unsigned int getDigits(T number)
{
  unsigned int digits{};
  assert(number >= 0);
  while(number)
  {
    number /= 10;
    digits++;
  }
  return digits;
}

template<typename T>
static std::string toString(const T number, const int digits)
{
  std::stringstream ss;
  ss << std::setw(digits) << std::setfill('0') << number;
  return ss.str();
}


void NumberGenerator::generate()
{
  if(mWords)
  {
    std::string word;
    const auto lines = getLines();

    constexpr const size_t startNum {11111};

    const auto maxNum = lines + startNum;
    const auto digits = getDigits(maxNum);

    size_t counter{startNum};

    mWords.clear();
    mWords.seekg(0, std::ios::beg);

    std::cout << "Generating passphrase..." << std::endl;
    while(std::getline(mWords, word))
    {
      mPass << toString(counter++, digits) << " " << word << std::endl;
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

