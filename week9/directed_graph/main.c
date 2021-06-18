#include "directedGraphlib.h"
#include <stdio.h>
#include <string.h>

void printVertex(int val){
	printf("%4d", val);
}

void DFS(Graph graph, int v, int color[], void (*func)(int)){
	
	int nout;
	color[v] = 0;
	func(v);
	for(int i = 0; i < 6; i++){
		if(hasEdge(graph, v, i)){
			if(color[i] == 1){
				DFS(graph, i, color, func);
			}
		}
	}
	color[v] = -1;
	
}

int DAG(Graph graph){
	JRB vertex;
	JRB node;
	int visited[1000];
	Dllist queue, temp;
	int i, n, ouput[100];
	jrb_traverse(vertex, graph.vertices){
		memset(visited, 0, sizeof(visited));
		queue = new_dllist();
        dll_append(queue, vertex->key);
        
        while(!dll_empty(queue)){
			temp = dll_first(queue);
            int value = jval_i(temp->val);
            dll_delete_node(temp);
            if(visited[value] == 0){
				visited[value] = 1;
				n = outdegree(graph, value, output);
				int outkey;
				for(i = 0; i < n; i++){
					outkey = output[i];
					if(outkey == jval_i(vertex->key)){
						free_dllist(queue);
						return 0;
					}
					
					if(visited[outkey] == 0){
						dll_append(queue, new_jval_i(outkey));
					}
				}
			}
		}
		free_dllist(queue);
	}
	return 1;
}

int main(){
  int i, n, output[100];
  Graph g = createGraph();
  int color[6] ;
  for(int i = 0; i < 6; i++)color[i] = 1;  
  char s1[] = "station 1";
  char s2[] = "station 2";
  char s3[] = "station 3";
  char s4[] = "station 4";
  char s5[] = "station 5";
  char s6[] = "station 6";
  //printf("\n%s\n",s);
  addVertex(g,0,s1);
  addVertex(g,1,s2);
  addVertex(g,2,s3);
  addVertex(g,3,s4);
  addVertex(g,4,s5);
  addVertex(g,5,s6);
  //char *out = getVertex(g,1);
  //printf("\nname of v1: %s\n",out);
  addEdge(g,0,1);
  addEdge(g,1,2);
  addEdge(g,0,3);
  addEdge(g,2,3);
  addEdge(g,3,5);
  addEdge(g,5,4);
  DFS(g, 1, color, printVertex);


  /*
  if(hasEdge(g,1,2)==1)
	printf("\nv1 v2 has edge\n");
  else
	printf("\nv1 v2 has no edge\n");
  
  int innum = indegree(g,2,output);
  printf("\nindegree of v2: \n");
  for(i=0;i<innum;i++)
  {
	  printf(" %d ",output[i]);
  }
  
  int outnum = outdegree(g,2,output);
  printf("\noutdegree of v2: \n");
  for(i=0;i<outnum;i++)
  {
	  printf(" %d ",output[i]);
  }

  innum = indegree(g,1,output);
  printf("\nindegree of v1: \n");
  for(i=0;i<innum;i++)
  {
	  printf(" %d ",output[i]);
  }

  outnum = outdegree(g,1,output);
  printf("\noutdegree of v1: \n");
  for(i=0;i<outnum;i++)
  {
	  printf(" %d ",output[i]);
  }
  printf("\n");
  */
  printf("\n");
  dropGraph(g);
}
