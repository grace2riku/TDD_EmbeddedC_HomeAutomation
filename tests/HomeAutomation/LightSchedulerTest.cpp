extern "C"
{
#include "LightScheduler.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LightScheduler)
{
    void setup()
    {
      LightScheduler_Create();
    }

    void teardown()
    {
       LightScheduler_Destroy();
    }
};

TEST(LightScheduler, Create)
{
  FAIL("Start here");
}

