#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
std::unordered_map<std::string,int> map;
std::unordered_map<std::string,std::vector<std::string>> m1;
int calcValue(std::string s) {
    if (!map.count(s)) {
        if (m1[s][1]=="XOR") {
            map[s]=calcValue(m1[s][0])^calcValue(m1[s][2]);
        }
        if (m1[s][1]=="OR") {
            map[s]=calcValue(m1[s][0])|calcValue(m1[s][2]);
        }
        if (m1[s][1]=="AND") {
            map[s]=calcValue(m1[s][0])&calcValue(m1[s][2]);
        }
    }
    return map[s];
}
std::string z(int i) {
    std::string out = std::to_string(i);
    if (out.size()==1) {
        out="z0"+out;
    } else out="z"+out;
    return out;
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
            m1[res]={s,op,arg2};
        }
    }
    size_t total=0;
    int i=0;
    for (auto i:m1) {
        calcValue(i.first);
    }
    while (map.count(z(i))) {
        i++;
    }
    i--;
    while (i>=0) {
        total<<=1;
        total+=map[z(i)];
        i--;
    }
    file.close();
    std::cout << total << std::endl;
}