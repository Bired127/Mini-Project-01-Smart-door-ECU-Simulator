#include "utils.h"
#include <stdio.h>

/**
 * @brief Kiểm tra parity chẵn của 1 byte.
 * @param byte Giá trị cần kiểm tra
 * @return 1 nếu số bit 1 là chẵn, ngược lại trả về 0.
 */
uint8_t chackParity(uint8_t byte) {
    uint8_t count = 0;
    // Đếm số bit 1 trong byte
    for (int i = 0; i < 8; i++) {
        if (byte & (1 << i)) {
            count++;
        }
    }
    // Trả về 1 nếu số bit 1 là chẵn, 0 nếu lẻ
    return (count % 2 == 0) ? 1 : 0;
}

/**
 * @brief Đảo thứ tự bit 8 bit của 1 byte.
 * @param byte Giá trị cần đảo bit
 * @return Giá trị đã đảo bit.
 */
uint8_t reverseBits(uint8_t byte) {
    uint8_t result = 0;
    // Đảo từng bit
    for (int i = 0; i < 8; i++) {
        result <<= 1;              // Dịch trái result
        result |= (byte & 1);      // Lấy bit thấp nhất của byte và gán vào result
        byte >>= 1;                // Dịch phải byte
    }
    return result;
}

/**
 * @brief Hàm minh họa thao tác advanced pointer:
 *        - Pointer to pointer
 *        - Void pointer
 *        - Const pointer, pointer-to-const
 * @param doors Mảng 4 cửa truyền vào để demo thao tác
 */
void pointerDemo(Door* doors) {
    if (doors == NULL) return; // Kiểm tra con trỏ hợp lệ

    // 1. Pointer to pointer
    Door* door_ptr = &doors[0]; // Con trỏ tới cửa 0
    Door** door_ptr_ptr = &door_ptr; // Con trỏ tới con trỏ cửa
    printf("Pointer to pointer demo: Door 0 isOpen = %d\n", (*door_ptr_ptr)->statusUnion.status.isOpen);

    // 2. Void pointer
    void* void_ptr = &doors[1]; // Void pointer tới cửa 1
    Door* door_from_void = (Door*)void_ptr; // Ép kiểu về Door*
    printf("Void pointer demo: Door 1 isLocked = %d\n", door_from_void->statusUnion.status.isLocked);

    // 3. Pointer-to-const
    const Door* const_door_ptr = &doors[2]; // Con trỏ tới cửa 2 (không thay đổi nội dung)
    printf("Pointer-to-const demo: Door 2 hasWindow = %d\n", const_door_ptr->statusUnion.status.hasWindow);
    // const_door_ptr->statusUnion.status.hasWindow = 1; // Lỗi biên dịch: không thể sửa dữ liệu qua const pointer

    // 4. Const pointer
    Door* const const_ptr = &doors[3]; // Con trỏ cố định tới cửa 3 (không thay đổi địa chỉ)
    printf("Const pointer demo: Door 3 isOpen = %d\n", const_ptr->statusUnion.status.isOpen);
    // const_ptr = &doors[0]; // Lỗi biên dịch: không thể thay đổi địa chỉ của const pointer
}