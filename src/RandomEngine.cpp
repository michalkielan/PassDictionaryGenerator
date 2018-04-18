/*
 * RandomEngine.cpp
 *
 *  Created on: Apr 6, 2018
 *      Author: Michal Kielan
 */

#include "RandomEngine.hpp"


unsigned char getCharacterIndex(unsigned char value)
{
  const unsigned char min = 0;
  assert(randomCharacters.size() < 0xFF);
  const unsigned char max = randomCharacters.size()-1;
  return value % (max + 1 - min) + min;
}
