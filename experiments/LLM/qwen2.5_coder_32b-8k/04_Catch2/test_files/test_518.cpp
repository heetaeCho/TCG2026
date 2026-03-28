#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_run_context.hpp"

#include "catch_assertion_info.hpp"

#include "catch_assertion_result.hpp"

#include "catch_assertion_handler.hpp"



using namespace Catch;



class RunContextTest_518 : public ::testing::Test {

protected:

    MockEventListener* mock_reporter;

    IEventListenerPtr reporter_ptr;

    RunContext* run_context;



    void SetUp() override {

        mock_reporter = new testing::NiceMock<MockEventListener>();

        reporter_ptr.reset(mock_reporter);

        run_context = new RunContext(nullptr, std::move(reporter_ptr));

    }



    void TearDown() override {

        delete run_context;

        delete mock_reporter;

    }

};



TEST_F(RunContextTest_518, HandleUnexpectedInflightException_NormalOperation_518) {

    AssertionInfo info{"ASSERT", "expression", ResultDisposition::Normal};

    std::string message = "unexpected exception";

    AssertionReaction reaction;



    EXPECT_CALL(*mock_reporter, assertionEnded(_)).Times(1);



    run_context->handleUnexpectedInflightException(info, std::move(message), reaction);

}



TEST_F(RunContextTest_518, HandleUnexpectedInflightException_BoundaryCondition_EmptyMessage_518) {

    AssertionInfo info{"ASSERT", "expression", ResultDisposition::Normal};

    std::string message = "";

    AssertionReaction reaction;



    EXPECT_CALL(*mock_reporter, assertionEnded(_)).Times(1);



    run_context->handleUnexpectedInflightException(info, std::move(message), reaction);

}



TEST_F(RunContextTest_518, HandleUnexpectedInflightException_ExceptionalCase_EmptyMacroName_518) {

    AssertionInfo info{"", "expression", ResultDisposition::Normal};

    std::string message = "unexpected exception";

    AssertionReaction reaction;



    EXPECT_CALL(*mock_reporter, assertionEnded(_)).Times(1);



    run_context->handleUnexpectedInflightException(info, std::move(message), reaction);

}



TEST_F(RunContextTest_518, HandleUnexpectedInflightException_ExceptionalCase_EmptyExpression_518) {

    AssertionInfo info{"ASSERT", "", ResultDisposition::Normal};

    std::string message = "unexpected exception";

    AssertionReaction reaction;



    EXPECT_CALL(*mock_reporter, assertionEnded(_)).Times(1);



    run_context->handleUnexpectedInflightException(info, std::move(message), reaction);

}



TEST_F(RunContextTest_518, HandleUnexpectedInflightException_VerifyExternalInteraction_518) {

    AssertionInfo info{"ASSERT", "expression", ResultDisposition::Normal};

    std::string message = "unexpected exception";

    AssertionReaction reaction;



    EXPECT_CALL(*mock_reporter, assertionEnded(_)).Times(1);



    run_context->handleUnexpectedInflightException(info, std::move(message), reaction);

}
