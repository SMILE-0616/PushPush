#pragma once
#include "Scene.h"
#include "Player.h"
#include "Stage.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	virtual void Initiailize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

private:
	void InitializeMap(int stageNumber = 1);

private:
	Stage mStage;
};
