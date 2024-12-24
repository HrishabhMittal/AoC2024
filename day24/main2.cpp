#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
std::unordered_map<std::string,int> map;
std::unordered_map<std::string,std::string> altnames;
std::vector<std::string> undefined;
std::unordered_map<std::string,std::vector<std::string>> ins;

std::pair<std::string,std::vector<std::string>> checkforrule(std::string arg1,std::string op,std::string arg2) {
    for (auto i:ins) {
        if (i.second==std::vector{arg1,op,arg2} || i.second==std::vector{arg2,op,arg1}) {
            return i;
        }
    }
    return {"none",{}};
}


std::string x(int i) {
    std::string out = std::to_string(i);
    if (out.size()==1) return "x0"+out;
    return "x"+out;
}
std::string y(int i) {
    std::string out = std::to_string(i);
    if (out.size()==1) return "y0"+out;
    return "y"+out;
}
std::string z(int i) {
    std::string out = std::to_string(i);
    if (out.size()==1) return "z0"+out;
    return "z"+out;
}
std::string aplha(char c,int i) {
    std::string out = std::to_string(i);
    if (out.size()==1) return c+"0"+out;
    return c+out;
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
        }
    }
}