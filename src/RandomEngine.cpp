/**
 * @file RandomEngine.cpp
 *
 * @brief
 *
 * @date Apr 6, 2018
 * @author Michal Kielan
 */

#include "RandomEngine.hpp"

#include <cassert>


unsigned char getCharacterIndex(unsigned char value)
{
  const unsigned char min = 0;
  assert(randomCharacters.size() < 0xFF);
  const unsigned char max = randomCharacters.size()-1;
  return value % (max + 1 - min) + min;
}
