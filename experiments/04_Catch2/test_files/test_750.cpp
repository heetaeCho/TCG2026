#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_junit.hpp"

#include "catch2/internal/catch_xmlwriter.hpp"

#include "catch2/internal/catch_test_run_info.hpp"

#include "catch2/catch_timer.hpp"



using namespace Catch;



class JunitReporterTest_750 : public ::testing::Test {

protected:

    std::ostringstream os;

    ReporterConfig config;

    XmlWriter xml{os};

    Timer suiteTimer;

    JunitReporter reporter{std::move(config)};

};



TEST_F(JunitReporterTest_750, TestRunStarting_StartsXmlAndSuiteTimer_750) {

    // Arrange

    TestRunInfo runInfo{"test_suite_name"};



    // Act

    reporter.testRunStarting(runInfo);



    // Assert

    EXPECT_THAT(os.str(), ::testing::HasSubstr("<testsuites>"));

}



TEST_F(JunitReporterTest_750, TestRunStarting_ClearsStdOutForSuite_750) {

    // Arrange

    TestRunInfo runInfo{"test_suite_name"};

    reporter.stdOutForSuite = "some_output";



    // Act

    reporter.testRunStarting(runInfo);



    // Assert

    EXPECT_TRUE(reporter.stdOutForSuite.empty());

}



TEST_F(JunitReporterTest_750, TestRunStarting_ClearsStdErrForSuite_750) {

    // Arrange

    TestRunInfo runInfo{"test_suite_name"};

    reporter.stdErrForSuite = "some_error";



    // Act

    reporter.testRunStarting(runInfo);



    // Assert

    EXPECT_TRUE(reporter.stdErrForSuite.empty());

}



TEST_F(JunitReporterTest_750, TestRunStarting_ResetsUnexpectedExceptions_750) {

    // Arrange

    TestRunInfo runInfo{"test_suite_name"};

    reporter.unexpectedExceptions = 1;



    // Act

    reporter.testRunStarting(runInfo);



    // Assert

    EXPECT_EQ(reporter.unexpectedExceptions, 0);

}
