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
	int ib, jb,i,j,k,kb, m, ind[3];
	m = n / sb;
	for (ib=1; ib <= sb; ib++)
		for (jb=1; jb <= sb; jb++)
			for (kb=1; kb <= sb; kb++)
		        for (ind[o[0]]=(ib-1)*m; ind[o[0]] < ib*m; ind[o[0]]++)
			    	for (ind[o[1]]=(kb-1)*m; ind[o[1]] < kb*m; ind[o[1]]++)
						for (ind[o[2]]=(jb-1)*m; ind[o[2]] < jb*m; ind[o[2]]++)
							c[ind[0]][ind[1]] = c[ind[0]][ind[1]] + a[ind[0]][ind[2]] * b[ind[2]][ind[1]];
	return;
}

void mat_prod_4d(int ****a, int ****b, int ****c, int n_blocks, int block_size, int o[3])
{
	int i, j, ib, jb, k;
	//int o[3] = { 0, 2, 1 };
	
	
	for (ib = 0; ib < n_blocks; ib++)
	for (k = 0; k < n_blocks; k++)
	for (jb = 0; jb < n_blocks; jb++)
	mat_prod_ijk(a[ib][k], b[k][jb], c[ib][jb], block_size, o);
}

void mat_clean(int **c, int n)
{
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		c[i][j] = 0;
}

void mat_clean4d(int ****c, int block_size, int n_blocks)
{
	for (int ib=0; ib<n_blocks; ib++)
		for (int jb=0; jb<n_blocks; jb++)
			for (int i=0; i<block_size; i++)
				for (int j=0; j<block_size; j++)
					c[ib][jb][i][j] = 0;
}

void mat_print_2d(int **a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}

void mat_print_4d(int ****a, int n_blocks, int block_size)
{
	for (int ib = 0; ib < n_blocks; ib++)
	{
		for (int i = 0; i < block_size; i++)
		{
			for (int jb = 0; jb < n_blocks; jb++)
			{
				for (int j = 0; j < block_size; j++)
				{
					cout << a[ib][jb][i][j] << " ";
				}
			}
			cout << endl;
		}
	}
}


int main()
{
	srand(time(NULL));
	int n,i,j,k,l, block_size;
	cin >> n >> block_size;
	int **a, **b, **c;
	int ****a_bl, ****b_bl, ****c_bl;
	int n_blocks = n / block_size;
	int order[3] = { 0, 2, 1 };
	a = new int*[n];
	b = new int*[n];
	c = new int*[n];
	a_bl = new int***[n_blocks];
	b_bl = new int***[n_blocks];
	c_bl = new int***[n_blocks];
	for (i = 0; i < n; i++)
	{
		a[i] = new int[n];
		b[i] = new int[n];
		c[i] = new int[n];
	}

	for (i = 0; i < n_blocks; i++)
	{
		a_bl[i] = new int**[n_blocks];
		b_bl[i] = new int**[n_blocks];
		c_bl[i] = new int**[n_blocks];
		for (j = 0; j < n_blocks; j++)
		{
			a_bl[i][j] = new int*[block_size];
			b_bl[i][j] = new int*[block_size];
			c_bl[i][j] = new int*[block_size];
			for (k = 0; k < block_size; k++)
			{
				a_bl[i][j][k] = new int[block_size];
				b_bl[i][j][k] = new int[block_size];
				c_bl[i][j][k] = new int[block_size];
				for (l = 0; l < block_size; l++)
				{
					a_bl[i][j][k][l] = rand() % 100 - 10;
					b_bl[i][j][k][l] = rand() % 100 - 10;
					c_bl[i][j][k][l] = 0;
					a[i*block_size + k][j*block_size + l] = a_bl[i][j][k][l];
					b[i*block_size + k][j*block_size + l] = b_bl[i][j][k][l];
					c[i*block_size + k][j*block_size + l] = 0;
				}
			}
		}
	}

	
	for (order[0] = 0; order[0] < 3; order[0]++)
		for (order[1] = 0; order[1] < 3; order[1]++)
		{
		    for (order[2] = 0; order[2] < 3; order[2]++)
		    {
				if (order[0] != order[1] && order[0] != order[2] && order[1] != order[2])
				{
					clock_t begin_time = clock();
					mat_prod_ijk(a, b, c, n, order);
					cout << "2d simple:   " << order[0] << " " << order[1] << " " << order[2] << ": ";
					cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
					mat_clean(c, n);

					begin_time = clock();
					mat_prod_4d(a_bl, b_bl, c_bl, n_blocks, block_size, order);
					cout << "4d block:    " << order[0] << " " << order[1] << " " << order[2] << ": ";
					cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
					mat_clean4d(c_bl, block_size, n_blocks);

					begin_time = clock();
					mat_prod_block_test_2(a,b,c,n,order,block_size);
					cout << "2d block:   " << order[0] << " " << order[1] << " " << order[2] << ": ";
					cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
					mat_clean(c, n);
					
				}
	        }
			cout << endl;
		}
			
	

	


	for (i = 0; i < n_blocks; i++)
	{
		for (j = 0; j < n_blocks; j++)
		{
			for (k = 0; k < block_size; k++)
			{
				delete [] a_bl[i][j][k];
				delete [] b_bl[i][j][k];
				delete [] c_bl[i][j][k];
			}
			delete[] a_bl[i][j];
			delete[] b_bl[i][j];
			delete[] c_bl[i][j];
		}
		delete[] a_bl[i];
		delete[] b_bl[i];
		delete[] c_bl[i];
	}
	delete[] a_bl;
	delete[] b_bl;
	delete[] c_bl;

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