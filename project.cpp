#include<iostream>
using namespace std;

class Edge
{
public:
	int source,dest,weight;
};
class Graph
{
public:
	int Vertices ,Edges;
	Edge *edge;
};
Graph* create_graph(int V,int E)
{
	Graph *graph=new Graph();
	graph->Vertices=V;
	graph->Edges=E;
	graph->edge =new Edge[E];
	for(int i=0;i<E;i++)
	{
	cout<<"Enter the value of source , destination and weight"<<endl;
	cin>>graph->edge[i].source;
	cin>>graph->edge[i].dest;
	cin>>graph->edge[i].weight;

	}	
	return graph;
}
// Comparing two edges according to their weights nd sorting using qsort() func.
  
int compare(const void* a,const void* b)
{
	Edge* a1=(Edge*)a;
	Edge* b1=(Edge*)b;
	return a1->weight >b1->weight;

}
class Makeset{
public:
	int parent;
	int rank;


};
int find_parent(Makeset subsets[],int i)
{
	//finding root and making it as parent (implementing path compression)
	if(subsets[i].parent !=i)
		subsets[i].parent =find_parent(subsets,subsets[i].parent);
	return subsets[i].parent;
}
void Union(Makeset subsets[],int Source_parent,int Dest_parent)
{
	//implementing union operation by rank
	int sourceRoot = find_parent(subsets,Source_parent);
	int destRoot=find_parent(subsets,Dest_parent);
	if(subsets[sourceRoot].rank==subsets[destRoot].rank)
	{
		subsets[destRoot].parent=sourceRoot;
		subsets[sourceRoot].rank++;
	}
	else if(subsets[sourceRoot].rank < subsets[destRoot].rank)
	{
		subsets[sourceRoot].parent=destRoot;
	}
	else if(subsets[sourceRoot].rank > subsets[destRoot].rank)
	{
		subsets[destRoot].parent=sourceRoot;
	}
}
void KruskalAlgoForMST(Graph* graph)
{
	int V =graph->Vertices;
	int E=graph->Edges;
	Edge output[V];
	int e=0;
	int i=0;
	int v;
	//Now  sorting the edges of graph in incresing order of wweight

	qsort(graph->edge,E,sizeof(graph->edge[0]),compare);
	//Alocating memory for makeset
	Makeset *subsets = new Makeset[(V*sizeof(Makeset))];
	for( v=0; v < V; v++)
	{
		subsets[v].parent=v;
		subsets[v].rank=0;
	}
	while(e < V-1 && i < E)
	{
		Edge current_edge=graph->edge[i++];
		int Source_parent=find_parent(subsets,current_edge.source);
		int Dest_parent=find_parent(subsets,current_edge.dest);

		 if(Source_parent!=Dest_parent)
		 {
		 	output[e++]=current_edge;
		 	Union(subsets,Source_parent,Dest_parent);
		 }

	}
	//Printing the MST stored in output
	 cout<<"Following are the edges in the constructed MST\n"<<endl;  
	 for(i=0 ; i < e ; i++)
	 {
	 	cout<<"S = "<<output[i].source<<"  "<<"D = "<<output[i].dest<<"    "<<"W == "<<output[i].weight<<endl;
	 }


	
}

int main()
{
	int E,V;//E=no of edges and V=no of vertices
	cout<<"Enter the number of vertices and edges"<<endl;
	cin>>V>>E;
	Graph* graph=create_graph(V,E);
	KruskalAlgoForMST(graph);


	

	return 0;
}