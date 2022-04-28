#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct{
    uint8_t emulator_flags;   //8-bit flag
}TestChip;

TestChip *Create()
{   
    TestChip *chip1 = malloc(sizeof(TestChip));
    chip1->emulator_flags = 0;
    return chip1;
}

void setFlag(char *flag_path,const uint8_t flag)
{
    *flag_path = *flag_path | flag;
    printf("Flag %d setted , emulator flag = 0x%X\n",flag,*flag_path);
}

void clearFlag(char *flag_path)
{
    *flag_path = 0;
    printf("Flag cleared 0x%d ",*flag_path);
}

void flagSetted(char *flag_path)
{
    uint16_t testFlag = 0;
    
}

int main()
{
    TestChip *chip = Create();
    setFlag(&chip->emulator_flags,1);
    setFlag(&chip->emulator_flags,2);
    setFlag(&chip->emulator_flags,0);
    clearFlag(&chip->emulator_flags);
    return 0;
}