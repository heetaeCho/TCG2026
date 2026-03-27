#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/generators/catch_generators.cpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_source_line_info.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;

using namespace Catch::Generators;

using namespace testing;



class MockIResultCapture : public IResultCapture {

public:

    MOCK_METHOD(IGeneratorTracker*, acquireGeneratorTracker, (StringRef generatorName, const SourceLineInfo & lineInfo), (override));

    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo & info), (override));

    MOCK_METHOD(bool, sectionStarted, (StringRef sectionName, const SourceLineInfo & sectionLineInfo, Counts & assertions), (override));

    MOCK_METHOD(void, sectionEnded, (SectionEndInfo && endInfo), (override));

    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo && endInfo), (override));

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

    MOCK_METHOD(const std::string, getCurrentTestName, (), (const override));

    MOCK_METHOD(const const AssertionResult*, getLastResult, (), (const override));

    MOCK_METHOD(void, exceptionEarlyReported, (), (override));

};



class AcquireGeneratorTrackerTest : public Test {

protected:

    MockIResultCapture mockResultCapture;

};



TEST_F(AcquireGeneratorTrackerTest_354, NormalOperation_354) {

    StringRef generatorName("example_generator");

    SourceLineInfo lineInfo(__FILE__, __LINE__);

    IGeneratorTracker* expectedTracker = nullptr;



    EXPECT_CALL(mockResultCapture, acquireGeneratorTracker(generatorName, lineInfo))

        .WillOnce(Return(expectedTracker));



    IGeneratorTracker* actualTracker = Catch::Generators::acquireGeneratorTracker(generatorName, lineInfo);

    EXPECT_EQ(actualTracker, expectedTracker);

}



TEST_F(AcquireGeneratorTrackerTest_354, BoundaryCondition_EmptyString_354) {

    StringRef generatorName("");

    SourceLineInfo lineInfo(__FILE__, __LINE__);

    IGeneratorTracker* expectedTracker = nullptr;



    EXPECT_CALL(mockResultCapture, acquireGeneratorTracker(generatorName, lineInfo))

        .WillOnce(Return(expectedTracker));



    IGeneratorTracker* actualTracker = Catch::Generators::acquireGeneratorTracker(generatorName, lineInfo);

    EXPECT_EQ(actualTracker, expectedTracker);

}



TEST_F(AcquireGeneratorTrackerTest_354, BoundaryCondition_MaxSizeString_354) {

    std::string maxSizedString(1024, 'a');

    StringRef generatorName(maxSizedString.c_str());

    SourceLineInfo lineInfo(__FILE__, __LINE__);

    IGeneratorTracker* expectedTracker = nullptr;



    EXPECT_CALL(mockResultCapture, acquireGeneratorTracker(generatorName, lineInfo))

        .WillOnce(Return(expectedTracker));



    IGeneratorTracker* actualTracker = Catch::Generators::acquireGeneratorTracker(generatorName, lineInfo);

    EXPECT_EQ(actualTracker, expectedTracker);

}
