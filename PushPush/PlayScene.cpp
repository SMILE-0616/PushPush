#include "PlayScene.h"
#include "Application.h"
#include "Ball.h"
#include "Player.h"

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initiailize()
{
	if (Application::GetInstance()->GetIsClear())
	{
		InitializeMap(2);
	}
	else
	{
		InitializeMap();
	}
}

void PlayScene::Update()
{
	mMap->Update();
}

void PlayScene::Render()
{
	short x = SIZE_MAP_X * 2;
	short y = 3;

	SET_COLOR(COLOR::DARK_RED);
	GOTO_XY(x, (y + 2));   std::wcout << (L"┏━━━━━━━━━━━━━━━━┓ ");
	GOTO_XY(x, (y + 3));   std::wcout << (L"┃   PLAY SCENE   ┃ ");
	GOTO_XY(x, (y + 4));   std::wcout << (L"┗━━━━━━━━━━━━━━━━┛ ");

	SET_COLOR(COLOR::DARK_YELLOW);
	GOTO_XY(x, (y + 5));   std::wcout << (L"STAGE : ") << mStage.GetStageNumber() << "\n";
	SET_COLOR(COLOR::WHITE);
	GOTO_XY(x, (y + 6));   std::wcout << (L"STEP : ") << mMap->GetPlayer()->GetStepCount() << "\n";
	
	y = 5;
	SET_COLOR(COLOR::DARK_GREEN);
	GOTO_XY((x - 35), y++); printf("[ Backspace ] : undo\n");
	GOTO_XY((x - 35), y++); printf("[ Reset ] : R \n");
	GOTO_XY((x - 35), y++); printf("[ Esc ] : Exit \n");
	SET_COLOR(BLUE);
	y++;
	GOTO_XY((x - 35), y++); printf("[ H ] : Replay\n"); //타이틀씬으로


	SET_COLOR(GRAY);
	y = 5;
	GOTO_XY((x + 35), y++); printf("      W      ");
	GOTO_XY((x + 35), y++); printf("     ↑      ");
	GOTO_XY((x + 35), y++); printf(" A ←   → S ");
	GOTO_XY((x + 35), y++); printf("     ↓      ");
	GOTO_XY((x + 35), y++); printf("      D      ");

	y++;
	y++;
	SET_COLOR(DARK_BLUE);
	GOTO_XY((x + 35), y++); printf("[ PAGE_UP ] : Next stage");
	GOTO_XY((x + 35), y++); printf("[ PAGE_DOWN ] : Previous");

	x = SIZE_MAP_X * 2 + 1;
	y = (7 + 6);
	GOTO_XY(x, y);
	mMap->Render(x, y);
}

void PlayScene::Destroy()
{
	delete mMap;
}

void PlayScene::InitializeMap(int stageNumber)
{
	//mStage 메모장데이터를 읽어들어서
	//그거에맞게 세팅해준다
	mMap = mStage.Load(stageNumber);
	

}




