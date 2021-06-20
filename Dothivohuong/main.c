#include <stdio.h>
#include <stdbool.h>
#include "graphlib.h"
#include <string.h>
void printVertex(int key)
{
  printf("%4d", key);
}

int main(){
 //  //Do thi vo huong
 //  int sodinh,socanh;
 //  graph g2 = creategraph();
 //  Ver ListVer[50];
 //  Mau bangmau[20];
 //  //su dung max k+1 mau;tuc la max la so dinh tuong duong moi dinh to 1 mau
 //  //cho san bang mau voi 8 mau
 //  int countmau=8;
 //  bangmau[0].idcolor=0;
 //  bangmau[1].idcolor=1;
 //  bangmau[2].idcolor=2;
 //  bangmau[3].idcolor=3;
 //  bangmau[4].idcolor=4;
 //  bangmau[5].idcolor=5;
 //  bangmau[6].idcolor=6;
 //  bangmau[7].idcolor=7;
 //  //tuy vao so dinh ta dat duoc cac gia tri cho bang mau, va dat san mau` cho tung id id se dien sau theo so dinh
 //  strcpy(bangmau[0].color,"red");
 //  strcpy(bangmau[1].color,"lightseagreen");
 //  strcpy(bangmau[2].color,"yellow");
 //  strcpy(bangmau[3].color,"brown");
 //  strcpy(bangmau[4].color,"green");
 //  strcpy(bangmau[5].color,"cyan");
 //  strcpy(bangmau[6].color,"whitesmoke");
 //  strcpy(bangmau[7].color,"blueviolet");
 //  g2=readfromfile("dothi.txt",ListVer,&sodinh,&socanh);
 //  sapxepbac(ListVer,sodinh);
 //  tomau(g2,ListVer,sodinh,countmau);
 //  //printf("%d %d ->%d\n",ListVer[0].idVer,ListVer[1].idVer,adjacent(g,ListVer[0].idVer,ListVer[1].idVer));
 //  printdotfile("dothi.txt","dothitomau.dot",ListVer,bangmau,countmau);
 // // dot -Tpdf dothitomau.dot -o graph.pdf
 //  dropgraph(g2);
 //  int n1; // so phan tu cua cay
 //  //bien luu tru gia tri canh khi nhap
 //  int bac[MAX]={0};
 //  dscanh ds1[MAX];
 //  readfilePrufer("pruferdata.txt",ds1,bac,&n1);
 //  printf("Prufercode:\n");
 //  prtprufercode(bac,ds1,n1+1);

  graph g = creategraph();
  addedge(g, 0, 1, 1.2);
  addedge(g, 0, 2, 1.1);
  addedge(g, 1, 2, 1.5);
  // printf("%lf\n", getEdgeValue(g, 1, 2));
  dscanh ds[MAX], mst[MAX];
  int canhmst;
  canhmst = MST(g, ds, mst);
  printf("So canh: %d\n", canhmst);
  for(int i = 0; i < canhmst; i++)
  {
    printf("%d %d %lf\n", mst[i].x, mst[i].y, mst[i].weight);
  }
  dropgraph(g);
  return 0;
}

