#include "chip8_cpu.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////

Chip8_CPU::Chip8_CPU() {}

////////////////////////////////////////////////////////////////////////////

Chip8_CPU::~Chip8_CPU() {}

////////////////////////////////////////////////////////////////////////////

// Inicializamos o registros do emulador
void Chip8_CPU::hardReset()
{
    // Inicializamos os registros gerais do emulador
    softReset();

    // Zeramos a memoria
    for ( int i = 80; i < MEMORY_SIZE; i++ )
    {
        memory[i] = 0;
    }

    quint8 chip8_fontset[80] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    // Load fontset
    for ( int i = 0; i < 80; i++ )
    {
        memory[i] = chip8_fontset[i];
    }

    // Incializamos o gerador randomico
    srand ( time ( NULL ) );

    // Iniciando mapa com metodos
    opcodeMap[0]  = &Chip8_CPU::opcodePrefix0;
    opcodeMap[1]  = &Chip8_CPU::opcodePrefix1;
    opcodeMap[2]  = &Chip8_CPU::opcodePrefix2;
    opcodeMap[3]  = &Chip8_CPU::opcodePrefix3;
    opcodeMap[4]  = &Chip8_CPU::opcodePrefix4;
    opcodeMap[5]  = &Chip8_CPU::opcodePrefix5;
    opcodeMap[6]  = &Chip8_CPU::opcodePrefix6;
    opcodeMap[7]  = &Chip8_CPU::opcodePrefix7;
    opcodeMap[8]  = &Chip8_CPU::opcodePrefix8;
    opcodeMap[9]  = &Chip8_CPU::opcodePrefix9;
    opcodeMap[10] = &Chip8_CPU::opcodePrefixA;
    opcodeMap[11] = &Chip8_CPU::opcodePrefixB;
    opcodeMap[12] = &Chip8_CPU::opcodePrefixC;
    opcodeMap[13] = &Chip8_CPU::opcodePrefixD;
    opcodeMap[14] = &Chip8_CPU::opcodePrefixE;
    opcodeMap[15] = &Chip8_CPU::opcodePrefixF;

    cout << "Init CHIP8 CPU" << endl;
}

////////////////////////////////////////////////////////////////////////////

void Chip8_CPU::softReset()
{

    // Inicializamos os registros
    opcode = 0;
    I      = 0;
    SP     = STACK_SIZE;
    PC     = 0x200;

    // Zeramos a pilha, registros e vetor de keys
    for ( int i = 0; i < 16; i++ )
    {
        V[i]     = 0;
        stack[i] = 0;
        currentKeyState[i] = false;
        lastKeyState[i]    = false;
    }

    waitForKey = false;

    for ( int i = 0; i < DISPLAY; i++ )
    {
        display[i] = false;
    }

    // Reset timer
    delay_timer = 0;
    sound_timer = 0;
}

////////////////////////////////////////////////////////////////////////////

bool Chip8_CPU::load ( const string &fileName )
{
    // Carregamos o arquivo
    ifstream is ( fileName.c_str(), std::ifstream::binary );

    if ( !is )
        return false;

    // Incializamos os registros, memoria e etc do chip8
    hardReset();

    // get length of file:
    is.seekg ( 0, is.end );
    int length = is.tellg();
    is.seekg ( 0, is.beg );

    char *buffer = new char [length];

    cout << "Loading ROM..." << endl;

    // read data as a block:
    is.read ( buffer, length );

    if ( !is )
    {
        std::cout << "ERROR: only " << is.gcount() << " could be read";
        return false;
    }

    if ( length > ( MEMORY_SIZE - 512 ) )
    {
        cout << "ERROR: ROM too big for memory" << endl;
        return false;
    }

    // Copiamos conteudo do buffer para a memoria
    for ( int i = 0; i < length; i++ )
    {
        memory[i + 0x200] = static_cast<quint8> ( buffer[i] );
    }

    // Fechamos o arquivo
    is.close();

    // ...buffer contains the entire file...
    delete[] buffer;

    return true;

}

////////////////////////////////////////////////////////////////////////////

