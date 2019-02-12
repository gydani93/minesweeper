#include "Table.h"
#include <time.h>
#include <stdlib.h>

void Table::placeMines() {
	int i = 0;
	srand((int)time(0));
	while (i < mineNum) {
		int rnd = (rand() % (width*width));
		if (B[rnd].getElement() != 'M') {
			B[rnd].placeMine();
			i++;
		}
	}
}

void Table::printCoordinates()const {
	for (int i = 0; i < width; i++) {
		cout << i + 1 << "   ";
	}
	cout << endl << endl << endl;
}

void Table::printboard()const {
	printCoordinates();
	int k = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {
			B[k].printPiece();
			cout << "   ";
			k++;
		}
		cout << "   " << i + 1;
		cout << endl << endl;
	}
}

const bool Table::isMine(int pos)const {
	return (B[pos].getElement() == 'M');
}

const bool Table::isLeftUp(int pos)const {
	if (pos == 0)
		return true;
	return false;
}

const bool Table::isRightUp(int pos)const {
	if (pos == (width - 1))
		return true;
	return false;
}

const bool Table::isLeftDown(int pos)const {
	if (pos == ((width - 1)*width))
		return true;
	return false;
}

const bool Table::isRightDown(int pos)const {
	if (pos == (width*width - 1))
		return true;
	return false;
}

const bool Table::isLeft(int pos)const {
	if (((pos % width) == 0) && (pos != 0) && (pos != (width*width - (width - 1))))
		return true;
	return false;
}

const bool Table::isRight(int pos)const {
	if ((((pos - width + 1) % width) == 0) && (pos != 0) && (pos != (width*width - 1)))
		return true;
	return false;
}

const bool Table::isUp(int pos)const {
	if ((pos < width) && (pos != 0) && (pos != width - 1))
		return true;
	return false;
}

const bool Table::isDown(int pos)const {
	if ((pos > ((width - 1)*width)) && (pos != (width*width - 1)))
		return true;
	return false;
}

void Table::createNumbering() {
	for (int i = 0; i < (width*width); i++) {
		if (isMine(i)) {
			if (isLeftUp(i)) {
				B[i + 1].increaseNum();
				B[i + width].increaseNum();
				B[i + width + 1].increaseNum();
			}
			else if (isRightUp(i)) {
				B[i - 1].increaseNum();
				B[i + width].increaseNum();
				B[i + width - 1].increaseNum();
			}
			else if (isLeftDown(i)) {
				B[i + 1].increaseNum();
				B[i - width].increaseNum();
				B[i - width + 1].increaseNum();
			}
			else if (isRightDown(i)) {
				B[i - 1].increaseNum();
				B[i - width].increaseNum();
				B[i - width - 1].increaseNum();
			}
			else if (isLeft(i)) {
				B[i - width].increaseNum();
				B[i - width + 1].increaseNum();
				B[i + 1].increaseNum();
				B[i + width].increaseNum();
				B[i + width + 1].increaseNum();
			}
			else if (isRight(i)) {
				B[i - width].increaseNum();
				B[i - width - 1].increaseNum();
				B[i - 1].increaseNum();
				B[i + width].increaseNum();
				B[i + width - 1].increaseNum();
			}
			else if (isUp(i)) {
				B[i - 1].increaseNum();
				B[i + width - 1].increaseNum();
				B[i + width].increaseNum();
				B[i + width + 1].increaseNum();
				B[i + 1].increaseNum();
			}
			else if (isDown(i)) {
				B[i - 1].increaseNum();
				B[i - width - 1].increaseNum();
				B[i - width].increaseNum();
				B[i - width + 1].increaseNum();
				B[i + 1].increaseNum();
			}
			else {
				B[i - width - 1].increaseNum();
				B[i - width].increaseNum();
				B[i - width + 1].increaseNum();
				B[i - 1].increaseNum();
				B[i + 1].increaseNum();
				B[i + width - 1].increaseNum();
				B[i + width].increaseNum();
				B[i + width + 1].increaseNum();
			}
		}
	}
}

void Table::printMessage()const {
	cout << "Enter X, Y coordinates and O(open) or F(flag) signs separated by space!" << endl << "You uncovered " <<
		visibleFieldsNum << " fields, there are " << fieldsToUncover - visibleFieldsNum <<
		" fields to uncover, you flagged " << foundMinesNum << " mines." << endl;
}

