#pragma once
#include "Common.h"
#include "Map.h"

class Stage
{
public:
	Stage();
	~Stage();

	// ���ο� �������� ���� �ҷ����� �Լ�
	Map* Load(int stageNumber = 1);

	// ���� ������Ʈ�� �����ϴ� �Լ�
	void CreateGameObject(wchar_t type, int x, int y);

	// ���� �������� ��ȣ�� ��ȯ�ϴ� �Լ�
	UINT GetStageNumber() { return mStageNumber; }

private:
	Map* mMap;
	UINT mStageNumber;
};