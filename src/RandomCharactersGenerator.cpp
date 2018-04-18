/**
 * @file RandomCharactersGenerator.cpp
 *
 * @brief
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#include "RandomCharactersGenerator.hpp"

#include "AnuRandom.hpp"
#include "SafeQueue.hpp"
#include "DownloadPool.hpp"

#include <iostream>
#include <chrono>

std::string RandomCharactersGenerator::getRandomString() const
{
  const auto v = mRandomEngine->getRandom();
  return std::string{v.begin(), v.end()};
}


RandomCharactersGenerator::RandomCharactersGenerator(const std::string wordsPath, const std::string passPath, std::size_t characters) :
  mWords{wordsPath, std::ios::in},
  mPass{passPath, std::ios::out},
  mLen{characters},
  mRandomEngine{std::make_shared<AnuRandom<char>>(characters)}
{
}


void RandomCharactersGenerator::generate()
{
  if(mWords)
  {
    std::cout << "Generating passphrase..." << std::endl;

    constexpr const std::size_t downloadThreads{100};
    SafeQueue<std::string> passphrases{};
    DownloadPool downloaderPool{downloadThreads};

    const auto pushRandom = [&]()
    {
      try
      {
        passphrases.push(getRandomString());
      }
      catch(...)
      {
        using namespace std::chrono_literals;
        std::cerr << ": Connecting error, try again" << std::endl;
        std::this_thread::sleep_for(1s);
      }
    };

    downloaderPool.start(pushRandom);

    for(std::string word; std::getline(mWords, word);)
    {
      const std::string rand = passphrases.pop();
      mPass << rand << "\t" << word << std::endl;
    }

    downloaderPool.stop();

    std::cout << "Generating passphrase done" << std::endl;
  }
  else
  {
    std::cerr << "Error open file" << std::endl;
    throw;
  }
}

RandomCharactersGenerator::~RandomCharactersGenerator()
{

}




