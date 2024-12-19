#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
struct towelgroup;
std::vector<std::string> patterns;
std::vector<std::string> towels;
bool matches(std::string& p,std::string& a,int ind) {
    for (int i=0;i<a.size();i++) {
        if (i+ind<p.size()&&a[i]==p[i+ind]);
        else return false;
    }
    return true;
}
bool matchPatterns(std::vector<int>& cache,std::string pattern,int i=0) {
    if (i==pattern.size()) return true;
    if (cache[i]!=-1) return cache[i];
    cache[i]=0;
    for (int j=0;j<towels.size();j++) {
        if (matches(pattern,towels[j],i)) {
            if (matchPatterns(cache,pattern,i+towels[j].size())) {
                cache[i]=1;
                return true;
            }
        }
    }
    return cache[i];
}
int main(int argc,char**argv) {
    std::ifstream file(argv[1]);
    std::string in;
    bool end=false;
    while (file>>in) {
        if (end) patterns.push_back(in);
        else {
            if (in.back()!=',') {
                end=true;
            } else in.pop_back();
            towels.push_back(in);
        }
    }
    file.close();
    long total=0;
    for (int i=0;i<patterns.size();i++) {
        std::vector<int> cache(patterns[i].size(),-1);
        total+=matchPatterns(cache,patterns[i]);
    }
    std::cout << total << std::endl;
}