void Chip8_CPU::fetch()
{
    // Lendo o opcode. Concatenamos os MSByte com LSBytes
    opcode = ( memory[PC] << 8 ) | memory[PC + 1];
}

////////////////////////////////////////////////////////////////////////////

void Chip8_CPU::execute()
{

    // Chamamos o metodo do respectivo opcode
    ( this->*opcodeMap[ ( opcode & 0xF000 ) >> 12 ] ) ();

    // Update timers
    if ( delay_timer != 0 )
        --delay_timer;

    if ( sound_timer > 0 )
    {

        --sound_timer;

        if ( sound_timer == 1 )
            cout <<  "BEEP!"  << endl;

    }//if

}

////////////////////////////////////////////////////////////////////////////

void Chip8_CPU::opcodePrefix0()
{

    switch ( opcode & 0x00FF )
    {

    case 0x00E0: // Clear screen

        for ( int i = 0; i < DISPLAY; i++ )
            display[i] = false;

        PC += 2;
        break;

    case 0x00EE: // Returns from a subroutine.
        PC = stack[SP];
        ++SP;

        break;

    case 0x00FB: // scroll screen 4 pixels right - schip
        break;

    case 0x00FC: // scroll screen 4 pixels left

        break;

    case 0x00FE: // disable extended screen mode
        extendDisplayMode = false;
        break;

    case 0x00FF: // enable extended screen mode (128 x 64)
        extendDisplayMode = true;
        break;

    default:
        switch ( opcode & 0xFFF0 )
        {
        case 0x00C0: // Scroll the screen down N lines - SuperChip

            break;

        default:
            cout << "Invalid OpcodePrefix0" << endl;
            break;

        }

        break;

    }//switch

}

////////////////////////////////////////////////////////////////////////////

// Jumps to address NNN.
void Chip8_CPU::opcodePrefix1()
{
    PC = opcode & 0xfff;

}

////////////////////////////////////////////////////////////////////////////

// Calls subroutine at NNN.
void Chip8_CPU::opcodePrefix2()
{
    SP--;
    stack[SP] = PC + 2;
    PC = opcode & 0x0fff;
}

////////////////////////////////////////////////////////////////////////////

// 3XNN - Skips the next instruction if VX equals NN.
void Chip8_CPU::opcodePrefix3()
{
    PC += V[ decodeX() ] == decodeNN() ? 4 : 2;
}

////////////////////////////////////////////////////////////////////////////

// 4XNN - Skips the next instruction if VX doesn’t equal NN.
void Chip8_CPU::opcodePrefix4()
{
    PC += ( V[ decodeX() ] != decodeNN() ) ? 4 : 2;
}

////////////////////////////////////////////////////////////////////////////

// 5XYN - Skips the next instruction if VX equals VY.
void Chip8_CPU::opcodePrefix5()
{
    PC += ( V[ decodeX() ] == V[ decodeY()] ) ? 4 : 2;
}

////////////////////////////////////////////////////////////////////////////

// 6XNN - Sets VX to NN.
void Chip8_CPU::opcodePrefix6()
{
    V[ decodeX() ] = decodeNN();
    PC += 2;
}

////////////////////////////////////////////////////////////////////////////

// 7XNN Adds NN to VX.
void Chip8_CPU::opcodePrefix7()
{
    V[ decodeX() ] += decodeNN();
    PC += 2;
}

////////////////////////////////////////////////////////////////////////////

