extern "C"
{
#include "RandomMinute.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(RandomMinute)
{
    void setup()
    {
      RandomMinute_Create();
    }

    void teardown()
    {
       RandomMinute_Destroy();
    }
};

TEST(RandomMinute, Create)
{
  FAIL("RandomMinute FAIL!!!");
}

