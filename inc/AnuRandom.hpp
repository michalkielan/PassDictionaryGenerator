/*
 * AnuRandom.hpp
 *
 *  Created on: Apr 6, 2018
 *      Author: Michal Kielan
 */

#ifndef ANURANDOM_HPP_
#define ANURANDOM_HPP_

#include "RandomEngine.hpp"
#include "HttpClient.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <cassert>


template<typename T>
class AnuRandom : public RandomEngine<T>
{
  std::size_t mLen;
	std::size_t mBytes;
	std::string mUrl;

public:
	AnuRandom(const std::size_t len) :
	  mLen{len},
	  mBytes{len},
	  mUrl{}
	{
	  mBytes *= sizeof(T);
	  const std::string format= "uint8";
	  mUrl = "/API/jsonI.php?length=" + std::to_string(mBytes) + "&type=" + format;
	}

	std::vector<char> deserialize(boost::property_tree::ptree& ptree)
	{
	  const std::string type = ptree.get<std::string>("type");
	  const std::string status = ptree.get<std::string>("success");

	  if(status == "false")
	  {
	    throw;
	  }

	  std::vector<char> v;
	  v.reserve(mBytes);

	  const auto data = ptree.get_child("data");

    for (const auto& actual : data)
    {
      const int i = getCharacter(actual.second.get_value<unsigned char>());
      v.push_back(randomCharacters[i]);
    }
    return v;
  }


	std::vector<T> getRandom() override
	{
	  HttpClient anuServer {"qrng.anu.edu.au"};
	  auto ss = anuServer.download(mUrl);

	  boost::property_tree::ptree ptree;
	  boost::property_tree::read_json(ss, ptree);

	  const auto bytes = deserialize(ptree);

	  std::vector<T> v;
	  v.resize(mLen);

	  char* v_p = reinterpret_cast<char*>(v.data());

	  for(std::size_t i=0; i<bytes.size(); i++)
	  {
	    *v_p++ = bytes[i];
	  }

	  return v;
	}


	virtual ~AnuRandom()
	{

	}
};

#endif /* ANURANDOM_HPP_ */
