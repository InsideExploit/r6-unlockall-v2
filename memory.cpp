#include "memory.h"

DWORD memory::pid = 0x0;
MODULEENTRY32 memory::module = { 0x0 };
DWORD64 memory::base = 0x0;
DWORD64 memory::base_size = 0x0;
HANDLE memory::handle = 0x0;

DWORD memory::get_processid(const std::string processName) {
    PROCESSENTRY32 entryList = { 0x0 };
    entryList.dwSize = sizeof(entryList);

    HANDLE processThreads = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL); if (processThreads == INVALID_HANDLE_VALUE) return false;

    Process32First(processThreads, &entryList);
    if (!processName.compare(entryList.szExeFile)) {
        CloseHandle(processThreads);
        return false;
    }
    while (Process32Next(processThreads, &entryList)) {
        if (!processName.compare(entryList.szExeFile)) {
            CloseHandle(processThreads);
            return entryList.th32ProcessID;
        }
    }
    CloseHandle(processThreads);
    return false;
}

MODULEENTRY32 memory::get_module(DWORD processId, const char* moduleName) {
    MODULEENTRY32 entryList = { 0x0 };
    HANDLE processThreads = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (processThreads != INVALID_HANDLE_VALUE)
    {
        entryList.dwSize = sizeof(entryList);
        if (Module32First(processThreads, &entryList))
        {
            do
            {
                if (!strcmp(entryList.szModule, moduleName))
                    break;
            } while (Module32Next(processThreads, &entryList));
        }
    }
    CloseHandle(processThreads);
    return entryList;
}

DWORD64 memory::get_base(MODULEENTRY32 original) {
    return (DWORD64)original.modBaseAddr;
}