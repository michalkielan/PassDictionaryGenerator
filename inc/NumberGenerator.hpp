/**
 * @file NumberGenerator.hpp
 *
 * @brief
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#ifndef INC_NUMBERGENERATOR_HPP_
#define INC_NUMBERGENERATOR_HPP_

#include "PassphraseGenerator.hpp"

#include <fstream>

class NumberGenerator: public PassphraseGenerator
{
  std::ifstream mWords;
  std::ofstream mPass;
  std::size_t mLen;

  size_t getLines();

public:
  NumberGenerator(const std::string wordsPath, const std::string passPath, std::size_t characters);

  void generate() override;

  virtual ~NumberGenerator();
};

#endif /* INC_NUMBERGENERATOR_HPP_ */
