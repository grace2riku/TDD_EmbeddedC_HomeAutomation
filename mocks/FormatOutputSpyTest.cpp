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
