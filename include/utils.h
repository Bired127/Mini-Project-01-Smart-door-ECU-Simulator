#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "door.h"

/**
 * @brief Kiểm tra parity chẵn của 1 byte.
 * @param byte Giá trị cần kiểm tra
 * @return 1 nếu số bit 1 là chẵn, ngược lại trả về 0.
 */
uint8_t chackParity(uint8_t byte);

/**
 * @brief Đảo thứ tự bit 8 bit của 1 byte.
 * @param byte Giá trị cần đảo bit
 * @return Giá trị đã đảo bit.
 */
uint8_t reverseBits(uint8_t byte);

/**
 * @brief Hàm minh họa thao tác advanced pointer:
 *        - Pointer to pointer
 *        - Void pointer
 *        - Const pointer, pointer-to-const
 * @param doors Mảng 4 cửa truyền vào để demo thao tác
 */
void pointerDemo(Door* doors);

#endif // UTILS_H