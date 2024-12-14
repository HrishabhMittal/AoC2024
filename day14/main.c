#include <stdio.h>
#include <string.h>
#define true 1
#define false 0
#define WIDTH 101
#define HEIGHT 103
#define STAGES 100
int isNum(int c) {
    if (c>='0' && c<='9') return 1;
    return 0;
}
int getnum(FILE* f,int* num) {
    int c;
    *num=-1;
    int sgn=1;
    while ((c=fgetc(f))!=EOF && !isNum(c) && c!='-');
    if (c==EOF) return c;
    if (c!='-') *num=c-'0';
    else sgn=-1,*num=0;
    while (isNum(c=fgetc(f))) {
        *num=*num*10+c-'0';
    }
    *num*=sgn;
    return c;
}
typedef struct {
    int px,py,vx,vy;
} robot;
int fract(int num,int base) {
    return (num%base+base)%base;
}
int rb[HEIGHT][WIDTH];
int main(int argc,char**argv) {
    memset(rb,0,sizeof(rb));
    FILE* f=fopen(argv[1],"r");
    int num,i=0;
    while (getnum(f,&num)!=EOF && num!=-1) {
        robot rr;
        rr.px=num;
        getnum(f,&num);
        rr.py=num;
        getnum(f,&num);
        rr.vx=num;
        getnum(f,&num);
        rr.vy=num;
//        printf("p=%d,%d:v=%d,%d\n",rr.px,rr.py,rr.vx,rr.vy);
        rr.px+=rr.vx*STAGES;
        rr.py+=rr.vy*STAGES;
        rr.px=fract(rr.px,WIDTH);
        rr.py=fract(rr.py,HEIGHT);
        rb[rr.py][rr.px]++;
    }
//    for (int i=0;i<HEIGHT;i++) {
//        for (int j=0;j<WIDTH;j++) {
//            printf("%c",rb[i][j]==0?'.':(rb[i][j]+'0'));
//        }
//        printf("\n");
//    }
    int total=1;
    for (int i=0;i<2;i++) for (int j=0;j<2;j++) {
        int num=0;
        for (int k=0;k<HEIGHT/2;k++) for (int l=0;l<WIDTH/2;l++) {
            if (rb[(HEIGHT+1)/2*i+k][(WIDTH+1)/2*j+l]!=0) {
                num+=rb[(HEIGHT+1)/2*i+k][(WIDTH+1)/2*j+l];
            }
        }
        total*=num;
    }
    printf("%d\n",total);
}
