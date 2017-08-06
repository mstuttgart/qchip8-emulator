#ifndef CHIP8DISASSEMBLER_HPP
#define CHIP8DISASSEMBLER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <iomanip>

class Chip8Disassembler
{

private:
	std::uint8_t *buffer;
	std::uint16_t opcode;
	unsigned int sizeFile;
	std::uint16_t PC;

public:

	/**
	 * @brief 
	 */
	Chip8Disassembler();
	
	/**
	 * @brief 
	 */
	virtual ~Chip8Disassembler();

	/**
	 * @brief 
	 * @param file
	 * @return 
	 */
	bool load ( const std::string& file );
	
	/**
	 * @brief 
	 */
	void disassemble();

};

#endif // CHIP8DISASSEMBLER_HPP
