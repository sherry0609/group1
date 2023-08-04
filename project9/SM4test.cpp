#include<stdio.h>
#include <stdint.h>
#include<time.h>
#include"SM4.h"

void SM4(uint32_t* plain, uint32_t* MK, uint32_t* M);

int main() {
    int i, j;
    uint32_t MK[4] = { 0x12345678,0XDFEDFEDD,0xfeDCBA98,0X76543210 };
    uint32_t plain[4] = { 0x01234567,0x89ABCDEF,0xfeDCBA98,0X76543210 };
    uint32_t M[4];
    clock_t time1, time2;
    time1 = clock();
    SM4(plain, MK, M);
    printf("SM4加密结果为：\n");
    for (i = 0; i < 4; i++)
        printf(" 0x%08x  ", M[i]);
    time2 = clock();
    printf("\n所用时间为：%d ms", (time2 - time1));
    return 0;
}