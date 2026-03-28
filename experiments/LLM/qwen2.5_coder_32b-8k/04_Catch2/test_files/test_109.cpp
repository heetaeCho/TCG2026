#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_message.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::MockFunction;



class MockIResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, captureMessage, (const MessageInfo&), (override));

};



TEST_F(CapturerTest_109, CaptureSingleValue_109) {

    MockIResultCapture mockResultCapture;

    SourceLineInfo lineInfo("file.cpp", 42);

    Capturer capturer("MACRO_NAME", lineInfo, ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, captureMessage(_)).Times(1);



    capturer.captureValue(0, "value");

}



TEST_F(CapturerTest_109, CaptureMultipleValues_109) {

    MockIResultCapture mockResultCapture;

    SourceLineInfo lineInfo("file.cpp", 42);

    Capturer capturer("MACRO_NAME", lineInfo, ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, captureMessage(_)).Times(3);



    capturer.captureValues(0, "value1", "value2", "value3");

}



TEST_F(CapturerTest_109, CaptureEmptyString_109) {

    MockIResultCapture mockResultCapture;

    SourceLineInfo lineInfo("file.cpp", 42);

    Capturer capturer("MACRO_NAME", lineInfo, ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, captureMessage(_)).Times(1);



    capturer.captureValue(0, "");

}



TEST_F(CapturerTest_109, CaptureLargeString_109) {

    MockIResultCapture mockResultCapture;

    SourceLineInfo lineInfo("file.cpp", 42);

    Capturer capturer("MACRO_NAME", lineInfo, ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, captureMessage(_)).Times(1);



    std::string largeString(1024, 'a'); // Large string of 1024 'a's

    capturer.captureValue(0, largeString);

}



TEST_F(CapturerTest_109, CaptureDifferentTypes_109) {

    MockIResultCapture mockResultCapture;

    SourceLineInfo lineInfo("file.cpp", 42);

    Capturer capturer("MACRO_NAME", lineInfo, ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, captureMessage(_)).Times(3);



    capturer.captureValues(0, 42, 3.14, std::string("hello"));

}



TEST_F(CapturerTest_109, CaptureBoundaryIndex_109) {

    MockIResultCapture mockResultCapture;

    SourceLineInfo lineInfo("file.cpp", 42);

    Capturer capturer("MACRO_NAME", lineInfo, ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, captureMessage(_)).Times(1);



    capturer.captureValue(0, "value");

}



TEST_F(CapturerTest_109, CaptureNoValues_109) {

    MockIResultCapture mockResultCapture;

    SourceLineInfo lineInfo("file.cpp", 42);

    Capturer capturer("MACRO_NAME", lineInfo, ResultWas::OfType::Unknown, "name");

    EXPECT_CALL(mockResultCapture, captureMessage(_)).Times(0);



    // No values captured

}
