//Remove from the matrix [A] a row and column containing the largest element of the matrix. 
//The matrix [A] is discharged and stored as multi-lists.

#include "MultiList.h"
#include <iostream>
#include <string>
#include <random>

using namespace mml;
using namespace std;

Matrix::Matrix()
{
}

//+
Matrix::Matrix(int **matr, unsigned int N, unsigned int M)
{
	setData(matr, N, M);
}
//+
Matrix::~Matrix()
{
	for (int i = 0; i < Rows.size(); ++i)
		removeRow(i);
}

void Matrix::clear()
{
	if (Rows.empty() && Columns.empty())
		return;
	for (int i = 0; i < Rows.size(); i++)
		removeRow(i);
	for (int i = 0; i < Columns.size(); i++)
		Columns[i] = nullptr;
}

void Matrix::genRand(unsigned int _rows, unsigned int _columns)
{
	rowsNum = _rows;
	columnsNum = _columns;
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> randProb(0.0, 1.0);
	srand(randProb(gen));
	double zeroProb = randProb(gen);
	for (unsigned int i = 0; i < _rows; ++i)
		for (unsigned int j = 0; j < _columns; ++j)
		{
			if (randProb(gen) < zeroProb)
				continue;
			insert(rand() + 1, i, j);
		}
}

void Matrix::consoleInput()
{
	cout << "Enter matrix columns: ";
	cin >> columnsNum;
	cout << "Enter matrix rows: ";
	cin >> rowsNum;

	clear();
	//Rows.resize(rowsNum);
	//Columns.resize(columnsNum);

	int data;
	cout << "Enter matrix: " << endl;

	for (int i = 0; i < rowsNum; i++)
	{
		for (int j = 0; j < columnsNum; j++)
		{
			cin >> data;
			insert(data, i, j);
		}
	}
}

void Matrix::setData(int **arr, unsigned int _rowsNum, unsigned int _columnsNum)
{
	rowsNum = _rowsNum;
	columnsNum = _columnsNum;
	clear();
	for (int i = 0; i < rowsNum; i++)
		for (int j = 0; j < columnsNum; j++)
			insert(arr[j][i], j, i);
}

void Matrix::print()
{
	//int prevColumn = 0;
	int rowsIter = 0;
	m_list *cur, *q;
	for (int i = 0; i < rowsNum; ++i)
	{
		cout << "|";

		if (rowsIter >= Rows.size() || Rows[rowsIter]->row != i)
		{
			for (int i = 0; i < columnsNum; ++i)
				cout << " 0";
		} 
		else
		{
			cur = Rows[rowsIter];
			for (int i = 0; i < columnsNum; ++i)
			{
				if (!cur || cur->column != i)
					cout << " 0";
				else {
					cout << " " << cur->data;
					cur = cur->nextInThisRow;
				}
			}
			++rowsIter;
		}
		cout << " |" << endl;
	}
}

void Matrix::removeRow(unsigned int x)
{
	if (x >= rowsNum)
		return;
	m_list *cur = nullptr;
	int indexActual;
	for (int i = 0; i < Rows.size(); ++i)
		if (Rows[i]->row >= x)
		{
			cur = Rows[i];
			indexActual = i;
			break;
		}

	if (!cur)
	{
		--rowsNum;
		return;
	}

	if (cur->row != x)
	{
		for (int i = indexActual; i < Rows.size(); ++i)
		{
			cur = Rows[i];
			--cur->row;
			while (cur->nextInThisColumn)
			{
				cur = cur->nextInThisColumn;
				--cur->row;
			}
		}
		--rowsNum;
		return;
	}

	int minRowIndex = 0;
	m_list *nextR, *prevC = nullptr;
	while (cur)
	{
		nextR = cur->nextInThisRow;
		
		for (int i = minRowIndex; i < Columns.size(); ++i)
		{
				if (Columns[i] == cur)
				{
					if (!cur->nextInThisColumn)
						Columns.erase(Columns.begin() + i);
					else Columns[i] = cur->nextInThisColumn;
					minRowIndex = i;
					break;
				}
				if (Columns[i]->column == cur->column)
				{
					prevC = Columns[i];
					while (prevC->nextInThisColumn != cur)
						prevC = prevC->nextInThisColumn;
					prevC->nextInThisColumn = cur->nextInThisColumn;
					minRowIndex = i;
					break;
				}
		}

		delete cur;
		cur = nextR;
	}
	for (int i = indexActual + 1; i < Rows.size(); ++i)
	{
		cur = Rows[i];
		--cur->row;
		while (cur->nextInThisRow)
		{
			cur = cur->nextInThisRow;
			--cur->row;
		}
	}
	Rows.erase(Rows.begin() + indexActual);
	--rowsNum;
}

