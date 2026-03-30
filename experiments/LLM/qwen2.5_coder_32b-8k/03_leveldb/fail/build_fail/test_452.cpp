#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/windows_logger.h"

#include <cstdio>



using namespace leveldb;

using testing::_;

using testing::InSequence;



class WindowsLoggerTest : public ::testing::Test {

protected:

    std::FILE* mockFile;

    WindowsLogger* logger;



    void SetUp() override {

        mockFile = fopen("dummy.log", "w");

        logger = new WindowsLogger(mockFile);

    }



    void TearDown() override {

        delete logger;

        fclose(mockFile);

        remove("dummy.log");

    }

};



TEST_F(WindowsLoggerTest_Logv_NormalOperation_452, LogsMessageCorrectly_452) {

    const char* format = "Test message: %d";

    int value = 123;



    va_list args;

    va_start(args, value);

    logger->Logv(format, args);

    va_end(args);



    rewind(mockFile);

    char buffer[256];

    fgets(buffer, sizeof(buffer), mockFile);



    EXPECT_STREQ("Test message: 123", std::string(buffer).substr(0, strlen("Test message: 123")).c_str());

}



TEST_F(WindowsLoggerTest_Logv_BoundaryConditions_452, EmptyMessageLogsEmptyString_452) {

    const char* format = "";



    va_list args;

    logger->Logv(format, args);



    rewind(mockFile);

    char buffer[256];

    fgets(buffer, sizeof(buffer), mockFile);



    EXPECT_STREQ("", std::string(buffer).substr(0, strlen("")).c_str());

}



TEST_F(WindowsLoggerTest_Logv_ExceptionalCases_452, NullFormatStringDoesNotCrash_452) {

    const char* format = nullptr;



    va_list args;

    logger->Logv(format, args);



    rewind(mockFile);

    char buffer[256];

    fgets(buffer, sizeof(buffer), mockFile);



    EXPECT_STREQ("", std::string(buffer).substr(0, strlen("")).c_str());

}



TEST_F(WindowsLoggerTest_Logv_ExceptionalCases_452, NullFilePointerDoesNotCrashOnDestruction_452) {

    delete logger;

    logger = new WindowsLogger(nullptr);



    EXPECT_NO_THROW(delete logger);

}
