#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>
#include <string>

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;

// Mock for IEventListener
class MockEventListener : public IEventListener {
public:
    MockEventListener() : IEventListener(nullptr) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef unmatchedSpec), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef invalidArgument), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo& testRunInfo), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo& testInfo), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo& testInfo, uint64_t partNumber), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo& sectionInfo), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef benchmarkName), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo& benchmarkInfo), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>& benchmarkStats), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef benchmarkName), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo& assertionInfo), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats& assertionStats), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats& sectionStats), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats& testCaseStats, uint64_t partNumber), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats& testCaseStats), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats& testRunStats), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo& testInfo), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef error), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>& descriptions), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>& descriptions), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>& tests), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>& tags), (override));
};

class MultiReporterTest_805 : public ::testing::Test {
protected:
    MultiReporter multiReporter{ nullptr };

    // Helper to create a mock and keep a raw pointer for expectations
    std::pair<MockEventListener*, Detail::unique_ptr<IEventListener>> createMockReporter() {
        auto* raw = new MockEventListener();
        Detail::unique_ptr<IEventListener> ptr(raw);
        return { raw, std::move(ptr) };
    }
};

// Test skipTest with no reporters (empty multi reporter)
TEST_F(MultiReporterTest_805, SkipTestWithNoReporters_805) {
    NameAndTags nameAndTags("test", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("", nameAndTags, lineInfo);

    // Should not crash with no reporters
    EXPECT_NO_THROW(multiReporter.skipTest(testInfo));
}

// Test skipTest delegates to a single reporter
TEST_F(MultiReporterTest_805, SkipTestDelegatesToSingleReporter_805) {
    auto [mock, ptr] = createMockReporter();
    multiReporter.addReporter(std::move(ptr));

    NameAndTags nameAndTags("test", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("", nameAndTags, lineInfo);

    EXPECT_CALL(*mock, skipTest(_)).Times(Exactly(1));
    multiReporter.skipTest(testInfo);
}

// Test skipTest delegates to multiple reporters
TEST_F(MultiReporterTest_805, SkipTestDelegatesToMultipleReporters_805) {
    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();
    auto [mock3, ptr3] = createMockReporter();

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));
    multiReporter.addReporter(std::move(ptr3));

    NameAndTags nameAndTags("test", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("", nameAndTags, lineInfo);

    EXPECT_CALL(*mock1, skipTest(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, skipTest(_)).Times(Exactly(1));
    EXPECT_CALL(*mock3, skipTest(_)).Times(Exactly(1));

    multiReporter.skipTest(testInfo);
}

// Test skipTest delegates to listeners as well
TEST_F(MultiReporterTest_805, SkipTestDelegatesToListenersAndReporters_805) {
    auto [mockListener, listenerPtr] = createMockReporter();
    auto [mockReporter, reporterPtr] = createMockReporter();

    multiReporter.addListener(std::move(listenerPtr));
    multiReporter.addReporter(std::move(reporterPtr));

    NameAndTags nameAndTags("test", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("", nameAndTags, lineInfo);

    EXPECT_CALL(*mockListener, skipTest(_)).Times(Exactly(1));
    EXPECT_CALL(*mockReporter, skipTest(_)).Times(Exactly(1));

    multiReporter.skipTest(testInfo);
}

// Test noMatchingTestCases delegates to all reporters
TEST_F(MultiReporterTest_805, NoMatchingTestCasesDelegatesToAll_805) {
    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(Exactly(1));

    multiReporter.noMatchingTestCases("spec");
}

// Test fatalErrorEncountered delegates to all reporters
TEST_F(MultiReporterTest_805, FatalErrorEncounteredDelegatesToAll_805) {
    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(Exactly(1));

    multiReporter.fatalErrorEncountered("fatal error");
}

// Test reportInvalidTestSpec delegates to all reporters
TEST_F(MultiReporterTest_805, ReportInvalidTestSpecDelegatesToAll_805) {
    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    EXPECT_CALL(*mock1, reportInvalidTestSpec(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, reportInvalidTestSpec(_)).Times(Exactly(1));

    multiReporter.reportInvalidTestSpec("invalid");
}

// Test testRunStarting delegates to all reporters
TEST_F(MultiReporterTest_805, TestRunStartingDelegatesToAll_805) {
    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    TestRunInfo runInfo("test run");

    EXPECT_CALL(*mock1, testRunStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, testRunStarting(_)).Times(Exactly(1));

    multiReporter.testRunStarting(runInfo);
}

// Test testCaseStarting delegates to all reporters
TEST_F(MultiReporterTest_805, TestCaseStartingDelegatesToAll_805) {
    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    NameAndTags nameAndTags("test", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("", nameAndTags, lineInfo);

    EXPECT_CALL(*mock1, testCaseStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, testCaseStarting(_)).Times(Exactly(1));

    multiReporter.testCaseStarting(testInfo);
}

// Test benchmarkPreparing delegates to all reporters
TEST_F(MultiReporterTest_805, BenchmarkPreparingDelegatesToAll_805) {
    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, benchmarkPreparing(_)).Times(Exactly(1));

    multiReporter.benchmarkPreparing("benchmark");
}

// Test benchmarkFailed delegates to all reporters
TEST_F(MultiReporterTest_805, BenchmarkFailedDelegatesToAll_805) {
    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, benchmarkFailed(_)).Times(Exactly(1));

    multiReporter.benchmarkFailed("error");
}

// Test skipTest called multiple times
TEST_F(MultiReporterTest_805, SkipTestCalledMultipleTimes_805) {
    auto [mock, ptr] = createMockReporter();
    multiReporter.addReporter(std::move(ptr));

    NameAndTags nameAndTags1("test1", "");
    SourceLineInfo lineInfo1("file1.cpp", 1);
    TestCaseInfo testInfo1("", nameAndTags1, lineInfo1);

    NameAndTags nameAndTags2("test2", "");
    SourceLineInfo lineInfo2("file2.cpp", 2);
    TestCaseInfo testInfo2("", nameAndTags2, lineInfo2);

    EXPECT_CALL(*mock, skipTest(_)).Times(Exactly(2));

    multiReporter.skipTest(testInfo1);
    multiReporter.skipTest(testInfo2);
}

// Test adding multiple listeners and a reporter
TEST_F(MultiReporterTest_805, MultipleListenersAndReporterSkipTest_805) {
    auto [mockL1, lPtr1] = createMockReporter();
    auto [mockL2, lPtr2] = createMockReporter();
    auto [mockR1, rPtr1] = createMockReporter();

    multiReporter.addListener(std::move(lPtr1));
    multiReporter.addListener(std::move(lPtr2));
    multiReporter.addReporter(std::move(rPtr1));

    NameAndTags nameAndTags("test", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("", nameAndTags, lineInfo);

    EXPECT_CALL(*mockL1, skipTest(_)).Times(Exactly(1));
    EXPECT_CALL(*mockL2, skipTest(_)).Times(Exactly(1));
    EXPECT_CALL(*mockR1, skipTest(_)).Times(Exactly(1));

    multiReporter.skipTest(testInfo);
}

// Test testCasePartialStarting delegates with correct part number
TEST_F(MultiReporterTest_805, TestCasePartialStartingDelegatesToAll_805) {
    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    NameAndTags nameAndTags("test", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("", nameAndTags, lineInfo);

    EXPECT_CALL(*mock1, testCasePartialStarting(_, 42)).Times(Exactly(1));
    EXPECT_CALL(*mock2, testCasePartialStarting(_, 42)).Times(Exactly(1));

    multiReporter.testCasePartialStarting(testInfo, 42);
}

// Test empty multi reporter for various methods - no crash
TEST_F(MultiReporterTest_805, EmptyMultiReporterDoesNotCrash_805) {
    EXPECT_NO_THROW(multiReporter.noMatchingTestCases("spec"));
    EXPECT_NO_THROW(multiReporter.fatalErrorEncountered("error"));
    EXPECT_NO_THROW(multiReporter.reportInvalidTestSpec("invalid"));
    EXPECT_NO_THROW(multiReporter.benchmarkPreparing("bench"));
    EXPECT_NO_THROW(multiReporter.benchmarkFailed("error"));
}

// Test sectionStarting delegates
TEST_F(MultiReporterTest_805, SectionStartingDelegatesToAll_805) {
    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    SectionInfo sectionInfo("", "section name", SourceLineInfo("file.cpp", 1));

    EXPECT_CALL(*mock1, sectionStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, sectionStarting(_)).Times(Exactly(1));

    multiReporter.sectionStarting(sectionInfo);
}
