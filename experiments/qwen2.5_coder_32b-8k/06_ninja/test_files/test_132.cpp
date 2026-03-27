#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "src/util.cc"  // Adjust the path as necessary



// Mocking a handler for testing Info function side effects if any.

class MockHandler {

public:

    MOCK_METHOD(void, HandleInfo, (const std::string& msg));

};



extern "C" void Info(const char* msg, ...) {

    va_list ap;

    va_start(ap, msg);

    char buffer[1024];

    vsnprintf(buffer, sizeof(buffer), msg, ap);

    va_end(ap);



    // Assuming there's a way to inject a handler for testing purposes

    static MockHandler* mock_handler = nullptr;

    if (mock_handler) {

        mock_handler->HandleInfo(buffer);

    }

}



void SetMockHandler(MockHandler* handler) {

    static MockHandler** mock_handler_ptr = reinterpret_cast<MockHandler**>(&Info);

    *mock_handler_ptr = handler;

}



TEST(InfoTest_132, NormalOperation_132) {

    MockHandler mock;

    SetMockHandler(&mock);



    EXPECT_CALL(mock, HandleInfo("Test message")).Times(1);



    Info("Test message");

}



TEST(InfoTest_132, BoundaryCondition_EmptyString_132) {

    MockHandler mock;

    SetMockHandler(&mock);



    EXPECT_CALL(mock, HandleInfo("")).Times(1);



    Info("");

}



TEST(InfoTest_132, BoundaryCondition_MaxLengthString_132) {

    MockHandler mock;

    SetMockHandler(&mock);



    std::string max_length_string(1023, 'a');  // Filling buffer with max length



    EXPECT_CALL(mock, HandleInfo(max_length_string)).Times(1);



    Info("%s", max_length_string.c_str());

}



TEST(InfoTest_132, ExceptionalCase_FormatStringWithNoArgs_132) {

    MockHandler mock;

    SetMockHandler(&mock);



    EXPECT_CALL(mock, HandleInfo("Format string with no args")).Times(1);



    Info("Format string with no args");

}



TEST(InfoTest_132, ExceptionalCase_FormatStringWithExtraArgs_132) {

    MockHandler mock;

    SetMockHandler(&mock);



    EXPECT_CALL(mock, HandleInfo("Only this will be logged")).Times(1);



    Info("Only this will be logged", 42);  // Extra arg should not be included in the log

}
