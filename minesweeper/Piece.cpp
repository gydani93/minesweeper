#include "Piece.h"

void Piece::printPiece()const {
	if (visible == true)
		cout << element;
	else if (getFlagged())
		cout << 'F';
	else
		cout << 'X';
}

void Piece::increaseNum() {
	if (element != 'M') {
		int tmp = (int)element;
		tmp++;
		element = (char)tmp;
	}
}