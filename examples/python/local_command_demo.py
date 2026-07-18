# SPDX-License-Identifier: Apache-2.0
# Copyright 2026 Xiaogou Remote Control contributors
"""不联网的命令演示，不含任何真实车辆变量。"""
from __future__ import annotations

from dataclasses import dataclass


@dataclass
class DemoVehicle:
    speed_kmh: float = 0.0
    front_door_open: bool = False
    headlights_on: bool = False
    next_stop_index: int = 0

    def execute(self, command: str) -> str:
        if command == "door.front.open":
            if abs(self.speed_kmh) > 0.5:
                return "rejected: vehicle is moving"
            self.front_door_open = True
            return "success: front door opened"
        if command == "lights.head.on":
            self.headlights_on = True
            return "success: headlights enabled"
        if command == "ibis.next_stop":
            self.next_stop_index += 1
            return "success: next stop accepted"
        return "rejected: unsupported command"


if __name__ == "__main__":
    vehicle = DemoVehicle()
    for item in ("lights.head.on", "ibis.next_stop", "door.front.open"):
        print(item, "->", vehicle.execute(item))
