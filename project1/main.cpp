#include <iostream>
#include <string>
#include "transform.h"
#include "sm3.h"
using namespace std;

void birthday_attack() {
    for (int i = 0; i < max_num; i++) {
        string str = to_string(i);
        string paddingValue = padding(str);
        string re = iteration(paddingValue);

        for (int j = 0; j < i; j++) {
            if (outlist[j].substr(0, 4) == re.substr(0, 4)) {
                cout << "找到碰撞！" << endl;
                cout << "碰撞字符串 1：" << str << endl;
                cout << "哈希值 1：" << re << endl;
                cout << "碰撞字符串 2：" << inlist[j] << endl;
                cout << "哈希值 2：" << outlist[j] << endl;
                cout << "查找总数：" << i << endl;
                return;
            }
        }

        inlist[i] = str;
        outlist[i] = re;
    }

    cout << "没有找到碰撞" << endl;
}

int main() {
    birthday_attack();
    return 0;
}