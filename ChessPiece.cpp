#include "ChessPiece.h"


void ChessPiece::GetPossibleMoves(ChessPiece* chessField[8][8])
{

}

bool ChessPiece::IsKingUnderAttack()
{
	return false;
}

bool ChessPiece::IsFieldClear(Point point, ChessPiece* chessField[8][8], ChessPiece chessPiece)
{
	if (chessField[point.x][point.y]->isOccupied())
	{
		if (chessField[point.x][point.y]->color != chessPiece.color && !chessPiece.isPawn)
		{
			int i = 0;
			while (true)
			{
				if (attacking[i].x == -1)
				{
					attacking[i] = point;
					break;
				}
				i++;
			}
		}
		attackForPawn(point, chessField, chessPiece);
		return false;
	}
	attackForPawn(point, chessField, chessPiece);
	return true;
}

void ChessPiece::attackForPawn(Point point, ChessPiece* chessField[8][8], ChessPiece chessPiece)
{
	if (chessField[point.x][point.y + 1]->isOccupied() && chessPiece.isPawn && chessField[point.x][point.y + 1]->color != chessPiece.color)
	{
		int i = 0;
		while (true)
		{
			if (attacking[i].x == -1)
			{
				point.y = point.y + 1;
				attacking[i] = point;
				point.y = point.y - 1;
				break;
			}
			i++;
		}
	}
	if (chessField[point.x][point.y - 1]->isOccupied() && chessPiece.isPawn && chessField[point.x][point.y - 1]->color != chessPiece.color)
	{
		char i = 0;
		while (true)
		{
			if (attacking[i].x == -1)
			{
				point.y = point.y - 1;
				attacking[i] = point;
				break;
			}
			i++;
		}
	}
}

bool ChessPiece::isOccupied()
{
	if (this == nullptr)
		return false;
	return true;
}
void ChessPiece::SetColor(Color color)
{
	this->color = color;
}