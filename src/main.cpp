#include <iostream>
#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const int CONNECTION_PORT = 1080;


struct AcceptorContext {
    boost::asio::io_context& io_context;
    tcp::acceptor& connection_acceptor;

    AcceptorContext(boost::asio::io_context& io_context, tcp::acceptor& connection_acceptor)
        : io_context(io_context)
        , connection_acceptor(connection_acceptor)
    {}
};


void handle_tcp_connection(tcp::socket& socket);
void accept_connection(std::shared_ptr<AcceptorContext> context);
std::string make_daytime_string();


int main(int nargs, char const *const *args)
{
    boost::asio::io_context io_context;
    tcp::acceptor connection_acceptor = tcp::acceptor(
        io_context,
        tcp::endpoint(tcp::v4(), CONNECTION_PORT)
    );
    std::shared_ptr<AcceptorContext> context = std::make_shared<AcceptorContext>(io_context, connection_acceptor);
    accept_connection(context);
    context->io_context.run();
}


void accept_connection(std::shared_ptr<AcceptorContext> context) {
    std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(context->io_context);
    context->connection_acceptor.async_accept(*socket, [context, socket](const boost::system::error_code& error_code){
        if (!error_code) {
            handle_tcp_connection(*socket);
        }
        accept_connection(context);
    });
}


void handle_tcp_connection(tcp::socket& socket) {
    std::string message = make_daytime_string();
    boost::asio::async_write(
        socket,
        boost::asio::buffer(message),
        [](const boost::system::error_code& error_code, std::size_t bytes_transferred) {
            std::cout << "Error: " << error_code << " transfered: " << bytes_transferred << "\n";
        }
    );
}

std::string make_daytime_string() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}
