#pragma once
#include <windows.h>
#include <string>
#include <vector>

namespace gta5opt::services {

class MemoryService {
public:
    void Bind(HANDLE h, DWORD pid);
    bool ReadBytes(uintptr_t addr, void* out, size_t n);
    bool WriteBytes(uintptr_t addr, const void* in, size_t n);
    uintptr_t ResolveBase(const std::wstring& moduleName);

    static DWORD FindProcessId(const std::wstring& exeName);

private:
    HANDLE handle_ = nullptr;
    DWORD pid_ = 0;
    uintptr_t base_ = 0;
};

} // namespace gta5opt::services