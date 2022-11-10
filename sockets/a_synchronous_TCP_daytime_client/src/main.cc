#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char **argv)
{
  try {
    if (argc != 2) {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;
    // a resolver takes a host name and service name and turns them
    // into a list of endpoints.
    tcp::resolver resolver(io_context);

    tcp::resolver::results_type endpoints
      = resolver.resolve(argv[1], "daytime");

    // create and connect the socket.
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    for (;;) {
      // to hold the received data
      boost::array<char, 128> buf;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      if (error == boost::asio::error::eof)
        // connection closed cleanly by peer.
        break;
      else if (error)
        // some other error.
        throw boost::system::system_error(error);

      std::cout.write(buf.data(), len);
    }
  }
  catch(std::exception &e) {
    std::cerr << "catch: " << e.what() << std::endl;
  }
}
