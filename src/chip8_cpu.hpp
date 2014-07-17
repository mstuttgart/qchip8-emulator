#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

#include <QtGui>

#define V_SIZE		16
#define STACK_SIZE	16
#define MEMORY_SIZE	4096	// 4K
#define DISPLAY		2048	// 64 * 32
#define DISPLAY_W	64
#define DISPLAY_H	32	// 64 * 32
#define DISPLAY_EXT_W	128
#define DISPLAY_EXT_H	64
#define KEY_SIZE	16

class Chip8_CPU
{

private:

	quint16 opcode;
	quint16 I;
	quint16 PC;
	quint16 SP;
	quint16 stack[STACK_SIZE];

	quint8 V[V_SIZE];
	quint8 memory[MEMORY_SIZE];

	quint8 delay_timer;
	quint8 sound_timer;

	bool display[ DISPLAY ]; // (64/8) * (32/8)
	bool extendDisplayMode;

	quint8 currentDisplayWidth;
	quint8 currentDisplayHeight;

	bool currentKeyState[KEY_SIZE];
	bool lastKeyState[KEY_SIZE];
	bool waitForKey;

	typedef void ( Chip8_CPU::*pFunc ) ();
	pFunc opcodeMap[16];


private:

	void opcodePrefix0();
	void opcodePrefix1();
	void opcodePrefix2();
	void opcodePrefix3();
	void opcodePrefix4();
	void opcodePrefix5();
	void opcodePrefix6();
	void opcodePrefix7();
	void opcodePrefix8();
	void opcodePrefix9();
	void opcodePrefixA();
	void opcodePrefixB();
	void opcodePrefixC();
	void opcodePrefixD();
	void opcodePrefixE();
	void opcodePrefixF();

	quint8 decodeX();
	quint8 decodeY();
	quint8 decodeN();
	quint8 decodeNN();

public:

	/**
	 * @brief
	 */
	Chip8_CPU();

	/**
	 * @brief
	 */
	virtual ~Chip8_CPU();

	/**
	 * @brief
	 * @param file
	 * @return
	 */
	bool load ( const std::string& fileName );

	/**
	 * @brief
	 */
	void fetch();

	/**
	 * @brief
	 */
	void execute();
	
	/**
	* @brief
	*/
	void hardReset();

	/**
	 * @brief
	 */
	void softReset();

	/**
	 * @brief
	 * @return
	 */
	const bool* getDisplay() const;

	/**
	 * @brief
	 * @param key
	 */
	void setKey ( int key, bool state );

};
