#include "Application.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "Sound.h"


Application* Application::mInstance = nullptr;

void Application::InitializeNextStage()
{
}

Application::Application()
	: mbRunning(true) // true로 지정
	, mPlaySceneNumber((int)SCENETYPE::TITLE)
	, mClearStage(false) // int 형변환
{
	clear();
}

Application::~Application()
{

}

void Application::clear()
{
	for (int i = 0; i < SCENETYPE::END; i++)
	{
		mScenes[i] = nullptr;
	}
}

bool Application::Initiailize()
{
	Sound::Play(true);

	mScenes[SCENETYPE::TITLE] = new TitleScene(); // 동적할당을 해서 메모리 로스를 줄인다
	mScenes[SCENETYPE::PLAY] = new PlayScene();

	for (int i = 0; i < SCENETYPE::END; i++) // 모든 씬들을 초기화
	{
		mScenes[i]->Initiailize(); // 포인터로 바꿔서 . 이 -> 로 바뀜
	}

	return true;
}

void Application::Update()
{
	mScenes[mPlaySceneNumber]->Update(); // 플레이 씬만 update 해주면 된다!
}

void Application::Rendering()
{
	// system("cls"); // 지우고, window.h에 있는 함수
	mScenes[mPlaySceneNumber]->Render(); // 플레이 씬만 Render 해주면 된다
	Sleep(200); // CPU를 0.5초동안 멈춤 = 그린 상태를 0.5초동안 멈춘다는 의미

	if (mClearStage)
	{
		mScenes[mPlaySceneNumber]->Destroy(); // 씬타입이 바뀔때마다 Destroy
		mScenes[mPlaySceneNumber]->Initiailize(); // 씬타입이 바뀔때마다 Initiailize

		mClearStage = false; // bool 변수가 false
	}
}

void Application::Destroy() // 모든 씬들을 destroy 해줘야 함
{
	for (int i = 0; i < SCENETYPE::END; i++) // 모든 씬들을 초기화
	{
		mScenes[i]->Destroy();
	}

	for (int i = 0; i < SCENETYPE::END; i++) // 모든 씬들을 동적 할당 해제
	{
		if (mScenes[i] != nullptr)
			delete mScenes[i];
	}
}
