#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
    uint8_t emulator_flags;   //8-bit flag
}TestChip;

TestChip *Create()
{   
    TestChip *chip1 = malloc(sizeof(TestChip));
    return chip1;
}

void setFlag(TestChip *chip,const uint8_t flag)
{   
    chip->emulator_flags = flag & 0xF ;
    printf("Flag %d setted , emulator flag = 0x%X\n",flag,chip->emulator_flags);
}

int main()
{
    time_t t;
    srand((unsigned)time(&t));
    uint8_t randomByte = rand() % 256;
    printf("%d\n",randomByte);
    
    /* TestChip *chip = Create();
    setFlag(chip,0x8); */
    return 0;
}

//Bit placement 
    //0000 0001 = 0x1
    //0000 0010 = 0x2
    //0000 0100 = 0x4
    //0000 1000 = 0x8
    //0001 0000 = 0x10
    //0010 0000 = 0x20
    //0100 0000 = 0x40
    //1000 0000 = 0x80
