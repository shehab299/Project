#include <iostream>
#include<stdlib.h>


using namespace std;



class Percolation
{
    private:
    	int N;
        int* mat;
        int* size;
        int* OPEN;
        int n_open = 0;

        int getIndex(int i , int j);



        //Quick union methods

        int root(int index);
        void Union(int x, int y);
        bool connected(int x , int y);



    public:
    	Percolation(int N);
    	void open(int i , int j);
    	bool isOpen(int i , int j);
    	bool percolates();
    	void Display();
    	int numberOfOpenSites();
    	
    	

};


Percolation::Percolation(int N)
{
	this -> N = N;
	int l = N * N;
	this -> mat = new int[l];
	this -> size =  new int[l];
	this -> OPEN = new int[l];


	for(int i = 0 ; i < l ; i++)
	{
		mat[i] = i;
		size[i] = 1;
		OPEN[i] = 0;
	}
}

//private methods


int Percolation::root(int index)
{
    while(mat[index] != index)
        {
            index = mat[index];
        }
        return index;
        

}



int Percolation::getIndex(int row , int column)
{
    row--;
    column--;
    return row * N + column;
}



void Percolation:: Union(int x , int y)
{
    int i = root(x);
    int j = root(y);
            
    if(i == j) return ;
            
         
    if(size[i] > size[j])
    {
        mat[j] = i;
        size[i] += size[j];
    }
    else 
    {
        mat[i] = j;
        size[j] += size[i];
    }            

}



//public methods


int Percolation::numberOfOpenSites()
{
	return n_open;
}



void Percolation:: open(int i , int j)
{
	int index = getIndex(i,j);

	if(OPEN[index] == 1)
		return;

	int ind[4];

	int k;
	int arr[2] = {1,-1};
	for(int c = 0 ; c < 2;  c++)
	{
		k = getIndex(i+arr[c],j);
		if(0 <= k && k < N*N)
			ind[c] = k;
		else 
			ind[c] = -1;
	}

	for(int c = 0 ; c < 2 ; c++)
	{
		k = getIndex(i,j+arr[c]);
		if(0 <= k && k < N*N)
			ind[2+c] = k;
		else
			ind[2+c] = -1;
	}

	for(int i = 0 ; i < 4 ; i++)
		if(!(ind[i] == -1))
			if(OPEN[ind[i]])
			    Union(index,ind[i]);

	OPEN[index] = 1;
	n_open++;
}

    
        


bool Percolation::isOpen(int i , int j)
{
	int index = getIndex( i , j);
	return OPEN[index] == 1;
}


bool Percolation:: percolates()
{
    int l = N*N;
    for(int i = 0 ; i < N ; i++)
        for(int j = l-1 ; j >= l-1-N ; j--)
        if(connected(i,j))
            return true;
    return false;
}



bool Percolation::connected(int x , int y)
{
	return root(x) == root(y);
}

void Percolation::Display() {
    for(int i = 0 ; i < N*N ; i++){
        cout << mat[i] << " ";
        if((i+1) % N == 0)
            cout << endl;
    }
    
     cout << "\n\n\n" ;
     
     
     for(int i = 0 ; i < N*N ; i++){
         cout << OPEN[i] << " ";
         if((i+1) % N == 0)
             cout << endl;
     }

}




class PercolationStats
{

private:
	int N;
	int trials;
	double* results;

public:
	PercolationStats(int N , int trials);
	double mean();

};



PercolationStats::PercolationStats(int N , int trials)
{
	this -> N = N;
	this -> trials = trials;
	this -> results = new double[trials];

	for(int i = 0 ; i < trials ; i++)
	{
		int x , y;
		Percolation trial(N);

		while(!trial.percolates()){

		x = rand() %  (N+1);
		y = rand() %  (N+1);

 
		while(x <= 0 || x > N || y <= 0 || x > N)
		{
		    x = rand() % (N+1);
		    y = rand() % (N+1);			
		}
		trial.open(x, y);
	   }
	   
	   trial.numberOfOpenSites() / double(N*N)<< endl;
	}
}


double PercolationStats::mean()
{
	double sum = 0;
	for(int i = 0 ; i < trials ; i++)
		sum += results[i];
	return sum / trials;
}


int main()
{
	PercolationStats simulation(100,100);
	cout << simulation.mean();
}