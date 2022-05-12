extern "C"
{
#include "FormatOutputSpy.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(FormatOutputSpy)
{
    void setup()
    {
      FormatOutputSpy_Create();
    }

    void teardown()
    {
       FormatOutputSpy_Destroy();
    }
};

TEST(FormatOutputSpy, Create)
{
  FAIL("FormatOutputSpy TEST_GROUP Create TEST FAIL.");
}

