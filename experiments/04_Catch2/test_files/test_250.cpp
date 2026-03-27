#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_message.hpp"

#include "catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo& message), (override));

    MOCK_METHOD(void, popScopedMessage, (const MessageInfo& message), (override));

};



class CapturerTest_250 : public ::testing::Test {

protected:

    MockResultCapture mock_result_capture;

    Capturer capturer{"MACRO_NAME", SourceLineInfo{"dummy_file.cpp", 42}, ResultWas::OfType::Unknown, "NAMES"};

};



TEST_F(CapturerTest_250, CaptureValue_CallsPushScopedMessageOnce_250) {

    EXPECT_CALL(mock_result_capture, pushScopedMessage(_)).Times(1);

    capturer.captureValue(0, "value");

}



TEST_F(CapturerTest_250, CaptureValues_SingleValue_CallsPushScopedMessageOnce_250) {

    EXPECT_CALL(mock_result_capture, pushScopedMessage(_)).Times(1);

    capturer.captureValues(0, 42);

}



TEST_F(CapturerTest_250, CaptureValues_MultipleValues_CallsPushScopedMessageMultipleTimes_250) {

    EXPECT_CALL(mock_result_capture, pushScopedMessage(_)).Times(3);

    capturer.captureValues(0, 42, "string", 3.14);

}



TEST_F(CapturerTest_250, Destructor_CallsPopScopedMessageForCapturedMessages_250) {

    EXPECT_CALL(mock_result_capture, pushScopedMessage(_)).Times(1);

    capturer.captureValue(0, "value");

    EXPECT_CALL(mock_result_capture, popScopedMessage(_)).Times(1);

}



TEST_F(CapturerTest_250, Destructor_DoesNotCallPopScopedMessageIfNoCapturedMessages_250) {

    EXPECT_CALL(mock_result_capture, pushScopedMessage(_)).Times(0);

    EXPECT_CALL(mock_result_capture, popScopedMessage(_)).Times(0);

}
