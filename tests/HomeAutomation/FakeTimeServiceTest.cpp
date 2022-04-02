extern "C"
{
#include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(FakeTimeService)
{
    void setup()
    {
      FakeTimeService_Create();
    }

    void teardown()
    {
       FakeTimeService_Destroy();
    }
};

TEST(FakeTimeService, Create)
{
  FAIL("Start here");
}

