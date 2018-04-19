/**
 * @file NumberGenerator.hpp
 *
 * @brief Generate number passphrase
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#ifndef INC_NUMBERGENERATOR_HPP_
#define INC_NUMBERGENERATOR_HPP_

#include "PassphraseGenerator.hpp"

#include <fstream>


/**
 * @brief Number passphrase generator
 */
class NumberGenerator: public PassphraseGenerator
{
  std::ifstream mWords;
  std::ofstream mPass;

  /**
   * @brief get number of lines
   *
   * @return number of lines
   */
  size_t getLines();

public:

  /**
   * @brief Constructor
   *
   * @param [in] path for file with words
   * @param [in] path for file with passphrases and words
   * @param [in] number of passphrase characters
   */
  NumberGenerator(const std::string wordsPath, const std::string passPath);

  /**
   * @brief Override
   */
  void generate() override;

  /**
   * @brief Destructor
   */
  virtual ~NumberGenerator();
};

#endif /* INC_NUMBERGENERATOR_HPP_ */
