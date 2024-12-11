#include <stdio.h>
#include <stdint.h>
#define true 1
#define false 0
//for some reason putting iterations to be exact gives some error idk why but kk
#define ITERATIONS 80


//real	0m0.152s
//user	0m0.151s
//sys	0m0.001s
//#define NUMBERS 100
//this is decent but i like SPEED

//real	0m0.010s
//user	0m0.007s
//sys	0m0.004s
#define NUMBERS 1000

#define Q2

#ifdef Q2
#define numberOfBlinks 75
#else
#define numberOfBlinks 25
#endif


uint64_t powof10[30];
uint64_t cache[NUMBERS][ITERATIONS];
uint64_t getnum(FILE* f) {
    uint64_t num=0;
    char c;
    while ((c=fgetc(f))!=EOF) {
        if (c>='0'&&c<='9') {
            num=num*10+(uint64_t)(c-'0');
        } else break;
    }
    return num;
}
int digits(uint64_t num) {
    if (num==0) return 1;
    int dig=0;
    while (num!=0) {
        dig++;
        num/=10;
    }
    return dig;
}
uint64_t calc(uint64_t num,int iter) {
    if (num<NUMBERS && iter>=0 && iter<ITERATIONS && cache[num][iter]!=-1) return cache[num][iter];
    uint64_t ans;
    int dig=digits(num);
    if (iter==0) ans=1;
    else if (num==0) ans=calc(1,iter-1);
    else if (dig%2) {
        ans=calc(num*2024,iter-1);
    } else {
        ans=calc(num/powof10[dig/2],iter-1)+calc(num%powof10[dig/2],iter-1);
    }
    if (num<NUMBERS && iter<ITERATIONS) cache[num][iter]=ans;
    return ans;
}
int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }
    FILE* f = fopen(argv[1], "r");
    uint64_t p=1;
    for (int i=0;i<NUMBERS;i++) {
        for (int j=0;j<ITERATIONS;j++) {
            cache[i][j]=-1;
        }
    }
    for (int i=0;i<30;i++) {
        powof10[i]=p;
        p*=10;
    }
    uint64_t total=0;
    while (true) {
        uint64_t n = getnum(f);
        if (!feof(f)) total+=calc(n,numberOfBlinks);
        else break;
    }
    printf("%zu\n",total);
    return 0;
}
