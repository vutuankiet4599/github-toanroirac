#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "weightedGraphlib.h"
#include "dllist.h"
#include <stdbool.h>

#define INFINITIVE_VALUE 10000000
#define MAX 10000

int time;
int pre[MAX], pos[MAX];

Graph createGraph(){
  Graph g = (Graph)malloc(sizeof(struct _Graph));
  if(g==NULL) {
	  printf("NULL, can not allocate mem, abort...\n");
	  return NULL;
  }
  g->vertices = make_jrb();
  g->edges = make_jrb();
  return g;
}

void addVertex(Graph graph, int id, char* name)
{
	JRB vertices  = graph->vertices;
	JRB edges  = graph->edges;
	JRB tree;
	
	//update vertex
	detailVertex iver = (detailVertex)malloc(sizeof(struct _detailVertex));
	if(iver==NULL) {
	  printf("NULL, can not allocate mem, abort...\n");
	  return;
	}
	iver->name = strdup(name);
	iver->indegreeTree = make_jrb();
	jrb_insert_int(vertices,id,new_jval_v(iver));
	
	//update edge
	tree = make_jrb();
	jrb_insert_int(edges,id,new_jval_v(tree));
}

char *getVertex(Graph graph, int id)
{
	JRB vnode=jrb_find_int(graph->vertices,id);
	
	if(vnode==NULL) return NULL;
	detailVertex iver = (detailVertex) vnode->val.v;
	
	return iver->name;
}

void addEdge(Graph graph, int v1, int v2, double wei)
{
	JRB enode = jrb_find_int(graph->edges,v1);
	JRB vnode = jrb_find_int(graph->vertices,v2);
	JRB tree;
	if((enode==NULL)||(vnode==NULL)) {
		printf("vertex not found\n");
		return;
    	}

	tree=(JRB)(enode->val).v;
	jrb_insert_int(tree,v2,new_jval_d(wei));
	
	detailVertex iver = (detailVertex) vnode->val.v;
	tree = iver->indegreeTree;
	jrb_insert_int(tree,v1,JNULL);
}

int hasEdge(Graph graph, int v1, int v2)
{
	JRB enode = jrb_find_int(graph->edges,v1);
	JRB tree;
	if(enode==NULL) {
		printf("vertex not found\n");
		return 0;
    	}
    	tree=(JRB)(enode->val).v;
	if(jrb_find_int(tree,v2)!=NULL)
		return 1;
	else return 0;
}

double getEdgeValue(Graph graph, int v1, int v2)
{
	JRB enode = jrb_find_int(graph->edges,v1);
	JRB tree;

	if(enode==NULL) {
		printf("vertex not found\n");
		return INFINITIVE_VALUE;
    	}
    
    	tree = jrb_find_int((JRB)(enode->val).v,v2);

	if(tree==NULL){
		return INFINITIVE_VALUE;
	}

    	return (tree->val).d;
}

int indegree(Graph graph, int v, int* output)
{
	JRB vnode = jrb_find_int(graph->vertices,v);
	JRB tree,node;
	int innum = 0;
	
	if(vnode==NULL) {
		printf("vertex not found\n");
		return 0;
    	}
    	detailVertex iver = (detailVertex) vnode->val.v;
	tree = iver->indegreeTree;
	//traverse tree
	jrb_traverse(node, tree){
		output[innum] = node->key.i;
		innum++;
		//printf("\nnumber innum:%d\n",output[innum-1]);
	}
	return innum;
}

int outdegree(Graph graph, int v, int* output)
{
	JRB enode = jrb_find_int(graph->edges,v);
	JRB tree,node;
	int outnum = 0;
	
	if(enode==NULL) {
		printf("vertex not found\n");
		return 0;
    	}

	tree =(JRB)(enode->val).v;
	//traverse tree
	jrb_traverse(node, tree){
		output[outnum] = node->key.i;
		outnum++;
		//printf("\nnumber innum:%d\n",output[outnum-1]);
	}
	return outnum;
}

