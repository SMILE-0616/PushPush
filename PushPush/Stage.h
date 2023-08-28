#pragma once
#include "Common.h"
#include "Map.h"

class Stage
{
public:
	Stage();
	~Stage();

	// 새로운 스테이지 맵을 불러오는 함수
	Map* Load(int stageNumber = 1);

	// 게임 오브젝트를 생성하는 함수
	void CreateGameObject(wchar_t type, int x, int y);

	// 현재 스테이지 번호를 반환하는 함수
	UINT GetStageNumber() { return mStageNumber; }

private:
	Map* mMap;
	UINT mStageNumber;
};