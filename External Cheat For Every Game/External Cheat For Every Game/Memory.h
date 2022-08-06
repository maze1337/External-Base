#pragma once

#include <Windows.h>
#include <TlHelp32.h>






inline HWND window;
inline DWORD procId;
inline HANDLE hProcess;
inline uintptr_t Base;


inline bool GameOpen = false;



void Attach();

// Read Function Template
template<typename T> T Read(SIZE_T address)
{
	T buffer;
	ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
	return buffer;
}

// Write Function Template  
template<typename T> void Write(SIZE_T address, T buffer)
{
	WriteProcessMemory(hProcess, (LPVOID)address, &buffer, sizeof(buffer), NULL);
}





