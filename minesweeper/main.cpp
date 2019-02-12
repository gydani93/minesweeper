#include <iostream>
#include "Table.h"
#include "Piece.h"

int main()
{
	//Table T(10,10);
	Table T;
	T.placeMines();
	T.createNumbering();
	T.gameCycle();
}
