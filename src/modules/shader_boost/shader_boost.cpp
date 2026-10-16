#include "core/optimizer_core.h"
#include "utils/logger.h"

namespace gta5opt::modules::shader_boost {

void Install(core::OptimizerCore& core) {
    LOG_INFO("[shader_boost] Enlarging shader cache");
    core.ApplyShaderCacheBoost();
}

} // namespace gta5opt::modules::shader_boost