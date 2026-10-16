#include "modules/fps_unlock/fps_unlock.h"
#include "utils/logger.h"

namespace gta5opt::modules::fps_unlock {

void Install(core::OptimizerCore& core) {
    LOG_INFO("[fps_unlock] Installing FPS unlock module");
    core.ApplyFpsUnlock();
}

void Uninstall(core::OptimizerCore& core) {
    LOG_INFO("[fps_unlock] Reverting");
    // Original bytes restored by PatchHandler destructor
}

} // namespace gta5opt::modules::fps_unlock