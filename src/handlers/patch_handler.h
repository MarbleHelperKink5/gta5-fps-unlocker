#pragma once
#include <cstdint>
#include <vector>
#include "services/memory_service.h"

namespace gta5opt::handlers {

class PatchHandler {
public:
    explicit PatchHandler(services::MemoryService& mem);

    bool NopBytes(uintptr_t addr, size_t count);
    bool WriteFloat(uintptr_t addr, float v);
    bool WriteInt(uintptr_t addr, int32_t v);
    void VerifyAll();

private:
    services::MemoryService& mem_;
    struct Patch { uintptr_t addr; std::vector<uint8_t> original; };
    std::vector<Patch> applied_;
};

} // namespace gta5opt::handlers