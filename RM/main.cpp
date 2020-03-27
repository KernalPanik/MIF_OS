#include <stdio.h>
#include "cpu.h"

#include "IOControl.h"

//TODO: Write a make file
//TODO: Implement memory segmentation

int main(int argc, char** argv)
{   
    if(argc == 1)
    {
        printf("no file provided");
        exit(1);
    }

    printf("Loading the program to the RAM\n");

    //Cpu cpu = Cpu();

    /*Program program = cpu.LoadProgram(argv[1]);
    cpu.ShowRam();

    cpu.ExecuteProgram(program);

    cpu.ShowRam();
    */
    IOControl c = IOControl();
    c.InitDisk();

    return 0;
}