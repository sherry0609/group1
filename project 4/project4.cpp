#include <stdio.h>
#include <stdint.h>
#include <string.h>


#define SM3_DIGEST_LENGTH 32

#define LEFT_ROTATE(word, bits) (((word) << (bits)) | ((word) >> (32 - (bits))))


#define FF(x, y, z) ((x) ^ (y) ^ (z))
#define GG(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))

 
#define P0(x) ((x) ^ LEFT_ROTATE((x), 9) ^ LEFT_ROTATE((x), 17))
#define P1(x) ((x) ^ LEFT_ROTATE((x), 15) ^ LEFT_ROTATE((x), 23))

// 初始化状态
const uint32_t IV[8] = {
    0x7380166F, 0x4914B2B9, 0x172442D7, 0xDA8A0600,
    0xA96F30BC, 0x163138AA, 0xE38DEE4D, 0xB0FB0E4E
};

// 常量T
const uint32_t T[64] = {
    0x79CC4519, 0x7A879D8A, 0x1E376C08, 0x2748774C, 0x34BAFB92, 0x4EF5B35A, 0x5EAB0EB2, 0x682E6FF3,
    0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2,
    0xCA273ECE, 0xD186B8C7, 0xEADA7DD6, 0xF57D4F7F, 0x06F067AA, 0x0A637DC5, 0x113F9804, 0x1B710B35,
    0x28DB77F5, 0x32CAAB7B, 0x3C9EBE0A, 0x431D67C4, 0x4CC5D4BE, 0x597F299C, 0x5FCB6FAB, 0x6C44198C,
    0x6DC5AACE, 0x735E2B97, 0x8089A3FA, 0x8AD0CCE1, 0x8DEB82D7, 0x95A55B97, 0x9A2D0F56, 0xA8082A6E,
    0xB3C1241A, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967, 0x27B70A85, 0x2E1B2138,
    0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85, 0xA2BFE8A1, 0xA81A664B,
    0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070, 0x19A4C116, 0x1E376C08
    
};

// 填充消息
void padMessage(uint8_t* message, uint64_t length) {
    message[length++] = 0x80; // 添加一个bit为1的标记

    // 补0直到消息长度 (mod 512) 为 448
    while (length % 64 != 56) {
        message[length++] = 0x00;
    }

    // 添加消息长度 (64-bit little-endian)
    for (int i = 0; i < 8; ++i) {
        message[length++] = (uint8_t)((length * 8) >> (56 - i * 8));
    }
}
// 处理消息分组
void processBlock(const uint8_t* block, uint32_t* state) {
    uint32_t W[68];
    uint32_t A, B, C, D, E, F, G, H;
    uint32_t SS1, SS2, TT1, TT2;

    // 将消息分组分为16个字，存入W[0..15]
    for (int i = 0; i < 16; ++i) {
        W[i] = ((uint32_t)block[i * 4] << 24) | ((uint32_t)block[i * 4 + 1] << 16) | ((uint32_t)block[i * 4 + 2] << 8) | block[i * 4 + 3];
    }

    // 填充W[16..67]
    for (int i = 16; i < 68; ++i) {
        W[i] = P1(W[i - 16] ^ W[i - 9] ^ LEFT_ROTATE(W[i - 3], 15)) ^ LEFT_ROTATE(W[i - 13], 7) ^ W[i - 6];
    }

    // 初始化工作变量
    A = state[0];
    B = state[1];
    C = state[2];
    D = state[3];
    E = state[4];
    F = state[5];
    G = state[6];
    H = state[7];

    // 压缩函数主循环
    for (int i = 0; i < 64; ++i) {
        SS1 = LEFT_ROTATE(LEFT_ROTATE(A, 12) + E + LEFT_ROTATE(T[i], i), 7);
        SS2 = SS1 ^ LEFT_ROTATE(A, 12);
        TT1 = FF(A, B, C) + D + SS2 + W[i];
        TT2 = GG(E, F, G) + H + SS1 + W[i];

        D = C;
        C = LEFT_ROTATE(B, 9);
        B = A;
        A = TT1;
        H = G;
        G = LEFT_ROTATE(F, 19);
        F = E;
        E = P0(TT2);
    }

    // 更新状态
    state[0] ^= A;
    state[1] ^= B;
    state[2] ^= C;
    state[3] ^= D;
    state[4] ^= E;
    state[5] ^= F;
    state[6] ^= G;
    state[7] ^= H;
}

// 计算SM3哈希值
void sm3(const uint8_t* message, uint64_t length, uint8_t* digest) {
    uint32_t state[8];
    uint8_t block[64];

    // 初始化状态
    memcpy(state, IV, sizeof(IV));

    // 填充消息并处理分组
    for (uint64_t offset = 0; offset < length; offset += 64) {
        memcpy(block, message + offset, 64);
        processBlock(block, state);
    }

    // 处理最后一个分组或单个分组
    memset(block, 0x00, sizeof(block));
    memcpy(block, message + (length - length % 64), length % 64);
    padMessage(block, length % 64);
    processBlock(block, state);

    // 输出哈希值
    for (int i = 0; i < SM3_DIGEST_LENGTH / 4; ++i) {
        digest[i * 4] = (uint8_t)(state[i] >> 24);
        digest[i * 4 + 1] = (uint8_t)(state[i] >> 16);
        digest[i * 4 + 2] = (uint8_t)(state[i] >> 8);
        digest[i * 4 + 3] = (uint8_t)state[i];
    }
}

int main() {
    uint8_t message[] = "Hello, World!";
    uint8_t digest[SM3_DIGEST_LENGTH];

    sm3(message, sizeof(message) - 1, digest);

    printf("SM3 哈希值：");
    for (int i = 0; i < SM3_DIGEST_LENGTH; ++i) {
        printf("%02X", digest[i]);
    }
    printf("\n");

    return 0;
}