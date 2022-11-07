/*
 * how to use a class member function as a completion handler.
 * using class can be used parameter of member variables at bind.
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

class printer
{
  private:
    // values
    boost::asio::steady_timer timer_;
    int count_;

  public:
    // functions
    printer(boost::asio::io_context &io)
      : timer_(io, boost::asio::chrono::seconds(1)),
        count_(0){
          // works just as well with class member functions as with free function.
          timer_.async_wait(boost::bind(&printer::print, this));
        }

    ~printer()
    {
      std::cout << "Final count is " << count_ << std::endl;
    }

    void print()
    {
      if (count_ >= 5)
        return;

      std::cout << "count_ is " << count_ << std::endl;
      ++count_;

      // move the expiry time for the timer along
      // by one second from the previous expiry time.
      timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
      timer_.async_wait(boost::bind(&printer::print, this));
    }
};

int main()
{
  boost::asio::io_context io;
  printer p(io);
  io.run();

  return 0;
}
