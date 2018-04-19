/**
 * @file RandomCharactersGenerator.hpp
 *
 * @brief Random characters generator
 *
 * @date Apr 7, 2018
 * @author Michal Kielan
 */

#ifndef INC_RANDOMCHARACTERSGENERATOR_HPP_
#define INC_RANDOMCHARACTERSGENERATOR_HPP_

#include "PassphraseGenerator.hpp"

template<typename T>
class RandomEngine;

#include <memory>
#include <fstream>


/**
 * @brief Random character generators, from anu random random engine
 */
class RandomCharactersGenerator : public PassphraseGenerator
{
  std::ifstream mWords;
  std::ofstream mPass;
  std::shared_ptr<RandomEngine<char>> mRandomEngine;

  /**
   * @brief Return random string
   *
   * @return random string
   */
  std::string getRandomString() const;

public:

  /**
   * @brief Constructor
   *
   * @param [in] path for file with words
   * @param [in] path for file with passphrases and words
   * @param [in] number of passphrase characters
   */
  RandomCharactersGenerator(const std::string wordsPath, const std::string passPath, std::size_t characters);

  /**
   * @brief Override
   */
  void generate() override;

  /**
   * @brief Destructor
   */
  virtual ~RandomCharactersGenerator();
};

#endif /* INC_RANDOMCHARACTERSGENERATOR_HPP_ */
