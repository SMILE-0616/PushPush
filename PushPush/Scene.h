#pragma once
#include "Map.h"


// 추상클래스 ( 순수가상함수가 하나라도 들어 있으면 )
class Scene
{
public:
	Scene();
	~Scene();

	// 순수가상함수
	virtual void Initiailize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

protected:
	Map* mMap;
};

