#include <iostream>
#include "bots.h"
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <unistd.h>

using boost::asio::ip::tcp;

int next_dir(int d_x,int d_y)
{
int dir = rand()%9;
	switch (d_x)
	{
		case -1: 
			if(d_y < 0)
				dir = 6;
			else if(d_y > 0)
					dir = 8;
			else
				dir = 7;
			break;
		case 0:
			if(d_y < 0)
				dir = 5;		
			else
				dir = 1;
			break;
		case 1:
			if(d_y < 0)
				dir = 4;
			else if(d_y > 0)
				dir = 2;
			else
				dir = 3;
			break;
		default:
			break;
	}
	return dir;
}

void pinta_escenario( bots & mis_bots, bot::field_size cols, bot::field_size filas)
{

	for ( int col = 0; col < cols + 2; col++ )
        std::cout << 'X'; 
	std::cout << std::endl;
	for ( int fila = 0; fila < filas; fila++ )
	{
		std::cout << 'X';
		for ( int col = 0; col < cols; col++ )
		{
			bot * pos_bot = mis_bots.find_at( { col, fila} );
			if ( pos_bot == nullptr )	std::cout << ' '; 
			else std::cout << pos_bot->get_team();
		}
		std::cout << 'X'; 
		std::cout << std::endl;
	}
	for ( int col = 0; col < cols + 2; col++ ) std::cout << 'X'; 
	std::cout << std::endl;
}

class client_bot
{
	private:
	tcp::resolver _resolver;
	tcp::socket _socket;
	boost::asio::streambuf _packetToSend;
	boost::asio::streambuf _receiver;
	bots & _bots;
	boost::mutex & _state_mutex;
	bot::team_id & _id;
	bot::field_size _field_width;
	bot::field_size _field_height;
	int counter = 1;

public:
 client_bot(boost::asio::io_service& io_service, const std::string& server,
   const std::string& port, bots & bts, boost::mutex & sm, bot::team_id & id)
 : _resolver(io_service),
   _socket(io_service),
   _bots(bts),
   _state_mutex(sm),
   _id(id)
 {
		// Start an asynchronous resolve to translate the server and service names
		// into a list of endpoints.
		std::cout << "Resolving..." << std::endl;
		tcp::resolver::query query(server, port);
		_resolver.async_resolve(query,
		boost::bind(&client_bot::handle_resolve, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::iterator));
 }

private:
 void handle_resolve(const boost::system::error_code& err,
   tcp::resolver::iterator endpoint_iterator)
	{
		if (!err)
		{
			// Attempt a connection to the first endpoint in the list. Each endpoint
			// will be tried until we successfully establish a connection.
			std::cout << "Connecting to " << endpoint_iterator->host_name() << std::endl;
			tcp::endpoint endpoint = *endpoint_iterator;
			_socket.async_connect(endpoint,
			boost::bind(&client_bot::handle_connect, this,
			boost::asio::placeholders::error, ++endpoint_iterator));
		}
		else
		{
			std::cout << "Error resolving: " << err.message() << "\n";
		}
	}

	void handle_connect(const boost::system::error_code& err,
   tcp::resolver::iterator endpoint_iterator)
	{
		if (!err)
		{
			// The connection was successful. Send the request.
			std::cout << "Retrieving..." << std::endl;
			// Read the response status line.
			boost::asio::async_read_until(_socket, _receiver, "\n",
			boost::bind(&client_bot::handle_read_command, this,
			boost::asio::placeholders::error));
		}
		else if (endpoint_iterator != tcp::resolver::iterator())
		{
			// The connection failed. Try the next endpoint in the list.
			_socket.close();
			tcp::endpoint endpoint = *endpoint_iterator;
			_socket.async_connect(endpoint,
			boost::bind(&client_bot::handle_connect, this,
			boost::asio::placeholders::error, ++endpoint_iterator));
		}
		else
		{
			std::cout << "Error: " << err.message() << "\n";
		}
	}

