#include <stdio.h>
#include <stdbool.h>
#include "graphlib.h"
#include <string.h>


int main(){
   //Do thi vo huong
   int sodinh,socanh;
   graph g = creategraph();
   Ver ListVer[MAX];
   Mau bangmau[MAX];
   //su dung max k+1 mau;tuc la max la so dinh tuong duong moi dinh to 1 mau
   //cho san bang mau voi 8 mau
   int countmau=8;
   for (int i = 0; i < countmau; i++)
   {
     bangmau[i].idcolor=i;
   }
   //tuy vao so dinh ta dat duoc cac gia tri cho bang mau, va dat san mau` cho tung id id se dien sau theo so dinh
   strcpy(bangmau[0].color,"red");
   strcpy(bangmau[1].color,"lightseagreen");
   strcpy(bangmau[2].color,"yellow");
   strcpy(bangmau[3].color,"brown");
   strcpy(bangmau[4].color,"green");
   strcpy(bangmau[5].color,"cyan");
   strcpy(bangmau[6].color,"whitesmoke");
   strcpy(bangmau[7].color,"blueviolet");
   //
   g=readfromfile("dothi.txt",ListVer,&sodinh,&socanh);
   sapxepbac(ListVer,sodinh);
   tomau(g,ListVer,sodinh,countmau);
   //printf("%d %d ->%d\n",ListVer[0].idVer,ListVer[1].idVer,adjacent(g,ListVer[0].idVer,ListVer[1].idVer));
   printdotfile("dothi.txt","dothitomau.dot",ListVer,bangmau,countmau);
  // dot -Tpdf dothitomau.dot -o graph.pdf
  //start prufer
   int n1; // so phan tu cua cay
   //bien luu tru gia tri canh khi nhap
   int bac[MAX]={0};
   dscanh ds1[MAX];
   readfilePrufer("pruferdata.txt",ds1,bac,&n1);
   printf("Prufercode:\n");
   prtprufercode(bac,ds1,n1+1);
   //end prufer
  dscanh mst[MAX];
  int canhmst;
  canhmst = MST(g,mst);
  prindotfilemst(mst,canhmst);
  dropgraph(g);
  return 0;
}

