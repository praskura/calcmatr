#pragma once

struct TMatrix
	{
		int m;
		int n;
		double *matrix;
	};

//инициализация матрицы
bool InitMatrix(TMatrix *t, int m, int n);
//освобождение памяти
void Free(TMatrix *t);
//функции переноса работы в динамические массивы
bool GridToMatrix(System::Windows::Forms::DataGridView^ grid, TMatrix *t);
bool MatrixToGrid(TMatrix *t, System::Windows::Forms::DataGridView^ grid);
//функция сложения/вычитания матриц
TMatrix PlusMinus(TMatrix *matrix1, TMatrix *matrix2, int mop);
//функция умножения матриц
TMatrix Multiply(TMatrix *matrix1, TMatrix *matrix2);
//функция умножения матрицы на число
TMatrix MultN(TMatrix *matrix, double num);
//функция нахождения наименьшего/наибольшего элемента
double findMinOrMax(TMatrix *matrix, int mom);
//функция вычисления среднего арифметического элементов матрицы
double aveMa(TMatrix *matrix);
//функция транспонирования матрицы
TMatrix transpM(TMatrix *matrix);
//функция приведения матрицы к ступенчатому виду
TMatrix stView(TMatrix *matrix);
//функция нахождения определителя матрицы
double determ(TMatrix *matrix);
//функция нахождения обратной матрицы
TMatrix matrM1(TMatrix *matrix);
//функция вычисления ранга матрицы
int rank(TMatrix *matrix);
//метод Крамера
TMatrix Cramer(TMatrix *A, TMatrix *B);
//метод Гаусса
TMatrix Gauss(TMatrix *A, TMatrix *B);