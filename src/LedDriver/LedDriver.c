#include "LedDriver.h"
#include "RuntimeError.h"

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};
enum {FIRST_LED = 1, LAST_LED = 16};

static uint16_t* ledsAddress;
static uint16_t ledsImage;

static BOOL IsLedOutOfBounds(int ledNumber)
{
    if (ledNumber <= 0 || ledNumber > 16) {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
        return TRUE;
    }
    return FALSE;
}

static uint16_t convertLedNumberToBit(int ledNumber)
{
    return 1 << (ledNumber - 1);
}

static void updateHardware(void)
{
    *ledsAddress = ledsImage;
}

void LedDriver_Create(uint16_t* address)
{
    ledsAddress = address;
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

void LedDriver_Destroy(void)
{
}

static void setLedImageBit(int ledNumber)
{
    ledsImage |= convertLedNumberToBit(ledNumber);
}

void LedDriver_TurnOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber)) {
        return;
    }

    setLedImageBit(ledNumber);
    updateHardware();
}

static void clearLedImageBit(int ledNumber)
{
    ledsImage &= ~(convertLedNumberToBit(ledNumber));
}

void LedDriver_TurnOff(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber)) {
        return;
    }

    clearLedImageBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnAllOn(void)
{
    ledsImage = ALL_LEDS_ON;
    updateHardware();
}

void LedDriver_TurnAllOff(void)
{
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

BOOL LedDriver_IsOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return FALSE;

    return 0 != (ledsImage & convertLedNumberToBit(ledNumber));
}

BOOL LedDriver_IsOff(int ledNumber)
{
    return !LedDriver_IsOn(ledNumber);
}
