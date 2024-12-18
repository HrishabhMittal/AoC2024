#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>
#define SIZE 71
#define BYTES 1024
std::vector<std::vector<int>> area(SIZE,std::vector<int>(SIZE,INT_MAX));
std::vector<std::vector<bool>> visited(SIZE,std::vector<bool>(SIZE,0));
void mark(int i,int j,int val) {
    if (i<0 || j<0 || i>=SIZE || j>=SIZE) return;
    if (visited[i][j]) return;
    area[i][j]=area[i][j]>val?val:area[i][j];
}
void path(int i,int j) {
    if (i<0 || j<0 || i>=SIZE || j>=SIZE) return;
    if (visited[i][j]) return;
    visited[i][j]=1;
    mark(i-1,j,area[i][j]+1);
    mark(i+1,j,area[i][j]+1);
    mark(i,j+1,area[i][j]+1);
    mark(i,j-1,area[i][j]+1);
    int min=INT_MAX,minx=-1,miny=-1;
    for (int i=0;i<SIZE;i++) {
        for (int j=0;j<SIZE;j++) if (!visited[i][j]) {
            if (area[i][j]<min) {
                min=area[i][j];
                minx=i,miny=j;
            }
        }
    }
    path(minx,miny);
}
int main(int argc,char**argv) {
    std::ifstream file(argv[1]);
    for (int i=0;i<BYTES;i++) {
        char c;
        int x=0,y=0;
        file>>x;
        file>>c;
        file>>y;
        visited[x][y]=1;
    }
    mark(0,0,0);
    path(0,0);
    file.close();
    std::cout << area[SIZE-1][SIZE-1] << std::endl;
}
