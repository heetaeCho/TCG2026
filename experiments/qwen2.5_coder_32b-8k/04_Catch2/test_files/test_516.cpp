#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/catch_assertion_info.hpp"

#include "catch2/catch_assertion_result.hpp"

#include "catch2/internal/catch_assertion_handler.hpp"



using namespace Catch;



class MockAssertionReaction : public AssertionReaction {

public:

    MOCK_METHOD(void, setShouldDebugBreak, (bool), (override));

    MOCK_METHOD(void, setShouldThrow, (bool), (override));

    MOCK_METHOD(void, setShouldSkip, (bool), (override));

};



class RunContextTest_516 : public ::testing::Test {

protected:

    MockAssertionReaction reaction;

    AssertionInfo info;

    std::string message = "Test Message";

    RunContext runContext(nullptr, nullptr);

};



TEST_F(RunContextTest_516, HandleMessage_OkResult_DoesNotModifyReaction_516) {

    ResultWas::OfType resultType = ResultWas::Ok;



    EXPECT_CALL(reaction, setShouldDebugBreak(testing::_)).Times(0);

    EXPECT_CALL(reaction, setShouldThrow(testing::_)).Times(0);

    EXPECT_CALL(reaction, setShouldSkip(testing::_)).Times(0);



    runContext.handleMessage(info, resultType, std::move(message), reaction);

}



TEST_F(RunContextTest_516, HandleMessage_FailureResult_ModifiesReaction_516) {

    ResultWas::OfType resultType = ResultWas::ExpressionFailed;



    EXPECT_CALL(reaction, setShouldDebugBreak(testing::_)).Times(0);

    EXPECT_CALL(reaction, setShouldThrow(testing::_)).Times(1);

    EXPECT_CALL(reaction, setShouldSkip(testing::_)).Times(0);



    runContext.handleMessage(info, resultType, std::move(message), reaction);

}



TEST_F(RunContextTest_516, HandleMessage_SkipResult_ModifiesReaction_516) {

    ResultWas::OfType resultType = ResultWas::ExplicitSkip;



    EXPECT_CALL(reaction, setShouldDebugBreak(testing::_)).Times(0);

    EXPECT_CALL(reaction, setShouldThrow(testing::_)).Times(0);

    EXPECT_CALL(reaction, setShouldSkip(true));



    runContext.handleMessage(info, resultType, std::move(message), reaction);

}



TEST_F(RunContextTest_516, HandleMessage_ExceptionResult_ModifiesReaction_516) {

    ResultWas::OfType resultType = ResultWas::ThrewException;



    EXPECT_CALL(reaction, setShouldDebugBreak(testing::_)).Times(0);

    EXPECT_CALL(reaction, setShouldThrow(true));

    EXPECT_CALL(reaction, setShouldSkip(testing::_)).Times(0);



    runContext.handleMessage(info, resultType, std::move(message), reaction);

}



TEST_F(RunContextTest_516, HandleMessage_UnhandledResult_DoesNotModifyReaction_516) {

    ResultWas::OfType resultType = ResultWas::Unknown;



    EXPECT_CALL(reaction, setShouldDebugBreak(testing::_)).Times(0);

    EXPECT_CALL(reaction, setShouldThrow(testing::_)).Times(0);

    EXPECT_CALL(reaction, setShouldSkip(testing::_)).Times(0);



    runContext.handleMessage(info, resultType, std::move(message), reaction);

}
