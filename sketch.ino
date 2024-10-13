#include "Queen.h"
#include "Horse.h"
#include "Bishop.h"
#include "King.h"
#include "Rook.h"
#include "Pawn.h"
#include <FastLED.h>

 
#define NUM_LEDS 64 // Количество светодиодов
#define PIN 4 // Пин для подключения ленты
CRGB leds[NUM_LEDS];
const byte latchPin = 9;        // Защелка
const byte clockPin = 13;       // clockPin
const byte dataPin = 12;        // Данные
byte okOptionSwitch[8] = {0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011};   // Массив, хранящий изначальное положение фигур
byte optionSwitch[8] = {0,0,0,0,0,0,0}; // массив, хранящий текущие состояние
byte oldOptionSwitch[8] = {0,0,0,0,0,0,0};
byte kingUpCounter = 0; //счетчик поднятия королей, для начала игры

struct Position
{
  int x, y;
};

Position position;
Position oldPosition;

const int pulseWidth = 1500;      // pulse width in microseconds
 
byte Up = 0;

byte counterForAttack = 0;
 
	King* kingB = new King();
	Queen* queenW = new Queen();
	Horse* horseW = new Horse();
	Pawn* pawnW = new Pawn();
  Rook* rookB = new Rook();
  Bishop* bishopB = new Bishop();

	ChessPiece* chessField[8][8] = { nullptr };
 
void setup ()
{
  Serial.begin(9600);
  FastLED.addLeds <WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(1000);
 
  pinMode( clockPin, OUTPUT);   // clock signal, idle LOW
  pinMode( latchPin, OUTPUT);   // latch (copy input into registers), idle HIGH
  digitalWrite( latchPin, HIGH);
 
  for( byte i=0; i<8; i++)
  {
    optionSwitch[i] = ReadOne165();
  }

  for(int i = 0; i < 8; i++)
  {
    oldOptionSwitch[i] = okOptionSwitch[i];
  }

	kingB->currentPosition.x = 0;
	kingB->currentPosition.y = 4;
	kingB->SetColor(Color::BLACK);

	queenW->currentPosition.x = 1;
	queenW->currentPosition.y = 3;
	queenW->SetColor(Color::WHITE);

	horseW->currentPosition.x = 1;
	horseW->currentPosition.y = 1;
	horseW->SetColor(Color::BLACK);

	pawnW->currentPosition.x = 0;
	pawnW->currentPosition.y = 2;
	pawnW->SetColor(Color::WHITE);
	pawnW->isPawn = true;

  rookB->currentPosition.x = 0;
	rookB->currentPosition.y = 0;
	rookB->SetColor(Color::BLACK);

  bishopB->currentPosition.x = 0;
	bishopB->currentPosition.y = 5;
	bishopB->SetColor(Color::BLACK);

	chessField[0][4] = kingB;
	chessField[1][1] = horseW;
	chessField[0][2] = pawnW;
	chessField[1][3] = queenW;
	chessField[0][0] = rookB;
	chessField[0][5] = bishopB;
}
 
void loop ()
{
  // Give a pulse to the parallel load latch of all 74HC165
  digitalWrite( latchPin, LOW);    
  delayMicroseconds( pulseWidth);
  digitalWrite( latchPin, HIGH);
 
 
  //Запись в массив байтов информации о каждом регистре
  for(byte i=0; i<8; i++)
  {
    optionSwitch[i] = ReadOne165();
  }
 
 
  if(kingUpCounter != 1)
  {
      if(checkStartPosition() && startGameCheck())
      {
        for(int i = 0; i < NUM_LEDS; i++)
        {
          leds[i] =CRGB::Black;
        }
        FastLED.show();
        kingUpCounter = 1;
      }
  }
 
  else
  {
    if(!comparePositions())
    {
      Up++;
      if(Up == 1)
      {
        oldPosition = position;
        chessField[position.x][position.y]->GetPossibleMoves(chessField);
        ShowMoves(chessField[position.x][position.y]);
      }
      for(int i = 0; i < 8; i++)
      {
        okOptionSwitch[i] = optionSwitch[i];
      }
    }
    if(Up == 2 && counterForAttack != 2)
    {
      Up = 0;
      counterForAttack = 0;
      ChessPieceDown();
      WriteNewPosition(chessField[oldPosition.x][oldPosition.y]);
    }
    if(Up == 3)
    {
      Up = 2;
      counterForAttack = 0;
    }
  }
  delay(25);      // slow down the sketch to avoid switch bounce
}
 
// The ReadOne165() function reads only 8 bits,
// because of the similar functions shiftIn() and SPI.transfer() 
// which both use 8 bits.
//
// The shiftIn() can not be used here, because the clock is set idle low
// and the shiftIn() makes the clock high to read a bit.
// The 74HC165 require to read the bit first and then give a clock pulse.
//
 
