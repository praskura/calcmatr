#include "StdAfx.h"
#include "MatrixLib.h"
#include <malloc.h>
#include <cstdlib>

#define NULL 0

using namespace System;
//инициализация матрицы
bool InitMatrix(TMatrix *t, int m, int n)
{
	t->matrix = (double *)malloc(m*n*sizeof(double)*2);
	if (t->matrix == NULL)
		return false;
	t->m = m;
	t->n = n;
	return true;
}

//освобождение памяти
void Free(TMatrix *t)
{
	free(t->matrix);
}
//функции переноса работы в динамические массивы
bool GridToMatrix(System::Windows::Forms::DataGridView^ grid, TMatrix *t)
{
	int m = grid->RowCount;
	int n = grid->ColumnCount;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			t->matrix[i*n+j] = Convert::ToDouble(grid->Rows[i]->Cells[j]->Value);
		return true;
}
bool MatrixToGrid(TMatrix *t, System::Windows::Forms::DataGridView^ grid)
{
	int m = t->m;
	int n = t->n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			grid->Rows[i]->Cells[j]->Value = Convert::ToString(t->matrix[i*n+j]);
	return true;
}
//функция сложения/вычитания матриц
TMatrix PlusMinus(TMatrix *matrix1, TMatrix *matrix2, int mop)
{
	if ((matrix1->m != matrix2->m) || (matrix1->n != matrix2->n))
		exit(0);
	TMatrix t3;
	InitMatrix(&t3, matrix1->m, matrix2->n);
	int m = t3.m;
	int n = t3.n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (mop == 1)
				t3.matrix[i*n+j] = matrix1->matrix[i*n+j] + matrix2->matrix[i*n+j];
			else if (mop == 0)
				t3.matrix[i*n+j] = matrix1->matrix[i*n+j] - matrix2->matrix[i*n+j];
	return t3;
}

//функция умножения матриц
TMatrix Multiply(TMatrix *matrix1, TMatrix *matrix2)
{
	if (matrix1->n != matrix2->m)
		exit(0);
	TMatrix t3;
	int a = matrix1->m;
	int b = matrix1->n;
	int c = matrix2->n;
	InitMatrix(&t3, a, c);
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < c; j++)
		{
			double tmp3 = 0;
			for (int k = 0; k < b; k++)
			{
				double tmp1 = matrix1->matrix[i*b+k];
				double tmp2 = matrix2->matrix[k*c+j];
				tmp3 = tmp3 + (tmp1 * tmp2);
				t3.matrix[i*c+j] = tmp3;
			}
		}
	}
	return t3;
}
//функция умножения матрицы на число
TMatrix MultN(TMatrix *matrix, double num)
{
	TMatrix t3;
	InitMatrix(&t3, matrix->m, matrix->n);
	int m = t3.m;
	int n = t3.n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			t3.matrix[i*n+j] = matrix->matrix[i*n+j] * num;
	return t3;
}
//функция нахождения наименьшего или наибольшего элемента
double findMinOrMax(TMatrix *matrix, int mom)
{
	double min = 1e300;
	double max = -1e300;
	int m = matrix->m;
	int n = matrix->n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (mom == 0)
			{
				if (matrix->matrix[i*n+j] < min)
					min = matrix->matrix[i*n+j];
			}
			else
				if (matrix->matrix[i*n+j] > max)
					max = matrix->matrix[i*n+j];
	if (mom == 0)
		return min;
	else
		return max;
}

//функция вычисления среднего арифметического элементов матрицы
double aveMa(TMatrix *matrix)
{
	double sum = 0;
	int m = matrix->m;
	int n = matrix->n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			sum += System::Convert::ToDouble(matrix->matrix[i*n+j]);
	return sum / (m*n);
}