void Table::getCoordinates() {
	int x, y;
	char c;
	cin >> x >> y >> c;
	while ((x < 1) || (x > width) || (y < 1) || (y > width) || (!((c == 'o') || (c == 'O') || (c == 'f') || (c == 'F')))) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input!" << endl;
		cin >> x >> y >> c;
	}
	cinPos = width * (y - 1) + x - 1;
	cinOF = c;
}

void Table::setvisibleFieldsNum() {
	int num = 0;;
	for (int i = 0; i < width*width; i++) {
		if (B[i].isVisible() == true)
			num++;
	}
	visibleFieldsNum = num;
}

void Table::setfoundMinesNum() {
	int num = 0;;
	for (int i = 0; i < width*width; i++) {
		if (B[i].getFlagged() == true)
			num++;
	}
	foundMinesNum = num;
}

void Table::openPieces() {
	B[cinPos].setVisible();
	if (B[cinPos].getElement() == 'M') {
		endOfGame = true;
	}
	if (B[cinPos].getElement() == '0') {
		for (int j = 0; j < width; j++) {
			for (int i = 0; i < width*width; i++) {
				if ((B[i].getElement() == '0') && (B[i].isVisible())) {
					if (isLeftUp(i)) {
						B[i + 1].setVisible();
						B[i + width].setVisible();
						B[i + width + 1].setVisible();
					}
					else if (isRightUp(i)) {
						B[i - 1].setVisible();
						B[i + width].setVisible();
						B[i + width - 1].setVisible();
					}
					else if (isLeftDown(i)) {
						B[i + 1].setVisible();
						B[i - width].setVisible();
						B[i - width + 1].setVisible();
					}
					else if (isRightDown(i)) {
						B[i - 1].setVisible();
						B[i - width].setVisible();
						B[i - width - 1].setVisible();
					}
					else if (isLeft(i)) {
						B[i - width].setVisible();
						B[i - width + 1].setVisible();
						B[i + 1].setVisible();
						B[i + width].setVisible();
						B[i + width + 1].setVisible();
					}
					else if (isRight(i)) {
						B[i - width].setVisible();
						B[i - width - 1].setVisible();
						B[i - 1].setVisible();
						B[i + width].setVisible();
						B[i + width - 1].setVisible();
					}
					else if (isUp(i)) {
						B[i - 1].setVisible();
						B[i + width - 1].setVisible();
						B[i + width].setVisible();
						B[i + width + 1].setVisible();
						B[i + 1].setVisible();
					}
					else if (isDown(i)) {
						B[i - 1].setVisible();
						B[i - width - 1].setVisible();
						B[i - width].setVisible();
						B[i - width + 1].setVisible();
						B[i + 1].setVisible();
					}
					else {
						B[i - width - 1].setVisible();
						B[i - width].setVisible();
						B[i - width + 1].setVisible();
						B[i - 1].setVisible();
						B[i + 1].setVisible();
						B[i + width - 1].setVisible();
						B[i + width].setVisible();
						B[i + width + 1].setVisible();
					}
				}
			}
		}
	}
	setvisibleFieldsNum();
	if (visibleFieldsNum == fieldsToUncover) {
		endOfGame = true;
	}
}

void Table::flagPiece() {
	B[cinPos].setFlagged();
	setfoundMinesNum();
}

void Table::setAllVisible() {
	for (int i = 0; i < width*width; i++) {
		B[i].setVisible();
	}
}

void Table::gameCycle() {
	do {
		system("CLS");
		printboard();
		printMessage();
		getCoordinates();
		if ((cinOF == 'O') || cinOF == 'o') {
			openPieces();
		}
		else if ((cinOF == 'F') || cinOF == 'f') {
			flagPiece();
		}
	} while (!endOfGame);

	if (visibleFieldsNum == fieldsToUncover) {
		setAllVisible();
		system("CLS");
		printboard();
		cout << "Victory" << endl;
	}
	if (B[cinPos].getElement() == 'M') {
		setAllVisible();
		system("CLS");
		printboard();
		cout << "Defeat" << endl;
	}
}