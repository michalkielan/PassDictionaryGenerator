/**
 * @file HttpClient.cpp
 *
 * @brief
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#include "HttpClient.hpp"


HttpClient::HttpClient(const std::string server) :
  mServer{std::move(server)},
  mIoContext{},
  mResolver{mIoContext},
  mQuery{mServer, "http"},
  mEndpointIterator{mResolver.resolve(mQuery)},
  mSocket{mIoContext}
{
}

void HttpClient::tryEndpoints()
{
  ba::ip::tcp::resolver::iterator end;
  boost::system::error_code error = boost::asio::error::host_not_found;

  while(error && mEndpointIterator != end)
  {
    mSocket.close();
    mSocket.connect(*mEndpointIterator, error);
  }
}

std::stringstream HttpClient::createResponse(ba::streambuf& response)
{
  std::stringstream msg;

  if(response.size() > 0)
  {
    msg << &response;
  }

  boost::system::error_code error = boost::asio::error::host_not_found;
  while(ba::read(mSocket, response, ba::transfer_at_least(1), error))
  {
    msg << &response;
  }

  if(mSocket.is_open())
  {
    mSocket.close();
  }

  return msg;
}

void HttpClient::readResponseHeaders(std::istream& msg, ba::streambuf& response)
{
  ba::read_until(mSocket, response, "\r\n\r\n");

  std::string header;
  while(std::getline(msg, header) && header != "\r");
}

std::stringstream HttpClient::readResponse()
{
  ba::streambuf response;
  ba::read_until(mSocket, response, "\r\n");

  std::istream msg{&response};
  std::string httpVersion{};

  msg >> httpVersion;
  unsigned int statusCode;
  msg >> statusCode;
  std::string statusMessage;
  std::getline(msg, statusMessage);

  readResponseHeaders(msg, response);

  return createResponse(response);
}

void HttpClient::sendRequest(const std::string& serverPath)
{
  tryEndpoints();

  boost::asio::streambuf request{};
  std::ostream msg{&request};

  msg << "GET " << serverPath << " HTTP/1.0\r\n";
  msg << "Host: " << mServer << "\r\n";
  msg << "Accept: */*\r\n";
  msg << "Connection: close\r\n\r\n";

  ba::write(mSocket, request);
}

std::stringstream HttpClient::download(const std::string serverPath)
{
  sendRequest(serverPath);
  return readResponse();
}

HttpClient::~HttpClient()
{
  if(mSocket.is_open())
  {
    mSocket.close();
  }
}

