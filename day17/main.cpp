#include <fstream>
#include <iostream>
#include <string>
#include <vector>
void panic(std::string s) {
    std::cout << s << std::endl;
    exit(1);
}
int combo(std::vector<int> program,int a) {
    if (a>=0 && a<4) return a;
    if (a<7) return program[a-4];
    else panic("combo value error");
    return -1;
}
bool instruction(std::vector<int>& program,int& isp,std::vector<int>& out) {
    if (program.size()%2==0) panic("program error");
    if (isp%2==0) panic("instruction pointer misaligned");
    if (isp>=program.size()) return false;
    int a=program[isp],b=program[isp+1];
    int inc=2;
    switch (a) {
        case 0:
            program[0]>>=combo(program,b);
            break;
        case 1:
            program[1]^=b;
            break;
        case 2:
            program[1]=(combo(program,b)%8+8)%8;
            break;
        case 3:
            if (program[0]!=0) {
                isp=b+3;
                inc=0;
            }
            break;
        case 4:
            program[1]^=program[2];
            break;
        case 5:
            out.push_back((combo(program,b)%8+8)%8);
            break;
        case 6:
            program[1]=program[0]>>combo(program,b);
            break;
        case 7:
            program[2]=program[0]>>combo(program,b);
            break;
    }
    isp+=inc;
    return true;
}
int main(int argc,char**argv) {
    char i;
    std::vector<int> program;
    std::vector<int> out;
    std::ifstream file(argv[1]);
    bool prev=0;
    int initreg=-1;
    while (file>>i) {
        if (i>='0' && i<='9') {
            if (prev) program.back()=program.back()*10+i-'0';
            else program.push_back(i-'0');
        }
        prev=(i>='0' && i<='9');
    }
    file.close();
    int isp=3;
    while (instruction(program,isp,out));
    for (int i:out) std::cout << i << ",";
    std::cout << std::endl;
    return 0;
}
