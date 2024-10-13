#pragma once
#include "ChessPiece.h"

class King: public ChessPiece
{
public:
	void GetPossibleMoves(ChessPiece* chessField[8][8]);
	
	private:
	static bool point_on_the_desk(Point point);
};