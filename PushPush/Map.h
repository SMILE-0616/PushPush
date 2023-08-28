#pragma once
#include "Common.h"
#include "GameObject.h"
#include "Player.h"

// ��¿� ��� ��ǥ
#define SIZE_MAP_Y 30
#define SIZE_MAP_X 24

struct Pixel // ���� ���� �� ĭ�� ��Ÿ���� ������
{
	wchar_t ch; // ����
	bool isLight; // �� ����
};

class Scene;
class Map
{
public:
	Map();
	Map(int x, int y);
	~Map();

	void Initiailize(std::wstring& stageString); // �������� ���ڿ��� ������� ���� �ʱ�ȭ�ϴ� �Լ�
	void Update();
	void Render(int x, int y); // ���� ���� ������ �ϴ� �Լ�
	void IntersectHouseToBall(); // ���� ���� �浹�� ó���ϴ� �Լ�
	void SetGameObjectInMap(int x, int y, wchar_t ch); // �־��� ��ġ�� Ư�� ���ڿ� �Բ� ���� ������Ʈ�� �����ϴ� �Լ�
	void SetGameObjectInMap(wchar_t ch, Vector2 pos, Vector2 prevPos = Vector2(-1, -1)); // ������ ��ġ�� ������Ʈ�� �����ϴ� �Լ�
	void SetPlayer(Player* player) { mPlayer = player; } // �÷��̾� �����ϴ� �Լ�
	Player* GetPlayer() { return mPlayer; } // �÷��̾ �������� �Լ�

	void AddGameObject(GameObject* gameObject); // ���� ������Ʈ�� �߰��ϴ� �Լ�
	bool IsBarrier(Pos pos); // �־��� ��ġ�� ��ֹ����� Ȯ���ϴ� �Լ�
	wchar_t GetPixel(Pos pos);
	wchar_t GetPixel(int y, int x); // Ư�� ��ġ�� �ȼ��� �������� �Լ�

private:
	//wchar_t** mDatas;

	std::vector<std::vector<Pixel>> mDatas;
	// �� �����͸� �����ϴ� 2���� ����

	Size mSize; // ���� ũ�⸦ ��Ÿ���� ��ü

	GameObject* mGameObjects[128]; // �ִ� 128���� ���� ������Ʈ�� �����ϴ� �迭
	Player* mPlayer; // �÷��̾� ��ü�� ����Ű�� ������
	Scene* mPlayScene; // Scene ��ü�� ����Ű�� ������
};