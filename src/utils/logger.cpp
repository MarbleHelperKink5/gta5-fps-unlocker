#include "utils/logger.h"
#include <cstdarg>
#include <ctime>
#include <mutex>

namespace gta5opt::utils {

static FILE* g_file = nullptr;
static std::mutex g_mtx;

void Logger::Init(const std::string& path) {
    g_file = fopen(path.c_str(), "a");
}

static void log_line(const char* level, const char* fmt, va_list ap) {
    std::lock_guard<std::mutex> lk(g_mtx);
    if (!g_file) return;
    time_t t = time(nullptr);
    char ts[32]; strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", localtime(&t));
    fprintf(g_file, "[%s] [%s] ", ts, level);
    vfprintf(g_file, fmt, ap);
    fputc('\n', g_file);
    fflush(g_file);
}

void Logger::Info(const char* fmt, ...) { va_list ap; va_start(ap, fmt); log_line("INFO", fmt, ap); va_end(ap); }
void Logger::Warn(const char* fmt, ...) { va_list ap; va_start(ap, fmt); log_line("WARN", fmt, ap); va_end(ap); }
void Logger::Err (const char* fmt, ...) { va_list ap; va_start(ap, fmt); log_line("ERR",  fmt, ap); va_end(ap); }

} // namespace gta5opt::utils