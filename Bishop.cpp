#include "Bishop.h"

void Bishop::GetPossibleMoves(ChessPiece* chessField[8][8])
{
  char counter = 0;
  char directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

  for (char i = 0; i < 4; i++)
  {
      for (char j = 1; j < 8; j++)
      {
          Point* point = new Point();
          point->x = char(currentPosition.x + j * directions[i][0]);
          point->y = char(currentPosition.y + j * directions[i][1]);

          if (point_on_the_desk(*point))
          {
              if (IsFieldClear(*point, chessField, *this))
              {
                moves[counter] = *point;
                counter++;
              }
          }
          else delete point;
        }
    }
}

bool Bishop::point_on_the_desk(Point point)
{
    return point.x < 8 && point.x >= 0 && point.y < 8 && point.y >= 0;
}