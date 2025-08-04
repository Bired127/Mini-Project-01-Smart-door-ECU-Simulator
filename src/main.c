#include <stdio.h>
#include <stdlib.h>
#include "door.h"
#include "can_frame.h"
#include "utils.h"

// Hàm actuator giả lập
void hw_open(Door* d) { printf("Hardware: Opening door\n"); }
void hw_close(Door* d) { printf("Hardware: Closing door\n"); }
void hw_lock(Door* d) { printf("Hardware: Locking door\n"); }
void hw_unlock(Door* d) { printf("Hardware: Unlocking door\n"); }

// Hàm hiển thị trạng thái tất cả cửa
void displayDoorStatus(Door* doors) {
    printf("\n=== Door Status ===\n");
    for (int i = 0; i < 4; i++) {
        printf("Door %d: isOpen=%d, isLocked=%d, hasWindow=%d\n",
               i,
               doors[i].statusUnion.status.isOpen,
               doors[i].statusUnion.status.isLocked,
               doors[i].statusUnion.status.hasWindow);
    }
}

// Hàm điều khiển cửa
void controlDoor(Door* doors) {
    int door_id, action;
    printf("\nEnter door ID (0-3): ");
    scanf("%d", &door_id);
    if (door_id < 0 || door_id > 3) {
        printf("Invalid door ID!\n");
        return;
    }
    printf("Select action: 1=Open, 2=Close, 3=Lock, 4=Unlock: ");
    scanf("%d", &action);
    switch (action) {
        case 1: openDoor(&doors[door_id]); break;
        case 2: closeDoor(&doors[door_id]); break;
        case 3: lockDoor(&doors[door_id]); break;
        case 4: unlockDoor(&doors[door_id]); break;
        default: printf("Invalid action!\n"); break;
    }
}

// Hàm packing và hiển thị frame
void packAndDisplay(Door* doors, CANFrame_t* frame) {
    packDoorStatus(doors, frame);
    printf("\nCAN Frame: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", frame->bytes[i]);
    }
    printf("\n");
}

// Hàm unpacking và hiển thị trạng thái cửa mới
void unpackAndDisplay(CANFrame_t* frame, Door* doors) {
    unpackDoorStatus(frame, doors);
    printf("\nAfter unpacking:\n");
    displayDoorStatus(doors);
}

// Hàm kiểm tra parity và đảo bit
void bitManipulation(Door* doors) {
    int door_id;
    printf("\nEnter door ID (0-3) to check parity and reverse bits: ");
    scanf("%d", &door_id);
    if (door_id < 0 || door_id > 3) {
        printf("Invalid door ID!\n");
        return;
    }
    uint8_t byte = doors[door_id].statusUnion.byte;
    printf("Door %d status (0x%02X): Parity=%d, Reversed=0x%02X\n",
           door_id, byte, checkParity(byte), reverseBits(byte));
}

// Hàm main
int main() {
    // Khởi tạo mảng 4 cửa
    Door doors[4];
    for (int i = 0; i < 4; i++) {
        Door_Init(&doors[i], hw_open, hw_close, hw_lock, hw_unlock);
        // Đặt trạng thái mặc định: cửa đóng, mở khóa
        doors[i].statusUnion.status.isOpen = 0;
        doors[i].statusUnion.status.isLocked = 0;
        doors[i].statusUnion.status.hasWindow = 0;
    }

    // Khởi tạo frame CAN
    CANFrame_t frame;

    // Menu console
    int choice;
    do {
        printf("\n=== Smart Door ECU Simulator ===\n");
        printf("1. View door status\n");
        printf("2. Control door\n");
        printf("3. Pack door status to CAN frame\n");
        printf("4. Unpack CAN frame to doors\n");
        printf("5. Check parity and reverse bits\n");
        printf("6. Test advanced pointers\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayDoorStatus(doors);
                break;
            case 2:
                controlDoor(doors);
                break;
            case 3:
                packAndDisplay(doors, &frame);
                break;
            case 4:
                unpackAndDisplay(&frame, doors);
                break;
            case 5:
                bitManipulation(doors);
                break;
            case 6:
                pointerDemo(doors);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 0);

    return 0;
}