#include <windows.h>
#include <string>
#include "utils/logger.h"

namespace gta5opt::injector {

bool InjectDll(DWORD pid, const std::wstring& dllPath) {
    HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!proc) { LOG_ERR("OpenProcess failed: %lu", GetLastError()); return false; }

    size_t len = (dllPath.size() + 1) * sizeof(wchar_t);
    LPVOID remote = VirtualAllocEx(proc, nullptr, len, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(proc, remote, dllPath.c_str(), len, nullptr);

    HMODULE k32 = GetModuleHandleW(L"kernel32.dll");
    auto loadLib = (LPTHREAD_START_ROUTINE)GetProcAddress(k32, "LoadLibraryW");

    HANDLE th = CreateRemoteThread(proc, nullptr, 0, loadLib, remote, 0, nullptr);
    if (!th) { LOG_ERR("CreateRemoteThread failed"); CloseHandle(proc); return false; }
    WaitForSingleObject(th, 5000);

    CloseHandle(th); CloseHandle(proc);
    LOG_INFO("Injected %ls into pid %lu", dllPath.c_str(), pid);
    return true;
}

} // namespace gta5opt::injector