#include "weightedGraphlib.h"
#include <stdio.h>
#include <stdbool.h>
#include "graphlib.h"
#include <string.h>
void printVertex(int key)
{
  printf("%4d", key);
}

int main(){
  int i, n, output[100];
  Graph g = createGraph();
  char s1[] = "station 1";
  char s2[] = "station 2";
  char s3[] = "station 3";
  char s4[] = "station 4";
  char s5[] = "station 5";
  char s6[] = "station 6";
  char s7[] = "station 7";

  addVertex(g,1,s1);
  addVertex(g,2,s2);
  addVertex(g,3,s3);
  addVertex(g,4,s4);
  addVertex(g,5,s5);
  addVertex(g,6,s6);
  addVertex(g,7,s7);

  addEdge(g,1,2,1.2);
  addEdge(g,1,3,3.4);
  addEdge(g,2,4,1.9);
  addEdge(g,3,5,2.4);
  addEdge(g,5,7,0.7);
  addEdge(g,2,6,6.0);

  printf("BFS:\n");
  BFS(g, 1, -1, printVertex);
  printf("\n");

  printf("DFS:\n");
  bool visited[1000];
  for(int i = 0; i < 1000; i++)
  {
    visited[i] = false;
  }
  DFS(g, 1, visited, printVertex);
  printf("\n\n");

  printf("Shortest path from 1 to 5:\n");
  double total;
  int length;
  int path[1000];
  total = dijikstra(g, 1, 5, path, &length);
  for(int i = 0; i < length; i++)
  {
    printf("%4d", path[i]);
  }
  printf("\n\n");
  printf("total = %f\n", total);
  printf("\n");
  //kiem tra DAG
  if(DAG(g)){
      printf("Topo sort:\n");
      topology(g, printVertex);
      printf("\n");
  }else printf("Khong co sap xep topology");
  dropGraph(g);
  //Do thi vo huong
  int sodinh,socanh;
  graph g2 = creategraph();
  Ver ListVer[50];
  Mau bangmau[20];
  //su dung max k+1 mau;tuc la max la so dinh tuong duong moi dinh to 1 mau
  //cho san bang mau voi 8 mau
  int countmau=8;
  bangmau[0].idcolor=0;
  bangmau[1].idcolor=1;
  bangmau[2].idcolor=2;
  bangmau[3].idcolor=3;
  bangmau[4].idcolor=4;
  bangmau[5].idcolor=5;
  bangmau[6].idcolor=6;
  bangmau[7].idcolor=7;
  //tuy vao so dinh ta dat duoc cac gia tri cho bang mau, va dat san mau` cho tung id id se dien sau theo so dinh
  strcpy(bangmau[0].color,"red");
  strcpy(bangmau[1].color,"lightseagreen");
  strcpy(bangmau[2].color,"yellow");
  strcpy(bangmau[3].color,"brown");
  strcpy(bangmau[4].color,"green");
  strcpy(bangmau[5].color,"cyan");
  strcpy(bangmau[6].color,"whitesmoke");
  strcpy(bangmau[7].color,"blueviolet");
  g2=readfromfile("dothi.txt",ListVer,&sodinh,&socanh);
  sapxepbac(ListVer,sodinh);
  tomau(g2,ListVer,sodinh,countmau);
  //printf("%d %d ->%d\n",ListVer[0].idVer,ListVer[1].idVer,adjacent(g,ListVer[0].idVer,ListVer[1].idVer));
  printdotfile("dothi.txt","dothitomau.dot",ListVer,bangmau,countmau);
 // dot -Tpdf dothitomau.dot -o graph.pdf
  dropgraph(g2);
  int n1; // so phan tu cua cay
  //bien luu tru gia tri canh khi nhap
  int bac[MAX]={0};
  dscanh ds1[MAX];
  readfilePrufer("pruferdata.txt",ds1,bac,&n1);
  printf("Prufercode:\n");
  prtprufercode(bac,ds1,n1+1);
  return 0;
}
