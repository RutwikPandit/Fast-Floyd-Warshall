#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono> 
#include <cassert>
using namespace std;
using namespace std::chrono; 

const int V = 4;
  
const int INF = 65535/2;  

  
void InnerLoops (int DP_FW[][V],int k)  
{  	
	int tm = 0;
	for (int i = 0; i < V; i++)  
	{  
		for (int j = 0; j < V; j++)  
		{  	
			tm=DP_FW[i][k]+DP_FW[k][j];
			if( tm<DP_FW[i][j] ){
				DP_FW[i][j]=tm;
			}
			//DP_FW[i][j] = tm*(tm < DP_FW[i][j])+ DP_FW[i][j]*(tm >= DP_FW[i][j]);  
		}  
		/*tm=DP_FW[i][k]+DP_FW[k][j];
		//DP_FW[i][j]= min(DP_FW[i][j],tm);
		DP_FW[i][j] = tm*(tm < DP_FW[i][j])+ DP_FW[i][j]*(tm >= DP_FW[i][j]); 
		*/ 
	}    
}  

void FloydWarshall(int DP_FW[][V])
{
		for (int k = 0; k < V; k++)  
		{  
				InnerLoops(DP_FW,k);
		}
}

int DP_FW[V][V]={ 	{ 0,1,INF,5 },	
					{ 1,0,3,1 }, 
					{ INF,1,0,INF },
					{ INF,INF,1,0 }
				};

//int DP_FW[V][V];

int main()  
{   
	//Input -> read from a file
	//Data -> graph matrix nxn -> use malloc or just normal declare
	//Create a FW function -> pass graph
	//Finally check your result

    
  	/*for (int i = 0; i < V; i++) 
	{
		for(int j = 0; j < V; j++)
		{
			if(j==i+1) DP_FW[i][j] = 1;
			else if (i!=j) DP_FW[i][j] = INF;
			else DP_FW[i][j] = 0;
			//cout<<" "<<dis[i][j];
		}
		//cout<<endl;
	}
	DP_FW[V-1][0]=1;*/
	

	/*DP_FW[V][V]={ 	{ 0,1,INF,5 },	
					{ 1,0,3,1 }, 
					{ INF,1,0,INF },
					{ INF,INF,1,0 }
				};*/
	

	auto start = high_resolution_clock::now();
	
	FloydWarshall(DP_FW);

	auto end = high_resolution_clock::now();

  	for (int i = 0; i < V; i++) 
	{
		for(int j = 0; j < V; j++)
		{
			cout<<" "<<DP_FW[i][j];
			//if(j>=i) assert(dis[i][j] == j-i);
			//else assert(dis[i][j] == INF);
		}
		cout<<endl;
	}
	
	duration<double> s_execution = end - start;
    cout<<"Exe time(s): "<< s_execution.count()<<endl;
  return 0;  
}
