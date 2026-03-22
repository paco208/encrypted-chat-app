#include <array>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: client <host> <message>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;


    tcp::resolver resolver(io_context);

    tcp::resolver::results_type endpoints =
    resolver.resolve(argv[1], "13");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    boost::asio::write(socket, boost::asio::buffer(std::string(argv[2]) + "\n"));  
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}