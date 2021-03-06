#pragma once 
#include <string>
#include <array>
#include "FileSys.h"
#include "memcontrol.h"


// Flag definition
enum
{
    sf = 1 << 0, // sign
    zf = 1 << 1, // zero
    lf = 1 << 2, // lower
    ef = 1 << 3, // end
    of = 1 << 4, // overflow
    cf = 1 << 5, // carry
    pf = 1 << 6  // parity
};

class Cpu
{
    public:
        Memcontrol memcontroller = Memcontrol();
        IOControl iocontroller = IOControl();
        FileSystem filesystem = FileSystem();
        Program activeProgram;

        Cpu(){}
        void ShowRam(); // Show the contents of the RAM
        Program LoadProgram(std::string filename);// Load the Program machine code to the memory
        Program LoadProgram(std::vector<int> programCode);// Load the Program machine code to the memory
        Program ExecuteProgram(Program program, int cycles = 14800); // Execute the loaded program for some cycles
        CpuSnapshot SaveToSnapshot();
        Program LoadBootloader();
        void SetFromSnapshot(CpuSnapshot snapshot);

    private:
        // Register definition
        int pc = 0x0;   // program counter
        int addr = 0x0; // internal addr register
        int acc = 0x0;   // accumulator
        int ir = 0x0;   // instruction register
        int sp = RAM_SIZE - 1; // stack pointer 
        int fs = 0x0; // flags
        int xReg = 0x0; // x register
        int cReg = 0x0; // c register
        int retReg = 0x0; // return register used in calls


        void Fetch();
        void Decode();

        void OP_STOP();

        // Loads
        void OP_LOADA(); // load value at address
        void OP_LOADI(); // load immediate value
        void OP_LOADR(); // load value from register

        // Stores
        void OP_STOREA(); // store value in accumulator at address
        void OP_STORER(); // store value in accumulator at register

        // Adds
        void OP_ADDA(); // add value at address to accumulator
        void OP_ADDI(); // add immediate to accumulator
        void OP_ADDR(); // add register to accumulator

        // Subs
        void OP_SUBA(); // subtract value at address from accumulator
        void OP_SUBI(); // subtract immediate from accumulator
        void OP_SUBR(); // subtract register from accumulator

        // Muls
        void OP_MULA(); // multiply accumulator by value at address
        void OP_MULI(); // multiply accumulator by immediate
        void OP_MULR(); // multiply accumulator by value at register

        void OP_DIVA(); // divide accumulator by value at address
        void OP_DIVI(); // divide accumulator by immediate
        void OP_DIVR(); // divide accumulator by value at register

        // Jumps
        void OP_JZ();
        void OP_JNZ();
        void OP_JL();
        void OP_JLE();
        void OP_JG();
        void OP_JGE();
        void OP_JMP();
        void OP_JP();
        void OP_JC();
        void OP_JO();

        void OP_MOD();
        void OP_PUSH();
        void OP_POP();
        void OP_INC();
        void OP_DEC();

        // Shifts
        void OP_SHL(); // shift left accumulator by immediate
        void OP_SHR(); // shift right accumulator by immediate

        void OP_INT(); // calls the interrupt at immediate
        void UNDEFINED();

        // Logic ops
        // Ands
        void OP_ANDA(); // perform logic AND on accumulator and value at address
        void OP_ANDI(); // perform logic AND on accumulator and immediate
        void OP_ANDR(); // perform logic AND on accumulator and value at register

        // Ors
        void OP_ORA(); // perform logic OR on accumulator and value at address
        void OP_ORI(); // perform logic OR on accumulator and immediate
        void OP_ORR(); // perform logic OR on accumulator and value at register

        // Xors
        void OP_XORA(); // perform logic XOR on accumulator and value at address
        void OP_XORI(); // perform logic XOR on accumulator and immediate
        void OP_XORR(); // perform logic XOR on accumulator and value at register

        // CMPs -> sets L flag to 1 if accumulator value is lower, 0 otherwise. Sets Z flag to 1 if equal
        void OP_CMPA(); // perform comparison between accumulator and value at address
        void OP_CMPI(); // perform comparison between accumulator and immediate
        void OP_CMPR(); // perform comparison between accumulator and value at register

        void OP_CALL(); // perform a long jump (uint 16 instead of 8)

        // Data Segment/Heap management
        void OP_VAR();
        void OP_PTR();
        void OP_LOADV();
        void OP_STOREV();
        void OP_LOADP();
        void OP_STOREP();

        void OP_RET();

        //string operations
        void OP_STR();
        void OP_RSTR();
        void OP_DELSTR();
        void OP_STRCAT();

        std::string buildString();

        int AddInternal(int x, int y);
        int MulInternal(int x, int y);
        bool ParityCheck();

        void int3();  // Load program from disk
        void int4();  // Execute kernel process by Id
        void int6();  // Load non-kernel program
        void int5();  // getchar
        void int10(); // print
        void int15(); // create file
        void int16(); // delete file
        void int17(); // modify file descriptor
        void int18(); // write into file
        void int30(); // get file descriptor string
        void int31(); // get file index size
        void int32(); // get process index size
        void int33(); // get process info string
        void int35(); // get count of args
        void int36(); // get arg by given index
};
