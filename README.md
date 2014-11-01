QChip8-Emulator
===============

## Introduction
The QChip8 Emulator is a freeware open source RCA COSMAC VIP emulator and CHIP-8 interpreter for 
Microsoft Windows and GNU Linux.implemented with Qt4 framework. QChip8 Emulator may be freely distributed, 
not for commercial purposes.If you want to reuse anything, go ahead, as long as you credit me, and your project is open source too.

## Compiling
Make sure the Qt (>= 4.8) development libraries are installed:

* In Ubuntu/Debian: sudo apt-get install libqt4-dev
* In Fedora: yum install qt-devel
* In Arch Linux: pacman -S qt

Now you can compile by running:

	$ qmake (or qmake-qt4 on some systems, like Fedora) <br>
	$ make

You can now simply run QChip8 Emulator using ./qchip8-emulator

### Keyboard Configuration
Keyboard configuration in CHIP and it respective in PC keyboard:

CHIP (PC):

1(1) 2(2) 3(3) C(4)

4(Q) 5(W) 6(E) D(R)

7(A) 8(S) 9(D) E(F)

A(Z) 0(X) B(C) F(V)


Ctrl+U: soft machine reset

Ctrl+R: hard machine reset (reload)

Ctrl+O: load state from memory

Ctrl+H: about

Ctrl+Q: exit emulator

## Contributing
If you'd like to contribute, please create a fork and issue pull requests! I am
very open to newcomers, and will need all the help we can get to make the best
Game Library available.

### I found a bug!
Please report any and all bugs using the project issue
tracker. Be as precise as possible so that the bug can be found easier. Thanks!

## About
Obs.: SCHIP support yet not implemented.
Developer: Michell Stuttgart
Internal RCA COSMAC VIP Operating System, CHIP-8 interpreters (C) Joseph Weisbecker 1977-1990(?)

