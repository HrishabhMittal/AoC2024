#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define Q2
#define vec(type) vec_##type

#define init_vec(type) typedef struct {\
    size_t len,size;\
    type* data;\
} vec_##type;\
vec_##type new_vec_##type (size_t len) {\
    size_t size=1;\
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
init_vec(size_t);
size_t concat(size_t a,size_t b) {
    size_t c;
    for (c=(size_t)1;c<=b;c*=(size_t)10);
    return a*c+b;
}
size_t fgetnum(FILE* f,size_t* num) {
    char c;
    size_t out=0;
    while ((c=fgetc(f))!=EOF) {
        if (c>='0' && c<='9') out=out*10+(size_t)(c-'0');
        else break;
    }
    *num=out;
    return c;
}
size_t isPossible(size_t res,vec_size_t v,size_t cur,size_t pos) {
    if (pos==v.len) {
        return res==cur?1:0;
    } else {
        size_t x=cur*v.data[pos];
        size_t y=cur+v.data[pos];
        if (cur>res) return 0;
        if (isPossible(res,v,x,pos+1)) return 1;
        if (isPossible(res,v,y,pos+1)) return 1;
#ifdef Q2
        size_t z=concat(cur,v.data[pos]);
        if (isPossible(res,v,z,pos+1)) return 1;
#endif
        return 0;
    }
}
int main(int argc,char**argv) {
    FILE* f=fopen(argv[1],"r");
    size_t total=0;
    while (true) {
        vec_size_t v=new_vec_size_t(16);
        size_t num,numm;
        if (fgetnum(f,&num)!=(size_t)':') break;
        fgetc(f);
        while (fgetnum(f,&numm)!=(size_t)'\n') {
            vec_size_tpush(&v,numm);
        }
        vec_size_tpush(&v,numm);
//        printf("%zu: ",num);
//        for (int i=0;i<v.len;i++) {
//            printf("%zu ",v.data[i]);
//        }
//        printf("\n");
        total+=isPossible(num,v,v.data[0],1)*num;
        vec_size_tfree(v);
    }
    printf("%zu\n",total);
}
