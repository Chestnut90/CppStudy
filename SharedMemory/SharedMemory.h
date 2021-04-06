#pragma once
#ifndef _SHAREDMEMORY_H_
#define	_SHAREDMEMORY_H_

#include <Windows.h>
#include <string>
#include <iostream>

#pragma pack(push, 1)
typedef struct Header
{
	bool isReceived;
	int size;
	int structSize;
};
#pragma pack(pop, 1)

#pragma pack(push, 1)
typedef struct Data : public Header
{
	int* integers;
	float* floats;
};
#pragma pack(pop, 1)

namespace SharedMemory
{
	//@ TODO : validation
	const SIZE_T MAX_SIZE = 100000;

	class SharedMemory
	{
	public:
		SharedMemory(std::wstring name, void * data, bool isClient=false);
		~SharedMemory();

		bool Create();
		void Destroy();

		void SetData(void* data, long size);
		void* GetData();

	private:
		HANDLE MakeFileMap();
		HANDLE OpenFileMap();

	private:

		//@ mapping file
		HANDLE mapFile;

		//@ void pointer of shared data
		PVOID data;	

		//@ name of this (named memory)
		std::wstring name;	
		
		bool isClient;
		bool isCreated;

	};
}

#endif // !_SHAREDMEMORY_H_
