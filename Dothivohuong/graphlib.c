#include<stdio.h>
#include<stdlib.h>
#include"graphlib.h"
#include "string.h"

#define INFINITIVE_VALUE 10000000

graph creategraph(){
  return make_jrb();
}

void addedge(graph graph, int v1, int v2, double weight)
{
  JRB node=jrb_find_int(graph,v1);
  JRB tree;
  if(node==NULL) {
    tree=make_jrb();
    jrb_insert_int(graph,v1,new_jval_v(tree));
    jrb_insert_int(tree,v2,new_jval_d(weight));
  }
  else {tree=(JRB)(node->val).v;
    jrb_insert_int(tree,v2,new_jval_d(weight));
  }
  node=jrb_find_int(graph,v2);
  if(node==NULL) { 
    tree=make_jrb();
    jrb_insert_int(graph,v2,new_jval_v(tree));
    jrb_insert_int(tree,v1,new_jval_d(weight));
  }
  else {tree=(JRB)(node->val).v;
    jrb_insert_int(tree,v1,new_jval_d(weight));
  }
}
//tra ve 0 neu khong tim thay ,1 tim thay
int adjacent(graph graph, int v1, int v2)
{
  JRB tree,node=jrb_find_int(graph,v1);
  if(node==NULL) return 0;
  
  tree=(JRB)(node->val).v;
  if(jrb_find_int(tree,v2)==NULL) return 0;
  return 1;
}

int incidentedges(graph graph, int vertex, int* output)
{
  int num=0;
  JRB tree,node=jrb_find_int(graph,vertex);
  if(node==NULL) return 0;
  tree=(JRB)(node->val).v;
  jrb_traverse(node,tree){
    output[num++]=(node->key).i;
  }
  return num;
}

double getEdgeValue(graph graph, int v1, int v2)
{
  JRB enode = jrb_find_int(graph, v1);
  JRB tree;
  if(enode == NULL)
  {
    printf("vertex not found\n");
    return INFINITIVE_VALUE;
  }

  tree = jrb_find_int((JRB)(enode->val).v, v2);
  if(tree == NULL)
  {
    return INFINITIVE_VALUE;
  }

  return (tree->val).d;
}

void swap(dscanh a[], int i, int j)
{
  dscanh temp;
  temp = a[i];
  a[i]=a[j];
  a[j]=temp;
}

int partition(dscanh a[], int left, int right)
{
  int i = left;
  int j = right+1;
  double pivot = a[left].weight;
  while(i<j)
  {
    i = i+1;
    while(i<=right && a[i].weight<=pivot)i++;
    j=j-1;
    while(j>=left && a[j].weight>pivot)j--;
    swap(a, i, j);
  }
  swap(a, i, j);
  swap(a,j,left);
  return j;
}

void qsort2way(dscanh a[], int left, int right)
{
  int pivot;
  if(left<right)
  {
    pivot = partition(a, left, right);
    qsort2way(a, left, pivot-1);
    qsort2way(a, pivot+1, right);
  }
}


int MST(graph g, dscanh mst[])
{
  dscanh ds[MAX];
  JRB node;
  int n;
  int path[MAX];
  int socanh, count, sodinh;
  socanh = 0;
  sodinh = 0;
  //Luu graph vao ds canh theo kiet to chang`
  jrb_traverse(node, g)
  {
    sodinh++;
    int id;
    id = jval_i(node->key);
    n = incidentedges(g, id, path);
    for(int i = 0; i < n; i++)
    {
      count = 0;
      for(int j = 0; j < socanh; j++)
      {
        if ((id == ds[j].x && path[i] == ds[j].y) || (id == ds[j].y && path[i] == ds[j].x))
        {
          count++;
        }
      }

      if(count == 0)
      {
        ds[socanh].x = id;
        ds[socanh].y = path[i];
        ds[socanh].weight = getEdgeValue(g, id, path[i]);
        socanh++;
      }
    }
  }
  qsort2way(ds, 0, socanh - 1);
//MST 
  int d[MAX], k;
  int dem = 0;
  double weight = 0;
  k = 0;

  for(int i = 0; i < sodinh; i++)d[i] = -i;
  for(int i = 0; i < socanh; i++)
  {
    if(d[ds[i].x] != d[ds[i].y])
    {
      mst[dem++] = ds[i];
      weight = weight + ds[i].weight;
      if(d[ds[i].x] < 0 && d[ds[i].y] < 0)
      {
        k++;
        d[ds[i].x] = k;
        d[ds[i].y] = k;
      }else if( d[ds[i].x] > 0 && d[ds[i].y] > 0)
      {
        int x = d[ds[i].y];
        for(int j = 0; j < sodinh; j++)
        {
          if(d[j] == x) d[j] = d[ds[i].x];
        }
      }else
      {
        int a;
        a = d[ds[i].x] > d[ds[i].y] ? d[ds[i].x] : d[ds[i].y];
        d[ds[i].x] = a;
        d[ds[i].y] = a;
      }
    }
  }

  return dem;
}

