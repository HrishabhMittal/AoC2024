#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Q2
typedef struct {
    int rows,cols;
    char**grid;
} grid;
void calcPA(grid g,int*perimeter,int*area,int r,int c) {
    if (g.grid[r][c]==0) return;
    (*area)++;
    char ch=g.grid[r][c];
#ifndef Q2
    g.grid[r][c]=0;
    (*perimeter)+=4;
    if (r+1<g.rows && ch==g.grid[r+1][c]) {
        (*perimeter)-=2;
    }
    if (r>0 && ch==g.grid[r-1][c]) {
        (*perimeter)-=2;
    }
    if (c>0 && ch==g.grid[r][c-1]) {
        (*perimeter)-=2;
    }
    if (c+1<g.cols && ch==g.grid[r][c+1]) {
        (*perimeter)-=2;
    }
#else
    g.grid[r][c]=1;
#endif
    if (r+1<g.rows && ch==g.grid[r+1][c]) {
        calcPA(g,perimeter,area,r+1,c);
    }
    if (r>0 && ch==g.grid[r-1][c]) {
        calcPA(g,perimeter,area,r-1,c);
    }
    if (c>0 && ch==g.grid[r][c-1]) {
        calcPA(g,perimeter,area,r,c-1);
    }
    if (c+1<g.cols && ch==g.grid[r][c+1]) {
        calcPA(g,perimeter,area,r,c+1);
    }
}
void calcSides(grid g,int* peri) {
    for (int i=-1;i<g.rows;i++) for (int j=-1;j<g.cols;j++) {
        int t=0;
        for (int k=0;k<=1;k++) for (int l=0;l<=1;l++) {
            if (i+k>=0 && i+k<g.rows && j+l>=0 && j+l<g.cols && g.grid[i+k][j+l]==1) t++; 
        }
        if (t==2) {
            if (i>=0 && i+1<g.rows && j>=0 && j+1<g.cols) {
                if ((g.grid[i][j]==g.grid[i+1][j+1])||(g.grid[i+1][j]==g.grid[i][j+1])) (*peri)+=2;
            }
        }
        if (t==1 || t==3) (*peri)++;
    }
}
void set(grid g) {
    for (int i=0;i<g.rows;i++) {
        for (int j=0;j<g.cols;j++) {
            if (g.grid[i][j]==1) g.grid[i][j]=0;
        }
    }
}
int main(int argc,char**argv) {
    if (argc!=2) return 1;
    FILE* f=fopen(argv[1],"r");
    grid g;
    int rowsize=32;
    g.grid=malloc(32*sizeof(char*));
    g.rows=0;
    while (1) {
        char* line=NULL;
        size_t size=0;
        getline(&line,&size,f);
        if (!feof(f)) {
            if (g.rows==rowsize) {
                rowsize*=2;
                g.grid=realloc(g.grid,rowsize*sizeof(char*));
            }
            g.grid[g.rows++]=line;
            g.cols=strlen(line)-1;
            line[g.cols]=0;
        } else {
            free(line);
            break;
        }
    }
    int total=0;
    for (int i=0;i<g.rows;i++) {
        for (int j=0;j<g.cols;j++) {
            if (g.grid[i][j]!=0) {
                int p=0,a=0;
                calcPA(g,&p,&a,i,j);
#ifdef Q2
                calcSides(g,&p);
                set(g);
#endif
                total+=a*p;
            }
        }
    }
    printf("%d\n",total);
}
