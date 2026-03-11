#pragma once

#ifdef ESP32
    #include "driver/twai.h"
    typedef twai_message_t can_msg_t;
#else
    typedef struct {
        uint32_t identifier;
        uint8_t  data_length_code;
        uint8_t  data[8];
    } can_msg_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CAN_MAX_DLC     8

can_msg_t toCanMsg(const twai_message_t *msg);
twai_message_t toTwaiMsg(const can_msg_t *msg);

#ifdef __cplusplus
}
#endif
