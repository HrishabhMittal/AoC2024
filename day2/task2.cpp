#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
void printvec(std::vector<int>& diffs) {
    std::cout << "{";
    for (int i=0;i<diffs.size();i++) {
        std::cout << diffs[i] << ", ";
    }
    std::cout << "} " << std::endl;
}

int eval(std::vector<int> diffs,int index=-1) {
    if (index!=-1) {
        if (index!=0&&index!=(int)diffs.size()) diffs[index-1]+=diffs[index];
        for (int i=index;i<diffs.size()-1;i++) {
            diffs[i]=diffs[i+1];
        }
        diffs.pop_back();
    }
    printvec(diffs);
    for (int i=1;i<diffs.size();i++) {
        if (diffs[i-1]*diffs[i]<=0 || abs(diffs[i-1])>3 || abs(diffs[i-1])<0 || abs(diffs[i])>3 || abs(diffs[i])<0) {
            return 0;
        }
    }
    return 1;
}
int main(int argc,char**argv) {
    std::ifstream file(argv[1]);
    std::string s;
    int total=0;
    while (true) {
        std::getline(file,s);
        if (file.good()) {
            std::stringstream ss;
            std::vector<int> diffs;
            ss<<s;
            int prev,n,diff;
            ss>>prev;
            ss>>n;
            diffs.push_back(prev-n);
            prev=n;
            while (ss>>n) {
                diffs.push_back(prev-n);
                prev=n;
            }
            for (int i=-1;i<=(int)diffs.size();i++) {
                if (eval(diffs,i)) {
                    total++;
                    break;
                }
            }
        } else break;
    }
    std::cout << total << std::endl;
}
