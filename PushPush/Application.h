#pragma once
#include "Common.h"
#include "Scene.h"

enum SCENETYPE
{
	TITLE,
	PLAY,
	END,
};

// �̱��� ����
class Application
{
public:
	static Application* GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new Application(); // Application Ŭ���� �Ҵ�
		}

		return mInstance;
	}

public:
	// ����Ƽ ������ ����Ŭ
	bool Initiailize(); // �ʱ�ȭ���� �� �߸��� ��츦 ����ؼ� void -> bool
	void Update();
	void Rendering();
	void Destroy();

	bool GetIsRunning() { return mbRunning; } // private�� �ִ� isRunning bool ������ �������� �Լ�
	void SetIsRunning(bool running) { mbRunning = running; }
	void SetPlaySceneNumber(int number) { mPlaySceneNumber = number; }
	bool GetIsClear() { return mClearStage; }
	void SetClearStage(bool value) { mClearStage = value; }
	void InitializeNextStage(); // ���� ���������� �ʱ�ȭ

private:
	Application(); //���� �۾� �� �����丵���� .cpp ���Ͽ� Applicaiton ����
	~Application();

	void clear(); // Ŭ���� ���ִ� �Լ�

private:
	static Application* mInstance;
	bool mbRunning; // ��, �������� ���ư��� ���� �����ϴ� bool ����
	Scene* mScenes[SCENETYPE::END]; // �����Լ��̹Ƿ� �����ͷ� �ٲ��ش�
	int mPlaySceneNumber;
	bool mClearStage;
};


