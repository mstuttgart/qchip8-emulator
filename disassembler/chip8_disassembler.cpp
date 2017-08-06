#include "chip8_disassembler.hpp"

using namespace std;

//-----------------------------------------------------

Chip8Disassembler::Chip8Disassembler() :
	buffer ( NULL ), opcode ( 0 ), sizeFile ( 0 ), PC ( 0x200 )
{
	// Incializamos o gerador randomico
	srand ( time ( NULL ) );
}

//-----------------------------------------------------

Chip8Disassembler::~Chip8Disassembler()
{
	if ( buffer )
		delete[] buffer;
}

//-----------------------------------------------------

bool Chip8Disassembler::load ( const string& file )
{
	// Carregamos o arquivo
	ifstream is ( file, ifstream::binary );

	if ( !is )
		return false;

	// get length of file:
	is.seekg ( 0, is.end );
	int length = is.tellg();
	is.seekg ( 0, is.beg );

	if ( buffer )
		delete[] buffer;

	sizeFile = length + 0x200;

	buffer    = new unsigned char[ sizeFile ];
	char* aux = new char[ length ];

	// read data as a block:
	is.read ( aux, length );

	for ( int i = 0; i < length; i++ ) {
		buffer[i + 0x200] = static_cast<uint8_t> ( aux[i] ) ;
	}

	delete[] aux;

	if ( !is ) {
		std::cout << "error: only " << is.gcount() << " could be read";
		return false;
	}

	is.close();

	return true;
}

//----------------------------------------------------

