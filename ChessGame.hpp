#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <memory>

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };	//https://beginnersbook.com/2017/09/cpp-enumeration/
enum Color { WHITE, BLACK, NONE };

using std::string;

class Square
{

	Piece piece; //typos enum
	Color color;
	int x, y;
public:
	void setSpace(Square*);
	void setEmpty();
	void setPieceAndColor(Piece, Color);
	Piece getPiece();
	Color getColor();
	void setX(int ex) { x = ex; }
	void setY(int why) { y = why; }
	int getX() { return x; }
	int getY() { return y; }
	Square();
};

class Board
{
	Square square[8][8];
	//Square kingsPos[1][2];
	Color turn=WHITE;
	bool moveForward(Square *src, Square *dest);
	bool moveBackwards(Square *src, Square *dest);
	bool moveUp(Square *src, Square *dest);
	bool moveDown(Square *src, Square *dest);
	bool moveDiagonal(Square *src, Square *dest);
	bool moveForwardOrBackwards(Square *src, Square *dest);
	bool moveUpDown(Square *src, Square *dest);
	bool checkIfKing(Square* thisKing, Square* thatSpace);
	bool checkIfQueen(Square* thisQueen, Square* thatSpace);
	bool checkIfBishop(Square* thisBishop, Square* thatSpace);
	bool checkIfKnight(Square* thisKnight, Square* thatSpace);
	bool checkIfRook(Square* thisRook, Square* thatSpace);
	bool checkIfPawn(Square* thisPawn, Square* thatSpace);
	bool makeMove(int x1, int y1, int x2, int y2);
	void printBoard();
	void saveToBinFile(std::string strFile);

public:
	Square* getSquare(int x, int y) {
		return &square[x][y];
	}
	void setSquare(Square * s, int x, int y){
		square[x][y]=*s;
	}
	bool doMove();
	void readFromBinFile(string strFile);
	void setBoard();
	bool playGame();
};
