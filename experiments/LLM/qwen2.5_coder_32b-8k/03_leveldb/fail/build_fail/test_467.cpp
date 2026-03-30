#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"



namespace leveldb {

class MockLogger : public Logger {

public:

    MOCK_METHOD(void, Logv, (const char* format, __va_list_tag* ap), (override));

};



TEST_F(LoggingTest_467, LogWithNonNullLogger_CallsLogv_467) {

    MockLogger mock_logger;

    EXPECT_CALL(mock_logger, Logv(::testing::_, ::testing::_)).Times(1);



    const char* test_message = "Test message";

    Log(&mock_logger, "%s", test_message);

}



TEST_F(LoggingTest_467, LogWithNullLogger_DoesNotCallLogv_467) {

    MockLogger mock_logger;

    EXPECT_CALL(mock_logger, Logv(::testing::_, ::testing::_)).Times(0);



    const char* test_message = "Test message";

    Log(nullptr, "%s", test_message);

}



TEST_F(LoggingTest_467, LogWithFormatString_CallsLogvOnce_467) {

    MockLogger mock_logger;

    EXPECT_CALL(mock_logger, Logv(::testing::_, ::testing::_)).Times(1);



    const char* format_string = "Value: %d";

    int value = 42;

    Log(&mock_logger, format_string, value);

}



TEST_F(LoggingTest_467, LogWithMultipleArguments_CallsLogvOnce_467) {

    MockLogger mock_logger;

    EXPECT_CALL(mock_logger, Logv(::testing::_, ::testing::_)).Times(1);



    const char* format_string = "Multiple values: %d and %s";

    int value = 42;

    const char* message = "test";

    Log(&mock_logger, format_string, value, message);

}

} // namespace leveldb
