#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_context.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;



class MockResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo& info), (override));

    MOCK_METHOD(bool, sectionStarted, (StringRef sectionName, const SourceLineInfo & sectionLineInfo, Counts & assertions), (override));

    MOCK_METHOD(void, sectionEnded, (SectionEndInfo && endInfo), (override));

    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo && endInfo), (override));

    MOCK_METHOD(IGeneratorTracker*, acquireGeneratorTracker, (StringRef generatorName, const SourceLineInfo & lineInfo), (override));

    MOCK_METHOD(IGeneratorTracker*, createGeneratorTracker, (StringRef generatorName, SourceLineInfo lineInfo, Generators::GeneratorBasePtr && generator), (override));

    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));

    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo & info), (override));

    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<> & stats), (override));

    MOCK_METHOD(void, benchmarkFailed, (StringRef error), (override));

    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo & message), (override));

    MOCK_METHOD(void, popScopedMessage, (const MessageInfo & message), (override));

    MOCK_METHOD(void, emplaceUnscopedMessage, (MessageBuilder && builder), (override));

    MOCK_METHOD(void, handleFatalErrorCondition, (StringRef message), (override));

    MOCK_METHOD(void, handleExpr, (const AssertionInfo & info, const ITransientExpression & expr, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleMessage, (const AssertionInfo & info, struct ResultWas::OfType resultType, std::string && message, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo & info, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo & info, std::string && message, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo & info), (override));

    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo & info, struct ResultWas::OfType resultType, AssertionReaction & reaction), (override));

    MOCK_METHOD(bool, lastAssertionPassed, (), (override));

    MOCK_METHOD(void, assertionPassed, (), (override));

    MOCK_METHOD(const std::string, getCurrentTestName, (), (const, override));

    MOCK_METHOD(const AssertionResult*, getLastResult, (), (const, override));

    MOCK_METHOD(void, exceptionEarlyReported, (), (override));

};



class ContextTest_254 : public ::testing::Test {

protected:

    Context context;

    std::unique_ptr<MockResultCapture> mockResultCapture = std::make_unique<MockResultCapture>();

};



TEST_F(ContextTest_254, SetAndGetResultCapture_NormalOperation_254) {

    EXPECT_EQ(context.getResultCapture(), nullptr);

    context.setResultCapture(mockResultCapture.get());

    EXPECT_EQ(context.getResultCapture(), mockResultCapture.get());

}



TEST_F(ContextTest_254, SetConfig_NormalOperation_254) {

    const IConfig* config = nullptr;

    EXPECT_EQ(context.getConfig(), nullptr);

    context.setConfig(config);

    EXPECT_EQ(context.getConfig(), config);

}



TEST_F(ContextTest_254, CleanUpContext_NoOp_254) {

    // As cleanUpContext does not have observable behavior, we can only call it

    context.cleanUpContext();

}
