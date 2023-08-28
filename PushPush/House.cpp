#include "House.h"
#include "Map.h"

House::House()
{
	mPos = Pos(-1, -1); // ���� �ʱ� ��ġ�� (-1, -1) ����
	mCh = L'��'; // ���� ��Ÿ���� �����ڵ� ���� '��'�� ����
}

House::House(Pos pos)
{
	mPos = pos; // �־��� ��ġ�� ���� ��ġ�� ����
	mCh = L'��'; // ���� ��Ÿ���� �����ڵ� '��'�� ����
}

House::~House()
{
}

void House::Update(Map* map)
{
	Pos prevPos = mPos; // ���� ��ġ�� ����
	map->SetGameObjectInMap(mCh, mPos, prevPos); // �ʿ��� ���� ��ġ�� ����
}

void House::Render()
{
}
