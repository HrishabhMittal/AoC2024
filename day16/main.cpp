#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
//  0
//1 + 3
//  2
int valat(std::vector<std::vector<std::vector<int>>>& b,int i,int j) {
    int out=INT_MAX;
    for (int k=0;k<4;k++) {
        if (out>b[i][j][k]) out=b[i][j][k];
    }
    return out;
}
int findMin(std::vector<std::vector<std::vector<int>>>& b,std::vector<std::vector<std::vector<int>>>& cache,std::vector<std::string>& data,int i,int j,int dirn,int score) {
    if (data[i][j]=='#') return INT_MAX;
    if (score<=cache[i][j][dirn]) {
        cache[i][j][dirn]=score;
        b[i][j][dirn]=score;
        if (i==1 && j==data[1].size()-2) {
            return score;
        }
    } else return INT_MAX;
    int out=INT_MAX;
    for (int x=-1;x<2;x++) {
        for (int y=-1;y<2;y++) {
            if (x*y==0 && x!=y) {
                int n=1,nd=(x+1+(y==1)*2);
                int diff=abs(nd-dirn);
                if (diff==3 || diff==1) n+=1000;
                if (diff==2) continue;
                out=std::min(findMin(b,cache,data,i+x,j+y,nd,score+n),out);
            }
        }
    }
    b[i][j][dirn]=out;
    return out;
}
int main(int argc,char**argv) {
    std::vector<std::string> data;
    std::string line;
    std::ifstream file(argv[1]);
    while (std::getline(file,line)) {
        data.push_back(line);
    }
    file.close();
    std::vector<std::vector<std::vector<int>>> cache(data.size(),std::vector<std::vector<int>>(data[0].size(),std::vector<int>(4,INT_MAX)));
    std::vector<std::vector<std::vector<int>>> b(data.size(),std::vector<std::vector<int>>(data[0].size(),std::vector<int>(4,INT_MAX)));
    findMin(b,cache,data,data.size()-2,1,3,0);
    int total=0;
    int ans=valat(b,1,b[1].size()-2);
    for (int i=0;i<b.size();i++) {
        for (int j=0;j<b[i].size();j++) {
            //if (b[i][j]!=INT_MAX) std::cout << b[i][j];
            //else std::cout<< "INT_MAX";
            //std::cout << ",";
            if (valat(b,i,j)==ans) total++;
        }
        //std::cout << std::endl;
    }
    std::cout << ans<<std::endl;
    std::cout << total << std::endl;
}
