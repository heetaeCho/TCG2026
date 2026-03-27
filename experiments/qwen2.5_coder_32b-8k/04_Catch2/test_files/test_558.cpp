#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"

#include "catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockIResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo &info, AssertionReaction &reaction), (override));

};



class AssertionHandlerTest_558 : public ::testing::Test {

protected:

    NiceMock<MockIResultCapture> mock_result_capture;

    AssertionInfo assertion_info{"macroName", SourceLineInfo{"filename.cpp", 10}, "capturedExpression"};

    AssertionReaction reaction{AssertionReaction::Normal};

    AssertionHandler handler{"macroName", SourceLineInfo{"filename.cpp", 10}, "capturedExpression", ResultDisposition::Normal};



    void SetUp() override {

        handler.m_resultCapture = &mock_result_capture;

    }

};



TEST_F(AssertionHandlerTest_558, HandleUnexpectedExceptionNotThrown_CallsResultCapture_558) {

    EXPECT_CALL(mock_result_capture, handleUnexpectedExceptionNotThrown(assertion_info, reaction));

    handler.handleUnexpectedExceptionNotThrown();

}



TEST_F(AssertionHandlerTest_558, HandleUnexpectedExceptionNotThrown_BoundaryCondition_558) {

    // Assuming the boundary condition is that assertion_info and reaction are in their default/constructed state

    AssertionInfo empty_assertion_info;

    AssertionReaction empty_reaction;

    EXPECT_CALL(mock_result_capture, handleUnexpectedExceptionNotThrown(empty_assertion_info, empty_reaction));

    handler.handleUnexpectedExceptionNotThrown();

}



TEST_F(AssertionHandlerTest_558, HandleUnexpectedExceptionNotThrown_ErrorCase_558) {

    // Assuming an error case could be that the result capture pointer is null

    handler.m_resultCapture = nullptr;

    EXPECT_NO_THROW(handler.handleUnexpectedExceptionNotThrown());

}
