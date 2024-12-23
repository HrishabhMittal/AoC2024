#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>
struct computer {
    std::string name;
    int done=0;
    std::vector<computer*> connections;
    computer(std::string name): name(name) {}
};
std::unordered_map<std::string,computer*> comp;
void connect(std::string comp1,std::string comp2) {
    if (!comp.count(comp1)) {
        comp[comp1]=new computer(comp1);
    }
    if (!comp.count(comp2)) {
        comp[comp2]=new computer(comp2);
    }
    comp[comp1]->connections.push_back(comp[comp2]);
    comp[comp2]->connections.push_back(comp[comp1]);
}
void connect(std::string comps) {
    std::string arg1,arg2;
    bool b=0;
    for (char i:comps) {
        if (b) arg2.push_back(i);
        else {
            if (i=='-') {
                b=1;
                continue;
            }
            arg1.push_back(i);
        }
    }
    connect(arg1,arg2);
}
template<typename T>
void remove(std::vector<T>& t,int index) {
    for (int i=index+1;i<t.size();i++) {
        t[i-1]=t[i];
    }
    t.pop_back();
}
void eliminate() {

}
std::vector<computer*> Expand(std::vector<computer*> group) {
    std::unordered_map<std::string,int> map;
    for (auto g:group) {
        for (int i=0;i<g->connections.size();i++) {
            map[g->connections[i]->name]++;
        }
    }
    std::vector<computer*> max=group;
    group.push_back(nullptr);
    for (auto c:comp) {
        if (map[c.first]==group.size()-1) {
            group.back()=c.second;
            std::vector v=Expand(group);
            if (v.size()>max.size()) max=v;
        }
    }
    return max;
}
int main(int argc,char**argv) {
    std::string line;
    std::ifstream file(argv[1]);
    while (file>>line) {
        connect(line);
    }
    file.close();
    std::vector<computer*> co;
    for (auto c:comp) {
        computer* i=c.second;
        std::cout << "yo" << std::endl;
        std::vector v=Expand({i});
        if (v.size()>co.size()) co=v;
        std::cout << "yo" << std::endl;
    }
    for (auto i:co) {
        std::cout << i->name << " ";
    }
    std::cout << std::endl;
}
