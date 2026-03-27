#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_message.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_message_info.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockIResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo &message), (override));

};



class CapturerTest : public ::testing::Test {

protected:

    MockIResultCapture mockResultCapture;

    SourceLineInfo lineInfo{"dummy_file.cpp", 123};

    MessageInfo messageInfo{"MACRO_NAME", lineInfo, ResultWas::OfType::Info};

    std::vector<MessageInfo> messages{messageInfo};



    CapturerTest() : capturer("MACRO_NAME", lineInfo, ResultWas::OfType::Info, "") {

        capturer.m_messages = messages;

    }



    Capturer capturer;

};



TEST_F(CapturerTest_251, CaptureValueValidIndex_251) {

    EXPECT_CALL(mockResultCapture, pushScopedMessage(messages[0])).Times(1);

    capturer.captureValue(0, "test_value");

}



TEST_F(CapturerTest_251, CaptureValueInvalidIndex_251) {

    EXPECT_THROW(capturer.captureValue(1, "test_value"), std::exception);

}



TEST_F(CapturerTest_251, CaptureValuesSingle_251) {

    EXPECT_CALL(mockResultCapture, pushScopedMessage(messages[0])).Times(1);

    capturer.captureValues(0, "single_value");

}



TEST_F(CapturerTest_251, CaptureValuesMultiple_251) {

    EXPECT_CALL(mockResultCapture, pushScopedMessage(messages[0])).Times(1);

    capturer.captureValues(0, "value1", "value2", "value3");

}
