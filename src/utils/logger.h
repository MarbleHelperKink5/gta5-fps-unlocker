#pragma once
#include <string>
#include <cstdio>

namespace gta5opt::utils {

class Logger {
public:
    static void Init(const std::string& path);
    static void Info(const char* fmt, ...);
    static void Warn(const char* fmt, ...);
    static void Err(const char* fmt, ...);
};

} // namespace gta5opt::utils

#define LOG_INFO(...) ::gta5opt::utils::Logger::Info(__VA_ARGS__)
#define LOG_WARN(...) ::gta5opt::utils::Logger::Warn(__VA_ARGS__)
#define LOG_ERR(...)  ::gta5opt::utils::Logger::Err(__VA_ARGS__)