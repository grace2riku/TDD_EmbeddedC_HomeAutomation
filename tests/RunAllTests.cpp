#include "CppUTest/CommandLineTestRunner.h"

//IMPORT_TEST_GROUP(LedDriver);
IMPORT_TEST_GROUP(LightScheduler);
IMPORT_TEST_GROUP(LightControllerSpy);
IMPORT_TEST_GROUP(FakeTimeService);
IMPORT_TEST_GROUP(RandomMinute);
IMPORT_TEST_GROUP(LightSchedulerRandomize);
IMPORT_TEST_GROUP(FormatOutputSpy);
IMPORT_TEST_GROUP(CircularBufferPrint);
IMPORT_TEST_GROUP(Flash);
IMPORT_TEST_GROUP(FlashTest_CppUMock);

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}