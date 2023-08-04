#include <iostream>;
#include<time.h>;
using namespace std;

//S��
const unsigned char S[16][16] = {                      //4                     //8              //b         //d
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,  //1
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, //2
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,//3
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,//4
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,//5
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,//6
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,//7
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,//8
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,//a
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,//c
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,//e
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

// ���ַ���ת��Ϊ4x4����
void StrToArray(unsigned char* plain, unsigned char parray[4][4]) {
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            parray[j][i] = plain[k];
            k++;
        }
    }

}

// ��ӡ����
void ShowArray(unsigned char array[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%02X", array[i][j]);
            printf("\t");

        }
        printf("\n");
    }
    printf("\n");
}

//�ֽڴ���
void SubBytes(unsigned char parray[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // ������
            int x = parray[i][j] / 16;
            // ������
            int y = parray[i][j] % 16;
            // S�д���
            parray[i][j] = S[x][y];
        }
    }

}

// ����λ
void ShiftRows(unsigned char parray[4][4]) {
    // ����parray��temp
    unsigned char temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            temp[i][j] = parray[i][j];
    }

    // ��ʼ��λ
    for (int i = 0; i < 4; i++) {
        // ��һ�в���
        // �ڶ���������һ���ֽ�
        if (i == 1) {
            for (int j = 0; j < 3; j++)
                parray[i][j] = parray[i][j + 1];
            parray[i][3] = temp[i][0];
        }
        // �����������������ֽ�
        if (i == 2) {
            for (int j = 0; j < 2; j++)
                parray[i][j] = parray[i][j + 2];
            parray[i][2] = temp[i][0];
            parray[i][3] = temp[i][1];
        }
        // �����������������ֽ�
        if (i == 3) {
            for (int j = 3; j > 0; j--)
                parray[i][j] = parray[i][j - 1];
            parray[i][0] = temp[i][3];
        }
    }
}


// �л���������
const int c[4][4] =
{
    2,3,1,1,
    1,2,3,1,
    1,1,2,3,
    3,1,1,2
};

// ����{02}*{x}
unsigned char GFmu2(unsigned char x) {
    // ����һλ
    unsigned char x_left = x << 1;
    // �ж�x������λ�ǲ���Ϊ1
    unsigned char b7 = x & 0x80;
    // ���Ϊ1,���ƺ��ֵ��0001 1011 ���
    if (b7 != 0)
        x_left = x_left ^ 0x1b;
    return x_left;
}

// ����{03}*{x}
unsigned char GFmu3(unsigned char x) {
    return GFmu2(x) ^ x;
}

// ���㵥��
unsigned char GFmu(int n, unsigned char x) {
    unsigned char result = 0;
    if (n == 2)
        result = GFmu2(x);
    else if (n == 3)
        result = GFmu3(x);
    else
        result = x;
    return result;

}

// �л��
void MixColums(unsigned char parray[4][4]) {
    // ����parray
    unsigned char temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            temp[i][j] = parray[i][j];
    }
    //��ʼ����
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            parray[i][j] = GFmu(c[i][0], temp[0][j]) ^ GFmu(c[i][1], temp[1][j]) ^ GFmu(c[i][2], temp[2][j]) ^ GFmu(c[i][3], temp[3][j]);
        }
    }
}


// ��һ��4�ֽ����ֿ�������
void SplitNumToArray(int num, unsigned char numarray[4]) {
    numarray[0] = num >> 24;
    numarray[1] = num >> 16;
    numarray[2] = num >> 8;
    numarray[3] = num;

}

// ������ϳ�һ��4�ֽ���
int CombineArrayToNum(unsigned char numarray[4]) {
    int num = 0;
    num = numarray[0];
    num = num << 8;
    num += numarray[1];
    num = num << 8;
    num += numarray[2];
    num = num << 8;
    num += numarray[3];

    return num;
}

