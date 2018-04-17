/**
 * @file PasspGenerator.hpp
 *
 * @brief
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#ifndef INC_PASSPHRASEGENERATOR_HPP_
#define INC_PASSPHRASEGENERATOR_HPP_

#include <string>

class PassphraseGenerator
{
public:

  PassphraseGenerator()
  {
  }

  virtual void generate() = 0;

  virtual ~PassphraseGenerator() = default;
};


#endif /* INC_PASSPHRASEGENERATOR_HPP_ */
