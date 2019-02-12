#pragma once
#include <iostream>
using namespace std;
class Piece {
protected:
	char element;	// M: mine, numbers of mines next
	bool visible;
	bool flagged;
public:
	Piece(char element = '0', bool visible = false, bool flagged = false) :element(element), visible(visible), flagged(flagged) {}
	void printPiece()const;
	const char getElement()const { return element; }
	const bool isVisible()const { return visible; }
	const bool getFlagged()const { return flagged; }
	void placeMine() { element = 'M'; }
	void setVisible() { visible = true; }
	void setFlagged() { flagged = true; }
	void increaseNum();
};