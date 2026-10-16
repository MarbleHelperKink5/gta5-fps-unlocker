#include <windows.h>
#include <iostream>
#include <thread>
#include "core/optimizer_core.h"
#include "core/config_loader.h"
#include "utils/logger.h"

int wmain(int argc, wchar_t** argv) {
    gta5opt::utils::Logger::Init("gta5-fps-unlocker.log");
    LOG_INFO("GtaV-Optimizer v2.4.1 booting...");

    gta5opt::core::ConfigLoader cfg;
    if (!cfg.Load("config/optimizer.toml")) {
        LOG_WARN("config/optimizer.toml missing, using defaults");
    }

    gta5opt::core::OptimizerCore core(cfg);
    if (!core.AttachToProcess(L"GTA5.exe")) {
        LOG_ERR("Failed to attach to GTA5.exe — is the game running?");
        std::cerr << "[!] GTA5.exe not found. Launch the game first.\n";
        return 1;
    }

    LOG_INFO("Attached. Applying frametime unlock patches...");
    core.ApplyFpsUnlock();
    core.ApplyStutterFix();
    core.ApplyShaderCacheBoost();

    std::thread watchdog([&core]() {
        while (core.IsAttached()) {
            core.Tick();
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    });

    std::cout << "[+] GtaV-Optimizer running. Press ENTER to detach.\n";
    std::cin.get();

    core.Detach();
    watchdog.join();
    LOG_INFO("Detached cleanly.");
    return 0;
}