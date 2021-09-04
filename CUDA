%%time
%%cu
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono> 
#include <cassert>
using namespace std;
using namespace std::chrono; 

// Kernel function for inner two loop of Floyd Warshall Algorithm
__global__
void GPUInnerLoops(int V, int k, int *dis)
{
	//calculates unique thread ID in the block
	int t= (blockDim.x*blockDim.y)*threadIdx.z+(threadIdx.y*blockDim.x)+(threadIdx.x);
	//calculates unique block ID in the grid
	int b= (gridDim.x*gridDim.y)*blockIdx.z+(blockIdx.y*gridDim.x)+(blockIdx.x);
	//block size (this is redundant though)
	int T= blockDim.x*blockDim.y*blockDim.z;
	//grid size (this is redundant though)
	int B= gridDim.x*gridDim.y*gridDim.z;
	
  int tm = 0;
	/*
	 * Each cell in the matrix is assigned to a different thread. 
	 * Each thread do O(N*number of asssigned cell) computation.
	 * Assigned cells of different threads does not overlape with
	 * each other. And so no need for synchronization.
	 */
	 
    for (int i=b;i<V;i+=B)
    {
		  for(int j=t;j<V;j+=T)
		  {
			  tm = dis[i*V+k] + dis[k*V+j];
        if (tm<dis[i*V+j])
			  {
				  dis[i*V+j]=tm;
			  }
			  //dis[i*V+j] = tm*(tm < dis[i*V+j])+ dis[i*V+j]*(tm >= dis[i*V+j]);
		  }
	  }
} 
  
const int V = 4096;
  
const int INF = 65535/2;  


void FloydWarshall(int *dis)
{
		for (int k = 0; k < V; k++)  
  	{
				GPUInnerLoops<<< dim3(16,16,16),dim3(8,8,8) >>>(V, k, dis);
				cudaDeviceSynchronize();
		}
}

int main(void)
{
	
	int *dis;
  
	// Allocate Unified Memory – accessible from CPU or GPU
	cudaMallocManaged(&dis, V*V*sizeof(int));
	// initialize dis array on the host
	for (int i = 0; i < V; i++) 
	{
		for(int j = 0; j < V; j++)
		{
			
			if(j==i+1) dis[i*V+j] = 1;
			else if (i!=j) dis[i*V+j] = INF;
			else dis[i*V+j] = 0;
		}
	}
  dis[(V-1)*V+0]=1;
  auto start = high_resolution_clock::now();
  FloydWarshall(dis);
	/*for (int i = 0; i < V; i++) 
	{
		for(int j = 0; j < V; j++)
		{
      cout<<" "<<dis[i*V+j];
			//if(j>=i) 
	 		//{
        
		 		//assert( dis[i*V+j] == j-i);
			//}
			//else assert( dis[i*V+j] == INF);
		}
  cout<<endl;
  
	}*/
  // Free memory
	cudaFree(dis);
  auto end = high_resolution_clock::now();
	duration<double> s_execution = end - start;
  cout<<"Exe time(s): "<< s_execution.count()<<endl;
	return 0;
}