void Chip8_CPU::opcodePrefix8()
{
    quint8 idx = decodeX(); //( opcode & 0x0f00 ) >> 8;
    quint8 idy = decodeY(); //( opcode & 0x00f0 ) >> 4;

    switch ( opcode & 0x000F )
    {

    // 8XY0 Sets VX to the value of VY.
    case 0x0000:
        V[idx] = V[idy];
        break;

    // 8XY1 Sets VX to VX or VY.
    case 0x0001:
        V[idx] = V[idx] | V[idy];
        break;

    case 0x0002: // 8XY2    Sets VX to VX and VY.
        V[idx] = V[idx] & V[idy];
        break;

    case 0x0003: // 8XY3    Sets VX to VX xor VY.
        V[idx] = V[idx] ^ V[idy];
        break;

    case 0x0004:
        // 8XY4 Adds VY to VX. VF is set to 1 when there’s a
        // carry, and to 0 when there isn’t.
        V[0xf] = ( V[idy] > ( 0xff - V[idx] ) ) ? 1 : 0;
        V[idx] += V[idy];
        break;

    case 0x0005:
        // 8XY5 VY is subtracted from VX. VF is set to 0 when
        // there’s a borrow, and 1 when there isn’t.
        V[0xf]  = ( V[idy] > V[idx] ) ? 0 : 1;
        V[idx] -= V[idy] ;
        break;

    case 0x0006:
        // 8XY6 Shifts VX right by one. VF is set to the value
        // of the least significant bit of VX before the shift
        //V[0xf] = V[idx] & 0x1;
        // V[idx] >>= 1;
        V[0xf] = V[idy] & 0x1;
        V[idx] = V[idy] >> 1;
        break;

    case 0x0007:
        // 8XY7 Sets VX to VY minus VX. VF is set to 0 when
        // there’s a borrow, and 1 when there isn’t.
        V[0xf] = ( V[idx] > V[idy] ) ? 0 : 1;
        V[idx] =   V[idy] - V[idx];
        break;

    case 0x000E:
        // 8XYE Shifts VX left by one. VF is set to the valueProgram exited with return code: 0
        // of the most significant bit of VX before the shift
        //V[0xf] = ( V[idx] & 0x80 ) == 0x80 ? 1 : 0;
        //V[0xf] = V[idx] >> 7;
        //V[idx] <<= 1;
        V[0xf] = ( V[idy] & 0x80 ) == 0x80 ? 1 : 0;
        V[idx] = V[idy] << 1;
        break;

    default:
        //cout << "Invalid opcode: " << opcode << endl;
        break;

    }//switch

    PC += 2;

}

////////////////////////////////////////////////////////////////////////////

// Skip next instruction if Vx != Vy.
void Chip8_CPU::opcodePrefix9()
{
    PC += V[ decodeX() ] != V[ decodeY() ] ? 4 : 2;
}

////////////////////////////////////////////////////////////////////////////

// ANNN: Sets I to the address NNN
void Chip8_CPU::opcodePrefixA()
{
    I   = opcode & 0x0fff;
    PC += 2;
}

////////////////////////////////////////////////////////////////////////////

// BNNN Jumps to the address NNN plus V0.
void Chip8_CPU::opcodePrefixB()
{
    PC = ( opcode & 0x0fff ) + V[0];
}

////////////////////////////////////////////////////////////////////////////

// CXNN Sets VX to a random number and NN.
void Chip8_CPU::opcodePrefixC()
{
    V[ decodeX() ] = decodeNN() & ( std::rand() % 0xff );
    PC += 2;
}

////////////////////////////////////////////////////////////////////////////

// 0xDXYN Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
void Chip8_CPU::opcodePrefixD()
{
    // Recebemos as coordenadas do sprite
    quint16 x = V[ decodeX() ];
    quint16 y = V[ decodeY() ];

    // Altura do sprite
    quint16 lines = decodeN();

    // Receb o byte doo sprite
    quint8 sprByte;

    quint16 px;
    quint16 py;

    V[0xF] = 0;

    for ( int i = 0; i < lines; i++ )
    {

        sprByte = memory[ I + i ];

        py = ( y + i ) << 6;//* 64

        for ( int j = 0; j < 8; j++ )
        {

            px = ( x + j );

            if ( ( sprByte & ( 0x80 >> j ) ) != 0 )
            {

                if ( display[ px + py ] )
                    V[0xf] = 1;

                display[ px + py ] ^= true;

            }//if

        }//for j

    }// for i

    PC += 2;
}

////////////////////////////////////////////////////////////////////////////


