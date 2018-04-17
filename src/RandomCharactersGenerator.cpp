/**
 * @file RandomCharactersGenerator.cpp
 *
 * @brief
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#include "RandomCharactersGenerator.hpp"

#include "AnuRandom.hpp"

#include <iostream>

std::string RandomCharactersGenerator::getRandomString() const
{
  const auto v = mRandomEngine->getRandom();
  return std::string{v.begin(), v.end()};
}


RandomCharactersGenerator::RandomCharactersGenerator(const std::string wordsPath, const std::string passPath, std::size_t characters) :
  mWords{wordsPath, std::ios::in},
  mPass{passPath, std::ios::out},
  mLen{characters},
  mRandomEngine{std::make_shared<AnuRandom<char>>(characters)}
{
}

void RandomCharactersGenerator::generate()
{
  if(mWords)
  {
    std::string word;
    std::cout << "Generating passphrase..." << std::endl;

    while(std::getline(mWords, word))
    {
      mPass << getRandomString() << " " << word << std::endl;
    }
    std::cout << "Generating passphrase done" << std::endl;
  }
  else
  {
    std::cerr << "Error open file" << std::endl;
    throw;
  }
}

RandomCharactersGenerator::~RandomCharactersGenerator()
{

}




