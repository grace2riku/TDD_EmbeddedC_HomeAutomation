extern "C"
{
#include "RandomMinute.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(RandomMinute)
{
    int minute;

    void setup()
    {
      RandomMinute_Create();
    }

    void teardown()
    {
       RandomMinute_Destroy();
    }

    void AssertMinuteIsInRange()
    {
      FAIL("Minute out of range");
    }
};

TEST(RandomMinute, GetIsInRange)
{
  for (int i = 0; i < 100; i++)
  {
    minute = RandomMinute_Get();
    AssertMinuteIsInRange();
  }
}

