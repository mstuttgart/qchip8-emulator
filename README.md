QChip8-Emulator
===============

## Introduction

The QChip8 Emulator is a freeware open source RCA COSMAC VIP emulator and CHIP-8 interpreter for 
Microsoft Windows and GNU Linux.implemented with Qt4 framework. QChip8 Emulator may be freely distributed, 
not for commercial purposes.If you want to reuse anything, go ahead, as long as you credit me, and your project is open source too.

<p align="center">
<a name="top" href="https://github.com/mstuttgart/qchip8-emulator"><img src="https://lh3.googleusercontent.com/i4SzkR5Y4c-d0pwSUgSaAyS0cz9C2lOWRR-XpYI-sr12zBrG0APys6bKUL5m71ZAum-JEeiuJrjznO9bN_duJ-urkkvqdEF9oX6fwVOnc--8MgHnyd_neg0DeUxzlO5LAanN8UXPnQg0yOznJa75MqIc7pyPuJ8Ze_QN1gPQIAK1PvQRwe9HdYRlb6gd1xlTfEEtbkVamod-4r0gV9qh-l0KHUQGgf5Gye9HSC2odhm14C9qg07fhgS_zBQHcXmbSVBVmZvIbiYmLNg0YLG_gqLCO-scTS_IguQRE90cQ2PT6cSmxEfovXpq1iS1jYLz9KoGhDkv1xBOWFBzaNm39s7GKYAnAQt6GviyY5jhDlxcEuM6VfXimUa7NgWf0otLvz2dw1oaqrxyqUSoYXxDwMdo0W13zXH4jQcD3Yg79voGiMMoKRbLMwzp7heMHCJCYJJoHk7ZCGDBrU_YVMq91Oc5sNbQMrXNUmtDkwxwjwZohbY0OsQ4rY0L_S9OK0WRgGff0mdrfJ1CidfUAJzyH3RyzQCJpna4HoNJBWHtumV8tDpnpXAJJ7MK_FW4NyQOVx955i4o6pJSDKDpDUlUkLZE6O6H3JrZTPCqM49QbXsO0-oMwMVRR8qrHumx0pNstg9Z-gKvkCf7jNIg17EWTa9g5EwXxly4aXsDDwHP2F2szTo=w516-h313-no"></a>
</p>


## Compiling
Make sure the Qt (<= 4.8) development libraries are installed:

```
* In Ubuntu/Debian: sudo apt-get install libqt4-dev
* In Fedora: yum install qt-devel
* In Arch Linux: pacman -S qt
```

Now you can compile by running:

```bash
qmake (or qmake-qt4 on some systems, like Fedora) 
make
```
You can now simply run QChip8 Emulator using ./qchip8-emulator

<p align="center">
<a name="top" href="https://github.com/mstuttgart/qchip8-emulator"><img src="https://lh3.googleusercontent.com/-beIOelZelI0/VyrDR_kImKI/AAAAAAAAGBY/vyagXZY-CoslskpIJ0Fuct-pPmHT2M03ACCo/s516/emu2.png"></a>
</p>

### Keyboard Configuration
Keyboard configuration in CHIP and it respective in PC keyboard:

|CHIP (PC)| CHIP (PC)| CHIP (PC) | CHIP (PC) 
:---:|:---:|:---:|:---:|
|1 (1)| 2 (2) |3 (3)| C (4)
|4 (Q)| 5 (W)| 6 (E)| D (R)
|7 (A)| 8 (S)| 9 (D)| E (F)
|A (Z) |0 (X)| B (C)| F (V)


* Ctrl+U: soft machine reset
* Ctrl+R: hard machine reset (reload)
* Ctrl+O: load state from memory
* Ctrl+H: about
* Ctrl+Q: exit emulator

## Contributing
If you'd like to contribute, please create a fork and issue pull requests! I am
very open to newcomers, and will need all the help we can get to make the best
Chip8 emulator available.

### I found a bug!
Please report any and all bugs using the project issue
tracker. Be as precise as possible so that the bug can be found easier. Thanks!

## About
Copyright (C) 2014-2016 by Michell Stuttgart Faria

Internal RCA COSMAC VIP Operating System, CHIP-8 interpreters (C) Joseph Weisbecker 1977-1990(?)

