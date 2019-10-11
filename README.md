# QChip8-Emulator

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
<a name="top" href="https://github.com/mstuttgart/qchip8-emulator"><img src="https://lh3.googleusercontent.com/xZ-YoycsnviVF6p5PsEIQaaRqPU1C7F-CVE_Lw0dWJ9yED8DKSKxXK4t-qTA8dXxkpiwwgHIyqRLEeUT0KLnBVMGVPX0myeKgBBme3Ky4oNaHGK1SKVCfsjWh1RchjB4hKR2_EJIzWtEGvm_5EdDz8zY8RgWIsDzEGAo4GXhOb-ceWf0p0GG-oAqCSXK-g9S_I2nhbFqs9lMYkaXvB5MAkU8WEVU4nsIH0J71wb5f7Df0e8XBhPq4qKV8zYkeYT6jPAbquegexeyY9ch_I9Ter7ecGKfl6mRYRm7Bfue5fKD1VPr46vNt8fsK63ZXGnd-9OCSAQAfbAFoSG31eXT5Ho8-vlfGMEqYFdSUgnfNTCITy7afFHhLXKhNB2AUyBsdFXRvCAASZJbhE2zN7isHnzla5CDPxhgD0PQbyhO1gXso8_0P_o8hto6-YL56QFWZp14loht0UnnltRjoT0znaAnXy00kV1GK0Q0jYpOH-1nG9hIezxhmNZwVVHHjngCD67TOYaiX7sK0u9BdxqcIyUnU0XhYtd1X2X6HN9Sa_qxGEFGjXTUO0yPjLBEu--ldH6ynPE2PbgsbXhzWggFkFSM-Ii4IZadIwaX9ZC1q9p_FzYJX3UIB2vgeXJ6O9g4fT6N-droElZ0RuAhRkER2gl0q81b7UrBUF0TOe8-e7JsA68=w516-h313-no"></a>
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

