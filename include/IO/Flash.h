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
} FlashStatus;


#endif  /* D_FakeFlash_H */