void Chip8_CPU::opcodePrefixE()
{
    switch ( opcode & 0x00FF )
    {

    case 0x009E:

        // EX9E Skips the next instruction if the key
        // stored in VX is pressed.
        PC += ( currentKeyState[ V[ decodeX() ] ] ) ? 4 : 2;
        break;

    case 0x00A1:

        //  EXA1 Skips the next instruction if the key
        // stored in VX isn’t pressed.
        PC += ( !currentKeyState[ V[ decodeX() ] ] ) ? 4 : 2;
        break;

    default:
        break;

    }//switch

}

////////////////////////////////////////////////////////////////////////////

void Chip8_CPU::opcodePrefixF()
{
    unsigned char idx = decodeX();

    switch ( opcode & 0x00FF )
    {

    case 0x0007: // FX07    Sets VX to the value of the delay timer.
        V[idx] = delay_timer;
        break;

    case 0x000A: // FX0A - A key press is awaited, and then stored in VX.

        if ( !waitForKey )
        {

            // Copiamos o estado de cada tecla para o vetor de teclas anteriores
            for ( int i = 0; i < KEY_SIZE; i++ )
            {
                lastKeyState[i] = currentKeyState[i];
            }

            // Indicamos que estamos esperando o pressionamento de uma tecla
            waitForKey = true;
            return;

        }//if
        else
        {

            // Verificamos se alguma tecla mudou de estado
            for ( int i = 0; i < KEY_SIZE; i++ )
            {

                if ( !lastKeyState[i] && currentKeyState[i] )
                {
                    V[idx] = i;
                    PC    += 2;
                    waitForKey = false;
                    return;
                }

                // Permite detectar se uma tecla estava pressiona
                // foi solta e depois pressionada novamente
                lastKeyState[i] = currentKeyState[i];
            }

            return;

        }//else

        break;

    case 0x0015: // FX15    Sets the delay timer to VX.
        delay_timer = V[idx];
        break;

    case 0x0018: // FX18    Sets the sound timer to VX.
        sound_timer = V[idx];
        break;

    case 0x001E: // FX1E    Adds VX to I

        V[0xf] = ( I + V[idx] > 0xfff ) ? 1 : 0;
        I += ( quint16 ) V[idx];
        break;

    case 0x0029:
        // FX29 Sets I to the location of the sprite for the
        // character in VX. Characters 0-F (in hexadecimal) are
        // represented by a 4×5 font.
        I = ( quint16 ) V[idx] * 0x5;
        break;

    case 0x0033:
    {
        // FX33 - Stores the Binary-coded decimal representation of VX
        // at the addresses I, I plus 1, and I plus 2
        quint8 value = V[idx];

        memory[I]   = value / 100;
        value       = value % 100;
        memory[I + 1] = value / 10;
        memory[I + 2] = value % 10;
    }

    break;

    case 0x0055:

        // FX55 Stores V0 to VX in memory starting at address I
        for ( int i = 0; i <= idx; ++i )
            memory[ I + i ] = V[i];

        // I += ( quint16 ) idx + 1;
        break;

    case 0x0065:

        // FX65 Fills V0 to VX with values from memory starting at address I
        for ( int i = 0; i <= idx; ++i )
            V[i] = memory[ I + i ];

        // I += ( quint16 ) idx + 1;
        break;

    default:
        break;

    }//switch

    PC += 2;

}

////////////////////////////////////////////////////////////////////////////

quint8 Chip8_CPU::decodeN()
{
    return opcode & 0x000f;
}

////////////////////////////////////////////////////////////////////////////

quint8 Chip8_CPU::decodeNN()
{
    return opcode & 0x00ff;
}

////////////////////////////////////////////////////////////////////////////

quint8 Chip8_CPU::decodeX()
{
    return ( opcode & 0x0f00 ) >> 8;
}

////////////////////////////////////////////////////////////////////////////

quint8 Chip8_CPU::decodeY()
{
    return ( opcode & 0x00f0 ) >> 4;
}

////////////////////////////////////////////////////////////////////////////

const bool *Chip8_CPU::getDisplay() const
{
    return display;
}

////////////////////////////////////////////////////////////////////////////

void Chip8_CPU::setKey ( int key, bool state )
{
    currentKeyState[ key ] = state;
}

////////////////////////////////////////////////////////////////////////////
