#pragma once
#include <string.h>             // for memset
#include "canbus_project.h"     // for nodeInfo_t and subModule_t

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    uint32_t identifier;
    uint8_t  data_length_code;
    uint8_t  data[8];
    bool     isLocal;
} can_msg_t;


#ifdef ESP32
#include "driver/twai.h"
/* TX queue payload type */
typedef twai_message_t CanTxMsg_t;

can_msg_t toCanMsg(const twai_message_t *msg);
twai_message_t toTwaiMsg(const can_msg_t *msg);
#endif

#ifdef __cplusplus
}
#endif
