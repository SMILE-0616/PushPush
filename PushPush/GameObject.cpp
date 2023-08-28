#include "GameObject.h"

GameObject::GameObject()
    : mPos()      // 위치 정보 초기화
    , mCh('\0')   // 문자 초기화
{

}

GameObject::~GameObject()
{
    // 추가적인 소멸 작업 없음
}

// 지정된 방향으로 위치를 변경하는 함수
DIRECTION GameObject::Move(DIRECTION inputDir, Pos& pos)
{
    DIRECTION dir = inputDir;
    switch (dir)
    {
    case DIRECTION::UP:
    {
        pos.y -= 1; // 위로 이동
        dir = DIRECTION::UP;
    }
    break;

    case DIRECTION::LEFT:
    {
        pos.x -= 1; // 왼쪽으로 이동
        dir = DIRECTION::LEFT;
    }
    break;

    case DIRECTION::DOWN:
    {
        pos.y += 1; // 아래로 이동
        dir = DIRECTION::DOWN;
    }
    break;

    case DIRECTION::RIGHT:
    {
        pos.x += 1; // 오른쪽으로 이동
        dir = DIRECTION::RIGHT;
    }
    break;

    default:
        break;
    }

    return dir;
}

// 입력된 문자에 따라 위치를 변경하는 함수
DIRECTION GameObject::Move(char ch, Pos& pos)
{
    DIRECTION dir = DIRECTION::NONE;
    switch (ch)
    {
    case 'W':
    {
        pos.y -= 1; // 위로 이동
        dir = DIRECTION::UP;
    }
    break;

    case 'A':
    {
        pos.x -= 1; // 왼쪽으로 이동
        dir = DIRECTION::LEFT;
    }
    break;

    case 'S':
    {
        pos.y += 1; // 아래로 이동
        dir = DIRECTION::DOWN;
    }
    break;

    case 'D':
    {
        pos.x += 1; // 오른쪽으로 이동
        dir = DIRECTION::RIGHT;
    }
    break;

    default:
        break;
    }

    return dir;
}