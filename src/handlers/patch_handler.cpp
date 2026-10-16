#include "handlers/patch_handler.h"
#include "utils/logger.h"

namespace gta5opt::handlers {

PatchHandler::PatchHandler(services::MemoryService& mem) : mem_(mem) {}

bool PatchHandler::NopBytes(uintptr_t addr, size_t count) {
    Patch p{ addr, std::vector<uint8_t>(count) };
    mem_.ReadBytes(addr, p.original.data(), count);
    std::vector<uint8_t> nops(count, 0x90);
    if (!mem_.WriteBytes(addr, nops.data(), count)) return false;
    applied_.push_back(std::move(p));
    return true;
}

bool PatchHandler::WriteFloat(uintptr_t addr, float v) {
    return mem_.WriteBytes(addr, &v, sizeof(v));
}

bool PatchHandler::WriteInt(uintptr_t addr, int32_t v) {
    return mem_.WriteBytes(addr, &v, sizeof(v));
}

void PatchHandler::VerifyAll() {
    for (auto& p : applied_) {
        std::vector<uint8_t> cur(p.original.size());
        mem_.ReadBytes(p.addr, cur.data(), cur.size());
        bool intact = true;
        for (size_t i = 0; i < cur.size(); ++i) if (cur[i] != 0x90) { intact = false; break; }
        if (!intact) {
            LOG_WARN("Patch at 0x%llX was reset, re-applying", p.addr);
            std::vector<uint8_t> nops(cur.size(), 0x90);
            mem_.WriteBytes(p.addr, nops.data(), nops.size());
        }
    }
}

} // namespace gta5opt::handlers