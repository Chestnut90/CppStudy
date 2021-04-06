
#include <iostream>
#include "SharedMemory.h"

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

int clientMain()
{
    std::cout << "Shared Memory Client" << std::endl;

    Data* sharedData = new Data;

    std::wstring name = L"SMTEST";
    SharedMemory::SharedMemory* client = new SharedMemory::SharedMemory(name, (void*)sharedData, true);
    if (!client->Create())
    {
        return -1;
    }

    while (1)
    {
        sharedData = (Data*)client->GetData();
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
            PrintArray(sharedData->integers, size);
            PrintArray(sharedData->floats, size);

        }
    }

}