void BFS(Graph graph, int v1, int v2, void (*func)(int))
{
   Dllist queue = new_dllist();
   Dllist tmp, node, ptr;
   Jval v;
   int count;
   bool visited[MAX];
   int adj[MAX];
   int n;

   for(int i = 0; i < MAX; i++)visited[i] = false;
   dll_append(queue, new_jval_i(v1));

   while(!dll_empty(queue))
   {
	   node = dll_first(queue);
	   v = node->val;
	   func(v.i);
	   if(v.i == v2) break;
	   dll_delete_node(node);
	   if(visited[v.i] == false){
		   
		   visited[v.i] = true;
		   n = outdegree(graph, v.i, adj);
		   
		   for(int i = 0; i < n; i++)
		   {
			   count = 0;
			   if(visited[adj[i]] == false)
			   {
				    dll_traverse(ptr, queue) {
						if(adj[i] == ptr->val.i)count++;
					}
					if(count == 0)
					dll_append(queue,new_jval_i(adj[i]));
					   
				   }
			   }
		   }
	   }
   
   printf("\n");
   
}

void DFS(Graph g, int v1, bool visited[], void (*func)(int))
{	
	int adj[MAX];
	int n;
	n = outdegree(g, v1, adj);

	func(v1);
	visited[v1] = true;

	for(int i = 0; i < n; i++)
	{
		if(visited[adj[i]] == false)
		DFS(g, adj[i], visited, func);
	}
}

void DFSfindSC(Graph g, int v1, bool visited[])
{	
	int adj[MAX];
	int n;
	n = outdegree(g, v1, adj);

	visited[v1] = true;

	for(int i = 0; i < n; i++)
	{
		if(visited[adj[i]] == false)
		DFSfindSC(g, adj[i], visited);
	}
}

void reverseDFSfindSC(Graph g, int v1, bool visited[])
{	
	int adj[MAX];
	int n;
	n = indegree(g, v1, adj);

	visited[v1] = true;
	pre[v1] = time;
	time += 1;

	for(int i = 0; i < n; i++)
	{
		if(visited[adj[i]] == false)
		reverseDFSfindSC(g, adj[i], visited);
	}

	pos[v1] = time;
	time += 1;
}

double dijikstra(Graph graph, int start, int stop, int *path, int *length){
	double total, distance[MAX];
	int min, id, i, n, neighbor, position, previous[MAX], output[MAX], temp[MAX];
	Dllist queue, shortest, node;
	
	for(i = 0; i < MAX; i++){
		distance[i] = INFINITIVE_VALUE;
	}
	
	distance[start] = 0;
	previous[start] = start;
	
	queue = new_dllist();
	dll_append(queue, new_jval_i(start));
	
	while(!dll_empty(queue)){
		
		min = INFINITIVE_VALUE;
		
		dll_traverse(node, queue){
			id = jval_i(node->val);
			if(min > distance[id]){
				min = distance[id];
				shortest = node;
			}
		}
		
		id = jval_i(shortest->val);
		dll_delete_node(shortest);
			
		if(id == stop)break;
			
		n = outdegree(graph, id, output);
		for(i = 0; i < n; i++){
			neighbor = output[i];
			if(distance[neighbor] > distance[id] + getEdgeValue(graph, id, neighbor)){
				distance[neighbor] = distance[id] + getEdgeValue(graph, id, neighbor);
				previous[neighbor] = id;
				dll_append(queue, new_jval_i(neighbor));
			}
		}
	}
	
	total = distance[stop];
	if(total != INFINITIVE_VALUE){
		temp[0] = stop;
		position = 1;
		while(stop != start){
			stop = previous[stop];
			temp[position] = stop;
			position += 1;
		}
		for(i = position - 1; i >= 0; i --){
            path[position - i - 1] = temp[i];
		}
        *length = position;
	}
	
	return total;
}

