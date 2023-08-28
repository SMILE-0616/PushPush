#pragma once
#include "Common.h"
#include "GameObject.h"


class House : public GameObject
{
public:
	House();
	House(Pos pos);
	~House();

	virtual void Update(Map* map) override;
	virtual void Render() override;

private:
};

