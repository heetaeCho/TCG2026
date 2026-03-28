#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Eq;

// Mock implementation of IEventListener for testing
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

class MultiReporterTest_797 : public ::testing::Test {
protected:
    void SetUp() override {
        multiReporter = Detail::make_unique<MultiReporter>(nullptr);
    }

    Detail::unique_ptr<MultiReporter> multiReporter;
};

// Helper to create a mock and get a raw pointer before moving ownership
struct MockAndPtr {
    MockEventListener* raw;
    Detail::unique_ptr<IEventListener> ptr;
};

static MockAndPtr makeMockReporter() {
    auto* raw = new MockEventListener();
    Detail::unique_ptr<IEventListener> ptr(raw);
    return {raw, std::move(ptr)};
}

// ====== testCasePartialStarting tests ======

TEST_F(MultiReporterTest_797, TestCasePartialStarting_NoReporters_797) {
    // With no reporters added, calling testCasePartialStarting should not crash
    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("ClassName", nameAndTags, lineInfo);
    EXPECT_NO_THROW(multiReporter->testCasePartialStarting(testInfo, 0));
}

TEST_F(MultiReporterTest_797, TestCasePartialStarting_SingleReporter_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("ClassName", nameAndTags, lineInfo);

    EXPECT_CALL(*mock, testCasePartialStarting(_, 42)).Times(1);
    multiReporter->testCasePartialStarting(testInfo, 42);
}

TEST_F(MultiReporterTest_797, TestCasePartialStarting_MultipleReporters_797) {
    auto [mock1, ptr1] = makeMockReporter();
    auto [mock2, ptr2] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("ClassName", nameAndTags, lineInfo);

    EXPECT_CALL(*mock1, testCasePartialStarting(_, 7)).Times(1);
    EXPECT_CALL(*mock2, testCasePartialStarting(_, 7)).Times(1);
    multiReporter->testCasePartialStarting(testInfo, 7);
}

TEST_F(MultiReporterTest_797, TestCasePartialStarting_ListenerAndReporter_797) {
    auto [mockListener, listenerPtr] = makeMockReporter();
    auto [mockReporter, reporterPtr] = makeMockReporter();
    multiReporter->addListener(std::move(listenerPtr));
    multiReporter->addReporter(std::move(reporterPtr));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("ClassName", nameAndTags, lineInfo);

    EXPECT_CALL(*mockListener, testCasePartialStarting(_, 0)).Times(1);
    EXPECT_CALL(*mockReporter, testCasePartialStarting(_, 0)).Times(1);
    multiReporter->testCasePartialStarting(testInfo, 0);
}

TEST_F(MultiReporterTest_797, TestCasePartialStarting_PartNumberZero_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("ClassName", nameAndTags, lineInfo);

    EXPECT_CALL(*mock, testCasePartialStarting(_, 0)).Times(1);
    multiReporter->testCasePartialStarting(testInfo, 0);
}

TEST_F(MultiReporterTest_797, TestCasePartialStarting_MaxPartNumber_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("ClassName", nameAndTags, lineInfo);

    uint64_t maxVal = std::numeric_limits<uint64_t>::max();
    EXPECT_CALL(*mock, testCasePartialStarting(_, maxVal)).Times(1);
    multiReporter->testCasePartialStarting(testInfo, maxVal);
}

// ====== Other delegated method tests ======

TEST_F(MultiReporterTest_797, NoMatchingTestCases_DelegatesToAll_797) {
    auto [mock1, ptr1] = makeMockReporter();
    auto [mock2, ptr2] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(1);
    multiReporter->noMatchingTestCases("someSpec");
}

TEST_F(MultiReporterTest_797, FatalErrorEncountered_DelegatesToAll_797) {
    auto [mock1, ptr1] = makeMockReporter();
    auto [mock2, ptr2] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));

    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(1);
    multiReporter->fatalErrorEncountered("fatal error");
}

TEST_F(MultiReporterTest_797, ReportInvalidTestSpec_DelegatesToAll_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    EXPECT_CALL(*mock, reportInvalidTestSpec(_)).Times(1);
    multiReporter->reportInvalidTestSpec("invalid");
}

TEST_F(MultiReporterTest_797, TestRunStarting_DelegatesToAll_797) {
    auto [mock1, ptr1] = makeMockReporter();
    auto [mock2, ptr2] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));

    TestRunInfo runInfo("test run");
    EXPECT_CALL(*mock1, testRunStarting(_)).Times(1);
    EXPECT_CALL(*mock2, testRunStarting(_)).Times(1);
    multiReporter->testRunStarting(runInfo);
}