int DAG(Graph graph){
	JRB vertex;
	JRB node;
	int visited[MAX];
	Dllist queue, temp;
	int i, n, output[MAX];
	jrb_traverse(vertex, graph->vertices){
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

void topology(Graph g, void (*func)(int)){
	
	Dllist queue = new_dllist();
	Dllist node, ptr;
	int count;
	int inde[MAX] ;
	Jval v;
	int inVertex[MAX];
	JRB node1;
	int key;

	if(DAG(g) == 0)
	{
		printf("Cannot topo sort!\n");
		return;
	}

	jrb_traverse(node1, g->vertices)
	{
		key = jval_i(node1->key);
		inde[key] = indegree(g, key, inVertex);
		if(inde[key] == 0)
		{
			dll_append(queue, new_jval_i(key));
		}
	}
	
	while(!dll_empty(queue)){
	   node = dll_first(queue);
	   v = node->val;
	   dll_delete_node(node);
	   func(v.i);

	   jrb_traverse(node1, g->vertices)
	   {
	   	int id;
	   	id = jval_i(node1->key);
	   	if(hasEdge(g, v.i, id) == 1)
	   	{
	   		inde[id] = inde[id] - 1;
	   		if(inde[id] == 0)
	   		{
	   			dll_append(queue, new_jval_i(id));
	   		}
	   	}
	   }
	}
	printf("\n");
	
	free_dllist(queue);
}

int numStrongConnect(Graph g)
{
	int count = 0;
	bool visited[MAX];
	memset(pre, 0, sizeof(pre));
	memset(pos, 0, sizeof(pos));
	memset(visited, false, sizeof(visited));
	JRB node;
	int id;
	int posMax[MAX], num = 0;
	time = 1;

	jrb_traverse(node, g->vertices)
	{
		id = jval_i(node->key);
		if(visited[id] == false)
		{
			reverseDFSfindSC(g, id, visited);
		}
	}

	int temp;
	jrb_traverse(node, g->vertices)
	{
		temp = 0;
		for(int i = 0; i < MAX; i++)
		{
			if(temp < pos[i])
			{
				temp = pos[i];
				id = i;
			}
		}
		posMax[num] = id;
		num ++;
		pos[id] = 0;
	}

	memset(visited, false, sizeof(visited));
	for(int i = 0; i < num; i++)
	{
		if(visited[posMax[i]] == false)
		{
			count ++;
			DFSfindSC(g, posMax[i], visited);
		}
	}

	return count;
}

void exportDotfile(Graph g, LE list[])
{
	JRB node;
	int n, path[MAX], count;
	int nVer = 0, nEdge = 0;
	jrb_traverse(node, g->vertices)
	{
		nVer ++;
		int id;
		id = jval_i(node->key);
		n = outdegree(g, id, path);
		for(int i = 0; i < n; i++)
		{
			count = 0;
			for(int j = 0; j < nEdge; j++)
			{
				if(id == list[j].first && path[i] == list[j].last)
				{
					count++;
				}
			}

			if(count == 0)
			{
				list[nEdge].first = id;
				list[nEdge].last = path[i];
				list[nEdge].weight = getEdgeValue(g, id, path[i]);
				nEdge++;
			}
		} 
	}

	FILE *f = fopen("Graph.dot","w+");
	if(f==NULL){
    printf("cannot write\n");
    exit(1);
  }

  fprintf(f,"digraph g{\n");
  for(int i = 0; i < nEdge; i++)
  {
  	fprintf(f, "%d -> %d [label = \"%.3f\", weight = \"%.3f\"];\n",list[i].first, list[i].last, list[i].weight, list[i].weight);
  }
  fprintf(f, "}");
	fclose(f);
}

void dropGraph(Graph graph)
{
	JRB node,innode;
	detailVertex detailnode;
	
	jrb_traverse(node,graph->edges){
		jrb_free_tree((JRB)jval_v(node->val));
	}
	jrb_free_tree(graph->edges);
	
	jrb_traverse(node,graph->vertices){
		detailnode = (detailVertex) node->val.v;
		free(detailnode->name);
		jrb_free_tree((JRB)detailnode->indegreeTree);
	}
	jrb_free_tree(graph->vertices);
	
	free(graph);
}
