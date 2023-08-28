#pragma once
#include "Common.h"
#include "GameObject.h"
#include "Player.h"

// 출력용 가운데 좌표
#define SIZE_MAP_Y 30
#define SIZE_MAP_X 24

struct Pixel // 게임 맵의 한 칸을 나타내는 데이터
{
	wchar_t ch; // 문자
	bool isLight; // 빛 여부
};

class Scene;
class Map
{
public:
	Map();
	Map(int x, int y);
	~Map();

	void Initiailize(std::wstring& stageString); // 스테이지 문자열을 기반으로 맵을 초기화하는 함수
	void Update();
	void Render(int x, int y); // 게임 맵을 렌더링 하는 함수
	void IntersectHouseToBall(); // 집과 공의 충돌을 처리하는 함수
	void SetGameObjectInMap(int x, int y, wchar_t ch); // 주어진 위치에 특정 문자와 함께 게임 오브젝트를 설정하는 함수
	void SetGameObjectInMap(wchar_t ch, Vector2 pos, Vector2 prevPos = Vector2(-1, -1)); // 지정한 위치에 오브젝트를 설정하는 함수
	void SetPlayer(Player* player) { mPlayer = player; } // 플레이어 설정하는 함수
	Player* GetPlayer() { return mPlayer; } // 플레이어를 가져오는 함수

	void AddGameObject(GameObject* gameObject); // 게임 오브젝트를 추가하는 함수
	bool IsBarrier(Pos pos); // 주어진 위치가 장애물인지 확인하는 함수
	wchar_t GetPixel(Pos pos);
	wchar_t GetPixel(int y, int x); // 특정 위치의 픽셀을 가져오는 함수

private:
	//wchar_t** mDatas;

	std::vector<std::vector<Pixel>> mDatas;
	// 맵 데이터를 저장하는 2차원 벡터

	Size mSize; // 맵의 크기를 나타내는 객체

	GameObject* mGameObjects[128]; // 최대 128개의 게임 오브젝트를 저장하는 배열
	Player* mPlayer; // 플레이어 객체를 가리키는 포인터
	Scene* mPlayScene; // Scene 객체를 가리키는 포인터
};