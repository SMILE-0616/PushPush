#include "Map.h"
#include "Ball.h"
#include "Application.h"

// Map Ŭ������ �⺻ ������
Map::Map()
    : mDatas()           // �� ������ �ʱ�ȭ
    , mSize({ 0, 0 })   // �� ũ�� �ʱ�ȭ
{
    memset(mGameObjects, 0, sizeof(GameObject*) * 128); // ���� ������Ʈ �迭 �ʱ�ȭ
}

// Map Ŭ������ ������
Map::Map(int x, int y)
    : mDatas()           // �� ������ �ʱ�ȭ
    , mSize({ x, y })   // �־��� ũ��� �� ũ�� ����
{
    memset(mGameObjects, 0, sizeof(GameObject*) * 128); // ���� ������Ʈ �迭 �ʱ�ȭ
    mDatas.resize(mSize.y); // �� ������ �迭�� ���� ũ�� ����

    // �� ������ �迭 �ʱ�ȭ
    for (size_t i = 0; i < mSize.y; i++)
    {
        mDatas[i].resize(mSize.x);
    }

    // �� �����͸� �� ������ �Һ��� ���� ���·� �ʱ�ȭ
    for (size_t iy = 0; iy < mSize.y; iy++)
    {
        for (size_t ix = 0; ix < mSize.x; ix++)
        {
            mDatas[iy][ix].ch = L'��'; // �� �������� ����
            mDatas[iy][ix].isLight = false; // �Һ� ���¸� false�� ����
        }
    }
}

// Map Ŭ������ �Ҹ���
Map::~Map()
{
    // ���� ������Ʈ �迭���� �޸� ����
    for (size_t i = 0; i < 128; i++)
    {
        if (mGameObjects[i] != nullptr)
        {
            delete mGameObjects[i];
            mGameObjects[i] = nullptr;
        }
    }

    // Ball Ŭ������ Clear �Լ� ȣ��
    Ball::Clear();
}

// �������� ���ڿ��� ������� �� ������ �ʱ�ȭ�ϴ� �Լ�
void Map::Initiailize(std::wstring& stageString)
{
    int idx = 0;
    for (size_t iY = 0; iY < mSize.y; iY++)
    {
        for (size_t iX = 0; iX < mSize.x; iX++)
        {
            mDatas[iY][iX].ch = stageString[idx++]; // �������� ���ڿ����� �о�� �� �����Ϳ� ����
        }
    }
}

// �� ���� ������Ʈ �Լ�
void Map::Update()
{
    std::list<Ball*> balls = Ball::GetBalls(); // Ball Ŭ������ ����� �� ��ü ����Ʈ ��������
    for (auto ball : balls)
    {
        Pos ballPos = (*ball).GetPos();
        mDatas[ballPos.y][ballPos.x].isLight = false; // ���� ��ġ�� ���� �Һ� ���¸� ����
    }

    // ��� ���� ������Ʈ ������Ʈ
    for (size_t i = 0; i < 128; i++)
    {
        if (mGameObjects[i] != nullptr)
            mGameObjects[i]->Update(this);
    }
}

// �� ������ �Լ�
void Map::Render(int x, int y)
{
    IntersectHouseToBall(); // ���� ���� ���� ���� üũ

    // �� �����Ϳ� ���� ������
    for (int iY = 0; iY < mSize.y; iY++)
    {
        for (int iX = 0; iX < mSize.x; iX++)
        {
            GOTO_XY((short)(x + iX * 2), (short)(y + iY));

            if (mDatas[iY][iX].ch == L'��')
            {
                Pen pen(COLOR::GREEN, mDatas[iY][iX].ch); // �÷��̾ ��ġ�� ���� �ʷϻ����� ǥ��
            }

            if (mDatas[iY][iX].isLight == false)
            {
                Pen pen(mDatas[iY][iX].ch); // �Һ��� ���� ���� �Ϲ� �������� ǥ��
            }
            else
            {
                void* p = new int();
                srand((int)p);

                // 0 ~ 15 ������ ���� ����
                COLOR col = (COLOR)((rand() % 15) + 1);
                Pen pen(col, mDatas[iY][iX].ch); // �Һ��� �ִ� ���� ���� �������� ǥ��

                delete p;
            }
        }
    }
}

// ���� ���� ���� ���θ� üũ�ϰ� ó���ϴ� �Լ�
void Map::IntersectHouseToBall()
{
    std::vector<GameObject*> houses;
    for (size_t i = 0; i < 128; i++)
    {
        GameObject* temp = nullptr;
        if (mGameObjects[i] != nullptr)
        {
            temp = mGameObjects[i];

            if (temp->GetWChar_t() == L'��')
            {
                houses.push_back(temp); // �� ��ü�� ��Ƶ� ���Ϳ� �߰�
            }
        }
    }

    int collisionCount = 0;
    std::list<Ball*> balls = Ball::GetBalls(); // Ball Ŭ������ ����� �� ��ü ����Ʈ ��������
    for (auto ball : balls)
    {
        for (GameObject* house : houses)
        {
            Pos ballPos = (*ball).GetPos();
            Pos housePos = house->GetPos();

            if (ballPos == housePos)
            {
                mDatas[housePos.y][housePos.x].isLight = true; // ���� ���� �����ϴ� ���� �Һ� ���� ����
                collisionCount++;
            }
        }
    }

    if (collisionCount == Ball::GetBallsCount()) // ��� ���� ���� �����ϸ�
    {
        Application::GetInstance()->SetClearStage(true); // �������� Ŭ���� ���·� ����
    }

    for (GameObject* house : houses)
    {
        Pos housePos = house->GetPos();
        mDatas[housePos.y][housePos.x].ch = L'��'; // �� ��ü�� �ִ� ���� �� ������� ����
    }
}

// Ư�� ��ġ�� ���ڸ� �����ϴ� �Լ�
void Map::SetGameObjectInMap(int x, int y, wchar_t ch)
{
    mDatas[y][x].ch = ch;
}

// Ư�� ��ġ�� ���ڿ� ��ġ ������ �����ϴ� �Լ�
void Map::SetGameObjectInMap(wchar_t ch, Vector2 pos, Vector2 prevPos)
{
    if (prevPos.y == -1 || prevPos.x == -1)
    {
        // ���� ��ġ ������ ���� ���
    }
    else
    {
        mDatas[prevPos.y][prevPos.x].ch = L'��'; // ���� ��ġ�� ���ڸ� �� �������� ����
    }
    mDatas[pos.y][pos.x].ch = ch; // ���ο� ��ġ�� ���� ����
}

// ���� ������Ʈ�� �ʿ� �߰��ϴ� �Լ�
void Map::AddGameObject(GameObject* gameObject)
{
    for (size_t i = 0; i < 128; i++)
    {
        if (mGameObjects[i] == nullptr)
        {
            mGameObjects[i] = gameObject; // �� ������ ���� ������Ʈ �߰�
            break;
        }
    }
}

// �־��� ��ġ�� ������ Ȯ���ϴ� �Լ�
bool Map::IsBarrier(Pos playerPos)
{
    wchar_t ch = mDatas[playerPos.y][playerPos.x].ch;

    if (ch == L'��') // �� ������ ���
        return true; // ������ ó��

    return false; // ���� �ƴ�
}

// �־��� ��ġ�� ���� ��ȯ
wchar_t Map::GetPixel(Pos pos)
{
    return mDatas[pos.y][pos.x].ch;
}

// �־��� ��ġ�� ���� ��ȯ
wchar_t Map::GetPixel(int y, int x)
{
    return mDatas[y][x].ch;
}