#pragma once
#include <string>
#include <unordered_map>
#include <variant>

namespace gta5opt::core {

class ConfigLoader {
public:
    bool Load(const std::string& path);

    template <typename T>
    T Get(const std::string& key) const;

private:
    std::unordered_map<std::string, std::variant<int, float, uintptr_t, std::string>> values_;
};

} // namespace gta5opt::core