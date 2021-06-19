#include "graphlib.h"
#include<stdio.h>

int main(){
  int i, n, output[100];
  graph g = creategraph();
  addedge(g, 0, 1);
  addedge(g, 0, 2);
  addedge(g, 1, 2);
  addedge(g, 1, 3);
  addedge(g, 1, 5);
  addedge(g, 1, 9);
  n = incidentedges(g, 1, output);
  if (n==0) printf("No adjacent vertices of node 1\n");
  else {
    printf("Adjacent vertices of node 1:");
    for (i=0; i<n; i++) printf("%5d", output[i]);
  }
  printf("\n");

  dropgraph(g);
}
