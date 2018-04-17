/*
 * RandomEngine.hpp
 *
 *  Created on: Apr 6, 2018
 *      Author: Michal Kielan
 */

#ifndef RANDOMENGINE_HPP_
#define RANDOMENGINE_HPP_

#include <vector>

template<typename T>
class RandomEngine
{
public:
	RandomEngine()
  {

  }

	virtual std::vector<T> getRandom() = 0;

	virtual ~RandomEngine() = default;
};

#endif /* RANDOMENGINE_HPP_ */
