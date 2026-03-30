#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_console.hpp"

#include "catch_interfaces_config.hpp"

#include "catch_assertion_result.hpp"

#include "catch_interfaces_reporter.hpp"



using namespace Catch;



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(includeSuccessfulResults, bool());

};



class ConsoleReporterTest_765 : public ::testing::Test {

protected:

    std::ostringstream stream;

    NiceMock<MockConfig> config;

    ConsoleReporter reporter{ ReporterConfig{ &stream, ColourMode::None, &config } };

};



TEST_F(ConsoleReporterTest_765, AssertionEnded_SuccessfulAssertionWithIncludeSuccessfulResultsTrue_765) {

    EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(::testing::Return(true));



    AssertionResult assertionResult(AssertionInfo{}, AssertionResultData{});

    ASSERT_TRUE(assertionResult.isOk());



    AssertionStats assertionStats(assertionResult, {}, Totals{});



    reporter.assertionEnded(assertionStats);



    EXPECT_NE(stream.str().find("Assertion succeeded"), std::string::npos);

}



TEST_F(ConsoleReporterTest_765, AssertionEnded_SuccessfulAssertionWithIncludeSuccessfulResultsFalse_765) {

    EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(::testing::Return(false));



    AssertionResult assertionResult(AssertionInfo{}, AssertionResultData{});

    ASSERT_TRUE(assertionResult.isOk());



    AssertionStats assertionStats(assertionResult, {}, Totals{});



    reporter.assertionEnded(assertionStats);



    EXPECT_EQ(stream.str().find("Assertion succeeded"), std::string::npos);

}



TEST_F(ConsoleReporterTest_765, AssertionEnded_UnsuccessfulAssertion_765) {

    EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(::testing::Return(false));



    AssertionResultData data;

    data.resultType = ResultWas::ExplicitFailure;



    AssertionResult assertionResult(AssertionInfo{}, std::move(data));

    ASSERT_FALSE(assertionResult.isOk());



    AssertionStats assertionStats(assertionResult, {}, Totals{});



    reporter.assertionEnded(assertionStats);



    EXPECT_NE(stream.str().find("Assertion failed"), std::string::npos);

}



TEST_F(ConsoleReporterTest_765, AssertionEnded_WarningResult_765) {

    EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(::testing::Return(false));



    AssertionResultData data;

    data.resultType = ResultWas::Warning;



    AssertionResult assertionResult(AssertionInfo{}, std::move(data));

    ASSERT_FALSE(assertionResult.isOk());



    AssertionStats assertionStats(assertionResult, {}, Totals{});



    reporter.assertionEnded(assertionStats);



    EXPECT_NE(stream.str().find("Assertion warning"), std::string::npos);

}



TEST_F(ConsoleReporterTest_765, AssertionEnded_ExplicitSkipResult_765) {

    EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(::testing::Return(false));



    AssertionResultData data;

    data.resultType = ResultWas::ExplicitSkip;



    AssertionResult assertionResult(AssertionInfo{}, std::move(data));

    ASSERT_FALSE(assertionResult.isOk());



    AssertionStats assertionStats(assertionResult, {}, Totals{});



    reporter.assertionEnded(assertionStats);



    EXPECT_NE(stream.str().find("Assertion skipped"), std::string::npos);

}



TEST_F(ConsoleReporterTest_765, AssertionEnded_ExceptionResult_765) {

    EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(::testing::Return(false));



    AssertionResultData data;

    data.resultType = ResultWas::Exception;



    AssertionResult assertionResult(AssertionInfo{}, std::move(data));

    ASSERT_FALSE(assertionResult.isOk());



    AssertionStats assertionStats(assertionResult, {}, Totals{});



    reporter.assertionEnded(assertionStats);



    EXPECT_NE(stream.str().find("Assertion threw exception"), std::string::npos);

}