 void handle_read_command(const boost::system::error_code& err)
 {
		if (!err)
		{
			// Check that response is OK.
			std::string data;
			std::istream _receiverstream(&_receiver);
			std::getline(_receiverstream, data);
			
			std::istringstream stream(data);
			std::string command;
			stream >> command;
			
			// Read the response headers, which are terminated by a blank line.
			if(command == "welcome") {
			stream >> _id;
			stream >> _field_width;
			stream >> _field_height;
			std::cout << data << std::endl;
			//ai.set_team(id);
			while(!stream.eof()) {
			 std::string a;
			 stream >> a;
			 //state << a << " ";
			}
	}
	else if(command == "state")
	{
		std::stringstream state;
		while(!stream.eof()) {
		 std::string a;
		 stream >> a;
		 state << a << " ";
		}
		boost::archive::text_iarchive ia(state);
		{
		 boost::mutex::scoped_lock lock(_state_mutex);
		 ia >> _bots;
		}
		std::cout << "\x1B[2J\x1B[H";
		pinta_escenario(_bots, _field_width, _field_height);
	}
		std::cout << "Counter: " << counter << "\n";	
		//sleep(1);
		std::cout << "Team" << "\t" << "X" << "\t" << "Y" << "\t" <<
		 "Energy" << "\t" << "Attack" << "\t" << "Defense" << "\t" << "Experience" << std::endl;         	
		_bots.for_each_bot([&] ( bot & b ) {
			std::cout << b.get_team() << "\t"; // std::endl;
			std::cout << b.get_x() << "\t";
			std::cout << b.get_y() << "\t";
			std::cout << b.get_energy() << "\t";
			std::cout << b.get_attack() << "\t";
			std::cout << b.get_defense() << "\t";
			std::cout << b.get_experience() << "\t";
			std::cout << std::endl;
		});
		int dir = rand()%9;
			if(true) //counter++ %20 == 0)
			{
				int dir;
				//counter = 1;				
				for(auto b : _bots.team_bots(_id))
				{
					dir = 0;
				  	//const bot & bc = &b;
					_bots.for_each_bot([&] (const bot & b_all ) {
						if(b_all.get_team() != b->get_team())
						{
							int delta_x = b_all.get_x() - b->get_x();
							if( abs(delta_x) < 2)
							{	
								int delta_y = b_all.get_y() - b->get_y();	
								if( abs(delta_y) < 2)
								{	
									std::cout << "Este es adjacente\n";
									std::cout << b->get_team() << "\t" <<b->get_x() << "\t"<< b->get_y() << "\n";
									std::cout << b_all.get_team() << "\t" <<b_all.get_x() << "\t"<< b_all.get_y() << "\n";
									dir = next_dir(delta_x,delta_y);
								}	
							}								
						}
					   
					  });

					if(!dir)
					{
						dir = rand()%9;
					}
					std::ostream _packetToSendstream(&_packetToSend);
				  	_packetToSendstream << "move " << b->get_x() << " " << b->get_y()<< " " << std::to_string(dir) << std::endl;
					boost::asio::async_write(_socket, _packetToSend,
					boost::bind(&client_bot::handle_write_request, this,
					boost::asio::placeholders::error));	
				}
			}
		boost::asio::async_read_until(_socket, _receiver, "\n",
		boost::bind(&client_bot::handle_read_command, this,
		boost::asio::placeholders::error));
	}
	else
  {
   std::cout << "Error reading command: " << err << "\n";
  }
 }

	void handle_write_request(const boost::system::error_code& err)
	{
		if (!err){}
		else {
		std::cout << "Error writing: " << err.message() << "\n";
	}
	}
};

int main (int argc, char* argv[])
{
	// Mi instancia de la clase bots        
	bots mi_bots;
	bot::team_id id = 1001;
	
	boost::asio::io_service io_service; // Inicia comunicaciones
	boost::mutex state_mutex;
	client_bot mi_cliente_bot(io_service, argv[1], argv[2], mi_bots, state_mutex, id);
	io_service.run();
	return(0);
}
