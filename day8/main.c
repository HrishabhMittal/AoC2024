#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
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
typedef struct {
    int x,y;
}pos;
pos Pos(int x, int y) {
    pos out;
    out.x=x;
    out.y=y;
    return out;
}
init_vec(int)
init_vec(pos)
init_vec(vec_pos);
int indexOf(vec_int v,int ind) {
    for (int i=0;i<v.len;i++) {
        if (v.data[i]==ind) return i;
    }
    return -1;
}
int posEqual(pos x,pos y) {
    return (x.x==y.x)&&(x.y==y.y);
}
int posindexOf(vec_pos vp,pos ind) {
    for (int i=0;i<vp.len;i++) {
        if (posEqual(vp.data[i],ind)) {
            return i;
        }
    }
    return -1;
}
int main(int argc,char**argv) {
    vec_vec_pos coords=new_vec_vec_pos(16);
    vec_int indices=new_vec_int(16);
    vec_pos posn=new_vec_pos(16);
    pos dimensions;
    FILE* f=fopen(argv[1],"r");
    int row=0;
    while (true) {
        char*line=NULL;
        size_t cols;
        getline(&line,&cols,f);
        if (!feof(f)) {
            int i;
            for (i=0;line[i]!=0;i++) {
                if (line[i]!='.' && line[i]!='\n') {
                    int ind=indexOf(indices,line[i]);
                    if (ind==-1) {
                        ind=indices.len;
                        vec_intpush(&indices,line[i]);
                        vec_vec_pospush(&coords,new_vec_pos(8));
                    }
                    vec_pospush(&coords.data[ind],Pos(row,i));
                }
            }
            dimensions.y=i-1;
        } else {
            free(line);
            break;
        }
        row++;
    }
    dimensions.x=row;
//    for (int i=0;i<coords.len;i++) {
//        printf("%c: ",indices.data[i]);
//        for (int j=0;j<coords.data[i].len;j++) {
//            printf("{%d,%d} ",coords.data[i].data[j].x,coords.data[i].data[j].y);
//        }
//        printf("\n");
//    }
//    printf("dimensions: %dx%d\n",dimensions.x,dimensions.y);
    for (int i=0;i<coords.len;i++) {
        for (int j=0;j<coords.data[i].len;j++) {
            for (int k=j+1;k<coords.data[i].len;k++) {
                pos a=coords.data[i].data[j],b=coords.data[i].data[k];
#ifdef Q2
                pos inc=Pos(a.x-b.x,a.y-b.y);
                while (true) {
                    if (a.x<0 || a.x>=dimensions.x || a.y<0 || a.y>=dimensions.y) break;
                    else {
                        if (posindexOf(posn,a)==-1) {
                            vec_pospush(&posn,a);
                        }
                        a=Pos(a.x+inc.x,a.y+inc.y);
                    }
                }
                while (true) {
                    if (b.x<0 || b.x>=dimensions.x || b.y<0 || b.y>=dimensions.y) break;
                    else {
                        if (posindexOf(posn,b)==-1) {
                            vec_pospush(&posn,b);
                        }
                        b=Pos(b.x-inc.x,b.y-inc.y);
                    }
                }
#else
                pos c=a;
                a.x+=a.x-b.x;
                a.y+=a.y-b.y;
                b.x+=b.x-c.x;
                b.y+=b.y-c.y;
                if (a.x<0 || a.x>=dimensions.x || a.y<0 || a.y>=dimensions.y) {
                } else {
                    if (posindexOf(posn,a)==-1) {
                        vec_pospush(&posn,a);
                    }
                }
                if (b.x<0 || b.x>=dimensions.x || b.y<0 || b.y>=dimensions.y) {
                }
                else {
                    if (posindexOf(posn,b)==-1) {
                        vec_pospush(&posn,b);
                    } 
                }
#endif
            }
        }
    }
    printf("%d\n",posn.len);
}
