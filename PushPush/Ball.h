#pragma once
#include "Common.h"
#include "GameObject.h"

class Ball : public GameObject
{
public:
	static std::list<Ball*>& GetBalls() { return mBalls; }// 생성된 모든 공 객체에 대한 리스트를 반환
	static int GetBallsCount() { return mBallCount; }// 생성된 공 객체의 개수를 반환
	static void Clear();// 생성된 모든 공 객체를 제거

	Ball();// 새로운 Ball 객체를 생성
	Ball(Pos pos);// 새로운 Ball 객체를 생성
	~Ball();

	void Initialize(Pos pos = Pos(-1, -1)); // 위치 정보를 받아 객체를 초기화
	virtual void Update(Map* map) override;
	virtual void Render() override;

private:
	static int mBallCount; // 생성된 공 객체의 총 개수를 저장
	static std::list<Ball*> mBalls; // 생성된 모든 공 객체에 대한 리스트를 관리
};
