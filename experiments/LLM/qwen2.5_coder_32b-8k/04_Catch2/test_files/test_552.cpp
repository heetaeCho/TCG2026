#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_assertion_handler.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockIResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, handleMessage, (const AssertionInfo &info, ResultWas::OfType resultType, std::string &&message, AssertionReaction &reaction), (override));

};



class AssertionHandlerTest_552 : public ::testing::Test {

protected:

    SourceLineInfo lineInfo{"filename", 10};

    AssertionHandler handler{"MACRO_NAME", lineInfo, "expression", ResultDisposition::Normal};

    MockIResultCapture mockResultCapture;



    void SetUp() override {

        handler.m_resultCapture = &mockResultCapture;

    }

};



TEST_F(AssertionHandlerTest_552, HandleMessage_CallsHandleMessageOnResultCapture_552) {

    AssertionReaction reaction;

    std::string message = "test message";

    EXPECT_CALL(mockResultCapture, handleMessage(_, ResultWas::Ok, message, _)).Times(1);

    handler.handleMessage(ResultWas::Ok, std::move(message));

}



TEST_F(AssertionHandlerTest_552, HandleMessage_PassesCorrectParameters_552) {

    AssertionReaction reaction;

    std::string message = "test message";

    EXPECT_CALL(mockResultCapture, handleMessage(_, ResultWas::Failed, message, _)).Times(1);

    handler.handleMessage(ResultWas::Failed, std::move(message));

}



TEST_F(AssertionHandlerTest_552, HandleMessage_EmptyStringHandling_552) {

    AssertionReaction reaction;

    std::string emptyMessage = "";

    EXPECT_CALL(mockResultCapture, handleMessage(_, ResultWas::Ok, emptyMessage, _)).Times(1);

    handler.handleMessage(ResultWas::Ok, std::move(emptyMessage));

}



TEST_F(AssertionHandlerTest_552, HandleMessage_DifferentResultTypes_552) {

    AssertionReaction reaction;

    EXPECT_CALL(mockResultCapture, handleMessage(_, ResultWas::Ok, _, _)).Times(1);

    handler.handleMessage(ResultWas::Ok, "ok message");



    EXPECT_CALL(mockResultCapture, handleMessage(_, ResultWas::Info, _, _)).Times(1);

    handler.handleMessage(ResultWas::Info, "info message");



    EXPECT_CALL(mockResultCapture, handleMessage(_, ResultWas::Warning, _, _)).Times(1);

    handler.handleMessage(ResultWas::Warning, "warning message");

}



TEST_F(AssertionHandlerTest_552, HandleMessage_LongStringHandling_552) {

    AssertionReaction reaction;

    std::string longMessage = std::string(1000, 'a');

    EXPECT_CALL(mockResultCapture, handleMessage(_, ResultWas::Failed, longMessage, _)).Times(1);

    handler.handleMessage(ResultWas::Failed, std::move(longMessage));

}
