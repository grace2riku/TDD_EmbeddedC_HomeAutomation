#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(LedDriver);
IMPORT_TEST_GROUP(LightScheduler);

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}