/**
 * @file SafeQueue.hpp
 *
 * @brief Thread safe queue
 *
 * @date Apr 18, 2018
 * @author Michal Kielan
 */

#ifndef INC_SAFEQUEUE_HPP_
#define INC_SAFEQUEUE_HPP_

#include <mutex>
#include <condition_variable>
#include <queue>


/**
 * @brief Queue with mutex and condition variable
 *
 */
template<typename T>
class SafeQueue
{
  std::condition_variable mCv;
  std::mutex              mMutex;
  std::queue<T>           mData;

public:

  /**
   * @brief Constructor
   */
  constexpr explicit SafeQueue()
  {
  }

  /**
   * @brief Move constructor
   */
  SafeQueue(SafeQueue&& other) :
    mCv{std::move(other.mCv)},
    mMutex{std::move(other.mMutex)},
    mData{std::move(other.mData)}
  {
  }

  /**
   * @brief Copy constructor deleted
   */
  SafeQueue(const SafeQueue& other) = delete;

  /**
   * @brief Push element into the queue
   *
   * @param [in] item to push
   *
   */
  void push(const T item)
  {
    std::unique_lock<std::mutex> lk{mMutex};
    mData.push(std::move(item));

    lk.unlock();
    mCv.notify_all();
  }


  /**
   * @brief Take the top element from the queue
   *
   * @return top element of the queue
   */
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


  /**
   * @brief Destructor
   */
  ~SafeQueue() = default;
};

#endif /* INC_SAFEQUEUE_HPP_ */
