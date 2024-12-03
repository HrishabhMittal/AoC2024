#include <stdio.h>
#define Q2
void addToTotal(int*total,FILE*f,int flag) {
    if (flag) return;
    int pos=ftell(f);
    char c;
    int i=0,j=0;
    while ((c=fgetc(f))!=',') {
        int dig=c-'0';
        if (dig>=0 && dig<=9) {
            i=i*10+dig;
        } else {
            fseek(f,pos,SEEK_SET);
            return;
        }
    }
    while ((c=fgetc(f))!=')') {
        int dig=c-'0';
        if (dig>=0 && dig<=9) {
            j=j*10+dig;
        } else {
            fseek(f,pos,SEEK_SET);
            return;
        }
    }
    *total+=i*j;
    fseek(f,pos,SEEK_SET);
}
int main(int argc,char**argv) {
    FILE*f=fopen(argv[1],"r");
    char c;
    int i=0;
    char mul[]="mul(";
    int j=0,k=0;
    char dont[]="don't()";
    char _do[]="do()";
    int flag=0;
    int total=0;
    while ((c=fgetc(f)) != EOF) {
        if (mul[i]==c) {
            if (i==sizeof(mul)-2) addToTotal(&total,f,flag),i=0;
            else i++;
        } else i=0;
#ifdef Q2
        if (dont[j]==c) {
            if (j==sizeof(dont)-2) flag=1,j=0;
            else j++;
        } else j=0;
        if (_do[k]==c) {
            if (k==sizeof(_do)-2) flag=0,k=0;
            else k++;
        } else k=0;
#endif
    }
    printf("%d\n",total);
}