//Функция, возвращающая байт информации с каждого регистра 
byte ReadOne165()
{
  byte ret = 0; // байт информации о регистре
 
  // The first one that is read is the highest bit (input D7 of the 74HC165).
  for( int i=7; i>=0; i--)
  {
    if( digitalRead( dataPin) == HIGH) // Проверка на замыкание переключателя
      bitSet( ret, i); // запись одного бита в позицию i в байте ret
 
    digitalWrite( clockPin, HIGH); // Сдвиг на 1 бит
    delayMicroseconds( pulseWidth);
    digitalWrite( clockPin, LOW);
  }
 
  return(ret);
}
 
//Сравнение с должным положением фигур
bool comparePositions()
{
    for(int i = 0; i < 8; i++)
    {
      for(int j = 0; j < 8; j++)
      {
        if(bitRead(optionSwitch[i], j) != bitRead(okOptionSwitch[i],j))
        {
          if(bitRead(okOptionSwitch[i],j) == 1 && kingUpCounter == 1)
          {
            counterForAttack++;
          }
          position.x = j;
          position.y = i;
          Serial.print(position.x, DEC);
          Serial.println(position.y, DEC);
          return false;
        }
      }
    }
    return true;
}
 
 
//Вывод информации о положении фигур
bool checkStartPosition()
{
    //Проверка на правильное положение фигур
  if(comparePositions())
  {
    for(byte i = 0; i < 64; i+=8)
    {
      for(byte j = 2 + i; j < 6 + i; j++)
      {
        leds[j] = CRGB::Black;
        FastLED.show();
      }
 
      for(byte j = i, counter = 0; counter < 2; j+=6)
      {
        leds[j] = CRGB::Green;
        leds[j + 1] = CRGB::Green;
        FastLED.show(); // отправляем информацию на ленту
        counter++;
      }
    }
    return false;
  }
 
  else
  {
    for(byte i = 0; i < 8; i++)
    {
      for(byte j = 0; j < 8; j++)
      {
        if(bitRead(optionSwitch[i], j) != bitRead(okOptionSwitch[i],j))
        {
           leds[j + i*8] = CRGB::Red; //Загарается, если фигура стоит не на месте
        }
        else if(bitRead(optionSwitch[i], j) == 0 && bitRead(optionSwitch[i], j) == bitRead(okOptionSwitch[i],j) )
        {
          leds[j + i*8] = CRGB::Black; // гаснет, когда фигуру убирают с не начальной позиции
        }
        else if(bitRead(optionSwitch[i], j) == 1 && bitRead(optionSwitch[i], j) == bitRead(okOptionSwitch[i],j) )
        {
          leds[j + i*8] = CRGB::Green; //загарается, когда фигуру поставили на место и есть другие неправильно расположенные фигуры
        }
      }
    }
    FastLED.show();
    return true;
  }
}
 
bool startGameCheck()
{
  byte counter = 0;
  for(byte i = 0; i < 8; i++)
  {
    for(byte j = 0; j < 8; j++)
    {
      if(bitRead(optionSwitch[i], j) == bitRead(okOptionSwitch[i],j))
        counter++;
    }
  }
  if(counter == 63 && (bitRead(optionSwitch[4], 0) == 0 || bitRead(optionSwitch[4], 7) == 0))
    return true;
 
  return false;
}
 
void ShowMoves(ChessPiece* piece)
{
  for(int i = 0; i < 28; i++)
  {
    if(piece->moves[i].x == -1)
    {
      break;
    }
    leds[8 * piece->moves[i].y + piece->moves[i].x] = CRGB::Green;
  }
  for(int i = 0; i < 8; i++)
  {
    if(piece->attacking[i].x == -1)
    {
      break;
    }
    leds[8 * piece->attacking[i].y + piece->attacking[i].x] = CRGB::Red;
  }
  FastLED.show();
  GetNull(piece);
}

void GetNull(ChessPiece* piece)
{
  for(int i = 0; i < 28; i++)
  {
    if(piece->moves[i].x == -1)
    {
      break;
    }
    piece->moves[i].x = -1;
    piece->moves[i].y = -1;
  }
  for(int i = 0; i <8; i++)
  {
    piece->attacking[i].x = -1;
    piece->attacking[i].y = -1;
  }
}
 
void ChessPieceDown()
{
    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] =CRGB::Black;
    }
    FastLED.show();
}
 
void WriteNewPosition(ChessPiece* piece)
{
  chessField[position.x][position.y] = piece;
  piece->currentPosition.x = position.x;
  piece->currentPosition.y = position.y;
  if(oldPosition.x != position.x || oldPosition.y != position.y)
  {
    chessField[oldPosition.x][oldPosition.y] = nullptr;
  }
}