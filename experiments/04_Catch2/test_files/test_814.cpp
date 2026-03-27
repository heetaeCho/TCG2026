#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_compact.hpp"

#include "catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::NiceMock;



// Mock class for IConfig

class MockIConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(includeSuccessfulResults, bool());

};



// Mock class for AssertionStats

class MockAssertionStats : public AssertionStats {

public:

    MockAssertionStats(const AssertionResult& result, const std::vector<MessageInfo>& messages, const Totals& totals)

        : AssertionStats(result, messages, totals) {}

};



// Test Fixture

class CompactReporterTest_814 : public ::testing::Test {

protected:

    NiceMock<MockIConfig> mockConfig;

    std::ostringstream stream;

    CompactReporter reporter{ ReporterConfig{ &mockConfig, Detail::unique_ptr<IStream>{new OstreamOut{&stream}} } };

};



// Test case for normal operation with a successful assertion

TEST_F(CompactReporterTest_814, SuccessfulAssertionPrintsNothingIfIncludeSuccessfulResultsIsFalse_814) {

    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillOnce(::testing::Return(false));



    AssertionResult result(AssertionInfo(), AssertionResultData());

    result.m_resultData.resultType = ResultWas::Ok;



    MockAssertionStats stats(result, {}, Totals{});

    reporter.assertionEnded(stats);



    EXPECT_EQ(stream.str(), "");

}



// Test case for normal operation with a failed assertion

TEST_F(CompactReporterTest_814, FailedAssertionPrintsSomethingRegardlessOfIncludeSuccessfulResults_814) {

    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillOnce(::testing::Return(false));



    AssertionResult result(AssertionInfo(), AssertionResultData());

    result.m_resultData.resultType = ResultWas::ExpressionFailed;



    MockAssertionStats stats(result, {}, Totals{});

    reporter.assertionEnded(stats);



    EXPECT_NE(stream.str(), "");

}



// Test case for boundary condition with a warning assertion

TEST_F(CompactReporterTest_814, WarningAssertionPrintsWhenIncludeSuccessfulResultsIsFalse_814) {

    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillOnce(::testing::Return(false));



    AssertionResult result(AssertionInfo(), AssertionResultData());

    result.m_resultData.resultType = ResultWas::Warning;



    MockAssertionStats stats(result, {}, Totals{});

    reporter.assertionEnded(stats);



    EXPECT_NE(stream.str(), "");

}



// Test case for boundary condition with an explicit skip

TEST_F(CompactReporterTest_814, ExplicitSkipAssertionPrintsWhenIncludeSuccessfulResultsIsFalse_814) {

    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillOnce(::testing::Return(false));



    AssertionResult result(AssertionInfo(), AssertionResultData());

    result.m_resultData.resultType = ResultWas::ExplicitSkip;



    MockAssertionStats stats(result, {}, Totals{});

    reporter.assertionEnded(stats);



    EXPECT_NE(stream.str(), "");

}



// Test case for normal operation with includeSuccessfulResults set to true

TEST_F(CompactReporterTest_814, SuccessfulAssertionPrintsWhenIncludeSuccessfulResultsIsTrue_814) {

    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillOnce(::testing::Return(true));



    AssertionResult result(AssertionInfo(), AssertionResultData());

    result.m_resultData.resultType = ResultWas::Ok;



    MockAssertionStats stats(result, {}, Totals{});

    reporter.assertionEnded(stats);



    EXPECT_NE(stream.str(), "");

}
