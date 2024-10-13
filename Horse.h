#pragma once
#include "ChessPiece.h"

class Horse: public ChessPiece
{
public:
	void GetPossibleMoves(ChessPiece* chessField[8][8]);
};