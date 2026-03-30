#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"

#include "catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



class MockResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo &, struct ResultWas::OfType, AssertionReaction &), (override));

};



class AssertionHandlerTest_559 : public ::testing::Test {

protected:

    MockResultCapture mock_result_capture;

    AssertionInfo assertion_info{"Macro", SourceLineInfo{"file.cpp", 10}, "Expression"};

    AssertionReaction reaction{AssertionReaction::Normal};

    AssertionHandler handler{"Macro", SourceLineInfo{"file.cpp", 10}, "Expression", ResultDisposition::None()};

};



TEST_F(AssertionHandlerTest_559, HandleThrowingCallSkipped_CallsHandleNonExprWithOkResult_559) {

    EXPECT_CALL(mock_result_capture, handleNonExpr(Ref(assertion_info), Eq(ResultWas::Ok), Ref(reaction)));



    handler.handleThrowingCallSkipped();

}



TEST_F(AssertionHandlerTest_559, HandleThrowingCallSkipped_VerifiesExternalInteraction_559) {

    EXPECT_CALL(mock_result_capture, handleNonExpr(_, _, _));



    handler.handleThrowingCallSkipped();

}
