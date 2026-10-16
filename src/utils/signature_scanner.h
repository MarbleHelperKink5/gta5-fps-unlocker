#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "services/memory_service.h"

namespace gta5opt::utils {

class SignatureScanner {
public:
    explicit SignatureScanner(services::MemoryService& mem);
    uintptr_t ScanModule(const std::wstring& module, const std::string& pattern);

private:
    services::MemoryService& mem_;
    static std::vector<int> ParsePattern(const std::string& pat);
};

} // namespace gta5opt::utils