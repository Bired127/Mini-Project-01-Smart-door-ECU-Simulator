#include "can_frame.h"
#include <stdio.h>


/**
 * @brief Đóng gói trạng thái của 4 cửa vào frame truyền thông.
 * @param doors  Mảng 4 cửa nguồn
 * @param frame  Con trỏ tới frame đích
 */
void packDoorStatus(Door *doors, CANFrame_t *frame)
{
    if(doors == NULL || frame == NULL) return;

    // Đóng gói trạng thái của 4 cửa vào frame
    frame->door0 = doors[0].statusUnion.byte; // Trạng thái cửa 0
    frame->door1 = doors[1].statusUnion.byte; // Trạng thái cửa 1
    frame->door2 = doors[2].statusUnion.byte; // Trạng thái cửa 2
    frame->door3 = doors[3].statusUnion.byte; // Trạng thái cửa 3

    frame->warn_flags = 0;
    frame->reverved[0] = 0; // padding
    frame->reverved[1] = 0; // padding
    frame->reverved[2] = 0; // padding
}

/**
 * @brief Giải mã frame truyền thông, cập nhật lại trạng thái cho 4 cửa.
 * @param frame  Frame nguồn
 * @param doors  Mảng 4 cửa sẽ được cập nhật
 */
void unpackDoorStatus(CANFrame_t* frame, Door* doors)
{
    if(frame == NULL || doors == NULL) return;
    doors[0].statusUnion.byte = frame->door0;
    doors[1].statusUnion.byte = frame->door1;
    doors[2].statusUnion.byte = frame->door2;
    doors[3].statusUnion.byte = frame->door3;
}