void Matrix::removeColumn(unsigned int y)
{
	if (y >= columnsNum)
		return;
	m_list *cur = nullptr;
	int indexActual;
	for (int i = 0; i < Columns.size(); ++i)
	{
		if (Columns[i]->column >= y)
		{
			cur = Columns[i];
			indexActual = i;
			break;
		}
	}

	if (!cur)
	{
		--columnsNum;
		return;
	}

	if (cur->column != y)
	{
		for (int i = indexActual; i < Columns.size(); ++i)
		{
			cur = Columns[i];
			--cur->column;
			while (cur->nextInThisColumn)
			{
				cur = cur->nextInThisColumn;
				--cur->column;
			}
		}
		--columnsNum;
		return;
	}

	int minRowIndex = 0;
	m_list *nextC, *prevR = nullptr;
	while (cur)
	{
		nextC = cur->nextInThisColumn;

		for (int i = minRowIndex; i < Rows.size(); ++i)
		{
			if (Rows[i] == cur)
			{

				if (!cur->nextInThisRow)
				{
					Rows.erase(Rows.begin() + i);
				}
				else Rows[i] = cur->nextInThisRow;
				minRowIndex = i;
				break;
			}
			if (Rows[i]->row == cur->row)
			{
				prevR = Rows[i];
				while (prevR->nextInThisRow != cur)
					prevR = prevR->nextInThisRow;
				prevR->nextInThisRow = cur->nextInThisRow;
				minRowIndex = i;
				break;
			}
		}
		delete cur;
		cur = nextC;
	}
	for (int i = indexActual + 1; i < Columns.size(); ++i)
	{
		cur = Columns[i];
		--cur->column;
		while (cur->nextInThisColumn)
		{
			cur = cur->nextInThisColumn;
			--cur->column;
		}
	}
	Columns.erase(Columns.begin() + indexActual);
	--columnsNum;
}

void Matrix::insert(int data, unsigned int x, unsigned int y)
{
	if (!data)
		return;
	int actualIndex = Rows.size();
	for (int i = 0; i < Rows.size(); ++i)
	{
		if (Rows[i]->row >= x)
		{
			actualIndex = i;
			break;
		}
	}
	
	m_list *curElem, *prevElem = nullptr, *saved;

	if (actualIndex == Rows.size() || Rows[actualIndex]->row != x)
	{
		saved = new m_list(data, x, y);
		Rows.insert(Rows.begin() + actualIndex, saved);
	}
	else {
		curElem = Rows[actualIndex];
		while (curElem && curElem->column < y)
		{
			prevElem = curElem;
			curElem = curElem->nextInThisRow;
		}
		if (curElem && curElem->column == y)
		{
			curElem->data = data;
			return;
		}
		saved = new m_list(data, x, y);
		if (!prevElem)
			Rows[actualIndex] = saved;
		else prevElem->nextInThisRow = saved;
		saved->nextInThisRow = curElem;
	}


	actualIndex = Columns.size();

	for (int i = 0; i < Columns.size(); ++i)
	{
		if (Columns[i]->column >= y)
		{
			actualIndex = i;
			break;
		}
	}

	if (actualIndex == Columns.size() || Columns[actualIndex]->column != y)
	{
		Columns.insert(Columns.begin() + actualIndex, saved);
		return;
	}
	else {
		prevElem = nullptr;
		curElem = Columns[actualIndex];
		while (curElem && curElem->row < x)
		{
			prevElem = curElem;
			curElem = curElem->nextInThisColumn;
		}
		if (!prevElem)
			Columns[actualIndex] = saved;
		else prevElem->nextInThisColumn = saved;
		saved->nextInThisColumn = curElem;
	}
}


///<summary>Finds max element in matrix.</summary>
///<returns>Absolute position in matrix in format {row, column}. If matrix is empty returns {-1, -1}.</returns>
m_pos Matrix::getMaxElemPos()
{
	if (rowsNum == 0 || columnsNum == 0)
		return { -1, -1 };
	m_list *max = Rows[0];
	m_list *cur = nullptr;
	for (int i = 0; i < Rows.size(); ++i)
	{
		cur = Rows[i];
		while (cur)
		{
			if (max->data < cur->data)
				max = cur;
			cur = cur->nextInThisRow;
		}
	}
	return m_pos(max->row, max->column);
}