#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"



using namespace Catch;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, handleExpr, (const AssertionInfo & info, const ITransientExpression & expr, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleMessage, (const AssertionInfo & info, struct ResultWas::OfType resultType, std::string && message, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo & info, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo & info, std::string && message, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo & info), (override));

    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo & info, struct ResultWas::OfType resultType, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo & info), (override));

    MOCK_METHOD(bool, sectionStarted, (StringRef sectionName, const SourceLineInfo & sectionLineInfo, Counts & assertions), (override));

    MOCK_METHOD(void, sectionEnded, (SectionEndInfo && endInfo), (override));

    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo && endInfo), (override));

    MOCK_METHOD(IGeneratorTracker *, acquireGeneratorTracker, (StringRef generatorName, const SourceLineInfo & lineInfo), (override));

    MOCK_METHOD(IGeneratorTracker *, createGeneratorTracker, (StringRef generatorName, SourceLineInfo lineInfo, Generators::GeneratorBasePtr && generator), (override));

    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));

    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo & info), (override));

    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<> & stats), (override));

    MOCK_METHOD(void, benchmarkFailed, (StringRef error), (override));

    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo & message), (override));

    MOCK_METHOD(void, popScopedMessage, (const MessageInfo & message), (override));

    MOCK_METHOD(void, emplaceUnscopedMessage, (MessageBuilder && builder), (override));

};



class RunContextTest_512 : public ::testing::Test {

protected:

    MockIEventListener mockListener;

    std::shared_ptr<IEventListener> listenerPtr = std::make_shared<MockIEventListener>(mockListener);

    TestRunInfo runInfo{"testName"};

    IConfig config{runInfo};

    RunContext context{&config, std::move(listenerPtr)};

};



TEST_F(RunContextTest_512, LastAssertionPassedInitiallyFalse_512) {

    EXPECT_FALSE(context.lastAssertionPassed());

}



TEST_F(RunContextTest_512, AssertionPassedSetsLastAssertionTrue_512) {

    context.assertionPassed();

    EXPECT_TRUE(context.lastAssertionPassed());

}
