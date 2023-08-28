#include "Player.h"
#include "Map.h"
#include "Ball.h"

Player::Player()
{
	mCh = L'��'; // �÷��̾� ���� ����
	mPos.y = 4; // �ʱ� y ��ǥ
	mPos.x = 4; // �ʱ� x ��ǥ
	mStepCount = 0; // ������ Ƚ�� �ʱ�ȭ
}

Player::Player(Pos pos)
{
	mCh = L'��';
	mPos.y = pos.y;
	mPos.x = pos.x;
	mStepCount = 0;
}

Player::~Player()
{
}

void Player::Update(Map* map)
{
	Pos prevPos = mPos; // ���� ��ġ ����
	DIRECTION dir = InputProcess(); // �Է� ó��

	// �÷��̾� �� �浹 üũ
	if (map->IsBarrier(mPos)) // ���̸� ���̴�
	{
		mPos = prevPos; // ���� ��ġ�� ���ư���
	}

	OnCollisionBalls(map, dir, prevPos); // ������ �浹 ó��

	map->SetGameObjectInMap(mCh, mPos, prevPos); // �ʿ� �÷��̾� ��ġ ����
}

void Player::Render()
{
}

DIRECTION Player::InputProcess()
{
	DIRECTION dir = DIRECTION::NONE; // �Է� ���� �ʱ�ȭ

	if (_kbhit()) // Ű �Է� Ȯ��
	{
		char input = _getch(); // Ű �Է� �ޱ�

		dir = Move(input, mPos); // �Է¿� ���� ���� ����
		mStepCount++; // ������ Ƚ�� ����

		Beep(800, 100); // �Ҹ� ���
	}

	return dir;
}


void Player::OnCollisionBalls(Map* map, DIRECTION dir, Pos& prevPos)
{
	// ������ �浹 ó��
	std::list<Ball*>& balls = Ball::GetBalls();
	for (std::list<Ball*>::iterator iter = balls.begin()
		; iter != balls.end()
		; iter++)
	{
		Pos ballPos = (*iter)->GetPos(); // ���� ��ġ ��������
		Pos prevBallPos = ballPos; // ���� ���� ��ġ ����
		if (mPos == ballPos) // �÷��̾�� ���� �浹�ϸ�
		{
			Move(dir, ballPos); // ���� �̵���Ű��

			// �� ���浹 üũ
			if (map->GetPixel(ballPos) == L'��'
				|| map->GetPixel(ballPos) == L'��')
			{
				ballPos = prevBallPos; // ���� ���� ��ġ�� ������

				// �÷��̾ �������� ���ϰ� �����־�� �Ѵ�.
				mPos = prevPos; // �÷��̾� ��ġ�� ���� ��ġ�� ������
			}

			(*iter)->SetPos(ballPos);
			map->SetGameObjectInMap((*iter)->GetWChar_t(), ballPos, prevBallPos);
		}
	}
}