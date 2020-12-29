#include <Windows.h>
#include <TlHelp32.h>
#include <PsApi.h>
#include <string>

namespace memory {
	extern DWORD pid;
	extern MODULEENTRY32 module;
	extern DWORD64 base;
	extern DWORD64 base_size;
	extern HANDLE handle;

	DWORD get_processid(const std::string processName);
	MODULEENTRY32 get_module(DWORD processId, const char* moduleName);
	DWORD64 get_base(MODULEENTRY32 original);
}