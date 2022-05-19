extern "C"
{
#include "Flash.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Flash)
{
    void setup()
    {
      Flash_Create();
    }

    void teardown()
    {
       Flash_Destroy();
    }
};

TEST(Flash, Create)
{
  FAIL("Start here");
}

