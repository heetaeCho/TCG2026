#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_multi.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats& testStats, uint64_t partNumber), (override));

};



class MultiReporterTest_802 : public ::testing::Test {

protected:

    MultiReporter reporter;

    NiceMock<MockIEventListener> mockListener;



    void SetUp() override {

        reporter.addListener(IEventListenerPtr(&mockListener, [](auto*){}));

    }

};



TEST_F(MultiReporterTest_802, testCasePartialEnded_DelegatesToListeners_NormalOperation_802) {

    TestCaseStats testStats(TestCaseInfo("test", "", 1), Totals(), "stdOut", "stdErr", false);

    uint64_t partNumber = 1;



    EXPECT_CALL(mockListener, testCasePartialEnded(testStats, partNumber));



    reporter.testCasePartialEnded(testStats, partNumber);

}



TEST_F(MultiReporterTest_802, testCasePartialEnded_StdOutEmpty_NoOutputToCout_802) {

    TestCaseStats testStats(TestCaseInfo("test", "", 1), Totals(), "", "stdErr", false);

    uint64_t partNumber = 1;



    EXPECT_CALL(mockListener, testCasePartialEnded(testStats, partNumber));



    reporter.testCasePartialEnded(testStats, partNumber);

}



TEST_F(MultiReporterTest_802, testCasePartialEnded_StdErrEmpty_NoOutputToCerr_802) {

    TestCaseStats testStats(TestCaseInfo("test", "", 1), Totals(), "stdOut", "", false);

    uint64_t partNumber = 1;



    EXPECT_CALL(mockListener, testCasePartialEnded(testStats, partNumber));



    reporter.testCasePartialEnded(testStats, partNumber);

}



TEST_F(MultiReporterTest_802, testCasePartialEnded_ShouldRedirectStdOutAndHaveNoncapturingReporters_OutputToCoutAndCerr_802) {

    TestCaseStats testStats(TestCaseInfo("test", "", 1), Totals(), "stdOut", "stdErr", false);

    uint64_t partNumber = 1;

    reporter.m_preferences.shouldRedirectStdOut = true;

    reporter.m_haveNoncapturingReporters = true;



    EXPECT_CALL(mockListener, testCasePartialEnded(testStats, partNumber));



    testing::internal::CaptureStdout();

    testing::internal::CaptureStderr();



    reporter.testCasePartialEnded(testStats, partNumber);



    std::string cout_output = testing::internal::GetCapturedStdout();

    std::string cerr_output = testing::internal::GetCapturedStderr();



    EXPECT_EQ(cout_output, "stdOut");

    EXPECT_EQ(cerr_output, "stdErr");

}



TEST_F(MultiReporterTest_802, testCasePartialEnded_NoListeners_NoDelegation_802) {

    TestCaseStats testStats(TestCaseInfo("test", "", 1), Totals(), "stdOut", "stdErr", false);

    uint64_t partNumber = 1;

    reporter.m_reporterLikes.clear();



    EXPECT_CALL(mockListener, testCasePartialEnded(testStats, partNumber)).Times(0);



    reporter.testCasePartialEnded(testStats, partNumber);

}



TEST_F(MultiReporterTest_802, testCasePartialEnded_ShouldNotRedirectStdOut_NoOutputToCout_802) {

    TestCaseStats testStats(TestCaseInfo("test", "", 1), Totals(), "stdOut", "stdErr", false);

    uint64_t partNumber = 1;

    reporter.m_preferences.shouldRedirectStdOut = false;



    EXPECT_CALL(mockListener, testCasePartialEnded(testStats, partNumber));



    testing::internal::CaptureStdout();

    testing::internal::CaptureStderr();



    reporter.testCasePartialEnded(testStats, partNumber);



    std::string cout_output = testing::internal::GetCapturedStdout();

    std::string cerr_output = testing::internal::GetCapturedStderr();



    EXPECT_EQ(cout_output, "");

    EXPECT_EQ(cerr_output, "");

}



TEST_F(MultiReporterTest_802, testCasePartialEnded_NoNoncapturingReporters_NoOutputToCoutAndCerr_802) {

    TestCaseStats testStats(TestCaseInfo("test", "", 1), Totals(), "stdOut", "stdErr", false);

    uint64_t partNumber = 1;

    reporter.m_preferences.shouldRedirectStdOut = true;

    reporter.m_haveNoncapturingReporters = false;



    EXPECT_CALL(mockListener, testCasePartialEnded(testStats, partNumber));



    testing::internal::CaptureStdout();

    testing::internal::CaptureStderr();



    reporter.testCasePartialEnded(testStats, partNumber);



    std::string cout_output = testing::internal::GetCapturedStdout();

    std::string cerr_output = testing::internal::GetCapturedStderr();



    EXPECT_EQ(cout_output, "");

    EXPECT_EQ(cerr_output, "");

}
