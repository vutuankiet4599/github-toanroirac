#include "weightedGraphlib.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
void printVertex(int key)
{
  printf("%4d", key);
}

int main(){
  int i, n, output[1000];
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

  printf("Topology sort:\n");
  topology(g, printVertex);
  printf("\n\n");

  int num;

  num = numStrongConnect(g);
  printf("Number of strongly connected components: %d\n\n", num);

  printf("Export file dot\n");

  exportDotfile(g);
 
  return 0;
}
