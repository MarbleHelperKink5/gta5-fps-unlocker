#include "core/optimizer_core.h"
#include "utils/logger.h"

namespace gta5opt::core {

OptimizerCore::OptimizerCore(const ConfigLoader& cfg) : cfg_(cfg), patcher_(mem_) {}
OptimizerCore::~OptimizerCore() { Detach(); }

bool OptimizerCore::AttachToProcess(const std::wstring& exeName) {
    pid_ = services::MemoryService::FindProcessId(exeName);
    if (!pid_) return false;
    handle_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid_);
    if (!handle_) return false;
    mem_.Bind(handle_, pid_);
    return true;
}

void OptimizerCore::Detach() {
    if (handle_) { CloseHandle(handle_); handle_ = nullptr; }
}

void OptimizerCore::ApplyFpsUnlock() {
    // Patch framerate limiter branch -> NOP
    patcher_.NopBytes(cfg_.Get<uintptr_t>("offsets.fps_limiter"), 6);
    LOG_INFO("FPS limiter NOPed at 0x%llX", cfg_.Get<uintptr_t>("offsets.fps_limiter"));
}

void OptimizerCore::ApplyStutterFix() {
    patcher_.WriteFloat(cfg_.Get<uintptr_t>("offsets.stutter_threshold"), 0.0f);
    LOG_INFO("Stutter threshold zeroed");
}

void OptimizerCore::ApplyShaderCacheBoost() {
    patcher_.WriteInt(cfg_.Get<uintptr_t>("offsets.shader_cache_size"), 0x40000000);
    LOG_INFO("Shader cache size raised to 1GB");
}

void OptimizerCore::Tick() {
    // Re-verify patches survived anti-tamper resets
    patcher_.VerifyAll();
}

} // namespace gta5opt::core