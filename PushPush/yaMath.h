#pragma once

enum class DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

struct Vector2 // 방향을 나타내는 구조체
{
	int x;
	int y;

	Vector2() // x,y를 대입하지 않았을 때 사용하는 함수
		:x(0), y(0)
	{

	}

	Vector2(int x, int y)// x,y를 대입할 때 사용되는 함수
		:x(x), y(y)
	{

	}

	Vector2(const Vector2& other)
	{
		x = other.x;
		y = other.y;
	}

	Vector2& operator =(const Vector2& other) // 참조자ㅡ
	{
		x = other.x;
		y = other.y;

		return *this; // 주소 연산자 &와 포인터 * = 짝꿍
	}

	bool operator == (const Vector2& other)
	{
		return (x == other.x && y == other.y);
	}
};

typedef Vector2 Pos; // typedef (재정의)를 통해서 Vector2, Pos 둘 다 사용 가능
typedef Vector2 Size;