TEST_F(MultiReporterTest_797, TestCaseStarting_DelegatesToAll_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("ClassName", nameAndTags, lineInfo);

    EXPECT_CALL(*mock, testCaseStarting(_)).Times(1);
    multiReporter->testCaseStarting(testInfo);
}

TEST_F(MultiReporterTest_797, SkipTest_DelegatesToAll_797) {
    auto [mock1, ptr1] = makeMockReporter();
    auto [mock2, ptr2] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("ClassName", nameAndTags, lineInfo);

    EXPECT_CALL(*mock1, skipTest(_)).Times(1);
    EXPECT_CALL(*mock2, skipTest(_)).Times(1);
    multiReporter->skipTest(testInfo);
}

TEST_F(MultiReporterTest_797, BenchmarkPreparing_DelegatesToAll_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    EXPECT_CALL(*mock, benchmarkPreparing(_)).Times(1);
    multiReporter->benchmarkPreparing("bench");
}

TEST_F(MultiReporterTest_797, BenchmarkFailed_DelegatesToAll_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    EXPECT_CALL(*mock, benchmarkFailed(_)).Times(1);
    multiReporter->benchmarkFailed("error");
}

TEST_F(MultiReporterTest_797, TestCasePartialEnded_DelegatesToAll_797) {
    auto [mock1, ptr1] = makeMockReporter();
    auto [mock2, ptr2] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("ClassName", nameAndTags, lineInfo);
    Totals totals;
    TestCaseStats stats(testInfo, totals, "", "", false);

    EXPECT_CALL(*mock1, testCasePartialEnded(_, 3)).Times(1);
    EXPECT_CALL(*mock2, testCasePartialEnded(_, 3)).Times(1);
    multiReporter->testCasePartialEnded(stats, 3);
}

TEST_F(MultiReporterTest_797, AddMultipleListeners_797) {
    auto [mock1, ptr1] = makeMockReporter();
    auto [mock2, ptr2] = makeMockReporter();
    auto [mock3, ptr3] = makeMockReporter();
    multiReporter->addListener(std::move(ptr1));
    multiReporter->addListener(std::move(ptr2));
    multiReporter->addReporter(std::move(ptr3));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("ClassName", nameAndTags, lineInfo);

    EXPECT_CALL(*mock1, testCasePartialStarting(_, 1)).Times(1);
    EXPECT_CALL(*mock2, testCasePartialStarting(_, 1)).Times(1);
    EXPECT_CALL(*mock3, testCasePartialStarting(_, 1)).Times(1);
    multiReporter->testCasePartialStarting(testInfo, 1);
}

TEST_F(MultiReporterTest_797, TestCasePartialStarting_CalledMultipleTimes_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("ClassName", nameAndTags, lineInfo);

    EXPECT_CALL(*mock, testCasePartialStarting(_, _)).Times(3);
    multiReporter->testCasePartialStarting(testInfo, 0);
    multiReporter->testCasePartialStarting(testInfo, 1);
    multiReporter->testCasePartialStarting(testInfo, 2);
}

TEST_F(MultiReporterTest_797, SectionStarting_DelegatesToAll_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    SectionInfo sectionInfo("file.cpp", 1, "section");

    EXPECT_CALL(*mock, sectionStarting(_)).Times(1);
    multiReporter->sectionStarting(sectionInfo);
}

TEST_F(MultiReporterTest_797, ListReporters_DelegatesToAll_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    std::vector<ReporterDescription> descriptions;
    EXPECT_CALL(*mock, listReporters(_)).Times(1);
    multiReporter->listReporters(descriptions);
}

TEST_F(MultiReporterTest_797, ListListeners_DelegatesToAll_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    std::vector<ListenerDescription> descriptions;
    EXPECT_CALL(*mock, listListeners(_)).Times(1);
    multiReporter->listListeners(descriptions);
}

TEST_F(MultiReporterTest_797, ListTests_DelegatesToAll_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    std::vector<TestCaseHandle> tests;
    EXPECT_CALL(*mock, listTests(_)).Times(1);
    multiReporter->listTests(tests);
}

TEST_F(MultiReporterTest_797, ListTags_DelegatesToAll_797) {
    auto [mock, ptr] = makeMockReporter();
    multiReporter->addReporter(std::move(ptr));

    std::vector<TagInfo> tags;
    EXPECT_CALL(*mock, listTags(_)).Times(1);
    multiReporter->listTags(tags);
}
