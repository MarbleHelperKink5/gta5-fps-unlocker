#include "services/memory_service.h"
#include <tlhelp32.h>

namespace gta5opt::services {

DWORD MemoryService::FindProcessId(const std::wstring& exeName) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return 0;
    PROCESSENTRY32W pe{ sizeof(pe) };
    DWORD pid = 0;
    if (Process32FirstW(snap, &pe)) {
        do {
            if (exeName == pe.szExeFile) { pid = pe.th32ProcessID; break; }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
    return pid;
}

void MemoryService::Bind(HANDLE h, DWORD pid) {
    handle_ = h; pid_ = pid;
    base_ = ResolveBase(L"GTA5.exe");
}

bool MemoryService::ReadBytes(uintptr_t addr, void* out, size_t n) {
    SIZE_T read = 0;
    return ReadProcessMemory(handle_, (LPCVOID)addr, out, n, &read) && read == n;
}

bool MemoryService::WriteBytes(uintptr_t addr, const void* in, size_t n) {
    DWORD old = 0;
    VirtualProtectEx(handle_, (LPVOID)addr, n, PAGE_EXECUTE_READWRITE, &old);
    SIZE_T wrote = 0;
    bool ok = WriteProcessMemory(handle_, (LPVOID)addr, in, n, &wrote) && wrote == n;
    VirtualProtectEx(handle_, (LPVOID)addr, n, old, &old);
    return ok;
}

uintptr_t MemoryService::ResolveBase(const std::wstring& moduleName) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid_);
    if (snap == INVALID_HANDLE_VALUE) return 0;
    MODULEENTRY32W me{ sizeof(me) };
    uintptr_t base = 0;
    if (Module32FirstW(snap, &me)) {
        do {
            if (moduleName == me.szModule) { base = (uintptr_t)me.modBaseAddr; break; }
        } while (Module32NextW(snap, &me));
    }
    CloseHandle(snap);
    return base;
}

} // namespace gta5opt::services