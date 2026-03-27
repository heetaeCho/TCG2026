#include <gtest/gtest.h>

#include "catch_reporter_streaming_base.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;



class StreamingReporterBaseTest_562 : public ::testing::Test {

protected:

    ReporterConfig config;

    StreamingReporterBase reporter;



    StreamingReporterBaseTest_562() : reporter(std::move(config)) {}



    TestCaseInfo createTestCaseInfo(const StringRef& className, const NameAndTags& nameAndTags, const SourceLineInfo& lineInfo) {

        return TestCaseInfo(className, nameAndTags, lineInfo);

    }

};



TEST_F(StreamingReporterBaseTest_562, TestCaseStarting_SetsCurrentTestCaseInfo_562) {

    TestCaseInfo testInfo = createTestCaseInfo("TestClass"_sr, {"testName"}, SourceLineInfo{"file.cpp", 10});

    reporter.testCaseStarting(testInfo);

    EXPECT_EQ(reporter.currentTestCaseInfo, &testInfo);

}



TEST_F(StreamingReporterBaseTest_562, TestCaseStarting_MultipleCalls_UpdateCurrentTestCaseInfo_562) {

    TestCaseInfo testInfo1 = createTestCaseInfo("TestClass"_sr, {"testName1"}, SourceLineInfo{"file.cpp", 10});

    TestCaseInfo testInfo2 = createTestCaseInfo("TestClass"_sr, {"testName2"}, SourceLineInfo{"file.cpp", 20});

    

    reporter.testCaseStarting(testInfo1);

    EXPECT_EQ(reporter.currentTestCaseInfo, &testInfo1);



    reporter.testCaseStarting(testInfo2);

    EXPECT_EQ(reporter.currentTestCaseInfo, &testInfo2);

}



TEST_F(StreamingReporterBaseTest_562, TestCaseStarting_DefaultConstructed_ShouldNotCrash_562) {

    TestCaseInfo testInfo = createTestCaseInfo("TestClass"_sr, {"testName"}, SourceLineInfo{"file.cpp", 10});

    reporter.testCaseStarting(testInfo);

    EXPECT_NO_THROW(reporter.testCaseStarting(TestCaseInfo{}));

}
