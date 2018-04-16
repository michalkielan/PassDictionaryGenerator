/*
 * PassDictionary.hpp
 *
 *  Created on: Apr 7, 2018
 *      Author: Michal Kielan
 */

#ifndef PASSDICTIONARY_HPP_
#define PASSDICTIONARY_HPP_

#include "RandomEngine.hpp"

#include <memory>
#include <fstream>

class PassDictionary
{
  std::ifstream mWords;
  std::ofstream mPass;
  std::shared_ptr<RandomEngine<char>> mRandomEngine;
  std::size_t mLen;

public:
  PassDictionary(const std::string wordsPath,
      const std::string passPath,
      std::shared_ptr<RandomEngine<char>> randomEngine,
      std::size_t len) :
    mWords{wordsPath, std::ios::in},
    mPass{passPath, std::ios::out},
    mRandomEngine{randomEngine},
    mLen{len}
  {
  }

  std::string getRandomString() const
  {
    const auto v = mRandomEngine->getRandom();
    return std::string{v.begin(), v.end()};
  }

  void generate()
  {
    std::string word;

    while(std::getline(mWords, word))
    {
      mPass << getRandomString() << " " << word << std::endl;
    }
  }

  virtual ~PassDictionary()
  {

  }
};

#endif /* PASSDICTIONARY_HPP_ */
