#include "Ball.h"
#include "Map.h"
#include "Application.h"

// Ball 클래스의 정적 멤버 변수 초기화
int Ball::mBallCount = 0;
std::list<Ball*> Ball::mBalls;

// 생성된 공 객체들을 초기화하는 함수
void Ball::Clear()
{
    mBalls.clear();       // 생성된 공 객체 리스트 초기화
    mBallCount = 0;       // 생성된 공 객체 수 초기화
}

// 기본 생성자
Ball::Ball()
{
    Initialize();         // 공 객체 초기화 함수 호출
}

// 위치 정보를 받는 생성자
Ball::Ball(Pos pos)
{
    Initialize(pos);      // 공 객체 초기화 함수 호출
}

// 소멸자
Ball::~Ball()
{
    // 추가적인 작업 없음
}

// 공 객체를 초기화하는 함수
void Ball::Initialize(Pos pos)
{
    mPos = pos;           // 위치 정보 설정
    mCh = L'●';           // 공 모양 설정

    mBallCount++;         // 생성된 공 객체 수 증가
    mBalls.push_back(this); // 생성된 공 객체를 리스트에 추가
}

// 공 객체의 상태를 업데이트하는 함수
void Ball::Update(Map* map)
{
    Pos prevPos = mPos;     // 이전 위치 정보 저장
    map->SetGameObjectInMap(mCh, mPos, prevPos); // 맵에 공 객체 정보 업데이트
}

// 공 객체를 렌더링하는 함수
void Ball::Render()
{
    // 구현되지 않음
}