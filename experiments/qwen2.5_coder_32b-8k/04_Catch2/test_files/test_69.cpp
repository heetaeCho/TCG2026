#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::Return;



class MockIConfig : public IConfig {

public:

    MOCK_METHOD(ReporterPreferences, getReporterPreferences, (), (const, override));

};



class IEventListenerTest : public ::testing::Test {

protected:

    std::unique_ptr<MockIConfig> mockConfig = std::make_unique<MockIConfig>();

    IEventListener listener{mockConfig.get()};

};



TEST_F(IEventListenerTest_69, GetPreferences_ReturnsStoredPreferences_69) {

    ReporterPreferences expectedPrefs;

    EXPECT_CALL(*mockConfig, getReporterPreferences()).WillOnce(Return(expectedPrefs));



    const ReporterPreferences& actualPrefs = listener.getPreferences();



    EXPECT_EQ(&actualPrefs, &expectedPrefs);

}



TEST_F(IEventListenerTest_69, NoMatchingTestCases_DoesNotThrow_69) {

    StringRef unmatchedSpec("unmatched");

    EXPECT_NO_THROW(listener.noMatchingTestCases(unmatchedSpec));

}



TEST_F(IEventListenerTest_69, ReportInvalidTestSpec_DoesNotThrow_69) {

    StringRef invalidArgument("invalid");

    EXPECT_NO_THROW(listener.reportInvalidTestSpec(invalidArgument));

}



TEST_F(IEventListenerTest_69, TestRunStarting_DoesNotThrow_69) {

    TestRunInfo testRunInfo("testRun", "description", SourceLineInfo{"file.cpp", 1});

    EXPECT_NO_THROW(listener.testRunStarting(testRunInfo));

}



TEST_F(IEventListenerTest_69, TestCaseStarting_DoesNotThrow_69) {

    TestCaseInfo testCaseInfo("testCase", "description", SourceLineInfo{"file.cpp", 2}, Tags{TagInfo{"tag"}});

    EXPECT_NO_THROW(listener.testCaseStarting(testCaseInfo));

}



TEST_F(IEventListenerTest_69, TestCasePartialStarting_DoesNotThrow_69) {

    TestCaseInfo testCaseInfo("testCase", "description", SourceLineInfo{"file.cpp", 3}, Tags{TagInfo{"tag"}});

    uint64_t partNumber = 1;

    EXPECT_NO_THROW(listener.testCasePartialStarting(testCaseInfo, partNumber));

}



TEST_F(IEventListenerTest_69, SectionStarting_DoesNotThrow_69) {

    SectionInfo sectionInfo("section", "description", SourceLineInfo{"file.cpp", 4});

    EXPECT_NO_THROW(listener.sectionStarting(sectionInfo));

}



TEST_F(IEventListenerTest_69, BenchmarkPreparing_DoesNotThrow_69) {

    StringRef benchmarkName("benchmark");

    EXPECT_NO_THROW(listener.benchmarkPreparing(benchmarkName));

}



TEST_F(IEventListenerTest_69, BenchmarkStarting_DoesNotThrow_69) {

    BenchmarkInfo benchmarkInfo("benchmark", "description", SourceLineInfo{"file.cpp", 5});

    EXPECT_NO_THROW(listener.benchmarkStarting(benchmarkInfo));

}



TEST_F(IEventListenerTest_69, BenchmarkEnded_DoesNotThrow_69) {

    BenchmarkStats<> benchmarkStats;

    EXPECT_NO_THROW(listener.benchmarkEnded(benchmarkStats));

}



TEST_F(IEventListenerTest_69, BenchmarkFailed_DoesNotThrow_69) {

    StringRef benchmarkName("benchmark");

    EXPECT_NO_THROW(listener.benchmarkFailed(benchmarkName));

}



TEST_F(IEventListenerTest_69, AssertionStarting_DoesNotThrow_69) {

    AssertionInfo assertionInfo("assertion", SourceLineInfo{"file.cpp", 6});

    EXPECT_NO_THROW(listener.assertionStarting(assertionInfo));

}



TEST_F(IEventListenerTest_69, AssertionEnded_DoesNotThrow_69) {

    AssertionStats assertionStats;

    EXPECT_NO_THROW(listener.assertionEnded(assertionStats));

}



TEST_F(IEventListenerTest_69, SectionEnded_DoesNotThrow_69) {

    SectionStats sectionStats("section", "description", SourceLineInfo{"file.cpp", 7}, true);

    EXPECT_NO_THROW(listener.sectionEnded(sectionStats));

}



TEST_F(IEventListenerTest_69, TestCasePartialEnded_DoesNotThrow_69) {

    TestCaseStats testCaseStats("testCase", "description", SourceLineInfo{"file.cpp", 8}, Tags{TagInfo{"tag"}}, true);

    uint64_t partNumber = 1;

    EXPECT_NO_THROW(listener.testCasePartialEnded(testCaseStats, partNumber));

}



TEST_F(IEventListenerTest_69, TestCaseEnded_DoesNotThrow_69) {

    TestCaseStats testCaseStats("testCase", "description", SourceLineInfo{"file.cpp", 9}, Tags{TagInfo{"tag"}}, true);

    EXPECT_NO_THROW(listener.testCaseEnded(testCaseStats));

}



TEST_F(IEventListenerTest_69, TestRunEnded_DoesNotThrow_69) {

    TestRunStats testRunStats("testRun", "description", SourceLineInfo{"file.cpp", 10}, 1, false);

    EXPECT_NO_THROW(listener.testRunEnded(testRunStats));

}



TEST_F(IEventListenerTest_69, SkipTest_DoesNotThrow_69) {

    TestCaseInfo testCaseInfo("testCase", "description", SourceLineInfo{"file.cpp", 11}, Tags{TagInfo{"tag"}});

    EXPECT_NO_THROW(listener.skipTest(testCaseInfo));

}



TEST_F(IEventListenerTest_69, FatalErrorEncountered_DoesNotThrow_69) {

    StringRef error("fatal error");

    EXPECT_NO_THROW(listener.fatalErrorEncountered(error));

}



TEST_F(IEventListenerTest_69, ListReporters_DoesNotThrow_69) {

    std::vector<ReporterDescription> descriptions;

    EXPECT_NO_THROW(listener.listReporters(descriptions));

}



TEST_F(IEventListenerTest_69, ListListeners_DoesNotThrow_69) {

    std::vector<ListenerDescription> descriptions;

    EXPECT_NO_THROW(listener.listListeners(descriptions));

}



TEST_F(IEventListenerTest_69, ListTests_DoesNotThrow_69) {

    std::vector<TestCaseHandle> tests;

    EXPECT_NO_THROW(listener.listTests(tests));

}



TEST_F(IEventListenerTest_69, ListTags_DoesNotThrow_69) {

    std::vector<TagInfo> tags;

    EXPECT_NO_THROW(listener.listTags(tags));

}
