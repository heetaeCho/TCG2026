#include <gtest/gtest.h>

#include <Catch2/reporters/catch_reporter_junit.hpp>



using namespace Catch;



class JunitReporterTest_751 : public ::testing::Test {

protected:

    JunitReporter reporter{ ReporterConfig{} };

    TestCaseInfo testCaseInfo{"ClassName", {"TestCaseName", ""}, SourceLineInfo{"filename", 42}};

};



TEST_F(JunitReporterTest_751, testCaseStarting_OkToFailTrue_751) {

    testCaseInfo = TestCaseInfo{"ClassName", {"TestCaseName", ""}, SourceLineInfo{"filename", 42}};

    testing::internal::CaptureStdout();

    reporter.testCaseStarting(testCaseInfo);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(reporter.m_okToFail);

}



TEST_F(JunitReporterTest_751, testCaseStarting_OkToFailFalse_751) {

    testCaseInfo = TestCaseInfo{"ClassName", {"TestCaseName", ""}, SourceLineInfo{"filename", 42}};

    testing::internal::CaptureStdout();

    reporter.testCaseStarting(testCaseInfo);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(reporter.m_okToFail);

}



TEST_F(JunitReporterTest_751, testCaseStarting_HiddenTrue_751) {

    testCaseInfo = TestCaseInfo{"ClassName", {"TestCaseName", ""}, SourceLineInfo{"filename", 42}};

    testCaseInfo.hidden = true;

    testing::internal::CaptureStdout();

    reporter.testCaseStarting(testCaseInfo);

    std::string output = testing::internal::GetCapturedStdout();

}



TEST_F(JunitReporterTest_751, testCaseStarting_HiddenFalse_751) {

    testCaseInfo = TestCaseInfo{"ClassName", {"TestCaseName", ""}, SourceLineInfo{"filename", 42}};

    testCaseInfo.hidden = false;

    testing::internal::CaptureStdout();

    reporter.testCaseStarting(testCaseInfo);

    std::string output = testing::internal::GetCapturedStdout();

}



TEST_F(JunitReporterTest_751, testCaseStarting_ThrowsTrue_751) {

    testCaseInfo = TestCaseInfo{"ClassName", {"TestCaseName", ""}, SourceLineInfo{"filename", 42}};

    testCaseInfo.thrown = true;

    testing::internal::CaptureStdout();

    reporter.testCaseStarting(testCaseInfo);

    std::string output = testing::internal::GetCapturedStdout();

}



TEST_F(JunitReporterTest_751, testCaseStarting_ThrowsFalse_751) {

    testCaseInfo = TestCaseInfo{"ClassName", {"TestCaseName", ""}, SourceLineInfo{"filename", 42}};

    testCaseInfo.thrown = false;

    testing::internal::CaptureStdout();

    reporter.testCaseStarting(testCaseInfo);

    std::string output = testing::internal::GetCapturedStdout();

}



TEST_F(JunitReporterTest_751, testCaseStarting_DefaultValues_751) {

    testCaseInfo = TestCaseInfo{"ClassName", {"TestCaseName", ""}, SourceLineInfo{"filename", 42}};

    reporter.testCaseStarting(testCaseInfo);

}
