/*
 * RandomCharactersGenerator.hpp
 *
 *  Created on: Apr 7, 2018
 *      Author: Michal Kielan
 */

#ifndef INC_RANDOMCHARACTERSGENERATOR_HPP_
#define INC_RANDOMCHARACTERSGENERATOR_HPP_

#include "PassphraseGenerator.hpp"

template<typename T>
class RandomEngine;

#include <memory>
#include <fstream>

class RandomCharactersGenerator : public PassphraseGenerator
{
  std::ifstream mWords;
  std::ofstream mPass;
  std::size_t mLen;
  std::shared_ptr<RandomEngine<char>> mRandomEngine;

  std::string getRandomString() const;


public:
  RandomCharactersGenerator(const std::string wordsPath, const std::string passPath, std::size_t characters);

  void generate() override;

  virtual ~RandomCharactersGenerator();
};

#endif /* INC_RANDOMCHARACTERSGENERATOR_HPP_ */
