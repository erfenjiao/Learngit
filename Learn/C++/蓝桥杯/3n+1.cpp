#include <iostream>

using namespace std;
int main() {
    int i, j,add1;

    while (cin >> i >> j) {
        cout  << i << ' ' << j << ' ';
        int add = 0;
        if (j < i) {
            int a;
            a = j;j = i;i = a;
        }//如果j小，调换位置。
        
        for (int x = i; x <= j; x++) {
            add1 = 1;//将每个数字的猜想初值设为1
            int y = x;
            //cout << y<<j;
            while (y != 1) {
                if (y % 2 == 1) y = 3 * y + 1;
                else y = y / 2;
                add1++;
            }//进行3n+1猜想

            if (add1 > add) add = add1;
        }//查找最大数字
        cout <<add<<endl;
    }

    return 0;
}

