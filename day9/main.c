#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Q2
int calcIndex(const char* disk,int index) {
    int out=0;
    for (int i=0;i<index;i++) {
        out+=disk[i]-'0';
    }
    return out;
}
int main(int argc,char**argv) {
    FILE* f=fopen(argv[1],"r");
    char* line=NULL;size_t length=0;
    getline(&line,&length,f);
    int len=strlen(line);
    line[--len]=0;
    size_t total=0;
#ifdef Q2
    char* linecopy=malloc(len);
    strcpy(linecopy,line);
    for (int i=len-1;i>=0;i-=2) {
        int flag=1;
        for (int j=1;j<i;j+=2) {
            if (line[j]>=line[i]) {
                int ind=calcIndex(linecopy,j);
                ind+=linecopy[j]-line[j];
                printf("shifting %d to index %d\n",i/2,ind);
                for (int k=0;k<line[i]-'0';k++) {
                    total+=(ind+k)*(i/2);
                }
                line[j]-=line[i]-'0';
                flag=0;
                break;
            }
        }
        if (flag) {
            int ind=calcIndex(linecopy,i);
            ind+=linecopy[i]-line[i];
            printf("%d remains at %d\n",i/2,ind);
            for (int j=0;j<line[i]-'0';j++) {
                total+=(ind+j)*(i/2);
            }
        }
    }
#else
    int val=len/2;
    int index=0;
    for (int i=0;i<len;i++) {
        while (line[i]!='0') {
            if (i%2==0) {
                total+=index*(i/2);
            } else {
                if (line[len-1]=='0') len-=2;
                total+=index*((len-1)/2);
                line[len-1]--;
            }
            line[i]--;
            index++;
        }
    }
#endif
    printf("%zu\n",total);
}
