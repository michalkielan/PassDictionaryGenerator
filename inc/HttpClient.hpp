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

namespace ba = boost::asio;

/**
 * @brief Http client to download data
 */
class HttpClient
{
  std::string                     mServer;
  ba::io_context                  mIoContext;
  ba::ip::tcp::resolver           mResolver;
  ba::ip::tcp::resolver::query    mQuery;
  ba::ip::tcp::resolver::iterator mEndpointIterator;
  ba::ip::tcp::socket             mSocket;


  /**
   * @brief Try each endpoint until we successfully establish a connection
   */
  void tryEndpoints();


  /**
   * @brief Send request
   */
  void sendRequest(const std::string& serverPath);


  /**
   * @brief Read response
   *
   * @return Stringstream with response
   */
  std::stringstream readResponse();


  /**
   * @brief Read response
   *
   * @param [in,out] response stream
   * @param [in] response buffer
   */
  void readResponseHeaders(std::istream& responseStream, ba::streambuf& response);


  /**
   * @brief Save response in stream
   *
   * @return response message
   */
  std::stringstream createResponse(ba::streambuf& response);

public:

  /**
   * @brief Constructor
   *
   * @param [in] server name/ip
   */
  HttpClient(const std::string server);


  /**
   * @brief Download data
   *
   * @param [in] server path
   * @return downloaded data
   */
  std::stringstream download(const std::string serverPath);


  /**
   * @brief Destructor
   */
  ~HttpClient();

};

#endif /* SRC_HTTPCLIENT_HPP_ */
