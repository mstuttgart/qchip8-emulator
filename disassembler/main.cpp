#include "chip8_disassembler.hpp"
#include <iostream>

int main ( int argc, char* argv[] )
{

	if( argc == 1 ){
		std::cout << "Numero de parâmetros incorreto." << std::endl;
		return -1;
	}

	// Declaramos o disassembler
	Chip8Disassembler daChip8;

	// Carregamor o arquiv binario
	daChip8.load ( argv[1] );
	
	// Disassemblamos
	daChip8.disassemble();

#ifdef WIN32
	system ( "pause" );
#endif

	return 0;
}
