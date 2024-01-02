#include <iostream>
#include <stdint.h>
using namespace std;

// Z80 Time Clock Registers
struct Z80_clock {
    uint8_t m = 0;
    uint8_t t = 0;
};

// Z80 CPU Registers
struct Z80_registers {
    uint8_t a = 0;
    uint8_t b = 0;
    uint8_t c = 0;
    uint8_t d = 0;
    uint8_t e = 0;
    uint8_t h = 0;
    uint8_t l = 0;
    uint8_t f = 0;
    uint8_t pc = 0;
    uint8_t sp = 0;
    uint8_t m = 0;
    uint8_t t = 0;
};

// Z80 CPU
struct Z80 {
    Z80_clock _clock; // Time Clock
    Z80_registers _r; // Registers
    //MMU _mmu;

    // CPU Operations

    // Add E to A, (ADD A, E)
    void ADDr_e() {
        _r.a += _r.e;                  // perform addition
        _r.f = 0;                       // clear flags
        if(!(_r.a & 255)) _r.f |= 0x80; // check for zero
        if(_r.a > 255) _r.f |= 0x10; // check for carry (overflowed 255: max 8-bit value)
        _r.a  &= 255;                // Mask to 8 bits
        _r.m = 1; _r.t = 4;          //  1 M-time taken
    }


    // Compare B to A, setting flags (CP A, B)
    void CPr_b() {
        uint8_t i = _r.a;                 // Temp copy of A
        i -= _r.b;                    // Subtract B
        _r.f |= 0x40;                 // Set subtraction flag
        if(!(i & 255)) _r.f |= 0x80;  // check for 0
        if(i < 0) _r.f |= 0x10;       // check for 0
        _r.m = 1; _r.t = 4;           //1 M-time taken
    }

/*
    // Memory Management

    // Push registers B and C to the stack (PUCH BC)
    void PUSHBC() {
        _r.sp--;              // offset stack position down
        _mmu.wb(_r.sp, _r.b); // Write b to mem address
        _r.sp--;              // offset stack position down
        _mmu.wb(_r.sp, _r.c); // Write c
        _r.m = 3; _r.t = 12;  // 3 M-times taken
    }

    // Pop registers H and L off the stack (POP HL)
    void POPHL() {
        _r.l = _mmu.rb(_r.sp); // read L
        _r.sp++;               // offset stack position up
        _r.h = _mmu.rb(_r.sp); // read H
        _r.sp++;               // offset stack position up
        _r.m = 3; _r.t = 12;   // 3 M-times taken
    }

    // read a byte from absolute location into A (LD A, addr)
    void LDAmm() {
        uint16_t addr = _mmu.rw(_r.pc); // Get address from instruction
        _r.pc += 2;                // advance the program counter (PC)
        _r.a = _mmu.rb(addr);      // read frim the address
        _r.m = 4; _r.t = 16;       // 4 M-times taken
    }

*/

    // No operation (NOP)
    void NOP() {
        _r.m = 1; _r.t = 4;           //1 M-time taken
    }

    // reset exectution
    void reset() {
        _r.a = 0;
        _r.b = 0;
        _r.c = 0;
        _r.d = 0;
        _r.e = 0;
        _r.h = 0;
        _r.l = 0;
        _r.f = 0;
        _r.sp = 0;
        _r.pc = 0;
        _clock.m = 0; _clock.t = 0;
    }

    // dispatcher
};

struct MMU {
    int rb(uint8_t addr) {
        // read 8-bit byte from a given address
        return addr;
    }

    int rw(uint16_t addr) {
        // read 16-bit word from a given address
        return addr;
    }

    void wb(uint8_t& addr, int val) {
        // write 8-bit word to a given address
        addr = val;
    }

    void ww(uint16_t& addr, int val) {
        // write 16-bit word to a given address
        addr = val;
    }
};




int main() {
    Z80 cpu;
    cpu._r.a = 4;
    cpu._r.e = 5;

    cpu.ADDr_e();
    cout << cpu._r.a << endl;
    return 0;
}

