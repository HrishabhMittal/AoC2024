#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
int main(int argc,char**argv) {
    std::ifstream file(argv[1]);
    std::string s;
    int total=0;
    while (true) {
        std::getline(file,s);
        std::cout << "yay" << std::endl;
        if (file.good()) {
            std::stringstream ss;
            std::cout << "yaay" << std::endl;
            ss<<s;
            int prev,n,diff;
            ss>>prev;
            ss>>n;
            int inc=1;
            diff=prev-n;
            if (abs(diff)>3||abs(diff)<1) continue;
            prev=n;
            while (ss>>n) {
                std::cout << prev << " " << n << std::endl;
                if ((prev-n)*diff<=0||abs(prev-n)>3) {
                    inc=0;
                    break;
                }
                prev=n;
            }
            total+=inc;
        } else break;
    }
    std::cout << total << std::endl;
}
