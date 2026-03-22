#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
  try
  {
    boost::asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    for (;;)
    {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      boost::asio::streambuf buf;
      boost::system::error_code ec;

      boost::asio::read_until(socket, buf, '\n', ec);

      if (!ec)
      {
        std::istream is(&buf);
        std::string receivedMessage;
        std::getline(is, receivedMessage);
        std::cout << "Dobil sem: " << receivedMessage << "\n";
      }
      else
      {
        std::cerr << "Napaka pri branju: " << ec.message() << "\n";
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}