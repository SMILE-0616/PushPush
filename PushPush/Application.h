#pragma once
#include "Common.h"
#include "Scene.h"

enum SCENETYPE
{
	TITLE,
	PLAY,
	END,
};

// 싱글턴 패턴
class Application
{
public:
	static Application* GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new Application(); // Application 클래스 할당
		}

		return mInstance;
	}

public:
	// 유니티 라이프 사이클
	bool Initiailize(); // 초기화했을 때 잘못될 경우를 대비해서 void -> bool
	void Update();
	void Rendering();
	void Destroy();

	bool GetIsRunning() { return mbRunning; } // private에 있는 isRunning bool 변수를 가져오는 함수
	void SetIsRunning(bool running) { mbRunning = running; }
	void SetPlaySceneNumber(int number) { mPlaySceneNumber = number; }
	bool GetIsClear() { return mClearStage; }
	void SetClearStage(bool value) { mClearStage = value; }
	void InitializeNextStage(); // 다음 스테이지를 초기화

private:
	Application(); //빠른 작업 및 리펙토링으로 .cpp 파일에 Applicaiton 정의
	~Application();

	void clear(); // 클리어 해주는 함수

private:
	static Application* mInstance;
	bool mbRunning; // 참, 거짓으로 돌아가는 것을 구분하는 bool 변수
	Scene* mScenes[SCENETYPE::END]; // 가상함수이므로 포인터로 바꿔준다
	int mPlaySceneNumber;
	bool mClearStage;
};


