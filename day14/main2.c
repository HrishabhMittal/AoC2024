#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
#define WIDTH 101
#define HEIGHT 103
#define STAGES 100
#define vec(type) vec_##type
#define init_vec(type) typedef struct {\
    int len,size;\
    type* data;\
} vec_##type;\
vec_##type new_vec_##type (int len) {\
    int size=1;\
    for (;size<len;size*=2);\
    vec_##type out;\
    out.len = 0;\
    out.size = size;\
    out.data = malloc(size*sizeof(type));\
    return out;\
}\
void vec_##type##push(vec_##type* v, type e) {\
    if (v->size==v->len) {\
        v->size*=2;\
        v->data=realloc(v->data,v->size*sizeof(type));\
    }\
    v->data[v->len++]=e;\
}\
void vec_##type##free(vec_##type v) {\
    free(v.data);\
}
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
init_vec(robot);
int fract(int num,int base) {
    return (num%base+base)%base;
}
void display(int rb[HEIGHT][WIDTH]) {
    for (int i=0;i<HEIGHT;i++) {
        for (int j=0;j<WIDTH;j++) {
            printf("%c",rb[i][j]==0?'.':(rb[i][j]+'0'));
        }
        printf("\n");
    }
}
void advance(vec_robot r) {
    for (int i=0;i<r.len;i++) {
        r.data[i].px+=r.data[i].vx;
        r.data[i].py+=r.data[i].vy;
        r.data[i].px=fract(r.data[i].px,WIDTH);
        r.data[i].py=fract(r.data[i].py,HEIGHT);
    }
}
void update(int rb[HEIGHT][WIDTH],int l,vec_robot r) {
    memset(rb,0,l);
    for (int i=0;i<r.len;i++) {
        rb[r.data[i].py][r.data[i].px]++;
    }
}
int findPool(int rb[HEIGHT][WIDTH],int i,int j) {
    if (i<0 || i>=HEIGHT || j<0 || j>=WIDTH || rb[i][j]==0) return 0;
    rb[i][j]=0;
    int total=1;
    total+=findPool(rb,i-1,j);
    total+=findPool(rb,i+1,j);
    total+=findPool(rb,i,j-1);
    total+=findPool(rb,i,j+1);
    return total;
}
int rb[HEIGHT][WIDTH];
int findGrouping(int rb[HEIGHT][WIDTH]) {
    for (int i=0;i<HEIGHT;i++) {
        for (int j=0;j<WIDTH;j++) {
            if (rb[i][j]!=0 && findPool(rb,i,j)>30) return 1; 
        }
    }
    return 0;
}
int main(int argc,char**argv) {
    memset(rb,0,sizeof(rb));
    FILE* f=fopen(argv[1],"r");
    vec_robot r=new_vec_robot(64);
    int num;
    while (getnum(f,&num)!=EOF && num!=-1) {
        robot rr;
        rr.px=num;
        getnum(f,&num);
        rr.py=num;
        getnum(f,&num);
        rr.vx=num;
        getnum(f,&num);
        rr.vy=num;
        vec_robotpush(&r,rr);
    }
    for (int i=1;i<=10000;i++) {
        advance(r);
        update(rb,sizeof(rb),r);
        if (findGrouping(rb)) printf("%d\n",i);
    }
}
