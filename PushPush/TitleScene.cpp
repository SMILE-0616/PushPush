#include "TitleScene.h"
#include "Application.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initiailize()
{
}

void TitleScene::Update() // ENTER를 누르면 플레 이씬으로 넘어간다
{
	if (_kbhit())
	{        //키보드 입력 확인 (true / false)
		char input = _getch();
		if (input == '\r') // \r은 enter 라는 의미
		{
			system("cls");
			SET_COLOR(COLOR::BLACK);
			Application::GetInstance()->SetPlaySceneNumber(SCENETYPE::PLAY);
		}
	}
}

void TitleScene::Render() // 타이틀 화면을 그려준다
{
	short x = SIZE_MAP_X * 2;
	short y = 10;

	SET_COLOR(COLOR::SKY_BLUE);
	GOTO_XY((x + 2), (y + 1));   std::wcout << (L"P U S H  P U S H");
	SET_COLOR(COLOR::DARK_YELLOW);
	GOTO_XY(x, (y + 2));   std::wcout << (L"┏━━━━━━━━━━━━━━━━┓");
	GOTO_XY(x, (y + 3));   std::wcout << (L"┃P U S H  P U S H┃");
	GOTO_XY(x, (y + 4));   std::wcout << (L"┃ made by AR 44th┃");
	GOTO_XY(x, (y + 5));   std::wcout << (L"┗━━━━━━━━━━━━━━━━┛");

	GOTO_XY(x, (y + 8));   std::wcout << (L"   PRESS ENTER");
	SET_COLOR(COLOR::YELLOW);

	// 반짝거리는 효과
	int to_add = 0;
	int cur_color = 0;
	while (true)
	{
		GOTO_XY((x - 7), (y + 9));
		for (to_add = 0; to_add < 37; to_add++)
		{
			SET_COLOR((cur_color + to_add) % 16 * 16);
			std::wcout << L" ";
		}
		if (cur_color > 0)
			cur_color--;
		else
			cur_color = 15;
		Sleep(100);

		if (_kbhit())
		{
			break;
		}
	}
}

void TitleScene::Destroy()
{
}