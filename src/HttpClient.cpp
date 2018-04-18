/**
 * @file HttpClient.cpp
 *
 * @brief
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#include "HttpClient.hpp"


HttpClient::HttpClient(std::string server) :
  mServer{std::move(server)},
  mIoService{}
{

}


std::stringstream HttpClient::download(const std::string getCommand)
{
// Get a list of endpoints corresponding to the server name.
  ba::ip::tcp::resolver resolver(mIoService);
  ba::ip::tcp::resolver::query query(mServer, "http");
  ba::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
  ba::ip::tcp::resolver::iterator end;

// Try each endpoint until we successfully establish a connection.
  ba::ip::tcp::socket socket(mIoService);
  boost::system::error_code error = boost::asio::error::host_not_found;

  while(error && endpoint_iterator != end)
  {
    socket.close();
    socket.connect(*endpoint_iterator, error);
  }

  boost::asio::streambuf request;
  std::ostream request_stream(&request);

  request_stream << "GET " << getCommand << " HTTP/1.0\r\n";
  request_stream << "Host: " << mServer << "\r\n";
  request_stream << "Accept: */*\r\n";
  request_stream << "Connection: close\r\n\r\n";

  // Send the request.
  ba::write(socket, request);

  // Read the response status line.
  ba::streambuf response;
  ba::read_until(socket, response, "\r\n");

  // Check that response is OK.
  std::istream response_stream(&response);
  std::string http_version;
  response_stream >> http_version;
  unsigned int status_code;
  response_stream >> status_code;
  std::string status_message;
  std::getline(response_stream, status_message);

  // Read the response headers, which are terminated by a blank line.
  ba::read_until(socket, response, "\r\n\r\n");

  // Process the response headers.
  std::string header;
  while (std::getline(response_stream, header) && header != "\r");

  std::stringstream ss;

  // Write whatever content we already have to output.
  if (response.size() > 0)
  {
    ss << &response;
  }

  // Read until EOF, writing data to output as we go.
  while (ba::read(socket, response, ba::transfer_at_least(1), error))
  {
    ss << &response;
  }

  if(socket.is_open())
  {
    socket.close();
  }

  return ss;
}

