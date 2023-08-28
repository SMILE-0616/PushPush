#include "GameObject.h"

GameObject::GameObject()
    : mPos()      // ��ġ ���� �ʱ�ȭ
    , mCh('\0')   // ���� �ʱ�ȭ
{

}

GameObject::~GameObject()
{
    // �߰����� �Ҹ� �۾� ����
}

// ������ �������� ��ġ�� �����ϴ� �Լ�
DIRECTION GameObject::Move(DIRECTION inputDir, Pos& pos)
{
    DIRECTION dir = inputDir;
    switch (dir)
    {
    case DIRECTION::UP:
    {
        pos.y -= 1; // ���� �̵�
        dir = DIRECTION::UP;
    }
    break;

    case DIRECTION::LEFT:
    {
        pos.x -= 1; // �������� �̵�
        dir = DIRECTION::LEFT;
    }
    break;

    case DIRECTION::DOWN:
    {
        pos.y += 1; // �Ʒ��� �̵�
        dir = DIRECTION::DOWN;
    }
    break;

    case DIRECTION::RIGHT:
    {
        pos.x += 1; // ���������� �̵�
        dir = DIRECTION::RIGHT;
    }
    break;

    default:
        break;
    }

    return dir;
}

// �Էµ� ���ڿ� ���� ��ġ�� �����ϴ� �Լ�
DIRECTION GameObject::Move(char ch, Pos& pos)
{
    DIRECTION dir = DIRECTION::NONE;
    switch (ch)
    {
    case 'W':
    {
        pos.y -= 1; // ���� �̵�
        dir = DIRECTION::UP;
    }
    break;

    case 'A':
    {
        pos.x -= 1; // �������� �̵�
        dir = DIRECTION::LEFT;
    }
    break;

    case 'S':
    {
        pos.y += 1; // �Ʒ��� �̵�
        dir = DIRECTION::DOWN;
    }
    break;

    case 'D':
    {
        pos.x += 1; // ���������� �̵�
        dir = DIRECTION::RIGHT;
    }
    break;

    default:
        break;
    }

    return dir;
}