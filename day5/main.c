#include <stdio.h>
#include <stdlib.h>
//#define Q2
// simple vectors
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
//END
int getnum(FILE*f,int*num) {
    int out=0;
    char c;
    while ((c=fgetc(f))!=EOF) {
        int dig=c-'0';
        if (dig>=0&&dig<=9) {
            out=out*10+dig;
        } else break;
    }
    *num = out;
    return c;
}
init_vec(int)
init_vec(vec_int)
int getIndexOf(vec(int) v,int n) {
    for (int i=0;i<v.len;i++) {
        if (v.data[i]==n) return i;
    }
    return -1;
}
int main(int argc,char**argv) {
    vec(int) llist=new_vec_int(31);
    vec(vec_int) rlist=new_vec_vec_int(31);
    FILE* f=fopen(argv[1],"r");
    int num,getch;
    int pn;
    while ((getch=getnum(f,&num))!=EOF) {
        if (getch=='\n'&&num==0) break;
        if (getch=='|') {
            pn=num; 
        } else {
            int index=getIndexOf(llist,pn);
            if (index==-1) {
                vec_intpush(&llist,pn);
                vec_vec_intpush(&rlist,new_vec_int(7));
                vec_intpush(&rlist.data[rlist.len-1],num);
            } else {
                vec_intpush(&rlist.data[index],num);
            }
        }
    }
    int total=0;
    int flag=true;
    while (flag) {
        vec(int) line=new_vec_int(31);
        while ((getch=getnum(f,&num))!='\n') {
            vec_intpush(&line,num);
        }
        vec_intpush(&line,num);
#ifndef Q2
        int add=line.data[line.len/2];
#endif
        if ((getch=fgetc(f))==EOF) {
            flag=false;
        } else {
          fseek(f,-1,SEEK_CUR);
        }
        int bool=0;
        for (int i=line.len-1;i>=0;i--) {
            for (int j=0;j<i;j++) {
                int ind=getIndexOf(llist,line.data[i]);
                if (ind==-1) break;
                if (getIndexOf(rlist.data[ind],line.data[j])!=-1) {
#ifndef Q2
                    add=0;
                    goto done;
#else
                    int temp=line.data[j];
                    line.data[j]=line.data[i];
                    line.data[i]=temp;
                    j=-1;
                    bool=1;
#endif
                }
            }
        }
#ifndef Q2
        done:
            total+=add;
#else
        if (bool) total+=line.data[line.len/2];
#endif
        vec_intfree(line);
    }
    printf("%d\n",total);
    fclose(f);
}
