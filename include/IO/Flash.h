#ifndef D_Flash_H
#define D_Flash_H

/**********************************************************
 *
 * Flash is responsible for ...
 *
 **********************************************************/

#include "IO.h"

void Flash_Create(void);
void Flash_Destroy(void);
int Flash_Write(ioAddress offset, ioData data);

typedef enum {
    FLASH_SUCCESS = 0,
    FLASH_VPP_ERROR, 
    FLASH_PROGRAM_ERROR,
    FLASH_PROTECTED_BLCOK_ERROR,
    FLASH_UNKNOWN_PROGRAM_ERROR,
    FLASH_READ_BACK_ERROR,
    FLASH_TIMEOUT_ERROR
} FlashStatus;


#endif  /* D_FakeFlash_H */
