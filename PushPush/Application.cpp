#include "Application.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "Sound.h"


Application* Application::mInstance = nullptr;

void Application::InitializeNextStage()
{
}

Application::Application()
	: mbRunning(true) // true�� ����
	, mPlaySceneNumber((int)SCENETYPE::TITLE)
	, mClearStage(false) // int ����ȯ
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

	mScenes[SCENETYPE::TITLE] = new TitleScene(); // �����Ҵ��� �ؼ� �޸� �ν��� ���δ�
	mScenes[SCENETYPE::PLAY] = new PlayScene();

	for (int i = 0; i < SCENETYPE::END; i++) // ��� ������ �ʱ�ȭ
	{
		mScenes[i]->Initiailize(); // �����ͷ� �ٲ㼭 . �� -> �� �ٲ�
	}

	return true;
}

void Application::Update()
{
	mScenes[mPlaySceneNumber]->Update(); // �÷��� ���� update ���ָ� �ȴ�!
}

void Application::Rendering()
{
	// system("cls"); // �����, window.h�� �ִ� �Լ�
	mScenes[mPlaySceneNumber]->Render(); // �÷��� ���� Render ���ָ� �ȴ�
	Sleep(200); // CPU�� 0.5�ʵ��� ���� = �׸� ���¸� 0.5�ʵ��� ����ٴ� �ǹ�

	if (mClearStage)
	{
		mScenes[mPlaySceneNumber]->Destroy(); // ��Ÿ���� �ٲ𶧸��� Destroy
		mScenes[mPlaySceneNumber]->Initiailize(); // ��Ÿ���� �ٲ𶧸��� Initiailize

		mClearStage = false; // bool ������ false
	}
}

void Application::Destroy() // ��� ������ destroy ����� ��
{
	for (int i = 0; i < SCENETYPE::END; i++) // ��� ������ �ʱ�ȭ
	{
		mScenes[i]->Destroy();
	}

	for (int i = 0; i < SCENETYPE::END; i++) // ��� ������ ���� �Ҵ� ����
	{
		if (mScenes[i] != nullptr)
			delete mScenes[i];
	}
}
