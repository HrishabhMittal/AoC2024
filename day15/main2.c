#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
int canMove(vec_vec_char grid,int i,int j,int dirn) {
    if (!validIndex(i,j,grid.len,grid.data[i].len)) return 0;
    if (grid.data[i].data[j]=='#') return 0;
    if (grid.data[i].data[j]=='.') return 1;
    if (grid.data[i].data[j]=='[') {
        if (dirn=='<') return canMove(grid,i,j-1,dirn);
        if (dirn=='>') return canMove(grid,i,j+2,dirn);
        if (dirn=='^') {
            return canMove(grid,i-1,j,dirn)&&canMove(grid,i-1,j+1,dirn);
        }
        if (dirn=='v') {
            return canMove(grid,i+1,j,dirn)&&canMove(grid,i+1,j+1,dirn);
        }
    }
    if (grid.data[i].data[j]==']') {
        if (dirn=='<') return canMove(grid,i,j-2,dirn);
        if (dirn=='>') return canMove(grid,i,j+1,dirn);
        if (dirn=='^') {
            return canMove(grid,i-1,j,dirn)&&canMove(grid,i-1,j-1,dirn);
        }
        if (dirn=='v') {
            return canMove(grid,i+1,j,dirn)&&canMove(grid,i+1,j-1,dirn);
        }
    }
    return 0;
}
void printvec_vec_char(vec_vec_char g) {
    for (int i=0;i<g.len;i++) {
        for (int j=0;j<g.data[i].len;j++) {
            printf("%c",g.data[i].data[j]);
        }
        printf("\n");
    }
}
void move(vec_vec_char grid,int i,int j,int dirn) {
    if (!validIndex(i,j,grid.len,grid.data[i].len)) {
        printf("problem");
        return;
    }
    if (grid.data[i].data[j]=='#') {
        printf("problem");
        return;
    }
    if (grid.data[i].data[j]=='.') return;
    if (grid.data[i].data[j]=='[') {
        if (dirn=='<') {
            move(grid,i,j-1,dirn);
            grid.data[i].data[j-1]='[';
            grid.data[i].data[j]=']';
            grid.data[i].data[j+1]='.';
        }
        if (dirn=='>') {
            move(grid,i,j+2,dirn);
            grid.data[i].data[j]='.';
            grid.data[i].data[j+1]='[';
            grid.data[i].data[j+2]=']';
        }
        if (dirn=='^') {
            move(grid,i-1,j,dirn);
            move(grid,i-1,j+1,dirn);
            grid.data[i].data[j]='.';
            grid.data[i].data[j+1]='.';
            grid.data[i-1].data[j]='[';
            grid.data[i-1].data[j+1]=']';
        }
        if (dirn=='v') {
            move(grid,i+1,j,dirn);
            move(grid,i+1,j+1,dirn);
            grid.data[i].data[j]='.';
            grid.data[i].data[j+1]='.';
            grid.data[i+1].data[j]='[';
            grid.data[i+1].data[j+1]=']';
        }
    }
    if (grid.data[i].data[j]==']') {
        if (dirn=='<') {
            move(grid,i,j-2,dirn);
            grid.data[i].data[j-2]='[';
            grid.data[i].data[j-1]=']';
            grid.data[i].data[j]='.';
        }
        if (dirn=='>') {
            move(grid,i,j+1,dirn);
            grid.data[i].data[j-1]='.';
            grid.data[i].data[j]='[';
            grid.data[i].data[j+1]=']';
        }
        if (dirn=='^') {
            move(grid,i-1,j,dirn);
            move(grid,i-1,j-1,dirn);
            grid.data[i].data[j]='.';
            grid.data[i].data[j-1]='.';
            grid.data[i-1].data[j-1]='[';
            grid.data[i-1].data[j]=']';
        }
        if (dirn=='v') {
            move(grid,i+1,j,dirn);
            move(grid,i+1,j-1,dirn);
            grid.data[i].data[j]='.';
            grid.data[i].data[j-1]='.';
            grid.data[i+1].data[j-1]='[';
            grid.data[i+1].data[j]=']';
        }

    }
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
            if (c=='O') {
                vec_charpush(&v,'[');
                vec_charpush(&v,']');
            } else {
                vec_charpush(&v,c);
                vec_charpush(&v,c);
            }
            j=2;
        } else {
            if (c=='@') {
                bi=i;
                bj=j;
                vec_charpush(&v,'@');
                vec_charpush(&v,'.');
            } else if (c=='O') {
                vec_charpush(&v,'[');
                vec_charpush(&v,']');
            } else {
                vec_charpush(&v,c);
                vec_charpush(&v,c);
            }
            j+=2;
        }
    }
    while ((c=fgetc(f))!=EOF) {
        if (c=='\n') continue;
        switch (c) {
            case '^':
                if (canMove(grid,bi-1,bj,c)) {
                    move(grid,bi-1,bj,c);
                    grid.data[bi-1].data[bj]='@';
                    grid.data[bi--].data[bj]='.';
                }
                break;
            case 'v':
                if (canMove(grid,bi+1,bj,c)) {
                    move(grid,bi+1,bj,c);
                    grid.data[bi+1].data[bj]='@';
                    grid.data[bi++].data[bj]='.';
                }
                break;
            case '>':
                if (canMove(grid,bi,bj+1,c)) {
                    move(grid,bi,bj+1,c);
                    grid.data[bi].data[bj+1]='@';
                    grid.data[bi].data[bj++]='.';
                }
                break;
            case '<':
                if (canMove(grid,bi,bj-1,c)) {
                    move(grid,bi,bj-1,c);
                    grid.data[bi].data[bj-1]='@';
                    grid.data[bi].data[bj--]='.';
                }
                break;
        }
    }
    printvec_vec_char(grid);
    int total=0;
    for (int i=0;i<grid.len;i++) {
        for (int j=0;j<grid.data[i].len;j++) {
            if (grid.data[i].data[j]=='[') {
                total+=i*100+j;
            }
        }
    }
    printf("%d\n",total);
}
