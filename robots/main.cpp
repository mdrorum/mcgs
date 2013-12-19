#include <iostream>
#include "bots.h"
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

using boost::asio::ip::tcp;

void async_send(tcp::socket &socket, const std::string & str) 
{
    boost::asio::async_write(socket, boost::asio::buffer(str + "\n"), boost::asio::transfer_all());
}

void pinta_escenario( bots mis_bots, int paso, int cols, int filas)
{
	std::cout << "Paso : " << paso << std::endl;

	for ( int col = 0; col < cols + 2; col++ ) // Primera fila de X
        	std::cout << 'X'; 
	std::cout << std::endl;
	for ( int fila = 0; fila < filas; fila++ ) //! Recorre toda la altura
        {
		std::cout << 'X'; // Primera X de la fila
		for ( int col = 0; col < cols; col++ ) // Espacios en blanco
		{
			bot * pos_bot = mis_bots.find_at( { col, fila} );
			if ( pos_bot == nullptr )
                        	std::cout << ' '; 
			else
				std::cout << pos_bot->get_team();
		}
		std::cout << 'X'; //! Espacios de 1a altura - fila
                std::cout << std::endl;
        }
	for ( int col = 0; col < cols + 2; col++ ) // Primera fila de X
                        std::cout << 'X'; 
	std::cout << std::endl;
}



int main (int argc, char* argv[])
{
	boost::asio::io_service io_service; // Inicia comunicaciones
	tcp::resolver resolver(io_service); // Resuelve la comunicación
	auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] }); // Iterador hacia puerto y dirección
	std::shared_ptr<tcp::socket> socket(new tcp::socket(io_service)); // Puntero compartido hacia el socket
	boost::asio::connect(*socket, endpoint_iterator); // Conexión
	
	io_service.run();
	
	
	int paso = 0;

	// Variables de comunicacion
	boost::mutex state_mutex;
	bool gameover = false;
	bool connected = false;
	bot::team_id id = 6666;
	bot::field_size field_width;
	bot::field_size field_height;
	int win_width = 500;
	int win_height = 500;
	// Mi instancia de la clase bots        
	bots mi_bots = bots(field_width, field_height); // Tamaño del campo 10x10, usa la pila
	//Lee el bufer de comunicaciones
	boost::asio::streambuf buf;
	read_until(*socket, buf, "\n");
	std::string data;
	std::istream is(&buf);
	std::getline(is, data);
	std::istringstream mi_stream(data);
	// Lee la primer palabra
	std::string command;
	mi_stream >> command;
	// Lee la información inicial	
	if(command == "welcome") 
	{
        mi_stream >> id;
        std::cout << "team id: " << id << std::endl;
        //ai.set_team(id);
        mi_stream >> field_width;
        mi_stream >> field_height;
        mi_bots.set_size(field_width, field_height);
        std::cout << "setting field: " << field_width << " x " << field_height << std::endl;
    }
    

	while (!gameover) 
	{
		{
			read_until(*socket, buf, "\n"); //Leo el bufer
			std::istream is2(&buf); // Input Stream (lectura) a la clase buf
			std::getline(is2, data); // Convierte a String y guarda en data
			std::istringstream mi_stream2(data); // Input Stream (letura) al string data
			mi_stream2 >> command;

			//Lee el estado del escenario
			if(command == "state") 
			{
				std::stringstream state;

				while(!mi_stream2.eof()) {
					std::string a;
					mi_stream2 >> a;
					state << a << " ";
				}
				std::cout << state.str() << std::endl;

				boost::archive::text_iarchive ia(state);
				{
					boost::mutex::scoped_lock lock(state_mutex);
					ia >> mi_bots;
					paso++;
					std::cout << "\x1B[2J\x1B[H"; // Limpia pantalla
					pinta_escenario(mi_bots, paso, field_width, field_height);
				}
			}
			else 
			{
				std::cout << "GAME OVER " << command << std::endl;
			}
			
		}

		mi_bots.for_each_bot([&] ( bot & b ) {
		std::stringstream stream;
		// Envia movimeinte del bot
        stream << "move " << b.get_x() << " " << b.get_y() << " " << bot::W;
        async_send(*socket, stream.str());
			
		});

		//while ( std::cin.get() != ' ' ); // Espera entrada espacio
	}
	return 0;
}
