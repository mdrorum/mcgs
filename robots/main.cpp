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

	//std::cout << "\x1B[2J\x1B[H"; // Despeja la pantalla del terminal
	std::cout << "A jugar!!" << std::endl;

	boost::asio::io_service io_service; // Inicia comunicaciones

	tcp::resolver resolver(io_service); // Resuelve la comunicación
	auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] }); // Iterador hacia puerto y dirección

	std::shared_ptr<tcp::socket> socket(new tcp::socket(io_service)); // Puntero compartido hacia el socket

	boost::asio::connect(*socket, endpoint_iterator); // Conexión

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
        
	bots mi_bots = bots(_LADO, _LADO); // Tamaño del campo 10x10, usa la pila
	// bots *mi_bots = new bots(10,10) // al monticulo

	mi_bots.generate(4,4); // Número de equipos y número de miembros por equipo, usa la pila
	// mi_bots->generate(3,10); // al monticulo
	
	boost::asio::streambuf buf;
	
	read_until(*socket, buf, "\n");

	std::string data;
	std::istream is(&buf);
	std::getline(is, data);


	std::istringstream mi_stream(data);

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
        
        //set_screen(win_width, win_height, field_width, field_height);
        //connected = true;
    }

	//while ( std::cin.get() != ' ' );

    

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
				std::cout << "Ha llegado: " << command << std::endl;
				std::stringstream state;

				while(!mi_stream2.eof()) {
					std::string a;
					mi_stream2 >> a;
					state << a << " ";
				}
				std::cout << state.str() << std::endl;

				boost::archive::text_iarchive ia(state);
				{
					// mutex:
					// segfaults if it draws during a state update (drawing +
					// incomplete state is fatal)
					boost::mutex::scoped_lock lock(state_mutex);
					ia >> mi_bots;
					paso++;
					std::cout << "\x1B[2J\x1B[H";
					pinta_escenario(mi_bots, paso);
				}
			}
			else 
			{
				std::cout << "GAME OVER " << command << std::endl;
			}
			
		}
			
		//mi_bots.step();
		//paso++;

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
            stream << "move " << b.get_x() << " " << b.get_y() << " " << bot::W;
            //stream << "gameover";
            send(*socket, stream.str());
            
            
			
		});
				
		//pinta_escenario(mis_bots_ord);
		//pinta_escenario(mi_bots, paso);

		while ( std::cin.get() != ' ' );
		//std::cout << "\x1B[2J\x1B[H";

	}
	return 0;
}
