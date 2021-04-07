#include "pch.h"
#include "SharedMemory.h"

SharedMemory::SharedMemory::SharedMemory(std::wstring name, void * data, bool isClient)
{
	this->name = name;
	this->data = data;
	this->isClient = isClient;
	this->isCreated = false;
}

SharedMemory::SharedMemory::~SharedMemory()
{
	this->Destroy();
}

//@ Create Shared Memory
bool SharedMemory::SharedMemory::Create()
{
	DWORD lastError;
	try
	{
		this->mapFile = isClient ? OpenFileMap() : MakeFileMap();
		if (mapFile == NULL)
		{
			// TODO : error code
			DWORD lastError = GetLastError();
			std::string error = "Failed to create file mapping. Error {%d}.\n";
			throw std::exception(error.c_str());
		}

		// Map View of File

		DWORD desiredAccess = FILE_MAP_ALL_ACCESS;
		DWORD highOffset = 0;
		DWORD lowOffset = 0;
		data = MapViewOfFile(
			mapFile,
			desiredAccess,
			highOffset,
			lowOffset,
			MAX_SIZE);

		if (data == NULL)
		{
			CloseHandle(mapFile);

			// TODO : error code
			lastError = GetLastError();
			std::string error = "Failed to Map view of file. Error {%d}.\n";
			throw std::exception(error.c_str());
		}
		isCreated = true;
	}
	catch (const std::exception& e)
	{
		printf(e.what());
		isCreated = false;
	}

	return isCreated;
}

//@ Destroy Shared Memory
void SharedMemory::SharedMemory::Destroy()
{
	if (!isCreated)
	{
		return;
	}

	UnmapViewOfFile(this->data);
	CloseHandle(mapFile);
}

//@ Set data with size
void SharedMemory::SharedMemory::SetData(void * data, long size)
{
	if (isClient)
	{
		return;
	}
	
	CopyMemory(this->data, data, size);
}

//@ Get data
void* SharedMemory::SharedMemory::GetData()
{
	if (!isClient)
	{
		return nullptr;
	}

	return data;
}

//@ Create File Mapping for Server
HANDLE SharedMemory::SharedMemory::MakeFileMap()
{
	HANDLE invalidHandle = INVALID_HANDLE_VALUE;
	LPSECURITY_ATTRIBUTES securityAttributes = NULL;
	DWORD access = PAGE_READWRITE;
	DWORD highOrder = 0;		// max 4GB in x64
	DWORD lowOrder = 100000;	// min 2GB in x86

	return CreateFileMapping(
		invalidHandle,		// use paging file
		securityAttributes,	// security
		access,				// read/write access
		highOrder,			// maximum object size
		lowOrder,			// minimumm object size
		name.c_str()		// named memory
	);
}

//@ Open File Mapping for Client
HANDLE SharedMemory::SharedMemory::OpenFileMap()
{
	DWORD desiredAccess = FILE_MAP_ALL_ACCESS;
	DWORD inherit = FALSE;
	return OpenFileMapping(
		desiredAccess,		// read/write access
		inherit,			// do not inherit the name
		name.c_str()		// named memory
	);
}
