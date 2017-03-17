#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <climits>	// INT_MAX
#include <ctime>	// clock

using namespace std;

int main(){
	int vertices; 	//number of vertices
	cout<<"Enter number of vertices"<<endl; 
	cin>>vertices;
	int edges;	//number of edges
	cout<<"Enter number of edges"<<endl;
	cin>>edges;
	//cout<<vertices<<" "<<edges<<endl;
	if(edges>(vertices*(vertices-1))){
		cout<<"Not possible"<<endl;
	}
	else{
		int ifConnected[vertices][vertices]; //Stores the information if 
											 //vertex[i] is connected with vertex[j]
		for (int i = 0; i < vertices; ++i)
		{
			for(int j=0;j<vertices;j++)
				ifConnected[i][j]=0;
		}
		//Stores vertex[i] is connected with which vertices and also its weight
		std::vector< pair<int,int> > vertex[vertices];
		//Connections between vertices and their weights are decided randomly
		for (int i = 0; i < edges; ++i)
		{
			int src = rand() % vertices;
			int dest = rand() % vertices;
			while(src==dest)
				dest = rand() % vertices;
			while(ifConnected[src][dest]==1){
				src = rand() % vertices;
				dest = rand() % vertices;
				while(src==dest)
					dest = rand() % vertices;
			}
			ifConnected[src][dest]=1;
			int weight = rand() % 21;
			weight-=5;

			pair<int,int> p(dest,weight);
			vertex[src].push_back(p);
		}

		cout<<"\nConnections are from: "<<endl;
		for (int i = 0; i < vertices; ++i)
		{
			cout<<"vertex "<<i<<" to "<<endl;
			for (int j = 0; j < vertex[i].size(); ++j)
			{
				cout<<vertex[i][j].first<<", weight = "<<vertex[i][j].second<<endl;
			}
			cout<<endl;
		}

		//Bellman-Ford algorithm starts

		//Setting initial distance to maximum value possible
		int dist[vertices];
		for (int i = 0; i < vertices; ++i)
		{
			dist[i] = INT_MAX/2;
		}
		dist[0]= 0;

		//Starting time of algorithm
		int startTime = clock();

		for (int i = 0; i < vertices-1; ++i)
		{
			/*
				Although below for loop looks like of O(vertices^2)
				it is O(edges) because it is only interating through
				all edges
			*/
			for(int j=0;j<vertices;j++){
				for(int k=0;k<vertex[j].size();k++){
					int dest = vertex[j][k].first;
					int weight = vertex[j][k].second;
					if(dist[j]!=INT_MAX){
						if(dist[dest]>(dist[j]+weight)){
							dist[dest] = dist[j]+weight;
						}
					}
				}
			}
		}

		bool negWtCycle = false;

		//Checking if negative-weight cycle is present or not
		for(int j=0;j<vertices;j++){
			for(int k=0;k<vertex[j].size();k++){
				int dest = vertex[j][k].first;
				int weight = vertex[j][k].second;
				if(dist[dest]>(dist[j]+weight)){
					dist[dest] = dist[j]+weight;
					negWtCycle = true;
				}
			}
		}

		int stopTime = clock();

		if(negWtCycle){
			cout<<"Negative-Weight cycle is present"<<endl;
			for (int i = 0; i < vertices; ++i)
			{
				cout<<"Vertex "<< i<<": "<<dist[i]<<endl;
			}
		}
		else{
			cout<<"Minimum distance of vertices from vertex 0 is:"<<endl;
			for (int i = 0; i < vertices; ++i)
			{
				cout<<"Vertex "<< i<<": "<<dist[i]<<endl;
			}
		}

		cout<<endl<<"Time taken (milliseconds): "<<(stopTime-startTime)/
							double(CLOCKS_PER_SEC)*1000<<endl;
	}
}
