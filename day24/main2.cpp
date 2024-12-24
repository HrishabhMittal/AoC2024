#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
std::unordered_map<std::string,int> map;
std::unordered_map<std::string,std::vector<std::string>> ins;
std::string z(int i) {
    std::string out = std::to_string(i);
    if (out.size()==1) return "z0"+out;
    return "z"+out;
}
void solve() {
    int i=1;
    while (map.count(z(i))) {
        if (map.count(z(i+1))) {
            if (ins[z(i)][1]!="XOR") {
                std::cout << z(i)  << std::endl;
            }
        } else {
            if (ins[z(i)][1]!="OR") {
                std::cout << z(i)  << std::endl;
            }
        }
        i++;
    }
    for (auto a:ins) {
        if (a.second[1]=="OR") {
            if (ins[a.second[0]][1]!="AND") {
                std::cout << a.second[0] << std::endl;
            }
            if (ins[a.second[2]][1]!="AND") {
                std::cout << a.second[2]<< std::endl;
            }
        } else if (a.second[1]=="XOR") {
            if (a.second[0][0]=='x' || a.second[0][0]=='y') continue;
            else {
                int xorr=0;
                if (ins[a.second[0]][1]=="XOR") {
                    xorr=1;
                } else if (ins[a.second[0]][1]!="OR" && ins[a.second[0]]!=std::vector<std::string>{"x00","AND","y00"} && ins[a.second[0]]!=std::vector<std::string>{"y00","AND","x00"}) {
                    xorr=-1;
                    std::cout << a.second[0] << std::endl;
                }
                if (ins[a.second[2]][1]=="XOR") {
                    if (xorr==1) {
                        std::cout << a.second[0] << " or " << a.second[2] << std::endl;
                    }
                } else if (ins[a.second[2]][1]!="OR" && ins[a.second[2]]!=std::vector<std::string>{"x00","AND","y00"} && ins[a.second[2]]!=std::vector<std::string>{"y00","AND","x00"}) {
                    std::cout << a.second[2] << std::endl;
                } else {
                    if (xorr==0) std::cout << a.second[0] << " or " << a.second[2] << std::endl;
                }
            }
        }
    }
}
int main(int argc,char**argv) {
    std::ifstream file(argv[1]);
    std::string s;
    while (file>>s) {
        if (s.back()==':') {
            int i;
            file>>i;
            s.pop_back();
            map[s]=i;
        } else {
            std::string op,arg2,res;
            file>>op;
            file>>arg2;
            file>>res;file>>res;
            ins[res]={s,op,arg2};
            map[res]=0;
        }
    }
    solve();
}