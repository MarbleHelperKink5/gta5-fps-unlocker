#include "utils/signature_scanner.h"
#include "utils/logger.h"
#include <sstream>

namespace gta5opt::utils {

SignatureScanner::SignatureScanner(services::MemoryService& mem) : mem_(mem) {}

std::vector<int> SignatureScanner::ParsePattern(const std::string& pat) {
    std::vector<int> out;
    std::istringstream ss(pat);
    std::string tok;
    while (ss >> tok) {
        if (tok == "?" || tok == "??") out.push_back(-1);
        else out.push_back(std::stoi(tok, nullptr, 16));
    }
    return out;
}

uintptr_t SignatureScanner::ScanModule(const std::wstring& module, const std::string& pattern) {
    uintptr_t base = mem_.ResolveBase(module);
    if (!base) return 0;
    auto pat = ParsePattern(pattern);
    std::vector<uint8_t> buf(0x1000);
    for (uintptr_t addr = base; addr < base + 0x4000000; addr += 0x1000) {
        if (!mem_.ReadBytes(addr, buf.data(), buf.size())) continue;
        for (size_t i = 0; i + pat.size() < buf.size(); ++i) {
            bool hit = true;
            for (size_t j = 0; j < pat.size(); ++j) {
                if (pat[j] != -1 && buf[i + j] != (uint8_t)pat[j]) { hit = false; break; }
            }
            if (hit) {
                LOG_INFO("Signature hit at 0x%llX", addr + i);
                return addr + i;
            }
        }
    }
    return 0;
}

} // namespace gta5opt::utils