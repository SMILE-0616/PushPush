#pragma once
#include "Common.h"
#include "GameObject.h"

class Ball : public GameObject
{
public:
	static std::list<Ball*>& GetBalls() { return mBalls; }// ������ ��� �� ��ü�� ���� ����Ʈ�� ��ȯ
	static int GetBallsCount() { return mBallCount; }// ������ �� ��ü�� ������ ��ȯ
	static void Clear();// ������ ��� �� ��ü�� ����

	Ball();// ���ο� Ball ��ü�� ����
	Ball(Pos pos);// ���ο� Ball ��ü�� ����
	~Ball();

	void Initialize(Pos pos = Pos(-1, -1)); // ��ġ ������ �޾� ��ü�� �ʱ�ȭ
	virtual void Update(Map* map) override;
	virtual void Render() override;

private:
	static int mBallCount; // ������ �� ��ü�� �� ������ ����
	static std::list<Ball*> mBalls; // ������ ��� �� ��ü�� ���� ����Ʈ�� ����
};
