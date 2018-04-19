/**
 * @file HttpClient.hpp
 *
 * @brief Http client
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#ifndef SRC_HTTPCLIENT_HPP_
#define SRC_HTTPCLIENT_HPP_

#include <boost/asio.hpp>

#include <string>

namespace ba = boost::asio;

/**
 * @brief Http client to download data
 */
class HttpClient
{
  std::string    mServer;
  ba::io_service mIoService;

public:

  /**
   * @brief Constructor
   *
   * @param [in] server name/ip
   */
  HttpClient(std::string server);

  /**
   * @brief Download data
   *
   * @param [in] server path
   * @return downloaded data
   */
  std::stringstream download(const std::string getCommand);

};

#endif /* SRC_HTTPCLIENT_HPP_ */
