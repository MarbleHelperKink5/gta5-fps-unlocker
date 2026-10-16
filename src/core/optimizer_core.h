#pragma once
#include <string>
#include <windows.h>
#include "core/config_loader.h"
#include "services/memory_service.h"
#include "handlers/patch_handler.h"

namespace gta5opt::core {

class OptimizerCore {
public:
    explicit OptimizerCore(const ConfigLoader& cfg);
    ~OptimizerCore();

    bool AttachToProcess(const std::wstring& exeName);
    void Detach();
    bool IsAttached() const { return handle_ != nullptr; }

    void ApplyFpsUnlock();
    void ApplyStutterFix();
    void ApplyShaderCacheBoost();
    void Tick();

private:
    const ConfigLoader& cfg_;
    HANDLE handle_ = nullptr;
    DWORD pid_ = 0;
    services::MemoryService mem_;
    handlers::PatchHandler patcher_;
};

} // namespace gta5opt::core