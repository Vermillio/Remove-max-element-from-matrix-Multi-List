#pragma once
#include <vector>

using namespace std;

namespace mml
{
	typedef struct m_pos
	{

		int column;

		int row;

		m_pos(int i, int j) : row(i), column(j) {};

	};

	class Matrix
	{
	public:

		//additional types
		typedef struct m_list
		{

			int data;

			unsigned int row, column;

			m_list *nextInThisRow, *nextInThisColumn;



			//constructors		
			m_list() : nextInThisRow(nullptr), nextInThisColumn(nullptr) {};

			m_list(int x) : data(x), nextInThisRow(nullptr), nextInThisColumn(nullptr) {};

			m_list(int x, unsigned int r, unsigned int c) : data(x), row(r), column(c), nextInThisRow(nullptr), nextInThisColumn(nullptr) {};

			m_list(int x, m_list *nr, m_list *nc) : data(x), nextInThisRow(nr), nextInThisColumn(nc) {};

		};

		//variables
		vector<m_list*> Rows, Columns;								//multi-list

		unsigned int rowsNum;
		unsigned int columnsNum;

		//constructors

		Matrix();

		Matrix(int **arr, unsigned int size_x, unsigned int size_y); //gets matrix from C array
		
		//destructors

		~Matrix();

		//methods
		void print();

		void clear();									//remove matrix data

		void genRand(unsigned int _rows, unsigned int _columns);

		void consoleInput();										//gets input from console

		void setData(int **arr, unsigned int size_r, unsigned int size_c);										//sets values

		void removeColumn(unsigned int _columnNum);									//removes column with index x

		void removeRow(unsigned int _rowNum);										//removes row with index x

		m_pos getMaxElemPos();

		void insert(int data, unsigned int row, unsigned int column);

	private:

		//methods
		//pushes element of matrix from array into multi-list



	};
}
