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
    if (i<0 || j>=SIZE) return 1;
    if (j<0 || i>=SIZE) return 0;
    if (!fallen[i][j]) return 0;
    fallen[i][j]=0;
    for (int x=-1;x<2;x++) for (int y=-1;y<2;y++) {
        if (x!=0 || y!=0) {
            if (val(x+i,y+j)) {
                return 1;
            }
        }
    }
    return 0;
}
int main(int argc,char**argv) {
    std::ifstream file(argv[1]);
    int ans;
    int run=1;
    for (ans=0;file.good()&&run;ans++) {
        char c;
        int x=0,y=0;
        file>>x;
        file>>c;
        file>>y;
        ogfallen[x][y]=1;
        fallen=ogfallen;
        for (int i=0;i<SIZE-1;i++) {
            if (val(i,0)) {
                std::cout << x << "," << y << std::endl;
                run=0;
                break;
            }
            if (val(SIZE-1,i)) {
                std::cout << x << "," << y << std::endl;
                run=0;
                break;
            }
        }
    }
    file.close();
}
