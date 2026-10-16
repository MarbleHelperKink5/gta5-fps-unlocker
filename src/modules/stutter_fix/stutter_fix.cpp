#include "modules/stutter_fix/stutter_fix.h"
#include "utils/logger.h"

namespace gta5opt::modules::stutter_fix {

void Install(core::OptimizerCore& core) {
    LOG_INFO("[stutter_fix] Applying frametime smoothing patches");
    core.ApplyStutterFix();
}

} // namespace gta5opt::modules::stutter_fix