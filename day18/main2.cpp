#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>
#define SIZE 71

std::vector<std::vector<bool>> ogfallen(SIZE,std::vector<bool>(SIZE,0));
std::vector<std::vector<bool>> fallen(SIZE,std::vector<bool>(SIZE,0));
int val(int i,int j) {
    if (i<0 || j>=SIZE) return 0;
    if (j<0 || i>=SIZE) return 1;
    if (!fallen[i][j]) return 0;
    fallen[i][j]=0;
    for (int x=-1;x<2;x++) for (int y=-1;y<2;y++) {
        if (x!=0 || y!=0) {
            if (val(x+i,y+j)) return 1;
        }
    }
    return 0;
}
int main(int argc,char**argv) {
    std::ifstream file(argv[1]);
    int ans;
    for (ans=1;file.good();ans++) {
        char c;
        int x=0,y=0;
        file>>x;
        file>>c;
        file>>y;
        ogfallen[x][y]=1;
        fallen=ogfallen;
        for (int i=0;i<SIZE-1;i++) {
            if (fallen[i][0] && val(i,0)) break;
            if (fallen[SIZE-1][i] && val(SIZE-1,i)) break;
        }
    }
    if (file.good()) std::cout << ans;
    else std::cout << "ohno" << std::endl;
    file.close();
}
