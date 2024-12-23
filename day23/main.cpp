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
template<typename T>
int indexOf(std::vector<T>& v,T e) {
    for (int i=0;i<v.size();i++) {
        if (v[i]==e) {
            return i;
        }
    }
    return -1;
}
void removeComputer(std::string c) {
    computer* cc=comp[c];
    for (auto i:cc->connections) {
        remove(i->connections,indexOf(i->connections,cc));
    }
    comp.erase(c);
    delete cc;
}
std::vector<std::vector<computer*>> cache,ncache;
void check(int in,std::vector<computer*>& c) {
    if (in==c.size()) {
        for (auto j:c) {
            j->done=1;
        }
        ncache.push_back(c);
    } else {
        std::unordered_map<std::string,int> map;
        int x=1;
        for (auto i:c) {
            x&=i->done;
            for (auto j:i->connections) {
                map[j->name]++;
            }
        }
        if (x) return;
        c.push_back(nullptr);
        for (auto i:map) {
            if (i.second==c.size()-1) {
                c.back()=comp[i.first];
                check(in,c);
            }
        }
        c.pop_back();
    }
}
bool allZero() {
    for (auto i:comp) {
        if (i.second->done) return 0;
    }
    return 1;
}
void purge() {
    for (auto i:comp) {
        if (!i.second->done) removeComputer(i.first);
        i.second->done=0;
    }
}
int main(int argc,char**argv) {
    std::string line;
    std::ifstream file(argv[1]);
    while (file>>line) {
        connect(line);
    }
    file.close();
    int n=2;
    for (auto i:comp) {
        cache.push_back({i.second});
    }
    while (true) {
        for (int i=0;i<cache.size();i++) {
            check(n,cache[i]);
        }
        cache=ncache;
        ncache={};
        if (!allZero()) purge();
        else break;
        n++;
    }
    for (auto i:comp) {
        std::cout << i.second->name << std::endl;
    }
}
