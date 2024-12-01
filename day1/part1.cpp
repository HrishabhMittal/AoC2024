#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
using namespace std;
#define SWAP(a,b) { typeof(a) temp=a;a=b;b=temp; }
#define ABS(a) (a>0?a:-a)
vector<int> r,l;
void sort(vector<int>& vec) {
    int i=1;
    while (i<vec.size()) {
        if (vec[i]>=vec[i-1]) i++;
        else {
            SWAP(vec[i],vec[i-1]);
            i--;
        }
    }
}
int main(int argc,char**argv) {
    int num;
    ifstream file(argv[1]);
    while (file.good()) {
        file>>num;
        l.push_back(num);
        file>>num;
        r.push_back(num);
    }
    file.close();
    sort(l);
    sort(r);
    int total=0;
    for (int i=0;i<l.size();i++) {
        total+= ABS((l[i]-r[i]));
    }
    cout << total << endl;
}
