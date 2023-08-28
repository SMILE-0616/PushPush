#pragma once
#include "Common.h"


class Map;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(Map* map) {} // ���� ������� ������Ʈ
	virtual void Render() {} // �������� �����Ѵ�

	void SetPos(Vector2 pos) { mPos = pos; } // ��ġ�� �����Ѵ�
	void SetPos(int x, int y) { mPos.x = x; mPos.y = y; } // x, y ��ǥ�� �̿��� ��ġ�� �����Ѵ�
	Vector2 GetPos() { return mPos; } // ���� ��ġ�� �����´�

	void SetWChar_t(wchar_t ch) { mCh = ch; } // �����ڵ� ���ڸ� �����Ѵ�
	wchar_t GetWChar_t() { return mCh; } // �����ڵ� ���ڸ� �����´�

	DIRECTION Move(DIRECTION inputDir, Pos& pos); // �Է� ���⿡ ���� �̵��ϰ� ��� ������ ��ȯ
	DIRECTION Move(char ch, Pos& pos); // Ư�� ���ڿ� ���� �̵��ϰ� ��� ������ ��ȯ

protected:
	Vector2 mPos; // ���� ������Ʈ ��ǥ�� ���� ���ϹǷ� protected�� ����
	wchar_t mCh;
};
