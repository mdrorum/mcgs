#include <iostream>
#include "bots.h"
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

const int _LADO = 10;


using boost::asio::ip::tcp;

void send(tcp::socket &socket, const std::string & str) 
{
    boost::asio::write(socket, boost::asio::buffer(str + "\n"), boost::asio::transfer_all());
}

void pinta_escenario( bots mis_bots, int paso)
{
	std::cout << "Paso : " << paso << std::endl;

	for ( int col = 0; col < _LADO + 2; col++ ) // Primera fila de X
        	std::cout << 'X'; 
	std::cout << std::endl;
	for ( int fila = 0; fila < _LADO; fila++ ) //! Recorre toda la altura
        {
		std::cout << 'X'; // Primera X de la fila
		for ( int col = 0; col < _LADO; col++ ) // Espacios en blanco
		{
			bot * pos_bot = mis_bots.find_at( { col, fila} );
			//std::cout << pos_bot->get_team();
			
			if ( pos_bot == nullptr )
                        	std::cout << ' '; 
			else
				std::cout << pos_bot->get_team();
				
		}
		std::cout << 'X'; //! Espacios de 1a altura - fila
                std::cout << std::endl;
        }
	for ( int col = 0; col < _LADO + 2; col++ ) // Primera fila de X
                        std::cout << 'X'; 
	std::cout << std::endl;
}



int main (int argc, char* argv[])
{

	std::cout << "\x1B[2J\x1B[H"; // Despeja la pantalla del terminal
	std::cout << "A jugar!!"
	return(0);
	boost::asio::io_service io_service; // Inicia comunicaciones

	tcp::resolver resolver(io_service); // Resuelve la comunicación
	auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] }); // Iterador hacia puerto y dirección

	std::shared_ptr<tcp::socket> socket(new tcp::socket(io_service)); // Puntero compartido hacia el socket
	boost::asio::connect(*socket, endpoint_iterator); // Conexión

	int paso = 0;

	// Variables del hilo
	boost::mutex state_mutex;
	bool gameover = false;
	bool connected = false;
	bot::team_id id = 6666;
	bot::field_size field_width;
	bot::field_size field_height;
	int win_width = 500;
	int win_height = 500;
        
	bots mi_bots = bots(_LADO, _LADO); // Tamaño del campo 10x10, usa la pila
	// bots *mi_bots = new bots(10,10) // al monticulo

	mi_bots.generate(4,4); // Número de equipos y número de miembros por equipo, usa la pila
	// mi_bots->generate(3,10); // al monticulo
	


	while (!gameover) 
	{
		mi_bots.step();
		paso++;

		mi_bots.for_each_bot([&] ( bot & b ) {
			//std::cout << b.get_team() << "\t"; // std::endl;
			//std::cout << b.get_x() << "\t";
			//std::cout << b.get_y() << "\t";
			//std::cout << b.get_energy() << "\t";
			//std::cout << std::endl;
			
			//mi_bots.can_move( b, bot::W);
			
			//if ( b.get_team() == 0) 
			//{
			//	b.try_to_do(bot::W);
			//}
			
			std::stringstream stream;
            //stream << "move " << b.get_x() << " " << b.get_y() << " " << b.get_next_direction();
            stream << "gameover";
            send(*socket, stream.str());
			
		});
				
		//pinta_escenario(mis_bots_ord);
		pinta_escenario(mi_bots, paso);

		while ( std::cin.get() != ' ' );
		std::cout << "\x1B[2J\x1B[H";

	}
	return 0;
}
