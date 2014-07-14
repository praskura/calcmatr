#pragma once

struct TMatrix
	{
		int m;
		int n;
		double *matrix;
	};

//������������� �������
bool InitMatrix(TMatrix *t, int m, int n);
//������������ ������
void Free(TMatrix *t);
//������� �������� ������ � ������������ �������
bool GridToMatrix(System::Windows::Forms::DataGridView^ grid, TMatrix *t);
bool MatrixToGrid(TMatrix *t, System::Windows::Forms::DataGridView^ grid);
//������� ��������/��������� ������
TMatrix PlusMinus(TMatrix *matrix1, TMatrix *matrix2, int mop);
//������� ��������� ������
TMatrix Multiply(TMatrix *matrix1, TMatrix *matrix2);
//������� ��������� ������� �� �����
TMatrix MultN(TMatrix *matrix, double num);
//������� ���������� �����������/����������� ��������
double findMinOrMax(TMatrix *matrix, int mom);
//������� ���������� �������� ��������������� ��������� �������
double aveMa(TMatrix *matrix);
//������� ���������������� �������
TMatrix transpM(TMatrix *matrix);
//������� ���������� ������� � ������������ ����
TMatrix stView(TMatrix *matrix);
//������� ���������� ������������ �������
double determ(TMatrix *matrix);
//������� ���������� �������� �������
TMatrix matrM1(TMatrix *matrix);
//������� ���������� ����� �������
int rank(TMatrix *matrix);
//����� �������
TMatrix Cramer(TMatrix *A, TMatrix *B);
//����� ������
TMatrix Gauss(TMatrix *A, TMatrix *B);