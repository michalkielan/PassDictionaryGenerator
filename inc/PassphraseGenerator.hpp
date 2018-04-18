/**
 * @file PasspGenerator.hpp
 *
 * @brief Interface for passphrase generators
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#ifndef INC_PASSPHRASEGENERATOR_HPP_
#define INC_PASSPHRASEGENERATOR_HPP_

#include <string>


/**
 * @brief Interface for passphrase generators
 */
class PassphraseGenerator
{
public:

  /**
   * @brief Constructor
   */
  PassphraseGenerator()
  {
  }

  /**
   * @brief Generate and save all passphrases into file
   */
  virtual void generate() = 0;

  /**
   * @brief Destructor
   */
  virtual ~PassphraseGenerator() = default;
};


#endif /* INC_PASSPHRASEGENERATOR_HPP_ */
