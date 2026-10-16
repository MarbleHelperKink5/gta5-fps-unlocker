#include "core/config_loader.h"
#include "utils/logger.h"
#include <fstream>
#include <sstream>

namespace gta5opt::core {

bool ConfigLoader::Load(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) return false;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string k = line.substr(0, eq);
        std::string v = line.substr(eq + 1);
        try {
            if (v.rfind("0x", 0) == 0) values_[k] = (uintptr_t)std::stoull(v, nullptr, 16);
            else if (v.find('.') != std::string::npos) values_[k] = std::stof(v);
            else values_[k] = std::stoi(v);
        } catch (...) { values_[k] = v; }
    }
    LOG_INFO("Loaded %zu config keys", values_.size());
    return true;
}

template <> uintptr_t ConfigLoader::Get<uintptr_t>(const std::string& k) const {
    auto it = values_.find(k);
    if (it == values_.end()) return 0;
    return std::get<uintptr_t>(it->second);
}
template <> int ConfigLoader::Get<int>(const std::string& k) const {
    auto it = values_.find(k);
    if (it == values_.end()) return 0;
    return std::get<int>(it->second);
}
template <> float ConfigLoader::Get<float>(const std::string& k) const {
    auto it = values_.find(k);
    if (it == values_.end()) return 0.0f;
    return std::get<float>(it->second);
}

} // namespace gta5opt::core