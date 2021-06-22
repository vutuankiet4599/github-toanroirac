#ifndef weightedGraphlib_h
#define weightedGraphlib_h
#endif

#define INFINITIVE_VALUE 10000000
#define MAX 10000

#include "jrb.h"
#include <stdbool.h>

typedef struct _detailVertex{
	char *name;
	JRB indegreeTree;
} *detailVertex;


typedef struct _Graph{
	JRB edges;
	JRB vertices;
} *Graph;

typedef struct listEdge{
	int first;
	int last;
	double weight;
}LE;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
void BFS(Graph graph, int v1, int v2, void (*func)(int));
void DFS(Graph g, int v1, bool visited[], void (*func)(int));
void DFSfindSC(Graph g, int v1, bool visited[]);
void reverseDFSfindSC(Graph g, int v1, bool visited[]);
double dijikstra(Graph graph, int start, int stop, int *path, int *length);
int DAG(Graph graph);
void topology(Graph g, void (*func)(int));
int numStrongConnect(Graph g);
void exportDotfile(Graph g, LE list[]);
void dropGraph(Graph graph);