void Chip8Disassembler::disassemble()
{

	cout << "=========================================" << endl << endl;
	cout << "PC\t" << "OPCODE\t" << "ASSEMBLY" << endl << endl;
	cout << uppercase;

	for ( PC = 0x200; PC < sizeFile; PC += 2 ) {

		// Lendo o opcode. Concatenamos os MSByte com LSBytes
		opcode = ( buffer[PC] << 8 ) | buffer[PC+1];

		// Imprimimos o PC e o opcode
		cout << hex << setw ( 4 ) << setfill ( '0' ) << PC     << "\t"
		     << hex << setw ( 4 ) << setfill ( '0' ) << opcode << "\t";

		switch ( opcode & 0xF000 ) {

			case 0x000:

				switch ( opcode & 0x00FF ) {

					case 0x00E0: // clear screen
						cout << "CLS" << endl;
						break;

					case 0x00EE: // Returns from a subroutine.
						cout << "RET" << endl;
						break;

					default:
						cout << "UKNO\t" << opcode << endl;

				}//switch 0x000

				break;

			case 0x1000: // Jumps to address NNN.
				cout << "JP\t" << hex << setw ( 3 ) << setfill ( '0' )
				     << ( opcode & 0xFFF ) << endl;
				break;

			case 0x2000: // Calls subroutine at NNN.
				cout << "CALL\t" << hex << setw ( 3 ) << setfill ( '0' )
				     << ( opcode & 0xFFF ) << endl;
				break;

			case 0x3000: // 3XNN - Skips the next instruction if VX equals NN.
				cout << "SE\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
				     << hex << setw ( 2 ) << setfill ( '0' ) << ( opcode & 0x0FF ) << endl;
				break;

			case 0x4000: // 4XNN - Skips the next instruction if VX doesn’t equal NN.
				cout << "SNE\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
				     << hex << "\t" << setw ( 2 ) << setfill ( '0' )
				     << ( opcode & 0x0FF ) << endl;
				break;

			case 0x5000: // 5XNN - Skips the next instruction if VX equals VY.
				cout << "SE\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 ) << "\tV"
				     << ( ( opcode & 0x00F0 ) >> 4 ) << endl;
				break;

			case 0x6000: // 6XNN - Sets VX to NN.
				cout << "LD\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
				     << "\t" << setw ( 2 ) << setfill ( '0' ) << ( opcode & 0x0FF ) << endl;
				break;

			case 0x7000: // 7XNN	Adds NN to VX.
				cout << "ADD\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
				     << "\t" << setw ( 2 ) << setfill ( '0' ) << ( opcode & 0x0FF ) << endl;
				break;

			case 0x8000:

				switch ( opcode & 0x000F ) {

					case 0x0000: // 8XY0	Sets VX to the value of VY.
						cout << "LD\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << "\tV" << ( ( opcode & 0x00F0 ) >> 4 ) << endl;
						break;

					case 0x0001: // 8XY1	Sets VX to VX or VY.
						cout << "OR\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << "\tV" << ( ( opcode & 0x00F0 ) >> 4 ) << endl;
						break;

					case 0x0002: // 8XY2	Sets VX to VX and VY.
						cout << "AND\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << "\tV" << ( ( opcode & 0x00F0 ) >> 4 ) << endl;
						break;

					case 0x0003: // 8XY3	Sets VX to VX xor VY.
						cout << "XOR\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << "\tV" << ( ( opcode & 0x00F0 ) >> 4 ) << endl;
						break;

					case 0x0004:
						// 8XY4	Adds VY to VX. VF is set to 1 when there’s a
						// carry, and to 0 when there isn’t.
						cout << "ADD\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << "\tV" << ( ( opcode & 0x00F0 ) >> 4 ) << endl;
						break;

					case 0x0005:
						// 8XY5	VY is subtracted from VX. VF is set to 0 when
						// there’s a borrow, and 1 when there isn’t.
						cout << "SUB\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << "\tV" << ( ( opcode & 0x00F0 ) >> 4 ) << endl;
						break;

					case 0x0006:
						// 8XY6	Shifts VX right by one. VF is set to the value
						// of the least significant bit of VX before the shift
						cout << "SHR\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 ) << endl;
						break;

					case 0x0007:
						// 8XY7	Sets VX to VY minus VX. VF is set to 0 when
						// there’s a borrow, and 1 when there isn’t.
						cout << "SUBN\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << "\tV" << ( ( opcode & 0x00F0 ) >> 4 ) << endl;
						break;

					case 0x000E:
						// 8XYE	Shifts VX left by one. VF is set to the value
						// of the most significant bit of VX before the shift
						cout << "SHL\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 ) << endl;
						break;

					default:
						cout << "UKNO\t" << opcode << endl;
						break;

				}//switch 0x8000

				break;

			case 0x9000: // 9XY0 Skips the next instruction if VX doesn’t equal VY.
				cout << "SNE\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 ) << "\tV"
				     << ( ( opcode & 0x00F0 ) >> 4 ) << endl;
				break;

			case 0xA000: // ANNN: Sets I to the address NNN
				cout << "LD\t" << "I\t" << hex << setw ( 3 ) << setfill ( '0' )
				     << ( opcode & 0xFFF ) << endl;
				break;

			case 0xB000: // BNNN	Jumps to the address NNN plus V0.
				cout << "JP\t" << "V0\t" << hex << setw ( 3 ) << setfill ( '0' )
				     << ( opcode & 0x0FFF ) << endl;
				break;

			case 0xC000:// CXNN	Sets VX to a random number and NN.
				cout << "RND\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 ) << "\t"
				     << hex << setw ( 2 ) << setfill ( '0' )
					 << ( opcode & 0x00FF ) << endl;
				break;

			case 0xD000:
				cout << "DRW\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 ) << "\tV"
				     << ( ( opcode & 0x00F0 ) >> 4 ) << "\t" << hex
				     << setw ( 1 ) << setfill ( '0' ) << ( opcode & 0x000F ) << endl;
				break;

			case 0xE000:

				switch ( opcode & 0x00FF ) {

					case 0x009E:
						// EX9E	Skips the next instruction if the key
						// stored in VX is pressed.
						cout << "SKP\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << endl;
						break;

					case 0x00A1:
						//	EXA1	Skips the next instruction if the key
						// stored in VX isn’t pressed.
						cout << "SKNP\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << endl;
						break;

					default:
						cout << "UKNO\t" << opcode << endl;

				}//switch 0x009E

				break;

			case 0xF000:

				switch ( opcode & 0x00FF ) {

					case 0x0007: // FX07	Sets VX to the value of the delay timer.
						cout << "LD\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << "\tDT" << endl;
						break;

					case 0x000A: // FX0A - A key press is awaited, and then stored in VX.
						cout << "LD\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << "\tWK" << endl;
						break;

					case 0x0015: // FX15	Sets the delay timer to VX.
						cout << "LD\t" << "DT\t"
						     << "V" << ( ( opcode & 0x0F00 ) >> 8 ) << endl;
						break;

					case 0x0018: // FX18	Sets the sound timer to VX.
						cout << "LD\t" << "ST"
						     << "\tV" << ( ( opcode & 0x0F00 ) >> 8 ) << endl;
						break;

					case 0x001E: // FX1E	Adds VX to I
						cout << "ADD\t" << "I"
						     << "\tV" << ( ( opcode & 0x0F00 ) >> 8 ) << endl;
						break;

					case 0x0029:
						// FX29	Sets I to the location of the sprite for the
						// character in VX. Characters 0-F (in hexadecimal) are
						// represented by a 4×5 font.
						cout << "LD\t" << "SPR"
						     << "\tV" << ( ( opcode & 0x0F00 ) >> 8 ) << endl;
						break;

					case 0x0033:
						// FX33 - Stores the Binary-coded decimal representation of VX
						// at the addresses I, I plus 1, and I plus 2
						cout << "LD\t" << "BCD"
						     << "\tV" << ( ( opcode & 0x0F00 ) >> 8 ) << endl;

						break;

					case 0x0055:
						// FX55 Stores V0 to VX in memory starting at address I
						cout << "LD\t" << "[I]\t" << "V0 - V"
						     << ( ( opcode & 0x0F00 ) >> 8 ) << endl;
						break;

					case 0x0065:
						// FX65 Fills V0 to VX with values from memory starting at address I
						cout << "LD\t" << "V" << ( ( opcode & 0x0F00 ) >> 8 )
						     << "\t[i]" << endl;
						break;

					default:
						cout << "UKNO\t" << opcode << endl;
						break;

				}//switch 0x000F

				break;

			default:
				cout << "UKNO\t" << opcode << endl;
				break;

		}//switch geral

	}//for

	cout << "\n=========================================" << endl << endl;

}

//---------------------------------------------------
