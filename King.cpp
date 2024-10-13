#include "King.h"

void King::GetPossibleMoves(ChessPiece* chessField[8][8]){
	char x_coord[] = { -1,-1,-1,0,0,1,1,1 };
	char y_coord[] = { -1,0,1,-1,1,-1,0,1 };
  int counter = 0;
	for (char i = 0; i < 8; i++)
	{
		char new_x = currentPosition.x + x_coord[i];
		char new_y = currentPosition.y + y_coord[i];
		
		Point new_point;
		new_point.x=new_x;
		new_point.y=new_y;

		 if (point_on_the_desk(new_point) && IsFieldClear(new_point, chessField, *this)) {
        moves[counter] = new_point;
        counter++;
        }
	}
}
bool King::point_on_the_desk(Point point){
	 
return point.x < 8 && point.x >= 0  && point.y < 8 && point.y >= 0;

}