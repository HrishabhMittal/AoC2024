#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;
#define SWAP(a,b) { typeof(a) temp=a;a=b;b=temp; }
#define ABS(a) (a>0?a:-a)
vector<int> l;
unordered_map<int,int> r;
int main(int argc,char**argv) {
    int num;
    ifstream file(argv[1]);
    while (file>>num) {
        l.push_back(num);
        cout << "adding" << num << "to l" << endl;
        file>>num;
        if (r.count(num)) r[num]++;
        else r[num]=1;
        cout << "adding" << num << "now" << r[num] << endl;
    }
    file.close();
    int total=0;
    for (int i=0;i<l.size();i++) {
        if (r.count(l[i])) {
            total+=r[l[i]]*l[i];
            cout << r[l[i]] << " " << l[i] << endl;
        }
    }
    cout << "total" << total << endl;
}
