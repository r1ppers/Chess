#ifndef ChessPiece_H_
#define ChessPiece_H_
enum Color
{
	WHITE,
	BLACK
};

struct Point
{
	char x = -1, y = -1;
};

class ChessPiece
{
public:
	Color color;
	Point currentPosition;
	Point attacking[8];
	Point moves[28];
	bool isPawn = false;

	bool IsFieldClear(Point point, ChessPiece* chessField[8][8], ChessPiece chessPiece);
	bool isOccupied();

	void SetColor(Color color);
public:
	virtual void GetPossibleMoves(ChessPiece* chessField[8][8]);
	bool IsKingUnderAttack();
private:
	void attackForPawn(Point point, ChessPiece* chessField[8][8], ChessPiece chessPiece);
};

#endif
