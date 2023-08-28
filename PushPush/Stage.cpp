#include "Stage.h"
#include "Player.h"
#include "Ball.h"
#include "House.h"
#include <string>

// Stage 클래스의 생성자
Stage::Stage()
    : mStageNumber(1) // 초기 스테이지 번호를 1로 설정
{

}

// Stage 클래스의 소멸자
Stage::~Stage()
{

}

// 지정된 스테이지 번호에 해당하는 맵을 불러오는 함수
Map* Stage::Load(int stageNumber)
{
    FILE* fp = nullptr;
    mStageNumber = stageNumber; // 전달받은 스테이지 번호로 멤버 변수 업데이트
    std::string path = "..\\Stages\\Stage" + std::to_string(mStageNumber) + ".txt"; // 스테이지 파일 경로 생성

    errno_t error = fopen_s(&fp, path.c_str(), "rt,ccs=UTF-8"); // 파일 열기 시도

    if (error != 0)
    {
        std::wcout << L"스테이지 파일이 없습니다.\n";
        std::wcout << L"파일 경로를 확인해주세요.\n";
        exit(0); // 파일 열기에 실패한 경우 프로그램 종료
    }
    wchar_t buff[64] = L"";
    std::wstring x = fgetws(buff, 63, fp);
    std::wstring y = fgetws(buff, 63, fp);

    int mapX = std::stoi(x); // 맵의 가로 크기를 정수로 변환하여 저장
    int mapY = std::stoi(y); // 맵의 세로 크기를 정수로 변환하여 저장
    mMap = new Map(mapX, mapY); // 맵 객체 생성

    for (size_t y = 0; y < mapY; y++)
    {
        fgetws(buff, 63, fp); // 한 줄씩 맵 파일에서 읽어옴
        for (size_t x = 0; x < mapX; x++)
        {
            if (buff[x] == L'ㅤ' || buff[x] == L'▩')
                mMap->SetGameObjectInMap(x, y, buff[x]); // 빈 공간 또는 벽을 맵에 추가
            else
                CreateGameObject(buff[x], x, y); // 게임 오브젝트 생성
        }
    }

    fclose(fp); // 파일 닫기
    return mMap; // 생성된 맵 반환
}

// 주어진 타입에 따라 게임 오브젝트를 생성하는 함수
void Stage::CreateGameObject(wchar_t type, int x, int y)
{
    switch (type)
    {
    case L'★': // 플레이어 생성
    {
        Player* player = new Player(Pos(x, y)); // 플레이어 객체 생성
        mMap->AddGameObject(dynamic_cast<GameObject*>(player)); // 맵에 플레이어 추가
        mMap->SetPlayer(player); // 맵의 플레이어 설정
    }
    break;

    case L'●': // 공 생성
    {
        Ball* ball = new Ball(Pos(x, y)); // 공 객체 생성
        mMap->AddGameObject(dynamic_cast<GameObject*>(ball)); // 맵에 공 추가
    }
    break;

    case L'◆': // 집 생성
    {
        House* house = new House(Pos(x, y)); // 집 객체 생성
        mMap->AddGameObject(dynamic_cast<GameObject*>(house)); // 맵에 집 추가
    }
    break;

    default:
        break;
    }
}