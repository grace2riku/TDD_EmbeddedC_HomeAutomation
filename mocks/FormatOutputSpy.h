#ifndef D_FormatOutputSpy_H
#define D_FormatOutputSpy_H

/**********************************************************
 *
 * FormatOutputSpy is responsible for ...
 *
 **********************************************************/

#include "Utils.h"

void FormatOutputSpy_Create(int size);
void FormatOutputSpy_Destroy(void);
const char* FormatOutputSpy_GetOutput(void);
int FormatOutputSpy(const char* format, ...);

#endif  /* D_FakeFormatOutputSpy_H */
