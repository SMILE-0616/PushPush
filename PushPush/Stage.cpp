#include "Stage.h"
#include "Player.h"
#include "Ball.h"
#include "House.h"
#include <string>

// Stage Ŭ������ ������
Stage::Stage()
    : mStageNumber(1) // �ʱ� �������� ��ȣ�� 1�� ����
{

}

// Stage Ŭ������ �Ҹ���
Stage::~Stage()
{

}

// ������ �������� ��ȣ�� �ش��ϴ� ���� �ҷ����� �Լ�
Map* Stage::Load(int stageNumber)
{
    FILE* fp = nullptr;
    mStageNumber = stageNumber; // ���޹��� �������� ��ȣ�� ��� ���� ������Ʈ
    std::string path = "..\\Stages\\Stage" + std::to_string(mStageNumber) + ".txt"; // �������� ���� ��� ����

    errno_t error = fopen_s(&fp, path.c_str(), "rt,ccs=UTF-8"); // ���� ���� �õ�

    if (error != 0)
    {
        std::wcout << L"�������� ������ �����ϴ�.\n";
        std::wcout << L"���� ��θ� Ȯ�����ּ���.\n";
        exit(0); // ���� ���⿡ ������ ��� ���α׷� ����
    }
    wchar_t buff[64] = L"";
    std::wstring x = fgetws(buff, 63, fp);
    std::wstring y = fgetws(buff, 63, fp);

    int mapX = std::stoi(x); // ���� ���� ũ�⸦ ������ ��ȯ�Ͽ� ����
    int mapY = std::stoi(y); // ���� ���� ũ�⸦ ������ ��ȯ�Ͽ� ����
    mMap = new Map(mapX, mapY); // �� ��ü ����

    for (size_t y = 0; y < mapY; y++)
    {
        fgetws(buff, 63, fp); // �� �پ� �� ���Ͽ��� �о��
        for (size_t x = 0; x < mapX; x++)
        {
            if (buff[x] == L'��' || buff[x] == L'��')
                mMap->SetGameObjectInMap(x, y, buff[x]); // �� ���� �Ǵ� ���� �ʿ� �߰�
            else
                CreateGameObject(buff[x], x, y); // ���� ������Ʈ ����
        }
    }

    fclose(fp); // ���� �ݱ�
    return mMap; // ������ �� ��ȯ
}

// �־��� Ÿ�Կ� ���� ���� ������Ʈ�� �����ϴ� �Լ�
void Stage::CreateGameObject(wchar_t type, int x, int y)
{
    switch (type)
    {
    case L'��': // �÷��̾� ����
    {
        Player* player = new Player(Pos(x, y)); // �÷��̾� ��ü ����
        mMap->AddGameObject(dynamic_cast<GameObject*>(player)); // �ʿ� �÷��̾� �߰�
        mMap->SetPlayer(player); // ���� �÷��̾� ����
    }
    break;

    case L'��': // �� ����
    {
        Ball* ball = new Ball(Pos(x, y)); // �� ��ü ����
        mMap->AddGameObject(dynamic_cast<GameObject*>(ball)); // �ʿ� �� �߰�
    }
    break;

    case L'��': // �� ����
    {
        House* house = new House(Pos(x, y)); // �� ��ü ����
        mMap->AddGameObject(dynamic_cast<GameObject*>(house)); // �ʿ� �� �߰�
    }
    break;

    default:
        break;
    }
}