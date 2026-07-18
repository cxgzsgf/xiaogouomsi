// SPDX-License-Identifier: Apache-2.0
// Copyright 2026 Xiaogou Remote Control contributors
#include <optional>

struct LightingSnapshot {
    double game_hour = -1.0;          // 0.0-24.0, negative means unavailable.
    double ambient_brightness = -1.0; // 0.0-1.0, negative means unavailable.
    bool headlights_on = false;
    bool driver_manual_override = false;
};

class LightingIo {
public:
    virtual ~LightingIo() = default;
    virtual bool SetHeadlights(bool enabled) = 0;
};

// 返回建议状态；没有足够信息时返回 std::nullopt。
std::optional<bool> SuggestedNightHeadlightState(const LightingSnapshot& state) {
    if (state.driver_manual_override) {
        return std::nullopt; // 本地驾驶员优先。
    }

    if (state.ambient_brightness >= 0.0) {
        // 简化迟滞：较暗时开启；较亮时才建议关闭。
        if (!state.headlights_on && state.ambient_brightness < 0.28) return true;
        if (state.headlights_on && state.ambient_brightness > 0.45) return false;
        return std::nullopt;
    }

    if (state.game_hour >= 0.0) {
        const bool is_night = state.game_hour >= 18.0 || state.game_hour < 6.0;
        if (is_night && !state.headlights_on) return true;
        // 示例默认不在白天强制关闭驾驶员已经打开的大灯。
    }

    return std::nullopt;
}

bool UpdateAutomaticHeadlights(LightingIo& vehicle,
                               const LightingSnapshot& state) {
    const auto suggestion = SuggestedNightHeadlightState(state);
    if (!suggestion.has_value()) return true;
    return vehicle.SetHeadlights(*suggestion);
}
