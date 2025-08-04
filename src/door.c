#include "door.h"
#include <stdio.h>

/**
 * @brief Hàm khởi tạo một cửa, gán các hàm actuator và reset trạng thái về mặc định.
 * @param d      Con trỏ tới cửa cần khởi tạo
 * @param open   Hàm actuator mở cửa
 * @param close  Hàm actuator đóng cửa
 * @param lock   Hàm actuator khóa cửa
 * @param unlock Hàm actuator mở khóa cửa
 */
void Door_Init(Door* d, ActuatorFunc open, ActuatorFunc close, ActuatorFunc lock, ActuatorFunc unlock)
{
    if (d == NULL) return;

    //Gán các hàm actuator
    d->open = open;
    d->close = close;
    d->lock = lock;
    d->unlock = unlock;

    // Đặt trạng thái ban đầu cho cửa
    d->statusUnion.status.isOpen = 0; // Cửa mặc định đóng ban đầu
    d->statusUnion.status.isLocked = 1; // Cửa mặc định khóa ban đầu
    d->statusUnion.status.hasWindow = 0; // Cửa mặc định không mở cửa sổ ban đầu
    d->statusUnion.status.reserved = 0; // backups;
}

/**
 * @brief Actuator mở cửa (set isOpen = 1).
 * @param d Con trỏ tới cửa
 */
void openDoor(Door *d)
{
    if(d == NULL || d->open == NULL) return; // con trỏ d hoặc trạng thái mở là NULL thì trả về
    if(d->statusUnion.status.isLocked == 0) // Chỉ có thể mở khi cửa không khóa (= 0)
    {
        d->statusUnion.status.isOpen = 1;
        d->open(d); // Gọi hàm actuator thực tế
    }
}

/**
 * @brief Actuator đóng cửa (set isOpen = 0).
 * @param d Con trỏ tới cửa
 */
void closeDoor(Door *d)
{
    if(d == NULL || d->close == NULL) return;
    d->statusUnion.status.isOpen = 0;
    d->close(d);
}

void lockDoor(Door *d)
{
    if(d == NULL || d->lock == NULL) return;
    d->statusUnion.status.isLocked = 1;
    d->lock(d);
}

void unlockDoor(Door *d)
{
    if(d == NULL || d->unlock == NULL) return;
    d->statusUnion.status.isLocked = 0;
    d->unlock(d);
}