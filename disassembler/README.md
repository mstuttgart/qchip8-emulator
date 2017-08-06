Chip8-Disassemblar
===============

Introduction
===============

The Chip8 Disassembler command line tool to disassemble bytecode of CHIP-8 interpreter. Work in Microsoft Windows and GNU Linux. QChip8 Emulator may be freely distributed, not for commercial purposes.If you want to reuse anything, go ahead, as long as you credit me, and your project is open source too.

Compiling
==============

Make sure the "build essentials" and essentials packages of compilation:

* In Ubuntu/Debian: sudo apt-get install build-essential checkinstall cdbs devscripts dh-make fakeroot libxml-parser-perl check avahi-daemon -y

Now you can compile by running in terminal:

	$ g++ main.cpp chip8_disassembler.cpp chip8_disassembler.hpp -o main -std=c++11
    $ ./main chipfile.ch8

where "chipfile.ch8" is a bytecode file of chip8 interpreter.

Observation
============
Chip8 interpreter don'n have a official language assembly, so i use
the assembly language developped of David Winter in your Chip8/SCHIP Manual.

About
======
Copyright (C) 2014-2015 by Michell Stuttgart Faria

Internal RCA COSMAC VIP Operating System, CHIP-8 interpreters (C) Joseph Weisbecker 1977-1990(?)

