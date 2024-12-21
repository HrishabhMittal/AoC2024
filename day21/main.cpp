#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#ifdef Q2
#define ITERATIONS 25
#else
#define ITERATIONS 2
#endif
struct vec2 {
    int x,y;
    vec2(int x=0,int y=0): x(x),y(y) {}
    vec2 operator-(vec2 a) {
        return {x-a.x,y-a.y};
    }
};
std::string repeat(char c,int j) {
    std::string out;
    for (int i=0;i<j;i++) out+=c;
    return out;
}
//  +---+---+---+
//  | 7 | 8 | 9 |
//  +---+---+---+
//  | 4 | 5 | 6 |
//  +---+---+---+
//  | 1 | 2 | 3 |
//  +---+---+---+
//      | 0 | A |
//      +---+---+
vec2 getNumericPos(int a) {
    if (a=='A') return {3,2};
    if (a=='0') return {3,1};
    a-='0';
    return {3-(a+2)/3,(a+2)%3};
}
std::string getNumericKeypadSequence(int from,int to) {
    vec2 distance=getNumericPos(to)-getNumericPos(from);
    std::string rl=repeat(distance.y>0?'>':'<',abs(distance.y));
    std::string ud=repeat(distance.x>0?'v':'^',abs(distance.x));
    if ((from=='7' || from=='4' || from=='1')&&(to=='0' || to=='A')) {
        return rl+ud+'A';
    } else if ((to=='7' || to=='4' || to=='1')&&(from =='0' || from=='A')) {
        return ud+rl+'A';
    } else {
        if (distance.y<0) return rl+ud+'A';
        else return ud+rl+'A';
    }
}
std::string getFullNumericSequence(std::string s) {
    s='A'+s;
    std::string out;
    for (int i=1;i<s.size();i++) {
        out+=getNumericKeypadSequence(s[i-1],s[i]);
    }
    return out;
}
//      +---+---+
//      | ^ | A |
//  +---+---+---+
//  | < | v | > |
//  +---+---+---+
vec2 getDirectionalPos(int a) {
    switch (a) {
        case '^':
            return {0,1};
        case '>':
            return {1,2};
        case '<':
            return {1,0};
        case 'v':
            return {1,1};
        case 'A':
            return {0,2};
        default:
            return {};
    }
}
std::unordered_map<int,std::string> dirsequences;
std::string getDirectionalKeypadSequence(int from,int to) {
    int ind=from*100+to;
    if (dirsequences.count(ind)) return dirsequences[ind];
    vec2 distance=getDirectionalPos(to)-getDirectionalPos(from);
    std::string rl=repeat(distance.y>0?'>':'<',abs(distance.y));
    std::string ud=repeat(distance.x>0?'v':'^',abs(distance.x));
    if (from=='<') {
        dirsequences[ind]=rl+ud+'A';
    } else if (to=='<') {
        dirsequences[ind]=ud+rl+'A';
    } else {
        if (distance.y<0) dirsequences[ind]=rl+ud+'A';
        else dirsequences[ind]=ud+rl+'A';
    }
    return dirsequences[ind];
}
std::unordered_map<std::string,std::vector<long>> cache;
long getDirectionalValue(std::string s,int i) {
    if (i==0) return s.size();
    if (cache.count(s)) {
        if (cache[s][i]!=-1) return cache[s][i];
    } else cache[s]=std::vector<long>(ITERATIONS+1,-1);
    long out=0;
    char start='A';
    for (char c:s) {
        out+=getDirectionalValue(getDirectionalKeypadSequence(start,c),i-1);
        start=c;
    }
    cache[s][i]=out;
    return out;
}

int main(int argc,char**argv) {
    std::ifstream file(argv[1]);
    std::string str;
    long total=0;
    while (file>>str) {
        std::string s=getFullNumericSequence(str);
        total+=(getDirectionalValue(s,ITERATIONS))*((long)stoi(str));
    }
    std::cout << total << std::endl;
    file.close();
}
