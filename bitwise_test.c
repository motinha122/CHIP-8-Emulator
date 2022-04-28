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
    uint8_t flag_set = 1;

    flag_set = flag_set << (flag - 1);

    *flag_path = *flag_path | flag_set;
    printf("Flag %d setted , emulator flag = 0x%X\n",flag,*flag_path);
}

void clearFlag(char *flag_path)
{
    *flag_path = 0;
    printf("Flag cleared 0x%d\n ",*flag_path);
}

void flagSetted(char *flag_path)
{
    uint8_t testFlag = 1;
    uint8_t flag;

    printf("Flags setted : ");

    for (int i = 1 ; i <= 8 ; i++)
    {
        flag = *flag_path & testFlag;

        if(flag != 0)
        {
            printf("%d ",i);
        }
        testFlag = testFlag << 1;
    }
    printf("\n");
}

int main()
{
    TestChip *chip = Create();
    setFlag(&chip->emulator_flags,1);
    setFlag(&chip->emulator_flags,2);
    setFlag(&chip->emulator_flags,3);
    flagSetted(&chip->emulator_flags);
    clearFlag(&chip->emulator_flags);
    return 0;
}
