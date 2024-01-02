#include <iostream>
#include <stdint.h>
using namespace std;


const uint8_t ZERO_FLAG_BYTE_POSITION = 7;
const uint8_t SUBTRACT_FLAG_BYTE_POSITION = 6;
const uint8_t HALF_CARRY_FLAG_BYTE_POSITION = 5;
const uint8_t CARRY_FLAG_BYTE_POSITION = 4;

struct Z80_FlagRegister {
    bool zero;
    bool subtract;
    bool half_carry;
    bool carry;
};

// Z80 CPU
class Z80 {
public:
    // registers
    uint8_t a = 0;
    uint8_t b = 0;
    uint8_t c = 0;
    uint8_t d = 0;
    uint8_t e = 0;
    uint8_t h = 0;
    uint8_t l = 0;
    uint8_t pc = 0;
    uint8_t sp = 0;
    uint8_t f = 0;
    uint8_t m = 0;
    uint8_t t = 0;

    // get virtual 16 bit register
    uint16_t getBC() {
        uint16_t bc = (b << 8) | c; 
        return bc;
    }

     // set virtual 16 bit register
    void setBC(uint16_t value) {
        b = (uint8_t)((value & 0xFF00 >> 8)); // 0xFF00 aka 1111 1111 0000 0000 
        c = (uint8_t)(value & 0xFF);
    }

    // get flag bits
    bool getflag() {
        //return (f & (1 << ));
    }

    // set flag bits
    void setFlag() {

    }



    // dispatcher (Op code look-up)
    // ..CPU Operations
    

    // reset exectution

    
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
    return 0;
}

