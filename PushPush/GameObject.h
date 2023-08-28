#pragma once
#include "Common.h"


class Map;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(Map* map) {} // 맵을 기반으로 업데이트
	virtual void Render() {} // 렌더링을 수반한다

	void SetPos(Vector2 pos) { mPos = pos; } // 위치를 설정한다
	void SetPos(int x, int y) { mPos.x = x; mPos.y = y; } // x, y 좌표를 이용해 위치를 설정한다
	Vector2 GetPos() { return mPos; } // 현재 위치를 가져온다

	void SetWChar_t(wchar_t ch) { mCh = ch; } // 유니코드 문자를 설정한다
	wchar_t GetWChar_t() { return mCh; } // 유니코드 문자를 가져온다

	DIRECTION Move(DIRECTION inputDir, Pos& pos); // 입력 방향에 따라 이동하고 결과 방향을 반환
	DIRECTION Move(char ch, Pos& pos); // 특정 문자에 따라 이동하고 결과 방향을 반환

protected:
	Vector2 mPos; // 게임 오브젝트 좌표는 변경 못하므로 protected로 지정
	wchar_t mCh;
};
