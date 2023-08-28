#include "Ball.h"
#include "Map.h"
#include "Application.h"

// Ball Ŭ������ ���� ��� ���� �ʱ�ȭ
int Ball::mBallCount = 0;
std::list<Ball*> Ball::mBalls;

// ������ �� ��ü���� �ʱ�ȭ�ϴ� �Լ�
void Ball::Clear()
{
    mBalls.clear();       // ������ �� ��ü ����Ʈ �ʱ�ȭ
    mBallCount = 0;       // ������ �� ��ü �� �ʱ�ȭ
}

// �⺻ ������
Ball::Ball()
{
    Initialize();         // �� ��ü �ʱ�ȭ �Լ� ȣ��
}

// ��ġ ������ �޴� ������
Ball::Ball(Pos pos)
{
    Initialize(pos);      // �� ��ü �ʱ�ȭ �Լ� ȣ��
}

// �Ҹ���
Ball::~Ball()
{
    // �߰����� �۾� ����
}

// �� ��ü�� �ʱ�ȭ�ϴ� �Լ�
void Ball::Initialize(Pos pos)
{
    mPos = pos;           // ��ġ ���� ����
    mCh = L'��';           // �� ��� ����

    mBallCount++;         // ������ �� ��ü �� ����
    mBalls.push_back(this); // ������ �� ��ü�� ����Ʈ�� �߰�
}

// �� ��ü�� ���¸� ������Ʈ�ϴ� �Լ�
void Ball::Update(Map* map)
{
    Pos prevPos = mPos;     // ���� ��ġ ���� ����
    map->SetGameObjectInMap(mCh, mPos, prevPos); // �ʿ� �� ��ü ���� ������Ʈ
}

// �� ��ü�� �������ϴ� �Լ�
void Ball::Render()
{
    // �������� ����
}