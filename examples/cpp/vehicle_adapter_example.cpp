// SPDX-License-Identifier: Apache-2.0
// Copyright 2026 Xiaogou Remote Control contributors
#include "../../include/xiaogou_remote_open.h"

#include <cmath>
#include <string>

using xiaogou_remote::Command;
using xiaogou_remote::ExecuteResult;

// 车辆作者自行实现这一层。这里故意不提供任何具体 OMSI 变量或 Trigger。
class LocalVehicleIo {
public:
    virtual ~LocalVehicleIo() = default;
    virtual double SpeedKmh() const = 0;
    virtual bool OpenFrontDoor() = 0;
    virtual bool CloseFrontDoor() = 0;
    virtual bool SetHeadlights(bool enabled) = 0;
    virtual bool MoveToNextStop() = 0;
};

ExecuteResult ExecuteApprovedCommand(LocalVehicleIo& vehicle,
                                     const Command& command) {
    if (command.type == "ibis.next_stop") {
        return vehicle.MoveToNextStop()
                   ? ExecuteResult{true, "success", "next stop accepted"}
                   : ExecuteResult{false, "failed", "vehicle rejected next stop"};
    }

    if (command.type == "door.front.open") {
        // 车辆端必须拥有最终安全决定权。
        if (std::abs(vehicle.SpeedKmh()) > 0.5) {
            return {false, "rejected", "vehicle is moving"};
        }
        return vehicle.OpenFrontDoor()
                   ? ExecuteResult{true, "success", "front door opened"}
                   : ExecuteResult{false, "failed", "front door command failed"};
    }

    if (command.type == "door.front.close") {
        return vehicle.CloseFrontDoor()
                   ? ExecuteResult{true, "success", "front door closed"}
                   : ExecuteResult{false, "failed", "front door command failed"};
    }

    if (command.type == "lights.head.on") {
        return vehicle.SetHeadlights(true)
                   ? ExecuteResult{true, "success", "headlights enabled"}
                   : ExecuteResult{false, "failed", "headlight command failed"};
    }

    if (command.type == "lights.head.off") {
        return vehicle.SetHeadlights(false)
                   ? ExecuteResult{true, "success", "headlights disabled"}
                   : ExecuteResult{false, "failed", "headlight command failed"};
    }

    return {false, "rejected", "unsupported command"};
}