void dropgraph(graph graph)
{
  JRB node;
  jrb_traverse(node,graph){
    jrb_free_tree((JRB)jval_v(node->val));
  }
  jrb_free_tree(graph);
}
//prufercode
void printVertex(int key)
{
  printf("%4d", key);
}
void prtprufercode(int *bac,dscanh *ds1,int n){
  int i,k;
  if(bac[0]==0)return;
  else{
    for ( i = 1; i < n; i++)
    {
      //printf("a[%d]=%d ",i,bac[i]);
      if(bac[i]==1){
        for ( k = 0; k < n-1; k++)
        {
          if (ds1[k].x==i){
            int z;
            z=ds1[k].y;
            if(z==0 && (bac[z]-1)==0)return;// khong in ra so 0 o cuoi cung
          	printf("%d",ds1[k].y);
          	ds1[k].x=-1;
            ds1[k].y=-1;
            bac[z]--;
            bac[i]--;
            break;
		  }
          if (ds1[k].y==i){
             int z;
             z=ds1[k].x;
             if(z==0 && (bac[z]-1)==0)return;// khong in ra so 0 o cuoi cungs
          	printf("%d",ds1[k].x);
           
          	ds1[k].x=-1;
            ds1[k].y=-1;
            bac[z]--;
            bac[i]--;
            break;
		  }
            //printf("canh %d %d",i,k);
        }
        break;
      }
    }
  }
  prtprufercode(bac,ds1,n);
}
graph readfromfile(char *filename,Ver ListVer[],int *sodinh,int *socanh){
  graph g=creategraph();
  int output[50];
  FILE *f=fopen(filename,"r");
  if(f==NULL){
    printf("Loi mo file!");
    exit(1);
  }
  fscanf(f,"%d %d\n",sodinh,socanh);
  int i,canh1,canh2;
  double weight;
  for ( i = 0; i < *socanh; i++)
  {
    fscanf(f,"%d %d %lf\n",&canh1,&canh2,&weight);
    //printf("check edge:%d--%d\n",canh1,canh2);
    addedge(g,canh1,canh2,weight);
    if(i==*socanh-1){
    fscanf(f,"%d %d %lf",&canh1,&canh2,&weight);
     //  printf("check edge:%d--%d\n",canh1,canh2);
    addedge(g,canh1,canh2,weight);
  }
  }
  for ( i = 0; i < *sodinh; i++)
  {
    ListVer[i].idVer=i+1;//tu danh so dinh bat dau bang 1
    ListVer[i].Bac=incidentedges(g,i+1,output);
  }
  
  fclose(f);
  return g;
}
void sapxepbac(Ver ListVer[],int sodinh){
  int i,j;
  for ( i = 0; i < sodinh; i++)
  {
    for (j=i+1; j < sodinh; j++)
    {
      if(ListVer[i].Bac<ListVer[j].Bac){
        Ver tmp=ListVer[i];
        ListVer[i]=ListVer[j];
        ListVer[j]=tmp;
      }
    }
  }
}
void tomau(graph g,Ver ListVer[],int sodinh,int countmau){
  ListVer[0].colorVer=0;
  int i,j,colorOfVer;
  int checkmau[countmau];
  for ( i = 1; i < sodinh; i++)
  {
    memset(checkmau,0,sizeof(int)*countmau);//0 la chua danh ,1 la danh roi
    for(j=0;j<i;j++){
        if(adjacent(g,ListVer[i].idVer,ListVer[j].idVer)){
          
            colorOfVer=ListVer[j].colorVer;
            checkmau[colorOfVer]=1;
        }
    }
    for (j = 0; j < countmau; j++)
    { 
      if(checkmau[j]==0){
        ListVer[i].colorVer=j;
        break;
      }
    }
  }
}
char *getnamecolor(Mau mau[],int countmau,int idmau){
  int i;
  for ( i = 0; i < countmau; i++)
  {
      if(mau[i].idcolor==idmau)return mau[i].color;
  }
  
}
void printdotfile(char *datafile,char *filenamedot,Ver ListVer[],Mau bangmau[],int countmau){
  
  FILE *f=fopen(filenamedot,"w+");
  if(f==NULL){
    printf("cannot write");
    exit(1);
  }
  FILE *f2=fopen(datafile,"r");
  if(f2==NULL){
    printf("Loi mo file!");
    exit(1);
  }
  int sodinh,socanh;
  fscanf(f2,"%d %d\n",&sodinh,&socanh);
  int i;
  fprintf(f,"graph dothi{\n");
  for ( i = 0; i < sodinh; i++)
  {
    fprintf(f,"%d [fillcolor=%s, style=filled];\n",ListVer[i].idVer,getnamecolor(bangmau,countmau,ListVer[i].colorVer));
  }
  
  int canh1,canh2;
  double weight;
  for ( i = 0; i < socanh; i++)
  {
    fscanf(f2,"%d %d %lf\n",&canh1,&canh2,&weight);
    //printf("check edge:%d--%d\n",canh1,canh2);
    fprintf(f,"%d--%d [label=\"%.2lf\"]\n",canh1,canh2,weight);
  }if(i==1){
    fscanf(f2,"%d %d %lf",&canh1,&canh2,&weight);
    fprintf(f,"%d--%d [label=\"%.2lf\"]\n",canh1,canh2,weight);
     //  printf("check edge:%d--%d\n",canh1,canh2);
  }
  fprintf(f,"}");

  fclose(f);
  fclose(f2);

}
void readfilePrufer(char *filename,dscanh ds1[],int bac[],int *n){

  
  FILE *f=fopen(filename,"r");
  if(f==NULL){
    printf("Error open file data file prufercode");
    exit(1);
  }
   fscanf(f,"%d\n",n);
  int x,y,i;
  for ( i = 0; i < *n; i++)
  {
    fscanf(f,"%d %d",&x,&y);
    if(i!=*n-1)fscanf(f,"\n");
    ds1[i].x=x;
    ds1[i].y=y;
    bac[x]++;
    bac[y]++;
  }

}
void prindotfilemst(dscanh *mst,int canhmst){
  FILE *f=fopen("graphMST.dot","w+");
  if(f==NULL){
    printf("cannot write");
    exit(1);
  }
  fprintf(f,"Graph MST{\n");
  for(int i = 0; i < canhmst; i++)
  {
    fprintf(f,"%d--%d [label=\"%.2lf\"]\n", mst[i].x, mst[i].y, mst[i].weight);
  }
  fprintf(f,"}");
  fclose(f);
}