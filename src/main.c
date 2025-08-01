/*
 * Chức năng chính:
 * - Khởi tạo mảng 4 cửa, gán actuator (Door_Init)
 * - Vòng lặp menu cho phép:
 *    + Xem trạng thái cửa: truy cập statusUnion/status/byte
 *    + Thao tác actuator: gọi open/close/lock/unlock
 *    + Packing trạng thái vào frame: packDoorStatus
 *    + Unpacking frame: unpackDoorStatus
 *    + Kiểm tra parity, đảo bit: checkParity, reverseBits
 *    + Thao tác advanced pointer: pointerDemo
 *    + In log kết quả ra màn hình
 */
#include "can_frame.h"
#include "door.h"
#include "utils.h"

 int main()
 {
    return 0;
 }