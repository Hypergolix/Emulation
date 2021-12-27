#include <iostream>

#define ROMSIZE 128
#define RAMSIZE 256

// STORE IMMEDIATE: STI, REG, ADD
// LOAD IMMEDIATE: LDI, REG, ADD
// JMP / BRNE / BRIE
// ADD, SUB, DIV, MUL

void clearMemory(uint8_t* mem, unsigned int size){
    for(unsigned int i = 0; i < size; i++){
        mem[i] = 0;
    }
}

void readMemory(uint8_t* mem, unsigned int size){
    for(unsigned int i = 0; i < size; i++){
        char toHex[2]; 
        toHex[0] = mem[i] & 0x0F;
        toHex[1] = (mem[i] & 0xF0) >> 4;
        for(unsigned int j = 0; j < 2; j++){
            if(toHex[j] > 9){
                toHex[j] += 0x37;
            }else{
                toHex[j] += 0x30;
            }
        }
        std::cout << toHex[1] << toHex[0] << " ";
        if((i + 1) % 16 == 0){
            std::cout << "\n";
        }
    }
}

int main(void){
    static uint8_t readonlymem[ROMSIZE];
    static uint8_t memory[RAMSIZE];
    register uint8_t registerA;
    register uint8_t registerB;
    register uint8_t SR = 0;
    static uint8_t PC = 0; 
    static uint8_t IR = 0;

    clearMemory(readonlymem, ROMSIZE);
    clearMemory(memory, RAMSIZE);

    // Hard coded instructions
    readonlymem[0] = 0x01;
    readonlymem[1] = 0xFF;
    readonlymem[2] = 0x05;

    for(uint8_t i = 0; i < ROMSIZE; i++){
        IR = readonlymem[PC];
        switch (IR)
        {
        // LOAD A BY VALUE
        case 0x01:
            registerA = readonlymem[PC + 1];
            PC += 2;
            break;
        // LOAD A BY ADDRESS
        case 0x02:
            registerA = memory[PC + 1];
            PC += 2;
            break;
        // STORE A 
        case 0x03:
            memory[PC + 1] = registerA;
            PC += 2;
        break;
        case 0x04:

        break;



        // HALT
        case 0x10:
            goto exit_;
        break;

        default:
            break;
        }
    }
    exit_: ;
    std::cout << "Accumulator: " << +registerA << "\n";
    std::cout << "B Register: " << +registerB << "\n";
    std::cout << "PC: " << +PC << "\n";
    std::cout << "IR: " << +IR << "\n";

    std::cout << "ROM: " << "\n";
    readMemory(readonlymem, ROMSIZE);

    std::cout << "RAM: " << "\n";
    readMemory(memory, RAMSIZE);

    while(1);

    return 0;
}
