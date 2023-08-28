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

	// 몇 번 움직였는지 세는 함수
	int GetStepCount() { return mStepCount; }

private:
	DIRECTION InputProcess();
	void OnCollisionBalls(Map* map, DIRECTION dir, Pos& prevPos);

private:
	int mStepCount;
};
