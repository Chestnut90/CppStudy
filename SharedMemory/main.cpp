// SharedMemory.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "SharedMemory.h"

static void CreateData(Data * data, int size)
{
	data->isReceived = false;
	data->integers = new int[size];
	data->floats = new float[size];
	data->size = size;
	data->structSize = sizeof(int) + (sizeof(float) + sizeof(int)) * size + sizeof(bool);
	int msize = sizeof(data);
	int msize2 = _msize(data);
	for (int i = 0; i < size; i++)
	{
		data->integers[i] = i;
		data->floats[i] = (float)i;
	}
}

int main()
{
	std::cout << "Shared memory host" << std::endl;

	Data* sharedData = new Data;
	int size = 10;
	CreateData(sharedData, size);

	std::wstring name = L"SMTEST";

	SharedMemory::SharedMemory* SM = new SharedMemory::SharedMemory(name, (void*)sharedData);
	
	if (!SM->Create())
	{
		return -1;
	}

	while (1)
	{
		std::cout << "Set Memory with size : " << size << std::endl;
		SM->SetData(sharedData, sharedData->structSize);
		Sleep(2000);

		size++;
		CreateData(sharedData, size);
	}
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
