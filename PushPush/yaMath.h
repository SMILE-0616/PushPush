#pragma once

enum class DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

struct Vector2 // ������ ��Ÿ���� ����ü
{
	int x;
	int y;

	Vector2() // x,y�� �������� �ʾ��� �� ����ϴ� �Լ�
		:x(0), y(0)
	{

	}

	Vector2(int x, int y)// x,y�� ������ �� ���Ǵ� �Լ�
		:x(x), y(y)
	{

	}

	Vector2(const Vector2& other)
	{
		x = other.x;
		y = other.y;
	}

	Vector2& operator =(const Vector2& other) // �����ڤ�
	{
		x = other.x;
		y = other.y;

		return *this; // �ּ� ������ &�� ������ * = ¦��
	}

	bool operator == (const Vector2& other)
	{
		return (x == other.x && y == other.y);
	}
};

typedef Vector2 Pos; // typedef (������)�� ���ؼ� Vector2, Pos �� �� ��� ����
typedef Vector2 Size;