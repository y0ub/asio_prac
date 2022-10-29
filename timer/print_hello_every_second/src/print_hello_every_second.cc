#include <iostream>
#include <boost/asio.hpp>

void print_hello_every_second()
{
  std::cout << "start print_hello_every_second." << '\n';

  // proveide access to I/O functionality.
  boost::asio::io_context io;

  for (int n = 1; ;) {
    // sets the timer to expire n second from now.
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(n));
    t.wait();
    std::cout << "Hello, World!!!!11!" << '\n';
  }
}

int main()
{
  print_hello_every_second();

  return 0;
}
