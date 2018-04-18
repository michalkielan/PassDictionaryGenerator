/**
 * @file HttpClient.hpp
 *
 * @brief
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#ifndef SRC_HTTPCLIENT_HPP_
#define SRC_HTTPCLIENT_HPP_

#include <boost/asio.hpp>

#include <string>

namespace ba = boost::asio;

class HttpClient
{
  std::string mServer;
  ba::io_service mIoService;

public:

  HttpClient(std::string server);

  std::stringstream download(const std::string getCommand);

};

#endif /* SRC_HTTPCLIENT_HPP_ */
