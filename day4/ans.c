#include <stdio.h>
#include <stdlib.h>
#define Q2
char match[]="XMAS";
#ifndef Q2
int isValid(char**data,int drows,int dcols,int x,int y,int dx,int dy) {
    for (int i=0;i<4;i++) {
        if (x>=0 && y>=0 && x<drows && y<dcols && data[x][y]==match[i]) {
            x+=dx;
            y+=dy;
        } else return 0;
    }
    return 1;
}
#else
int check(char**data,int i,int j) {
    int m=0;
    for (int k=-1;k<2;k+=2) {
        for (int l=-1;l<2;l+=2) {
            switch (data[i+k][j+l]) {
                case 'M':
                    m++;break;
                case 'S':
                    m--;break;
                default:
                    return 0;
            }
        }
    }
    return (m==0&&data[i-1][j-1]!=data[i+1][j+1]);

}
#endif
int main(int argc,char**argv) {
    FILE* f=fopen(argv[1],"r");
    char**data=malloc(64*sizeof(char*));
    int size=64,len=0;
    int collen;
    while (!feof(f)) {
        int s=32,l=0;
        char*line=malloc(s);
        while ((line[l++]=fgetc(f))!='\n'&&!feof(f)) {
            if (l==s) {
                s*=2;
                line=realloc(line,s);
            }
        }
        line[--l]=0;
        if (l!=0) {
            if (len==size) {
                size*=2;
                data=realloc(data,size*sizeof(char*));
            }
            data[len++]=line;
            collen=len;
        } else free(line);
    }
    int total=0;
#ifndef Q2
    for (int i=0;i<len;i++) {
        for (int j=0;j<collen;j++) {
            for (int k=-1;k<2;k++) {
                for (int l=-1;l<2;l++) {
                    if (k!=0 || l!=0) {
                        total+=isValid(data,len,collen,i,j,k,l);
                    }
                }
            }
        }
    }
#else
    for (int i=1;i<len-1;i++) {
        for (int j=1;j<collen-1;j++) if (data[i][j]=='A') {
            total+=check(data,i,j);
        }
    }
#endif
    printf("%d\n",total);
    return 0;
}
