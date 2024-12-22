#include <fstream>
#include <iostream>
long nextNum(long num) {
    num^=num<<6;
    num&=16777215;
    num^=num>>5;
    num&=16777215;
    num^=num<<11;
    num&=16777215;
    return num;
}
int main(int argc,char**argv) {
    std::ifstream file(argv[1]);
    long num,total=0;
    while (file>>num) {
        for (int i=0;i<2000;i++) {
            num=nextNum(num);
        }
        total+=num;
    }
    file.close();
    std::cout << total << std::endl;
}
