#include "Player.h"
#include "Map.h"
#include "Ball.h"

Player::Player()
{
	mCh = L'★'; // 플레이어 문자 설정
	mPos.y = 4; // 초기 y 좌표
	mPos.x = 4; // 초기 x 좌표
	mStepCount = 0; // 움직인 횟수 초기화
}

Player::Player(Pos pos)
{
	mCh = L'★';
	mPos.y = pos.y;
	mPos.x = pos.x;
	mStepCount = 0;
}

Player::~Player()
{
}

void Player::Update(Map* map)
{
	Pos prevPos = mPos; // 이전 위치 저장
	DIRECTION dir = InputProcess(); // 입력 처리

	// 플레이어 벽 충돌 체크
	if (map->IsBarrier(mPos)) // 참이면 벽이다
	{
		mPos = prevPos; // 이전 위치로 돌아가기
	}

	OnCollisionBalls(map, dir, prevPos); // 공과의 충돌 처리

	map->SetGameObjectInMap(mCh, mPos, prevPos); // 맵에 플레이어 위치 개신
}

void Player::Render()
{
}

DIRECTION Player::InputProcess()
{
	DIRECTION dir = DIRECTION::NONE; // 입력 방향 초기화

	if (_kbhit()) // 키 입력 확인
	{
		char input = _getch(); // 키 입력 받기

		dir = Move(input, mPos); // 입력에 따라 방향 결정
		mStepCount++; // 움직인 횟수 증가

		Beep(800, 100); // 소리 출력
	}

	return dir;
}


void Player::OnCollisionBalls(Map* map, DIRECTION dir, Pos& prevPos)
{
	// 공과의 충돌 처리
	std::list<Ball*>& balls = Ball::GetBalls();
	for (std::list<Ball*>::iterator iter = balls.begin()
		; iter != balls.end()
		; iter++)
	{
		Pos ballPos = (*iter)->GetPos(); // 공의 위치 가져오기
		Pos prevBallPos = ballPos; // 이전 공의 위치 저장
		if (mPos == ballPos) // 플레이어와 공이 충돌하면
		{
			Move(dir, ballPos); // 공을 이동시키기

			// 공 벽충돌 체크
			if (map->GetPixel(ballPos) == L'▩'
				|| map->GetPixel(ballPos) == L'●')
			{
				ballPos = prevBallPos; // 공을 원래 위치로 돌리기

				// 플레이어도 움직이지 못하게 돌려주어야 한다.
				mPos = prevPos; // 플레이어 위치를 이전 위치로 돌리기
			}

			(*iter)->SetPos(ballPos);
			map->SetGameObjectInMap((*iter)->GetWChar_t(), ballPos, prevBallPos);
		}
	}
}