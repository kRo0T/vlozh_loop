#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

void mat_prod_ijk(int **a, int **b, int **c, int n, int o[3])
{
	int ind[3], i,j,k;	
	for (ind[o[0]] = 0; ind[o[0]] < n; ind[o[0]]++)
	    for (ind[o[1]] = 0; ind[o[1]] < n; ind[o[1]]++)
		    for (ind[o[2]] = 0; ind[o[2]] < n; ind[o[2]]++)
			    c[ind[0]][ind[1]] = c[ind[0]][ind[1]] + a[ind[0]][ind[2]] * b[ind[2]][ind[1]];				
}

void mat_prod_block_test(int **a, int **b, int **c, int n, int o[3], int sb)
{
	int ib, jb,i,j,k,kb, m;
	m = n / sb;
	for (ib=1; ib <= sb; ib++)
		for (i=(ib-1)*m; i < ib*m; i++)
			
					for (kb=1; kb <= sb; kb++)
						for (k=(kb-1)*m; k < kb*m; k++)
							for (jb=1; jb <= sb; jb++)
				for (j=(jb-1)*m; j < jb*m; j++)
							c[i][j] = c[i][j] + a[i][k]*b[k][j];
	return;
}

void mat_prod_block_test_2(int **a, int **b, int **c, int n, int o[3], int sb)
{
	int ib, jb,i,j,k,kb, m;
	m = n / sb;
	for (ib=1; ib <= sb; ib++)
		for (jb=1; jb <= sb; jb++)
			for (kb=1; kb <= sb; kb++)
		for (i=(ib-1)*m; i < ib*m; i++)
			
				
					
						for (k=(kb-1)*m; k < kb*m; k++)
							for (j=(jb-1)*m; j < jb*m; j++)
							c[i][j] = c[i][j] + a[i][k]*b[k][j];
	return;
}

void mat_clean(int **c, int n)
{
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		c[i][j] = 0;
}
void mat_print(int **a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}


int main()
{
	srand(time(NULL));
	int n,i,j,k, block_size;
	cin >> n >> block_size;
	int **a, **b, **c;
	int order[3];
	a = new int*[n];
	b = new int*[n];
	c = new int*[n];
	for (i = 0; i < n; i++)
	{
		a[i] = new int[n];
		b[i] = new int[n];
		c[i] = new int[n];
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			a[i][j] = rand() % 100 - 10;
			b[i][j] = rand() % 100 - 10;
			c[i][j] = 0;
		}
	}
	/*
	for (order[0] = 0; order[0] < 3; order[0]++)
		for (order[1] = 0; order[1] < 3; order[1]++)
		    for (order[2] = 0; order[2] < 3; order[2]++)
		    {
				if (order[0] != order[1] && order[0] != order[2] && order[1] != order[2])
				{
					clock_t begin_time = clock();
					mat_prod_ijk(a, b, c, n, order);
					cout << order[0] << " " << order[1] << " " << order[2] << ": ";
					cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
					mat_clean(c, n);
				}
	        }
			*/
	order[0]=0; order[1]=1; order[2]=2;
	clock_t begin_time = clock();
	mat_prod_block_test(a,b,c,n,order, block_size);
	cout << order[0] << " " << order[1] << " " << order[2] << ": ";
	cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
	mat_clean(c,n);

	begin_time = clock();
	mat_prod_block_test_2(a,b,c,n,order, block_size);
	cout << order[0] << " " << order[1] << " " << order[2] << ": ";
	cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
	mat_clean(c,n);


	


    for (i = 0; i < n; i++)
	{
			delete [] a[i];
			delete [] b[i];
			delete [] c[i];
	}
	delete[] a;
	delete[] b;
	delete[] c;

	return 0;
}