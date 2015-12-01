QChip8-Emulator
===============

## Introduction
The QChip8 Emulator is a freeware open source RCA COSMAC VIP emulator and CHIP-8 interpreter for 
Microsoft Windows and GNU Linux.implemented with Qt4 framework. QChip8 Emulator may be freely distributed, 
not for commercial purposes.If you want to reuse anything, go ahead, as long as you credit me, and your project is open source too.

Obs.: SCHIP support yet not implemented.

## Preview

Follow there is screenshots of QChip8 Emulator

![image1](http://4.bp.blogspot.com/-_cO_rqTqxFA/U6o5W1gamDI/AAAAAAAACMw/QIw-G_EebTs/s1600/ExemploGeometric23.png)

![image2](http://4.bp.blogspot.com/-PLAfy60JC8w/U6o5W-v5ZPI/AAAAAAAACM0/JqBT_4bFnQU/s1600/ExemploGeometric25.png)

![image3](http://3.bp.blogspot.com/-elzc9rgnHoQ/U6o5W0qUHVI/AAAAAAAACNA/AGMD9lpNRQ0/s1600/ExemploGeometric24.png)

## Compiling
Make sure the Qt (>= 4.8) development libraries are installed:
```
* In Ubuntu/Debian: sudo apt-get install libqt4-dev
* In Fedora: yum install qt-devel
* In Arch Linux: pacman -S qt
```

Now you can compile by running:
```
	$ qmake (or qmake-qt4 on some systems, like Fedora) <br>
	$ make
```
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
Chip8 emulator available.

### I found a bug!
Please report any and all bugs using the project issue
tracker. Be as precise as possible so that the bug can be found easier. Thanks!

## About
Copyright (C) 2014-2015 by Michell Stuttgart Faria

Internal RCA COSMAC VIP Operating System, CHIP-8 interpreters (C) Joseph Weisbecker 1977-1990(?)

