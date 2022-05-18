extern "C"
{
#include "CircularBuffer.h" 
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(CircularBufferPrint)
{
    CircularBuffer buffer;
    const char* expectedOutput;
    const char* actualOutput;
    
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(CircularBufferPrint, PrintEmpty)
{
  expectedOutput = "Circular buffer content:\n<>\n";
  CircularBuffer_Print(buffer);
  STRCMP_EQUAL(expectedOutput, actualOutput);
}

