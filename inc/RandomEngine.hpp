/**
 * @file RandomEngine.hpp
 *
 * @brief Random engine interface
 *
 * @date Apr 6, 2018
 * @author Michal Kielan
 */

#ifndef RANDOMENGINE_HPP_
#define RANDOMENGINE_HPP_

#include <array>
#include <vector>


/**
 * @brief Array of random characters
 */
constexpr const std::array<unsigned char, 77> randomCharacters
{
  '0','1','2','3','4','5','6','7','8','9',
  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
  '!','@','#','$','%','^','&','*','(',')','-','+','_','=','?'
};


/**
 * @brief Get index from random value
 *
 * @param [in] random index
 *
 * @return Index of 'randomCharacters' array
 */
unsigned char getCharacterIndex(unsigned char value);


/**
 * @brief Random Engine inteface
 */
template<typename T>
class RandomEngine
{

public:

  /**
   * @brief Constructor
   */
	RandomEngine()
  {
  }

	/**
	 * @brief Get vector of random data
	 */
	virtual std::vector<T> getRandom() = 0;

	/**
	 * @brief Destructor
	 */
	virtual ~RandomEngine() = default;
};

#endif /* RANDOMENGINE_HPP_ */
