#pragma once
#include "ChessPiece.h"
class Pawn : public ChessPiece
{
public:
	void GetPossibleMoves(ChessPiece* chessField[8][8]);
};