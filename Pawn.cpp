#include "Pawn.h"

void Pawn::GetPossibleMoves(ChessPiece* chessField[8][8])
{
    Point tempPoint;
    tempPoint.y = currentPosition.y;
    tempPoint.x = currentPosition.x + 1;
    if (IsFieldClear(tempPoint, chessField, *this))
    {
        moves[0] = tempPoint;
    }
}