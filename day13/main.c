#include <stdio.h>
#include <stdlib.h>
#define Q2
#define true 1
#define false 0
#define vec(type) vec_##type
#define init_vec(type) typedef struct {\
    int len,size;\
    type* data;\
} vec_##type;\
vec_##type new_vec_##type (int len) {\
    int size=1;\
    for (;size<=len;size*=2);\
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
init_vec(long)
int isNum(int ch) {
    if (ch>='0' && ch<='9') return true;
    return false;
}
int getnum(FILE* f,long* num) {
    int c;
    *num=-1;
    while ((c=fgetc(f))!=EOF && !isNum(c));
    if (c==EOF) return c;
    *num=c-'0';
    while (isNum(c=fgetc(f))) {
        *num=*num*10+c-'0';
    }
    return c;
}
long calc(long* arr) {
#ifdef Q2
    arr[4] += 10000000000000LL;
    arr[5] += 10000000000000LL;
#endif
    long delta = arr[0]*arr[3]-arr[1]*arr[2];
    long deltax = arr[4]*arr[3]-arr[5]*arr[2];
    long deltay = arr[0]*arr[5]-arr[1]*arr[4];

    if (delta==0) return 0;
    if (deltax%delta!=0 || deltay%delta!=0) return 0;
    long A = deltax/delta;
    long B = deltay/delta;
#ifndef Q2
    if (A<0 || A>100 || B<0 || B>100) return 0;
#endif
    return A*3+B;
}
int main(int argc,char**argv) {
    FILE* f=fopen(argv[1],"r");
    vec_long v=new_vec_long(128);
    long num;
    while (getnum(f,&num)!=EOF || num!=-1) {
        vec_longpush(&v,num);
    }
    long total=0;
    for (int i=0;i<v.len;i+=6) {
        total+=calc(v.data+i);
    }
    printf("%ld\n",total);
    return 0;
}
