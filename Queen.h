#pragma once
#include "ChessPiece.h"
class Queen : public ChessPiece
{
	void GetPossibleMoves(ChessPiece* chessField[8][8]) override;
};

