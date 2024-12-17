#include <climits>
#include <fstream>
#include <iostream>
#include <vector>
void panic(std::string s) {
    std::cout << s << std::endl;
    exit(1);
}
int combo(std::vector<long> program,long a) {
    if (a>=0 && a<4) return a;
    if (a<7) return program[a-4];
    else panic("combo value error");
    return -1;
}
long pow(int x,int i) {
    long out=1;
    for (int j=0;j<i;j++) out*=(long)x;
    return out;
}
bool instruction(std::vector<long>& reg,std::vector<long>& program,int& isp,std::vector<long>& out) {
    if (program.size()%2) panic("program error");
    if (isp%2) panic("instruction pointer misaligned");
    if (isp>=program.size()) return 0;
    int a=program[isp],b=program[isp+1];
    int inc=2;
    int outval;
    switch (a) {
        case 0:
            reg[0]/=pow(2,combo(reg,b));
            break;
        case 1:
            reg[1]^=b;
            break;
        case 2:
            reg[1]=(combo(reg,b)%8+8)%8;
            break;
        case 3:
            if (reg[0]!=0) {
                isp=b;
                inc=0;
            }
            break;
        case 4:
            reg[1]^=reg[2];
            break;
        case 5:
            outval=(combo(reg,b)%8+8)%8;
            out.push_back(outval);
            break;
        case 6:
            reg[1]=reg[0]/pow(2,combo(reg,b));
            break;
        case 7:
            reg[2]=reg[0]/pow(2,combo(reg,b));
            break;
    }
    isp+=inc;
    return 1;
}
int main(int argc,char**argv) {
    char c;
    std::vector<long> program;
    std::vector<long> reg;
    std::ifstream file(argv[1]);
    bool prev=0;
    int initreg=-1;
    while (file>>c) {
        if (c>='0' && c<='9') {
            if (prev) {
                if (program.size()!=0) program.back()=program.back()*10+c-'0';
                else reg.back()=reg.back()*10+c-'0';
            }
            else {
                if (reg.size()==3) program.push_back(c-'0');
                else reg.push_back(c-'0');
            }
        }
        prev=(c>='0' && c<='9');
    }
    file.close();
    long i=pow(8,(program.size()-1)),a=program.size()-1,j=0;
    long ans=LONG_MAX;
    std::vector<long> out;
    std::vector<std::vector<long>> stack;
    for (;;) {
        reg={i,0,0};
        out={};
        int isp=0;
        while (instruction(reg,program,isp,out));
        if (program==out) {
            if (i<ans) ans=i;
        } else if (program[a]==out[a]&&a!=0) {
            stack.push_back({i,a});
        }
        j++;
        i+=pow(8,a);
        if (j==8) {
            if (stack.size()==0) break;
            i=stack.back()[0],a=stack.back()[1];
            stack.pop_back();
            j=0;
            a--;
        }
        if (a==-1) break;
    }
    std::cout << ans << std::endl;
    return 0;
}
