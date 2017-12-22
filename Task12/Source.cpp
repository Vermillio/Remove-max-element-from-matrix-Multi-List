#include "MultiList.h"
#include <iostream>
using namespace std;
using namespace mml;

int main()
{
	bool choise;
	Matrix M;

	cout << "0 - generate random, 1 - input from console : " << endl;
	cin >> choise;
	if (choise)
		M.consoleInput();
	else {
		unsigned int rows_sz, columns_sz;
		double zeroProb;
		cout << "Enter rows num : " << endl;
		cin >> rows_sz;
		cout << "Enter columns num: " << endl;
		cin >> columns_sz;
		M.genRand(rows_sz, columns_sz);
	}
	m_pos max = M.getMaxElemPos();
	if (max.column == -1)
	{
		cout << "Matrix is empty." << endl;
		system("pause");
		return 0;
	}
	M.print();
	M.removeRow(max.row);
	M.removeColumn(max.column);
	M.print();
	system("pause");
	return 0;
}