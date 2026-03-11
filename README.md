# can_platform
---

# **can_platform — Cross‑Platform CAN Message Abstraction**

`can_platform` provides a unified, hardware‑agnostic CAN message type (`can_msg_t`) and conversion helpers that isolate MCU‑specific CAN driver details from the rest of the firmware.  
This allows higher‑level modules (router, producer, consumer, personality logic) to operate on a consistent CAN frame format across all supported platforms.

---

## **Features**

- Defines a portable CAN frame type: `can_msg_t`
- Maps to native CAN driver types on each platform  
  - ESP32: `twai_message_t` (ESP‑IDF TWAI driver)  
  - Other platforms: generic 11‑bit CAN frame struct
- Provides conversion helpers:
  - `recastTwaiMsg()` — ESP32 RX → portable `can_msg_t`
  - `toTwaiMsg()` — portable `can_msg_t` → ESP32 TX
- Keeps all hardware‑specific CAN logic isolated in one place
- Enables clean portability to STM32, RP2040, Linux, and unit tests

---

## **Directory Structure**

```
can_platform/
└── src/
    └── can_platform.c
│   └── can_platform.h

```

---

## **Usage**

Include the header from any module that needs to work with CAN frames:

```c
#include "can_platform.h"
```

Convert incoming ESP32 TWAI frames:

```c
can_msg_t msg = recastTwaiMsg(twai_rx_msg);
```

Convert portable frames back to TWAI for transmission:

```c
twai_message_t hw = toTwaiMsg(msg);
```

---

## **Why This Exists**

This library creates a clean separation between:

- **Hardware‑specific CAN drivers** (TWAI, FDCAN, MCP2515, etc.)
- **Platform‑agnostic logic** (routing, producers, consumers, automation)

By standardizing on `can_msg_t`, the rest of the firmware never needs to know which MCU or CAN driver is in use.

---

## **Future Platforms**

To support a new MCU:

1. Add a new `can_platform_<mcu>` library  
2. Implement the same API (`can_msg_t`, conversion helpers)  
3. Keep the router and producer libraries unchanged

---

