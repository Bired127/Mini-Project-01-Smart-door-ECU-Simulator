#ifndef CAN_FRAME_H
#define CAN_FRAME_H

#include <stdint.h>
#include "door.h"

/**
 * @brief Frame dữ liệu truyền thông, gồm trạng thái 4 cửa và cờ cảnh báo.
 * - door0..door3:  Trạng thái từng cửa (dưới dạng byte)
 * - warn_flags:    Dự phòng cho cảnh báo, parity, lỗi, v.v.
 * - reserved:      Đệm
 */
typedef union {
    struct {
        uint8_t door0;
        uint8_t door1;
        uint8_t door2;
        uint8_t door3;
        uint8_t warn_flags;
        uint8_t reverved[3];
    };
    uint8_t bytes[8];
} CANFrame_t;

/**
 * @brief Đóng gói trạng thái của 4 cửa vào frame truyền thông.
 * @param doors  Mảng 4 cửa nguồn
 * @param frame  Con trỏ tới frame đích
 */
void packDoorStatus(Door *doors, CANFrame_t *frame);

/**
 * @brief Giải mã frame truyền thông, cập nhật lại trạng thái cho 4 cửa.
 * @param frame  Frame nguồn
 * @param doors  Mảng 4 cửa sẽ được cập nhật
 */
void unpackDoorStatus(CANFrame_t* frame, Door* doors);

 #endif // CAN_FRAME_H