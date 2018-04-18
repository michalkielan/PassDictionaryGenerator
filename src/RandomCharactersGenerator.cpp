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

#include <iostream>

#include <future>
#include <queue>
#include <mutex>
#include <atomic>
#include <stack>
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

template<typename T>
class ThreadQueue
{
  std::condition_variable mCv;
  std::mutex              mMutex;
  std::queue<T>           mData;

public:

  ThreadQueue()
  {

  }

  ThreadQueue(const ThreadQueue& other) = delete;
  ThreadQueue(ThreadQueue&& other) :
    mCv{std::move(other.mCv)},
    mMutex{std::move(other.mMutex)},
    mData{std::move(other.mData)}
  {

  }

  void push(const T item)
  {
    std::unique_lock<std::mutex> lk{mMutex};
    mData.push(item);

    lk.unlock();
    mCv.notify_all();
  }

  T pop()
  {
    std::unique_lock<std::mutex> lk{mMutex};
    while(mData.empty())
    {
      mCv.wait(lk);
    }

    const T tmp = mData.front();
    mData.pop();
    return tmp;
  }

  ~ThreadQueue() = default;
};


class DownloadPool
{
  std::vector<std::thread> mDownloaders;
  std::size_t              mThreads;
  std::atomic_bool         mIsDone;
public:

  DownloadPool(const std::size_t threads) :
    mThreads{threads},
    mIsDone{false}
  {
    mDownloaders.reserve(mThreads);
  }

  template<typename Function, class... Args>
  void start(Function&& function, Args&&... args)
  {
    for(std::size_t i=0; i< mThreads; i++)
    {
      mDownloaders.emplace_back([&]()
      {
        while(!mIsDone.load())
        {
          function(args...);
        }
      });
    }
  }

  void stop()
  {
    mIsDone.store(true);
  }

  ~DownloadPool()
  {
    for(auto& downloader : mDownloaders)
    {
      downloader.detach();
    }
  }
};

void RandomCharactersGenerator::generate()
{
  if(mWords)
  {
    std::cout << "Generating passphrase..." << std::endl;

    constexpr const std::size_t downloadThreads{100};
    ThreadQueue<std::string> passphrases{};
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




