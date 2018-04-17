/*
 * AnuRandom.hpp
 *
 *  Created on: Apr 6, 2018
 *      Author: Michal Kielan
 */

#ifndef ANURANDOM_HPP_
#define ANURANDOM_HPP_

#include "RandomEngine.hpp"

#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <limits>

template<typename T>
class AnuRandom : public RandomEngine<T>
{
  std::size_t mLen;
	std::size_t mBytes;
	std::string mUrl;

public:
	AnuRandom(const std::size_t len) :
	  mLen{len},
	  mBytes{len},
	  mUrl{}
	{
	  mBytes *= sizeof(T);
	  const std::string format= "uint8";
	  mUrl = "/API/jsonI.php?length=" + std::to_string(mBytes) + "&type=" + format;
	}

	std::stringstream download(const std::string serverName, const std::string getCommand)
	{
	  using namespace boost::asio;

	  boost::asio::io_service io_service;

	// Get a list of endpoints corresponding to the server name.
	  ip::tcp::resolver resolver(io_service);
	  ip::tcp::resolver::query query(serverName, "http");
	  ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	  ip::tcp::resolver::iterator end;

	// Try each endpoint until we successfully establish a connection.
	  ip::tcp::socket socket(io_service);
	  boost::system::error_code error = boost::asio::error::host_not_found;

	  while(error && endpoint_iterator != end)
	  {
	    socket.close();
	    socket.connect(*endpoint_iterator, error);
	  }

	  boost::asio::streambuf request;
	  std::ostream request_stream(&request);

	  request_stream << "GET " << getCommand << " HTTP/1.0\r\n";
	  request_stream << "Host: " << serverName << "\r\n";
	  request_stream << "Accept: */*\r\n";
	  request_stream << "Connection: close\r\n\r\n";

	  // Send the request.
	  boost::asio::write(socket, request);

	  // Read the response status line.
	  boost::asio::streambuf response;
	  boost::asio::read_until(socket, response, "\r\n");

	  // Check that response is OK.
	  std::istream response_stream(&response);
	  std::string http_version;
	  response_stream >> http_version;
	  unsigned int status_code;
	  response_stream >> status_code;
	  std::string status_message;
	  std::getline(response_stream, status_message);

	  // Read the response headers, which are terminated by a blank line.
	  boost::asio::read_until(socket, response, "\r\n\r\n");

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
	  while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
	  {
	    ss << &response;
	  }

	  return ss;
	}

	std::vector<char> deserialize(boost::property_tree::ptree& ptree)
	{
	  const std::string type = ptree.get<std::string>("type");
	  const std::string status = ptree.get<std::string>("success");

	  if(status == "false")
	  {
	    throw;
	  }

	  std::vector<char> v;
	  v.reserve(mBytes);

	  const auto data = ptree.get_child("data");

	  for(const auto& actual : data)
	  {
	    const unsigned int characters {26};
	    const auto toAscii = [&]()
	    {
        long val;
        do
        {
          val = actual.second.get_value<unsigned int>();
        }

        while (val >= (std::numeric_limits<int>::max()/characters)*characters);
        return (unsigned)(val % characters);
	    };

	    v.push_back(toAscii());
	  }
	  return v;
	}


	std::vector<T> getRandom() override
	{
	  const std::string server{ "qrng.anu.edu.au" };

	  auto ss = download(server, mUrl);

	  boost::property_tree::ptree ptree;
	  boost::property_tree::read_json(ss, ptree);

	  const auto bytes = deserialize(ptree);

	  std::vector<T> v;
	  v.resize(mLen);

	  char* v_p = reinterpret_cast<char*>(v.data());

	  for(std::size_t i=0; i<bytes.size(); i++)
	  {
	    *v_p++ = bytes[i] + '0';
	  }

	  return v;
	}


	virtual ~AnuRandom()
	{

	}
};

#endif /* ANURANDOM_HPP_ */
