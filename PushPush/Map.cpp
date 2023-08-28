#include "Map.h"
#include "Ball.h"
#include "Application.h"

// Map 클래스의 기본 생성자
Map::Map()
    : mDatas()           // 맵 데이터 초기화
    , mSize({ 0, 0 })   // 맵 크기 초기화
{
    memset(mGameObjects, 0, sizeof(GameObject*) * 128); // 게임 오브젝트 배열 초기화
}

// Map 클래스의 생성자
Map::Map(int x, int y)
    : mDatas()           // 맵 데이터 초기화
    , mSize({ x, y })   // 주어진 크기로 맵 크기 설정
{
    memset(mGameObjects, 0, sizeof(GameObject*) * 128); // 게임 오브젝트 배열 초기화
    mDatas.resize(mSize.y); // 맵 데이터 배열의 세로 크기 조정

    // 맵 데이터 배열 초기화
    for (size_t i = 0; i < mSize.y; i++)
    {
        mDatas[i].resize(mSize.x);
    }

    // 맵 데이터를 빈 공간과 불빛을 갖는 상태로 초기화
    for (size_t iy = 0; iy < mSize.y; iy++)
    {
        for (size_t ix = 0; ix < mSize.x; ix++)
        {
            mDatas[iy][ix].ch = L'ㅤ'; // 빈 공간으로 설정
            mDatas[iy][ix].isLight = false; // 불빛 상태를 false로 설정
        }
    }
}

// Map 클래스의 소멸자
Map::~Map()
{
    // 게임 오브젝트 배열에서 메모리 해제
    for (size_t i = 0; i < 128; i++)
    {
        if (mGameObjects[i] != nullptr)
        {
            delete mGameObjects[i];
            mGameObjects[i] = nullptr;
        }
    }

    // Ball 클래스의 Clear 함수 호출
    Ball::Clear();
}

// 스테이지 문자열을 기반으로 맵 데이터 초기화하는 함수
void Map::Initiailize(std::wstring& stageString)
{
    int idx = 0;
    for (size_t iY = 0; iY < mSize.y; iY++)
    {
        for (size_t iX = 0; iX < mSize.x; iX++)
        {
            mDatas[iY][iX].ch = stageString[idx++]; // 스테이지 문자열에서 읽어와 맵 데이터에 설정
        }
    }
}

// 맵 상태 업데이트 함수
void Map::Update()
{
    std::list<Ball*> balls = Ball::GetBalls(); // Ball 클래스에 저장된 공 객체 리스트 가져오기
    for (auto ball : balls)
    {
        Pos ballPos = (*ball).GetPos();
        mDatas[ballPos.y][ballPos.x].isLight = false; // 공이 위치한 곳의 불빛 상태를 해제
    }

    // 모든 게임 오브젝트 업데이트
    for (size_t i = 0; i < 128; i++)
    {
        if (mGameObjects[i] != nullptr)
            mGameObjects[i]->Update(this);
    }
}

// 맵 렌더링 함수
void Map::Render(int x, int y)
{
    IntersectHouseToBall(); // 집과 공의 교차 여부 체크

    // 맵 데이터에 따라 렌더링
    for (int iY = 0; iY < mSize.y; iY++)
    {
        for (int iX = 0; iX < mSize.x; iX++)
        {
            GOTO_XY((short)(x + iX * 2), (short)(y + iY));

            if (mDatas[iY][iX].ch == L'★')
            {
                Pen pen(COLOR::GREEN, mDatas[iY][iX].ch); // 플레이어가 위치한 곳은 초록색으로 표시
            }

            if (mDatas[iY][iX].isLight == false)
            {
                Pen pen(mDatas[iY][iX].ch); // 불빛이 없는 곳은 일반 색상으로 표시
            }
            else
            {
                void* p = new int();
                srand((int)p);

                // 0 ~ 15 사이의 색상 지정
                COLOR col = (COLOR)((rand() % 15) + 1);
                Pen pen(col, mDatas[iY][iX].ch); // 불빛이 있는 곳은 랜덤 색상으로 표시

                delete p;
            }
        }
    }
}

// 집과 공의 교차 여부를 체크하고 처리하는 함수
void Map::IntersectHouseToBall()
{
    std::vector<GameObject*> houses;
    for (size_t i = 0; i < 128; i++)
    {
        GameObject* temp = nullptr;
        if (mGameObjects[i] != nullptr)
        {
            temp = mGameObjects[i];

            if (temp->GetWChar_t() == L'◆')
            {
                houses.push_back(temp); // 집 객체를 모아둔 벡터에 추가
            }
        }
    }

    int collisionCount = 0;
    std::list<Ball*> balls = Ball::GetBalls(); // Ball 클래스에 저장된 공 객체 리스트 가져오기
    for (auto ball : balls)
    {
        for (GameObject* house : houses)
        {
            Pos ballPos = (*ball).GetPos();
            Pos housePos = house->GetPos();

            if (ballPos == housePos)
            {
                mDatas[housePos.y][housePos.x].isLight = true; // 집과 공이 교차하는 곳에 불빛 상태 설정
                collisionCount++;
            }
        }
    }

    if (collisionCount == Ball::GetBallsCount()) // 모든 공이 집에 교차하면
    {
        Application::GetInstance()->SetClearStage(true); // 스테이지 클리어 상태로 설정
    }

    for (GameObject* house : houses)
    {
        Pos housePos = house->GetPos();
        mDatas[housePos.y][housePos.x].ch = L'◆'; // 집 객체가 있는 곳에 집 모양으로 설정
    }
}

// 특정 위치에 문자를 설정하는 함수
void Map::SetGameObjectInMap(int x, int y, wchar_t ch)
{
    mDatas[y][x].ch = ch;
}

// 특정 위치에 문자와 위치 정보를 설정하는 함수
void Map::SetGameObjectInMap(wchar_t ch, Vector2 pos, Vector2 prevPos)
{
    if (prevPos.y == -1 || prevPos.x == -1)
    {
        // 이전 위치 정보가 없는 경우
    }
    else
    {
        mDatas[prevPos.y][prevPos.x].ch = L'ㅤ'; // 이전 위치의 문자를 빈 공간으로 설정
    }
    mDatas[pos.y][pos.x].ch = ch; // 새로운 위치에 문자 설정
}

// 게임 오브젝트를 맵에 추가하는 함수
void Map::AddGameObject(GameObject* gameObject)
{
    for (size_t i = 0; i < 128; i++)
    {
        if (mGameObjects[i] == nullptr)
        {
            mGameObjects[i] = gameObject; // 빈 공간에 게임 오브젝트 추가
            break;
        }
    }
}

// 주어진 위치가 벽인지 확인하는 함수
bool Map::IsBarrier(Pos playerPos)
{
    wchar_t ch = mDatas[playerPos.y][playerPos.x].ch;

    if (ch == L'▩') // 벽 문자인 경우
        return true; // 벽으로 처리

    return false; // 벽이 아님
}

// 주어진 위치의 문자 반환
wchar_t Map::GetPixel(Pos pos)
{
    return mDatas[pos.y][pos.x].ch;
}

// 주어진 위치의 문자 반환
wchar_t Map::GetPixel(int y, int x)
{
    return mDatas[y][x].ch;
}