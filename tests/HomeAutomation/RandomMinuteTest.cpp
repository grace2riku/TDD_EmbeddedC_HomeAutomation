extern "C"
{
#include "RandomMinute.h"
}

#include "CppUTest/TestHarness.h"

enum { BOUND = 30 };

TEST_GROUP(RandomMinute)
{
    int minute;

    void setup()
    {
      RandomMinute_Create(BOUND);
      srand(1);
    }

    void teardown()
    {
       RandomMinute_Destroy();
    }

    void AssertMinuteIsInRange()
    {
      if (minute < -BOUND || minute > BOUND)
      {
        printf("bad minute value: %d\n", minute);
        FAIL("Minute out of range");
      }
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

