// SPDX-License-Identifier: Apache-2.0
// Copyright 2026 Xiaogou Remote Control contributors
#ifndef XIAOGOU_REMOTE_OPEN_H
#define XIAOGOU_REMOTE_OPEN_H

#include <cstdint>
#include <string>
#include <vector>

namespace xiaogou_remote {

inline constexpr const char* kProtocolName = "xiaogou-remote-control";
inline constexpr const char* kProtocolVersion = "1.0";

struct Command {
    std::string command_id;
    std::string type;
    std::string payload_json;
    std::int64_t created_at = 0;
    std::int64_t expires_at = 0;
};

struct Telemetry {
    double speed_kmh = 0.0;
    double game_hour = -1.0;          // 0.0-24.0, unknown when negative.
    double ambient_brightness = -1.0; // 0.0 dark, 1.0 bright, unknown when negative.
    std::string line;
    std::string route;
    std::string current_stop;
    std::string next_stop;
    bool front_door_open = false;
    bool rear_door_open = false;
    bool headlights_on = false;
    bool hazard_on = false;
    bool authorized = false;
};

struct ExecuteResult {
    bool success = false;
    std::string status;  // success / failed / rejected
    std::string message;
};

class VehicleAdapter {
public:
    virtual ~VehicleAdapter() = default;
    virtual std::string ExternalVehicleId() const = 0;
    virtual std::string DisplayName() const = 0;
    virtual std::string AdapterVersion() const = 0;
    virtual std::vector<std::string> Capabilities() const = 0;
    virtual Telemetry CollectTelemetry() = 0;
    virtual ExecuteResult Execute(const Command& command) = 0;
};

}  // namespace xiaogou_remote

#endif  // XIAOGOU_REMOTE_OPEN_H
