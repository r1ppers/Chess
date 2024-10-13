#include "Horse.h"

void Horse::GetPossibleMoves(ChessPiece* chessField[8][8])
{
	char x_coord[] = { currentPosition.x + 2, currentPosition.x + 2, currentPosition.x - 2, currentPosition.x - 2, currentPosition.x + 1, currentPosition.x + 1, currentPosition.x - 1, currentPosition.x - 1};
	char y_coord[] = { currentPosition.y + 1, currentPosition.y - 1, currentPosition.y + 1, currentPosition.y - 1, currentPosition.y + 2, currentPosition.y - 2, currentPosition.y + 2, currentPosition.y - 2};
	char counter = 0;
	for (char i = 0; i < 8; i++)
	{
		if(x_coord[i] > 7 || x_coord[i] < 0 || y_coord[i] < 0 || y_coord[i] > 7)
		{
			continue;
		}
		Point point;
		point.x = x_coord[i];
		point.y = y_coord[i];

		if (IsFieldClear(point, chessField, *this))
    {
			moves[counter] = point;
			counter++;
    }
		//moves.push_back(*point);
	}
}