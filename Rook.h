#pragma once
#include "ChessPiece.h"
class Rook : public ChessPiece
{
public:
	void GetPossibleMoves(ChessPiece* chessField[8][8]);
};