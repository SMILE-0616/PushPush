#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	Player(Pos pos);
	~Player();

	virtual void Update(Map* map) override;
	virtual void Render() override;

	// �� �� ���������� ���� �Լ�
	int GetStepCount() { return mStepCount; }

private:
	DIRECTION InputProcess();
	void OnCollisionBalls(Map* map, DIRECTION dir, Pos& prevPos);

private:
	int mStepCount;
};
