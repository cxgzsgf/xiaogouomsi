# SPDX-License-Identifier: Apache-2.0
# Copyright 2026 Xiaogou Remote Control contributors
"""公开接口签名示例。真实凭据从环境变量读取。"""
from __future__ import annotations

import hashlib
import hmac
import json
import os
import secrets
import time
import urllib.request
import uuid
from typing import Any

BASE_URL = os.environ.get("XIAOGOU_API_BASE", "https://example.com/wp-json")
CLIENT_ID = os.environ.get("XIAOGOU_CLIENT_ID", "")
PROJECT_SECRET = os.environ.get("XIAOGOU_PROJECT_SECRET", "")


def require_credentials() -> None:
    if not CLIENT_ID or not PROJECT_SECRET:
        raise RuntimeError(
            "Set XIAOGOU_CLIENT_ID and XIAOGOU_PROJECT_SECRET in the environment."
        )


def signed_request(route: str, payload: dict[str, Any]) -> dict[str, Any]:
    require_credentials()
    body = json.dumps(payload, ensure_ascii=False, separators=(",", ":")).encode()
    timestamp = str(int(time.time()))
    nonce = secrets.token_urlsafe(24)
    body_hash = hashlib.sha256(body).hexdigest()
    canonical = "\n".join(("POST", route, timestamp, nonce, body_hash))
    signature = hmac.new(
        PROJECT_SECRET.encode(), canonical.encode(), hashlib.sha256
    ).hexdigest()

    request = urllib.request.Request(
        BASE_URL + route,
        data=body,
        method="POST",
        headers={
            "Content-Type": "application/json",
            "X-Xiaogou-Client-ID": CLIENT_ID,
            "X-Xiaogou-Timestamp": timestamp,
            "X-Xiaogou-Nonce": nonce,
            "X-Xiaogou-Signature": signature,
        },
    )
    with urllib.request.urlopen(request, timeout=10) as response:
        return json.loads(response.read().decode())


def create_demo_session() -> dict[str, Any]:
    return signed_request(
        "/xiaogou-remote-open/v1/vehicle/session/create",
        {
            # 正式适配器应在首次安装时生成并持久保存唯一实例 ID。
            "external_vehicle_id": str(uuid.uuid4()),
            "display_name": "Third-party Demo Vehicle",
            "adapter_version": "0.1.0",
            "capabilities": [
                "vehicle.status",
                "telemetry.basic",
                "ibis.next_stop",
                "door.front",
                "lights.head",
            ],
        },
    )


if __name__ == "__main__":
    print(json.dumps(create_demo_session(), ensure_ascii=False, indent=2))
