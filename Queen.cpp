#include "Queen.h"
void Queen::GetPossibleMoves(ChessPiece* chessField[8][8])
{
	int counter = 0;
	Point tempPoint;
	tempPoint.x = currentPosition.x;
	tempPoint.y = currentPosition.y;
while(tempPoint.x < 7)
	{
		tempPoint.x = tempPoint.x + 1;
		if (IsFieldClear(tempPoint, chessField, *this))
		{
			moves[counter] = tempPoint;
		}
		else
		{
			break;
		}
		counter++;
	}
	tempPoint.x = currentPosition.x;

	while(true)
	{
		tempPoint.x = tempPoint.x - 1;
		if (tempPoint.x == -1)
			break;
		if (IsFieldClear(tempPoint, chessField, *this))
		{
				moves[counter] = tempPoint;
		}
		else
		{
			break;
		}
		counter++;
	}
	tempPoint.x = currentPosition.x;

	while (tempPoint.y < 7)
	{
		tempPoint.y = tempPoint.y + 1;
		if (IsFieldClear(tempPoint, chessField, *this))
		{
				moves[counter] = tempPoint;
		}
		else
		{
			break;
		}
		counter++;
	}
	tempPoint.y = currentPosition.y;

	while (true)
	{
		tempPoint.y = tempPoint.y - 1;
		if (tempPoint.y == -1)
			break;
		if (IsFieldClear(tempPoint, chessField, *this))
		{
				moves[counter] = tempPoint;
		}
		else
		{
			break;
		}
		counter++;
	}
	tempPoint.y = currentPosition.y;

	while (true)
	{
		tempPoint.x = tempPoint.x + 1;
		tempPoint.y = tempPoint.y + 1;
		if (tempPoint.x > 7 || tempPoint.y > 7)
			break;
		if (IsFieldClear(tempPoint, chessField, *this))
		{
						moves[counter] = tempPoint;
		}
		else
		{
			break;
		}
		counter++;
	}
	tempPoint.x = currentPosition.x;
	tempPoint.y = currentPosition.y;
	while (true)
	{
		tempPoint.x = tempPoint.x - 1;
		tempPoint.y = tempPoint.y - 1;
		if (tempPoint.x < 0 || tempPoint.y < 0)
			break;
		if (IsFieldClear(tempPoint, chessField, *this))
		{
			moves[counter] = tempPoint;
		}
		else
		{
			break;
		}
		counter++;
	}
	tempPoint.x = currentPosition.x;
	tempPoint.y = currentPosition.y;
	while (true)
	{
		tempPoint.x = tempPoint.x + 1;
		tempPoint.y = tempPoint.y - 1;
		if (tempPoint.x > 7 || tempPoint.y < 0)
			break;
		if (IsFieldClear(tempPoint, chessField, *this))
		{
			moves[counter] = tempPoint;
		}
		else
		{
			break;
		}
		counter++;
	}
	tempPoint.x = currentPosition.x;
	tempPoint.y = currentPosition.y;
	while (true)
	{
		tempPoint.x = tempPoint.x - 1;
		tempPoint.y = tempPoint.y + 1;
		if (tempPoint.x < 0 || tempPoint.y > 7)
			break;
		if (IsFieldClear(tempPoint, chessField, *this))
		{
			moves[counter] = tempPoint;
		}
		else
		{
			break;
		}
		counter++;
	}
}