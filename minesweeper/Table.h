#pragma once
#include "Piece.h"
#include <iostream>
using namespace std;
class Table {
	int width, mineNum, fieldsToUncover, visibleFieldsNum, foundMinesNum, cinPos;
	char cinOF;	//open or flag
	bool endOfGame;
	Piece* B;
public:
	Table(int width = 10, int mineNum = 3) :width(width), mineNum(mineNum) {
		if (this->mineNum > (int)width*width/2) {
			this->mineNum = (int)width * width/2;
		}
		B = new Piece[width*width];
		fieldsToUncover = width*width-this->mineNum;
		visibleFieldsNum = 0;
		foundMinesNum = 0;
		cinPos = -1;
		cinOF = 'w';
		endOfGame = false;
	}
	void placeMines();					//places mineNum piece of mines randomly
	void printCoordinates()const;
	void printboard()const;
	const bool isMine(int pos)const;	//for createNumbering()
	const bool isLeftUp(int pos)const;
	const bool isRightUp(int pos)const;
	const bool isLeftDown(int pos)const;
	const bool isRightDown(int pos)const;
	const bool isLeft(int pos)const;
	const bool isRight(int pos)const;
	const bool isUp(int pos)const;
	const bool isDown(int pos)const;
	void createNumbering();				//creates the numbering. each field has the number of mines nearby
	void printMessage()const;
	void getCoordinates();
	void setvisibleFieldsNum();
	void setfoundMinesNum();
	void openPieces();
	void flagPiece();
	void setAllVisible();
	void gameCycle();
	~Table() { if (B != nullptr) delete[]B; }
};