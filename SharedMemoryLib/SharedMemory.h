#pragma once
#ifndef _SHAREDMEMORY_H_
#define	_SHAREDMEMORY_H_

#include "pch.h"
#include <Windows.h>
#include <string>
#include <iostream>

namespace SharedMemory
{
	//@ TODO : validation
	// bytes
	const SIZE_T MAX_SIZE = 100000;

	class DllExport SharedMemory
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
