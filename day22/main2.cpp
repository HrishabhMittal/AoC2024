#include <climits>
#include <fstream>
#include <iostream>
#include <ostream>
#include <unordered_map>
long nextNum(long num) {
    num^=num<<6;
    num&=16777215;
    num^=num>>5;
    num&=16777215;
    num^=num<<11;
    num&=16777215;
    return num;
}
std::unordered_map<long,long> map;
void add(long num) {
    long index=0;
    std::unordered_map<long,long> m;
    for (int i=0;i<2000;i++) {
        long next=nextNum(num);
        long dif=next%10-num%10+10;
        index/=20;
        index+=(dif)*8000;
        if (i>=3) {
            if (m[index]!=1) map[index]+=next%10;
            m[index]=1;
        }
        num=next;
    }
}
int main(int argc,char**argv) {
    std::ifstream file(argv[1]);
    long num;
    while (file>>num) {
        add(num);
    }
    file.close();
    long max=LONG_MIN;
    long index;
    for (auto i:map) {
        if (i.second>max) {
            index=i.first;
            max=i.second;
        }
    }
    std::cout << max << std::endl;
}
