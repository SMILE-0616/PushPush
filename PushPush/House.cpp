#include "House.h"
#include "Map.h"

House::House()
{
	mPos = Pos(-1, -1); // 집의 초기 위치를 (-1, -1) 설정
	mCh = L'◆'; // 집을 나타내는 유니코드 문자 '◆'로 설정
}

House::House(Pos pos)
{
	mPos = pos; // 주어진 위치로 집의 위치를 설정
	mCh = L'◆'; // 집을 나타내는 유니코드 '◆'로 설정
}

House::~House()
{
}

void House::Update(Map* map)
{
	Pos prevPos = mPos; // 이전 위치를 저장
	map->SetGameObjectInMap(mCh, mPos, prevPos); // 맵에서 집의 위치를 갱신
}

void House::Render()
{
}
