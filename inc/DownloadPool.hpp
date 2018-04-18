/**
 * @file DownloadPool.hpp
 *
 * @brief
 *
 * @date Apr 18, 2018
 * @author Michal Kielan
 */

#ifndef INC_DOWNLOADPOOL_HPP_
#define INC_DOWNLOADPOOL_HPP_

#include <vector>
#include <atomic>
#include <thread>


/**
 * @brief Download thread pools
 */
class DownloadPool
{
  std::vector<std::thread> mDownloaders;
  std::size_t              mThreads;
  std::atomic_bool         mIsDone;
public:

  /**
   * @brief Constructor
   *
   * @param [in] number of threads to run
   */
  DownloadPool(const std::size_t threads);


  /**
   * @brief Start download threads
   *
   * @param [in] functor
   * @param [in] functor arguments
   */
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

  /**
   * @brief Stop threads
   */
  void stop();

  /**
   * @brief Destructor
   */
  ~DownloadPool();
};

#endif /* INC_DOWNLOADPOOL_HPP_ */