// ����Կ��ÿһ�кϳ�һ��4�ֽ���
void KeyColumsCombine(unsigned char karray[4][4], int carray[44]) {
    for (int i = 0; i < 4; i++) {
        // temp[4]��ž����ÿһ��
        unsigned char temp[4];
        temp[0] = karray[0][i];
        temp[1] = karray[1][i];
        temp[2] = karray[2][i];
        temp[3] = karray[3][i];

        // �������ÿһ�кϳ�һ������������չ��Կ����
        carray[i] = CombineArrayToNum(temp);

    }
}

// ������ֵ��
static const int Rcon[10] =
{ 0x01000000, 0x02000000,
    0x04000000, 0x08000000,
    0x10000000, 0x20000000,
    0x40000000, 0x80000000,
    0x1b000000, 0x36000000 };

// g����
int g(int carray, int round) {
    unsigned char numarray[4];

    // ��4�ֽ����ֿ�
    SplitNumToArray(carray, numarray);

    // ѭ������һλ
    unsigned char temp = numarray[0];
    for (int j = 0; j < 3; j++)
        numarray[j] = numarray[j + 1];
    numarray[3] = temp;

    // ��s�����ֽڴ���
    for (int j = 0; j < 4; j++) {
        // ������
        int x = numarray[j] / 16;
        // ������
        int y = numarray[j] % 16;

        numarray[j] = S[x][y];

    }
    /*
    cout << "\n" << "�ֽڴ�����";
    for (int j = 0; j < 4; j++)
    {
        printf("%02x%s", numarray[j], "\t");
    }
    */

    // ���ϳ�һ��4�ֽ���
    int num = 0;
    num = CombineArrayToNum(numarray);

    // ��Rcon���
    num = num ^ Rcon[round];

    return num;
}

// ��չ��Կ
int carray[44];

// ��չ��Կ karrayΪ����Կ
void KeyExtend(unsigned char karray[4][4]) {
    // ������Կ������չ����
    KeyColumsCombine(karray, carray);
    for (int i = 4, j = 0; i < 44; i++) {
        // 4��������Ҫ����g����
        if (i % 4 == 0) {
            carray[i] = carray[i - 4] ^ g(carray[i - 1], j);
            j++; // ��һ��
        }
        else
            carray[i] = carray[i - 1] ^ carray[i - 4];
        //cout << carray[i];
    }
}

// ��������Կ,������
void AddKeyRound(unsigned char parray[4][4], int round) {
    // cout <<"\n"<< round << "����Կ:";
     // ����е�����Կ
    unsigned char rarray[4];
    for (int i = 0; i < 4; i++) {
        // ��carray[44]��ȡ��������rarray[4]
        SplitNumToArray(carray[round * 4 + i], rarray);
        // һ��һ�м���
        for (int j = 0; j < 4; j++) {
            //printf("%02x%s",rarray[j],"\t");     
            parray[j][i] = parray[j][i] ^ rarray[j];
        }
    }
}


int main() {
    unsigned char input[16] = "lishutingsdusdu";
    // ����Կ
    unsigned char key[16] = "lishutingsdusdu";
    clock_t start_time = clock();
    // ��Կ�������������
    unsigned char karray[4][4];
    unsigned char parray[4][4];
    // ����Կת��Ϊ����
    StrToArray(key, karray);
    //������ת��Ϊ����
    StrToArray(input, parray);
    // ��չ��Կ
    KeyExtend(karray);

    // ��һ�ּ���
    AddKeyRound(parray, 0);
    // ǰ����
    for (int i = 1; i < 11; i++) {
        //  �ֽڴ���
        SubBytes(parray);
        // ����λ
        ShiftRows(parray);
        // �л��
        if (i < 10) {//��ʮ�ֲ������л��
            MixColums(parray);
        }
        // ����
        AddKeyRound(parray, i);
    }
    cout << "AES���ܽ����" << "\n";
    ShowArray(parray);
    clock_t end_time = clock();
    cout << "ʱ��Ϊ��" << end_time - start_time << "ms";
    return 0;
}