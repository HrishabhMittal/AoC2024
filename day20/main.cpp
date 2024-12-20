#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#define Q2
std::vector<std::vector<int>> data;
std::vector<std::vector<bool>> visited; 
void mark(int i,int j,int val) {
    if (i<0 || j<0 || i>=data.size() || j>=data[0].size()) return;
    if (visited[i][j]) return;
    data[i][j]=data[i][j]>val?val:data[i][j];
}
void path(int i,int j) {
    if (i<0 || j<0 || i>=data.size() || j>=data[0].size()) return;
    if (visited[i][j]) return;
    visited[i][j]=1;
    mark(i-1,j,data[i][j]+1);
    mark(i+1,j,data[i][j]+1);
    mark(i,j+1,data[i][j]+1);
    mark(i,j-1,data[i][j]+1);
    int min=INT_MAX,minx=-1,miny=-1;
    for (int i=0;i<data.size();i++) {
        for (int j=0;j<data[0].size();j++) if (!visited[i][j]) {
            if (data[i][j]<min) {
                min=data[i][j];
                minx=i,miny=j;
            }
        }
    }
    path(minx,miny);
}
int distanceAt(int i,int j) {
    if (i<0 || j<0 || i>=data.size() || j>=data[0].size()) return INT_MAX;
    return data[i][j];
}
void findShortCuts(int& total,int posx,int posy,int threshold,int shortcut=2) {
    for (int i=-shortcut;i<=shortcut;i++) {
        for (int j=abs(i)-shortcut;j<=shortcut-abs(i);j++) {
            int dist=abs(i)+abs(j);
            if (distanceAt(posx+i,posy+j)!=INT_MAX && data[posx][posy]-distanceAt(posx+i,posy+j)-dist>=threshold) total++;
        }
    }
}
int main(int argc,char**argv) {
    int startx,starty;
    int endx,endy;
    std::ifstream file(argv[1]); {
        std::string fullline;
        while (file>>fullline) {
            std::vector<int> line;
            std::vector<bool> bline;
            for (char c:fullline) {
                if (c=='S') {
                    startx=data.size();
                    starty=line.size();
                } else if (c=='E') {
                    endx=data.size();
                    endy=line.size();
                }
                line.push_back(INT_MAX);
                bline.push_back(c=='#'?1:0);
            }
            data.push_back(line);
            visited.push_back(bline);
        }
    } file.close();
    mark(endx,endy,0);
    path(endx,endy);
    int total=0;
    for (int i=0;i<data.size();i++) for (int j=0;j<data[0].size();j++) if (visited[i][j] && data[i][j]!=INT_MAX) {
        findShortCuts(total,i,j,100,
#ifndef Q2
                2
#else
                20
#endif
        );
    }
    std::cout << total << std::endl;
}
