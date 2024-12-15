#include <stdio.h>
#include <stdlib.h>
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
init_vec(char)
init_vec(vec_char);
int validIndex(int i,int j,int w,int h) {
    if (i>=0 && j>=0 && i<w && j<h) return 1;
    return 0;
}
int main(int argc,char**argv) {
    FILE* f=fopen(argv[1],"r");
    char c;
    vec_char v=new_vec_char(16);
    vec_vec_char grid=new_vec_vec_char(16);
    int i=0,j=0,bi=0,bj=0;
    while ((c=fgetc(f))!=EOF) {
        if (c=='\n') {
            i++;
            vec_vec_charpush(&grid,v);
            if ((c=fgetc(f))=='\n') {
                break;
            }
            v=new_vec_char(16);
            vec_charpush(&v,c);
            j=1;
        } else {
            if (c=='@') {
                bi=i;
                bj=j;
            }
            vec_charpush(&v,c);
            j++;
        }
    }
    printf("%d,%d\n",grid.len,grid.data[0].len);
    while ((c=fgetc(f))!=EOF) {
        if (c=='\n') continue;
        printf("%d,%d,%c\n",bi,bj,c);
        i=bi,j=bj;
        int canmove=0;
        switch (c) {
            case '^':
                i--;
                while (i>0) {
    printf("^here %d,%d\n",i,j);
                    if (grid.data[i].data[j]=='#') {
                        canmove=0;
                        break;
                    }
                    if (grid.data[i].data[j]=='.') {
                        canmove=1;
                        break;
                    }
                    i--;
                }
                if (canmove) {
                    grid.data[i].data[j]=grid.data[bi-1].data[bj];
                    grid.data[bi-1].data[bj]='@';
                    grid.data[bi--].data[bj]='.';
                }
                break;
            case 'v':
                i++;
                while (i<grid.len) {
                    if (grid.data[i].data[j]=='#') {
                        canmove=0;
                        break;
                    }
                    if (grid.data[i].data[j]=='.') {
                        canmove=1;
                        break;
                    }
    printf("vhere %d,%d\n",i,j);
                    i++;
                }
                if (canmove) {
                    grid.data[i].data[j]=grid.data[bi+1].data[bj];
                    grid.data[bi+1].data[bj]='#';
                    grid.data[bi++].data[bj]='.';
                }
                break;
            case '>':
                j++;
                while (j<grid.data[i].len) {
    printf(">here %d,%d\n",i,j);
                    if (grid.data[i].data[j]=='#') {
                        canmove=0;
                        break;
                    }
                    if (grid.data[i].data[j]=='.') {
                        canmove=1;
                        break;
                    }
                    j++;
                }
                if (canmove) {
                    grid.data[i].data[j]=grid.data[bi].data[bj+1];
                    grid.data[bi].data[bj+1]='#';
                    grid.data[bi].data[bj++]='.';
                }
                break;
            case '<':
                j--;
                while (j>0) {
    printf("<here %d,%d\n",i,j);
                    if (grid.data[i].data[j]=='#') {
                        canmove=0;
                        break;
                    }
                    if (grid.data[i].data[j]=='.') {
                        canmove=1;
                        break;
                    }
                    j--;
                }
                if (canmove) {
                    grid.data[i].data[j]=grid.data[bi].data[bj-1];
                    grid.data[bi].data[bj-1]='#';
                    grid.data[bi].data[bj--]='.';
                }
                break;
        }
    }
    int total=0;
    for (int i=0;i<grid.len;i++) {
        for (int j=0;j<grid.data[i].len;j++) {
            if (grid.data[i].data[j]=='O') {
                total+=i*100+j;
            }
        }
    }
    printf("%d\n",total);
}
