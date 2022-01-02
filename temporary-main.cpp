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

void printHex(uint8_t binary){
    char toHex[2]; 
    toHex[0] = binary & 0x0F;
    toHex[1] = (binary & 0xF0) >> 4;
    for(unsigned int j = 0; j < 2; j++){
        if(toHex[j] > 9){
            toHex[j] += 0x37;
        }else{
            toHex[j] += 0x30;
        }
    }
    std::cout << toHex[1] << toHex[0] << " ";
}

void readMemory(uint8_t* mem, unsigned int size){
    for(unsigned int i = 0; i < size; i++){
        printHex(mem[i]);
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
    // Stack? SP & BP, PUSH, POP

    clearMemory(readonlymem, ROMSIZE);
    clearMemory(memory, RAMSIZE);

    // Hard coded instructions
    const int nrOf = 5;
    const uint8_t Instructions[] = {0x01, 0xFF, 0x04, 0xBB, 0x10 };  

    // sizeof
    for(int i = 0; i < nrOf; i++){
        readonlymem[i] = Instructions[i];
    }

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
        // LOAD B BY VALUE
        case 0x04:
            registerB = readonlymem[PC + 1];
            PC += 2;
        break;
        // LOAD B BY ADDRESS
        case 0x05:
            registerB = memory[PC + 1];
            PC += 2;
        break;
        case 0x06:


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
    std::cout << "Accumulator: ";
    printHex(registerA);
    std::cout << "\n";
    std::cout << "B Register: ";
    printHex(registerB);
    std::cout << "\n";
    std::cout << "PC: ";
    printHex(PC);
    std::cout << "\n";
    std::cout << "IR: ";
    printHex(IR);
    std::cout << "\n";

    std::cout << "ROM: " << "\n";
    readMemory(readonlymem, ROMSIZE);
    /*
        std::cout << "RAM: " << "\n";
        readMemory(memory, RAMSIZE);
    */
    while(1);

    return 0;
}
