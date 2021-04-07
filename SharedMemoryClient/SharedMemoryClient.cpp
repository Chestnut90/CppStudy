
#include "./../SharedMemoryLib/SharedMemory.h"
#include "./../SharedMemoryLib/DataStruct.h"
#pragma comment(lib, "./../x64/Debug/SharedMemoryLib.lib")

#include <iostream>

static void PrintArray(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;
}

static void PrintArray(float* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Shared Memory Client" << std::endl;
    DataStruct::Data* sharedData = new DataStruct::Data;

    std::wstring name = L"SMTEST";
    SharedMemory::SharedMemory* client = new SharedMemory::SharedMemory(name, (void*)sharedData, true);
    
	while (1)
	{
		std::cout << "wait host" << std::endl;
		if (client->Create())
		{
			std::cout << "created" << std::endl;
			break;
		}
		Sleep(1500);
	}
	
    while (1)
    {
        sharedData = (DataStruct::Data*)client->GetData();
        if (sharedData == nullptr)
        {
            std::cout << "nullptr" << std::endl;
            continue;
        }

        if (!sharedData->isReceived)
        {
            sharedData->isReceived = true;
            int size = sharedData->size;

            std::cout << "read data" << std::endl;
			std::cout << (unsigned long)sharedData->integers << std::endl;
			std::cout << (unsigned long)sharedData->floats << std::endl;
			PrintArray(sharedData->integers, size);
            PrintArray(sharedData->floats, size);

        }
    }
}