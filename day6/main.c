#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
#define Q2
typedef struct {
    int x,y;
} vec2;
vec2 Vec2(int x,int y) {
    vec2 out;
    out.x=x;
    out.y=y;
    return out;
}
typedef struct {
    vec2 pos;
    int facing;
} guard;
typedef struct {
    char**grid;
    vec2 dimensions;
} grid;
grid loadGrid(const char*file) {
    grid out;
    out.dimensions.x=0,out.dimensions.y=0;
    int sr=16;
    FILE* f=fopen(file,"r");
    out.grid=malloc(sizeof(char*)*sr);
    while (true) {
        char*line=NULL;size_t len=0;
        getline(&line,&len,f);
        if (!feof(f)) {
            if (sr==out.dimensions.x) {
                sr*=2;
                out.grid=realloc(out.grid,sizeof(char*)*sr);
            }
            out.grid[(out.dimensions.x)++]=line;
            out.dimensions.y=strlen(line);
            line[--(out.dimensions.y)]=0;
        } else {
            free(line);
            break;
        }
    }
    fclose(f);
    return out;
}
#ifndef Q2
#define OUT
void markplaces(grid* g,guard* gg) {
#else
grid copyGrid(grid g) {
    grid out;
    out.dimensions.x=g.dimensions.x;
    out.dimensions.y=g.dimensions.y;
    out.grid=malloc(sizeof(char*)*g.dimensions.x);
    for (int i=0;i<g.dimensions.x;i++) {
        out.grid[i]=malloc(g.dimensions.y);
        for (int j=0;j<g.dimensions.y;j++) {
            out.grid[i][j]=g.grid[i][j];
        }
    }
    return out;
}
grid ogGridCopy;
guard ogGuardCopy;
grid checkGrid;
void freeGrid(grid g) {
    for (int i=0;i<g.dimensions.x;i++) {
        free(g.grid[i]);
    }
    free(g.grid);
}
int areEqual(guard g1,guard g2) {
    if (g1.pos.x == g2.pos.x && g1.pos.y==g2.pos.y && g1.facing==g2.facing) return true;
    return false;
}
#define OUT total
int markplaces(grid* g,guard* gg,int alrPlaced) {
    grid backup;
    guard ggback;
    if (alrPlaced) ggback=*gg;
    int total=0;
#endif
    while (true) {
        switch (gg->facing) {
            case 0:
                if (gg->pos.x==0) {
                    g->grid[gg->pos.x][gg->pos.y]=0;
                    return OUT;
                }
                if (g->grid[gg->pos.x-1][gg->pos.y]!='#') {
#ifdef Q2
                    if (!alrPlaced) {
                        backup=copyGrid(ogGridCopy);
                        backup.grid[gg->pos.x-1][gg->pos.y]='#';
                        ggback=ogGuardCopy;
                        if (markplaces(&backup,&ggback,1)&&!checkGrid.grid[gg->pos.x-1][gg->pos.y]) {
                            checkGrid.grid[gg->pos.x-1][gg->pos.y]=1;
                            total++;
                        }
                        freeGrid(backup);
                    } else if (g->grid[gg->pos.x][gg->pos.y]==0) {
                        return 1;
                    }
#endif
                    g->grid[gg->pos.x--][gg->pos.y]=0;
                } else {
                    gg->facing=1;
                }
                break;
            case 1:
                if (gg->pos.y==g->dimensions.y-1) {
                    g->grid[gg->pos.x][gg->pos.y]=1;
                    return OUT;
                }
                if (g->grid[gg->pos.x][gg->pos.y+1]!='#') {
#ifdef Q2
                    if (!alrPlaced) {
                        backup=copyGrid(ogGridCopy);
                        backup.grid[gg->pos.x][gg->pos.y+1]='#';
                        ggback=ogGuardCopy;
                        if (markplaces(&backup,&ggback,1)&&!checkGrid.grid[gg->pos.x][gg->pos.y+1]) {
                            checkGrid.grid[gg->pos.x][gg->pos.y+1]=1;
                            total++;
                        }
                        freeGrid(backup);
                    } else if (g->grid[gg->pos.x][gg->pos.y]==1) {
                        return 1;
                    }
#endif
                    g->grid[gg->pos.x][gg->pos.y++]=1;
                } else {
                    gg->facing=2;
                }
                break;
            case 2:
                if (gg->pos.x==g->dimensions.x-1) {
                    g->grid[gg->pos.x][gg->pos.y]=2;
                    return OUT;
                }
                if (g->grid[gg->pos.x+1][gg->pos.y]!='#') {
#ifdef Q2
                    if (!alrPlaced) {
                        backup=copyGrid(ogGridCopy);
                        backup.grid[gg->pos.x+1][gg->pos.y]='#';
                        ggback=ogGuardCopy;
                        if (markplaces(&backup,&ggback,1)&&!checkGrid.grid[gg->pos.x+1][gg->pos.y]) {
                            checkGrid.grid[gg->pos.x+1][gg->pos.y]=1;
                            total++;
                        }
                        freeGrid(backup);
                    } else if (g->grid[gg->pos.x][gg->pos.y]==2) {
                        return 1;
                    }
#endif
                    g->grid[gg->pos.x++][gg->pos.y]=2;
                } else {
                    gg->facing=3;
                }
                break;
            case 3:
                if (gg->pos.y==0) {
                    g->grid[gg->pos.x][gg->pos.y]=3;
                    return OUT;
                }
                if (g->grid[gg->pos.x][gg->pos.y-1]!='#') {
#ifdef Q2
                    if (!alrPlaced) {
                        backup=copyGrid(ogGridCopy);
                        backup.grid[gg->pos.x][gg->pos.y-1]='#';
                        ggback=ogGuardCopy;
                        if (markplaces(&backup,&ggback,1)&&!checkGrid.grid[gg->pos.x][gg->pos.y-1]) {
                            checkGrid.grid[gg->pos.x][gg->pos.y-1]=1;
                            total++;
                        }
                        freeGrid(backup);
                    } else if (g->grid[gg->pos.x][gg->pos.y]==3) {
                        return 1;
                    }
#endif
                    g->grid[gg->pos.x][gg->pos.y--]=3;
                } else {
                    gg->facing=0;
                }
                break;
        }
    }
}
//  0
//3   1
//  2
int main(int argc,char**argv) {
    grid g=loadGrid(argv[1]);
    guard gg;
    for (int i=0;i<g.dimensions.x;i++) {
        for (int j=0;j<g.dimensions.y;j++) {
            if (g.grid[i][j]=='^') {
                gg.pos.x=i;
                gg.pos.y=j;
                gg.facing=0;
            }
        }
    }
#ifndef Q2
    int total=0;
    markplaces(&g,&gg);
    for (int i=0;i<g.dimensions.x;i++) {
        for (int j=0;j<g.dimensions.y;j++) {
            if (g.grid[i][j]<4) total++;
        }
    }
    printf("%d\n",total);
#else
    ogGuardCopy=gg;
    ogGridCopy=copyGrid(g);
    checkGrid=copyGrid(g);
    for (int i=0;i<checkGrid.dimensions.x;i++) {
        for (int j=0;j<checkGrid.dimensions.y;j++) {
            checkGrid.grid[i][j]=0;
        }
    }
    printf("%d\n",markplaces(&g,&gg,0));
#endif
}
