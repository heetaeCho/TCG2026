#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_message.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class MockResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, setResultType, (ResultWas::OfType), (override));

    MOCK_METHOD(void, addMessageInfo, (const MessageInfo&), (override));

};



TEST_F(CapturerTest_108, CaptureSingleValue_108) {

    MockResultCapture mockResultCapture;

    Capturer capturer("MACRO", SourceLineInfo(), ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, setResultType(_)).Times(1);

    EXPECT_CALL(mockResultCapture, addMessageInfo(_)).Times(1);



    capturer.captureValues(0, 42);

}



TEST_F(CapturerTest_108, CaptureMultipleValues_108) {

    MockResultCapture mockResultCapture;

    Capturer capturer("MACRO", SourceLineInfo(), ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, setResultType(_)).Times(1);

    EXPECT_CALL(mockResultCapture, addMessageInfo(_)).Times(2);



    capturer.captureValues(0, 42, 3.14);

}



TEST_F(CapturerTest_108, CaptureBoundaryIndexValue_108) {

    MockResultCapture mockResultCapture;

    Capturer capturer("MACRO", SourceLineInfo(), ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, setResultType(_)).Times(1);

    EXPECT_CALL(mockResultCapture, addMessageInfo(_)).Times(1);



    capturer.captureValues(std::numeric_limits<size_t>::max(), 42);

}



TEST_F(CapturerTest_108, CaptureString_108) {

    MockResultCapture mockResultCapture;

    Capturer capturer("MACRO", SourceLineInfo(), ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, setResultType(_)).Times(1);

    EXPECT_CALL(mockResultCapture, addMessageInfo(_)).Times(1);



    capturer.captureValues(0, std::string("test"));

}



TEST_F(CapturerTest_108, CaptureConstCharPtr_108) {

    MockResultCapture mockResultCapture;

    Capturer capturer("MACRO", SourceLineInfo(), ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, setResultType(_)).Times(1);

    EXPECT_CALL(mockResultCapture, addMessageInfo(_)).Times(1);



    capturer.captureValues(0, "test");

}



TEST_F(CapturerTest_108, CaptureBoolValueTrue_108) {

    MockResultCapture mockResultCapture;

    Capturer capturer("MACRO", SourceLineInfo(), ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, setResultType(_)).Times(1);

    EXPECT_CALL(mockResultCapture, addMessageInfo(_)).Times(1);



    capturer.captureValues(0, true);

}



TEST_F(CapturerTest_108, CaptureBoolValueFalse_108) {

    MockResultCapture mockResultCapture;

    Capturer capturer("MACRO", SourceLineInfo(), ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, setResultType(_)).Times(1);

    EXPECT_CALL(mockResultCapture, addMessageInfo(_)).Times(1);



    capturer.captureValues(0, false);

}