//функция транспонирования матрицы
TMatrix transpM(TMatrix *matrix)
{
	int m = matrix->m;
	int n = matrix->n;
	TMatrix tmp;
	InitMatrix(&tmp, n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			tmp.matrix[i*m+j] = matrix->matrix[j*n+i];
	TMatrix t2;
	InitMatrix(&t2, n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			t2.matrix[i*m+j] = tmp.matrix[i*m+j];
	free(tmp.matrix);
	return t2;
}
//функция приведения матрицы к ступенчатому виду
TMatrix stView(TMatrix *matrix)
{
	int m = matrix->m;
	int n = matrix->n;
	TMatrix t2;
	InitMatrix(&t2, m, n);
	for (int k = 0; k < n+1; k++)
		for (int i = k+1; i < m+1; i++)
		{
			double mu = matrix->matrix[i*n+k]/matrix->matrix[k*n+k];
			for (int j = 0; j < n+1; j++)
				matrix->matrix[i*n+j] -= matrix->matrix[k*n+j] * mu;
		}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			if (((matrix->matrix[i*n+j] <= 1e-10) && (matrix->matrix[i*n+j] > 0)) || ((matrix->matrix[i*n+j] >= -1e-10) && (matrix->matrix[i*n+j] < 0)))
							 matrix->matrix[i*n+j] = 0;
			t2.matrix[i*n+j] = matrix->matrix[i*n+j];
		}
	return t2;
}

//функция нахождения определителя матрицы
double determ(TMatrix *matrix)
{
	if (matrix->m != matrix->n)
		exit(0);
	TMatrix res;
	InitMatrix(&res, matrix->m, matrix->n);
	res = stView(matrix);
	double det = 1;
	int m = res.m;
	int n = res.n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				det *= res.matrix[i*n+j];
	Free(&res);
	return det;
}

//функция нахождения обратной матрицы
TMatrix matrM1(TMatrix *matrix)
{
	if (matrix->m != matrix->n)
		exit(0);
	int n = matrix->m;
	TMatrix tmp;
	InitMatrix(&tmp, n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				tmp.matrix[i*n+j] = 1;
			else
				tmp.matrix[i*n+j] = 0;
		}
	double temp;
	for (int k = 0; k < n; k++)
	{
		temp = matrix->matrix[k*n+k];
		for (int j = 0; j < n; j++)
		{
			matrix->matrix[k*n+j] /= temp;
			tmp.matrix[k*n+j] /= temp;
		}
 
		for (int i = k + 1; i < n; i++)
		{
			temp = matrix->matrix[i*n+k];
			for (int j = 0; j < n; j++)
			{
				matrix->matrix[i*n+j] -= matrix->matrix[k*n+j] * temp;
				tmp.matrix[i*n+j] -= tmp.matrix[k*n+j] * temp;
			}
		}
	}

	for (int k = n - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = matrix->matrix[i*n+k];
 
			for (int j = 0; j < n; j++)
			{
				matrix->matrix[i*n+j] -= matrix->matrix[k*n+j] * temp;
				tmp.matrix[i*n+j] -= tmp.matrix[k*n+j] * temp;
			}
		}
	}
	return tmp;
}

//функция вычисления ранга матрицы
int rank(TMatrix *matrix)
{
	TMatrix res;
	InitMatrix(&res, matrix->m, matrix->n);
	res = stView(matrix);
	int m = res.m;
	int n = res.n;
	bool f = false;
	int rank = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (res.matrix[i*n+j] != 0)
				f = true;
			else 
				f = false;
		}
		if (f)
			rank++;
	}
	Free(&res);
	return rank;
}

//решение методом Крамера
TMatrix Cramer(TMatrix *A, TMatrix *B)
{
	if ((A->m != B->m) || (B->n != 1))
		exit(0);
	int n = A->m;
	TMatrix tmp;
	InitMatrix(&tmp, n, n);
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tmp.matrix[i*n+j] = A->matrix[i*n+j];
		}
	}

	double d = determ(A);
	if (d == 0)
		exit(0);
	for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				 A->matrix[i*n+j] = tmp.matrix[i*n+j];

	double *deltas = (double *)malloc(n*sizeof(double));

	for (int i = 0; i < n; i++)
	{	
		for (int j = 0; j < n; j++)
		{
			A->matrix[j*n+i] = B->matrix[j];
		}
	
		deltas[i] = determ(A);

		for (int i1 = 0; i1 < n; i1++)
			for (int j1 = 0; j1 < n; j1++)
				 A->matrix[i1*n+j1] = tmp.matrix[i1*n+j1];
	}
	TMatrix res;
	InitMatrix(&res, n, 1);
	int k;
	for (k = 0; k < n; k++)
		res.matrix[k] = deltas[k]/d;
	Free(&tmp);
	free(deltas);
	return res;
}

//решение методом Гаусса:
TMatrix Gauss(TMatrix *A, TMatrix *B)
{
	if ((A->m != B->m) || (B->n != 1))
		exit(0);
	int n = A->m;
	TMatrix AWave;
	InitMatrix(&AWave, n, n+1);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			AWave.matrix[i*(n+1)+j] = A->matrix[i*n+j];
	for (int i = 0; i < n; i++)
		AWave.matrix[i*(n+1)+n] = B->matrix[i];

	TMatrix AWavest;
	InitMatrix(&AWavest, n, n+1);
	AWavest = stView(&AWave);

	TMatrix res;
	InitMatrix(&res, n, 1);

	for (int i = n-1; i >= 0; i--)
	{
		res.matrix[i] = AWavest.matrix[i*(n+1)+n]/AWavest.matrix[i*(n+1)+i];
		for (int j = 0; j < n; j++)
		{
			AWavest.matrix[j*(n+1)+i] *= res.matrix[i];
			AWavest.matrix[j*(n+1)+n] -= AWavest.matrix[j*(n+1)+i];
		}
	}
	Free(&AWave);
	Free(&AWavest);
	return res;
}