extern "C"
{
#include "FormatOutputSpy.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(FormatOutputSpy)
{
    void setup()
    {
      UT_PTR_SET(FormatOutput, FormatOutputSpy);
//      FormatOutputSpy_Create();
    }

    void teardown()
    {
       FormatOutputSpy_Destroy();
    }
};

TEST(FormatOutputSpy, HelloWorld)
{
  FormatOutputSpy_Create(20);
  FormatOutput("Hello, World\n");
  STRCMP_EQUAL("Hello, World\n", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, LimitTheOutputBufferSize)
{
  FormatOutputSpy_Create(4);
  FormatOutput("Hello, World\n");
  STRCMP_EQUAL("Hell", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, PrintMultipleTimes)
{
  FormatOutputSpy_Create(25);
  FormatOutput("Hello");
  FormatOutput(", World\n");
  STRCMP_EQUAL("Hello, World\n", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, PrintMultipleOutputsPastFull)
{
  FormatOutputSpy_Create(12);
  FormatOutput("12345");
  FormatOutput("67890");
  FormatOutput("ABCDEF");
  STRCMP_EQUAL("1234567890AB", FormatOutputSpy_GetOutput());
}