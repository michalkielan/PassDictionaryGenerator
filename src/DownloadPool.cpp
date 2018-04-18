/**
 * @file DownloadPool.cpp
 *
 * @brief
 *
 * @date Apr 18, 2018
 * @author Michal Kielan
 */

#include "DownloadPool.hpp"


DownloadPool::DownloadPool(const std::size_t threads) :
  mThreads{threads},
  mIsDone{false}
{
  mDownloaders.reserve(mThreads);
}

void DownloadPool::stop()
{
  mIsDone.store(true);
}

DownloadPool::~DownloadPool()
{
  for(auto& downloader : mDownloaders)
  {
    downloader.detach();
  }
}
