#include "can_platform.h"


#ifdef ESP32

can_msg_t toCanMsg(const twai_message_t *msg) {
    can_msg_t rx = {};  // zero‑initialize

    rx.identifier       = msg->identifier;
    uint8_t dlc         = msg->data_length_code;
    if (dlc > CAN_MAX_DLC) 
        dlc = CAN_MAX_DLC;   // defensive clamp
    rx.data_length_code = dlc;

    memcpy(rx.data, msg->data, dlc);

    return rx;
}

twai_message_t toTwaiMsg(const can_msg_t *msg) {
    twai_message_t out   = {};

    out.identifier       = msg->identifier;
    out.data_length_code = msg->data_length_code;

    out.extd             = TWAI_MSG_FLAG_NONE;
    out.rtr              = TWAI_MSG_FLAG_NONE;
    out.ss               = TWAI_MSG_FLAG_NONE;
    out.self             = TWAI_MSG_FLAG_NONE;
    out.dlc_non_comp     = TWAI_MSG_FLAG_NONE;
    memcpy(out.data, msg->data, msg->data_length_code);
    return out;
}

#endif
