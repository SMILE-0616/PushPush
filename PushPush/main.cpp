//메인 프로그램 및 유니티 사이클이 돌아가는 곳
#include <iostream>
#include "Application.h"

int main()
{
	setlocale(LC_ALL, ""); // 모든 언어를 처리해주는 함수

	Application::GetInstance()->Initiailize();

	while (Application::GetInstance()->GetIsRunning()) // 캐릭터가 죽거나 나가는 단축키를 누르면 isRunning 변수가 false가 되어서 while 문 탈출
	{
		Application::GetInstance()->Update();
		Application::GetInstance()->Rendering();
	}
	Application::GetInstance()->Destroy();

	return 0;
}