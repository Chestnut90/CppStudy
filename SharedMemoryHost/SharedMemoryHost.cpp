// SharedMemoryHost.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "./../SharedMemoryLib/SharedMemory.h"
#include "./../SharedMemoryLib/DataStruct.h"
#pragma comment(lib, "./../x64/Debug/SharedMemoryLib.lib")

#include <iostream>

static void MemoryStage(DataStruct::Data * data)
{
	std::cout << (unsigned long)(data) << std::endl;

	std::cout << (unsigned long)&(data->isReceived) << std::endl;
	std::cout << (unsigned long)&(data->size) << std::endl;
	std::cout << (unsigned long)&(data->structSize) << std::endl;
	
	std::cout << (unsigned long)data->integers << std::endl;
	for (int i = 0; i < data->size; i++)
	{
		std::cout << (unsigned long)&(data->integers[i]) << std::endl;
	}
	std::cout << (unsigned long)data->floats << std::endl;
	for (int i = 0; i < data->size; i++)
	{
		std::cout << (unsigned long)&(data->floats[i]) << std::endl;
	}
}

static void CreateData(DataStruct::Data * data, int size)
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

	//MemoryStage(data);
}

int main()
{
	std::cout << "Shared memory host" << std::endl;

	DataStruct::Data* sharedData = new DataStruct::Data;
	int size = 10;

	std::wstring name = L"SMTEST";

	SharedMemory::SharedMemory* SM = new SharedMemory::SharedMemory(name, (void*)sharedData);

	if (!SM->Create())
	{
		return -1;
	}

	while (1)
	{
		std::cout << "Set Memory with size : " << size << std::endl;
		CreateData(sharedData, size);
		SM->SetData(sharedData, sharedData->structSize);
		size++;

		Sleep(4000);
	}
}
