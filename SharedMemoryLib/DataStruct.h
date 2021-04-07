#pragma once
#ifndef _DATASTRUCT_H_
#define _DATASTRUCT_H_

#include "pch.h"

namespace DataStruct
{
#pragma pack(push, 1)
	typedef struct DllExport Header
	{
		bool isReceived;
		int size;
		int structSize;
	};
#pragma pack(pop, 1)

#pragma pack(push, 1)
	typedef struct DllExport Data : public Header
	{
		int* integers;
		float* floats;
	};
#pragma pack(pop, 1)
}

#endif // !_DATASTRUCT_H_
