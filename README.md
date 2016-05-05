QChip8-Emulator
===============

## Introduction
The QChip8 Emulator is a freeware open source RCA COSMAC VIP emulator and CHIP-8 interpreter for 
Microsoft Windows and GNU Linux.implemented with Qt4 framework. QChip8 Emulator may be freely distributed, 
not for commercial purposes.If you want to reuse anything, go ahead, as long as you credit me, and your project is open source too.

Obs.: SCHIP support yet not implemented.

![](https://lh3.googleusercontent.com/-N0KN_mpGh1s/VvFtLNmpYVI/AAAAAAAAFm4/t0dhbK0yVi0BWF0S-kcP9LYIGrNHtJ72QCCo/s516/687474703a2f2f342e62702e626c6f6773706f742e636f6d2f2d5f634f5f727154717846412f55366f35573167616d44492f4141414141414141434d772f5149772d475f45656254732f73313630302f4578656d706c6f47656f6d657472696332332e706e67.png)

![](https://lh3.googleusercontent.com/-zrUG5q4Fa7Y/VvFtLC09wqI/AAAAAAAAFm4/RABpKQmvjD0pc7z-M2m5qmm0syp5p-QmgCCo/s516/687474703a2f2f342e62702e626c6f6773706f742e636f6d2f2d504c41667936304a4338772f55366f35572d76355a50492f4141414141414141434d302f4a7142545f3462466e51552f73313630302f4578656d706c6f47656f6d657472696332352e706e67.png)

![](https://lh3.googleusercontent.com/-Awelpq6suBs/VvFtLN6T4AI/AAAAAAAAFmw/8F7yE0TUdGsX-D8HOjLMdVj_niK2a1RkACCo/s516-Ic42/687474703a2f2f332e62702e626c6f6773706f742e636f6d2f2d656c7a633972676e486f512f55366f35573071554856492f4141414141414141434e412f41474d44396c704e5251302f73313630302f4578656d706c6f47656f6d657472696332342e706e67.png)

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

