
#include <asio.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/strand.hpp>
#include <iostream>

using namespace std;
using namespace asio;

void performHttpRequest(io_context &ioContext, const string &host,
                        const string &path, io_context::strand &strand) {
  ip::tcp::resolver resolver(ioContext);
  ip::tcp::socket socket(ioContext);

  auto endpoints = resolver.resolve(host, "http");

  async_connect(
      socket, endpoints,
      [&socket, &path, &strand](const error_code &ec,
                                const ip::tcp::endpoint &endpoint) {
        if (!ec) {
          string request = "GET " + path + " HTTP/1.1\r\nHost: " +
                           endpoint.address().to_string() + "\r\n\r\n";
          asio::async_write(
              socket, asio::buffer(request),
              [&socket, &strand](const error_code &ec,
                                 size_t /*bytes_written*/) {
                if (!ec) {
                  asio::streambuf response;
                  asio::async_read_until(
                      socket, response, "\r\n",
                      [&socket, &response, &strand](const error_code &ec,
                                                    size_t /*bytes_read*/) {
                        if (!ec) {
                          string httpVersion;
                          istream responseStream(&response);
                          responseStream >> httpVersion;
                          unsigned int statusCode;
                          responseStream >> statusCode;

                          // Read and print the HTTP response headers
                          asio::async_read_until(
                              socket, response, "\r\n\r\n",
                              [&socket, &response, &strand](
                                  const error_code &ec, size_t /*bytes_read*/) {
                                if (!ec) {
                                  istream responseStream(&response);
                                  string header;
                                  while (getline(responseStream, header) &&
                                         header != "\r") {
                                    cout << header << "\n";
                                  }
                                  cout << "\n";

                                  // Read and print the HTTP response body
                                  asio::async_read(
                                      socket, response,
                                      [&socket, &strand,
                                       &response](const error_code &ec,
                                                  size_t bytes_read) {
                                        if (!ec) {
                                          string data(asio::buffers_begin(
                                                          response.data()),
                                                      asio::buffers_begin(
                                                          response.data()) +
                                                          bytes_read);
                                          cout << data;

                                          // Close the socket
                                          socket.close();

                                          // The strand is used to ensure
                                          // synchronized execution of handlers

                                          strand.post([&]() {
                                            cout << "HTTP Request completed.\n";
                                          });
                                        }
                                      });
                                }
                              });
                        }
                      });
                }
              });
        }
      });
}

int main() {
  io_context ioContext;
  io_context::strand strand(ioContext);

  string host = "example.com";
  string path = "/";

  performHttpRequest(ioContext, host, path, strand);

  ioContext.run();

  return 0;
}
