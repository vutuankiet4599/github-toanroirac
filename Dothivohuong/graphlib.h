#ifndef graphlib_h
#define graphlib_h
#include"jrb.h"

#define MAX 10000
#define INFINITIVE_VALUE 10000000
typedef JRB graph;

typedef struct bangmau{
  char color[50];
  int idcolor;
}Mau;

typedef struct Vertice
{
  int colorVer;
  int idVer;
  int Bac;
}Ver;//dung cho bai 2

typedef struct dscanh
{
    int x;
    int y;
    double weight;
}dscanh;//dung cho bai 1

graph creategraph();
void addedge(graph graph, int v1, int v2, double weight);
int adjacent(graph graph, int v1, int v2);
int incidentedges(graph graph, int vertex, int* output); 
double getEdgeValue(graph graph, int v1, int v2);
int MST(graph g,dscanh mst[]);
void dropgraph(graph graph);
void printdotfileTomau(char *datafile,char *filenamedot,Ver ListVer[],Mau bangmau[],int countmau);
char *getnamecolor(Mau mau[],int countmau,int idmau);
void tomau(graph g,Ver ListVer[],int sodinh,int countmau);
void sapxepbac(Ver ListVer[],int sodinh);
graph readfromfile(char *filename,Ver ListVer[],int *sodinh,int *socanh);
void prtprufercode(int *bac,dscanh *ds1,int n);
void readfilePrufer(char *filename,dscanh ds1[],int bac[],int *n);
void printVertex(int key);
void prindotfilemst(dscanh *mst,int canhmst);
#endif
