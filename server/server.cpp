#include <iostream>
#include <array>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

boost::asio::io_context io_context;
tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

void do_accept()
{
  acceptor.async_accept(
      [](boost::system::error_code ec, tcp::socket socket)
      {
        if (!ec)
        {
          std::array<char, 128> buf;
          boost::system::error_code read_ec;
          size_t n = socket.read_some(boost::asio::buffer(buf), read_ec);
          if (!read_ec)
          {
            std::cout << "Dobil sem: "
                      << std::string(buf.data(), n) << std::endl;
          }
        }
        do_accept();
      });
}

int main()
{
  try
  {
    do_accept();
    io_context.run();
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}