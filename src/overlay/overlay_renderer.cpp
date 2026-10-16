#include <windows.h>
#include <d3d11.h>
#include "utils/logger.h"

namespace gta5opt::overlay {

// Minimal in-game overlay showing FPS + patch status.
// Hooked via Present() vtable swap in a future release.

static ID3D11Device* g_device = nullptr;
static bool g_visible = true;

bool Initialize(ID3D11Device* dev, ID3D11DeviceContext* ctx) {
    g_device = dev;
    LOG_INFO("[overlay] D3D11 overlay initialized");
    return g_device != nullptr;
}

void Toggle() { g_visible = !g_visible; }

void Render() {
    if (!g_visible || !g_device) return;
    // Draw stats text via ImGui backend (stubbed)
}

} // namespace gta5opt::overlay