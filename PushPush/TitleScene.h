#pragma once
#include "Scene.h"


class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();

	virtual void Initiailize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

private:
	
};

