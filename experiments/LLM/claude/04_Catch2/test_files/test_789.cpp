#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Eq;

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

class MultiReporterTest_789 : public ::testing::Test {
protected:
    MultiReporter multiReporter{nullptr};

    // Helper to create a mock and keep a raw pointer for expectations
    std::pair<MockEventListener*, Detail::unique_ptr<IEventListener>> createMock() {
        auto* raw = new MockEventListener();
        Detail::unique_ptr<IEventListener> ptr(raw);
        return {raw, std::move(ptr)};
    }
};

// --- fatalErrorEncountered tests ---

TEST_F(MultiReporterTest_789, FatalErrorEncountered_NoReporters_DoesNotCrash_789) {
    // No reporters added, should not crash
    multiReporter.fatalErrorEncountered("some error");
}

TEST_F(MultiReporterTest_789, FatalErrorEncountered_SingleReporter_CallsReporter_789) {
    auto [mock, ptr] = createMock();
    EXPECT_CALL(*mock, fatalErrorEncountered(_)).Times(1);
    multiReporter.addReporter(std::move(ptr));
    multiReporter.fatalErrorEncountered("fatal error");
}

TEST_F(MultiReporterTest_789, FatalErrorEncountered_MultipleReporters_CallsAll_789) {
    auto [mock1, ptr1] = createMock();
    auto [mock2, ptr2] = createMock();
    auto [mock3, ptr3] = createMock();

    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mock3, fatalErrorEncountered(_)).Times(1);

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));
    multiReporter.addReporter(std::move(ptr3));

    multiReporter.fatalErrorEncountered("crash");
}

TEST_F(MultiReporterTest_789, FatalErrorEncountered_ListenerAndReporter_CallsBoth_789) {
    auto [mockListener, ptrListener] = createMock();
    auto [mockReporter, ptrReporter] = createMock();

    EXPECT_CALL(*mockListener, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mockReporter, fatalErrorEncountered(_)).Times(1);

    multiReporter.addListener(std::move(ptrListener));
    multiReporter.addReporter(std::move(ptrReporter));

    multiReporter.fatalErrorEncountered("error");
}

TEST_F(MultiReporterTest_789, FatalErrorEncountered_EmptyString_789) {
    auto [mock, ptr] = createMock();
    EXPECT_CALL(*mock, fatalErrorEncountered(_)).Times(1);
    multiReporter.addReporter(std::move(ptr));
    multiReporter.fatalErrorEncountered("");
}

// --- noMatchingTestCases tests ---

TEST_F(MultiReporterTest_789, NoMatchingTestCases_NoReporters_DoesNotCrash_789) {
    multiReporter.noMatchingTestCases("spec");
}

TEST_F(MultiReporterTest_789, NoMatchingTestCases_SingleReporter_789) {
    auto [mock, ptr] = createMock();
    EXPECT_CALL(*mock, noMatchingTestCases(_)).Times(1);
    multiReporter.addReporter(std::move(ptr));
    multiReporter.noMatchingTestCases("unmatched");
}

TEST_F(MultiReporterTest_789, NoMatchingTestCases_MultipleReporters_789) {
    auto [mock1, ptr1] = createMock();
    auto [mock2, ptr2] = createMock();

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(1);

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));
    multiReporter.noMatchingTestCases("spec");
}

// --- reportInvalidTestSpec tests ---

TEST_F(MultiReporterTest_789, ReportInvalidTestSpec_NoReporters_789) {
    multiReporter.reportInvalidTestSpec("bad spec");
}

TEST_F(MultiReporterTest_789, ReportInvalidTestSpec_MultipleReporters_789) {
    auto [mock1, ptr1] = createMock();
    auto [mock2, ptr2] = createMock();

    EXPECT_CALL(*mock1, reportInvalidTestSpec(_)).Times(1);
    EXPECT_CALL(*mock2, reportInvalidTestSpec(_)).Times(1);

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));
    multiReporter.reportInvalidTestSpec("invalid");
}

// --- benchmarkPreparing tests ---

TEST_F(MultiReporterTest_789, BenchmarkPreparing_MultipleReporters_789) {
    auto [mock1, ptr1] = createMock();
    auto [mock2, ptr2] = createMock();

    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkPreparing(_)).Times(1);

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));
    multiReporter.benchmarkPreparing("bench1");
}

// --- benchmarkFailed tests ---

TEST_F(MultiReporterTest_789, BenchmarkFailed_MultipleReporters_789) {
    auto [mock1, ptr1] = createMock();
    auto [mock2, ptr2] = createMock();

    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkFailed(_)).Times(1);

    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));
    multiReporter.benchmarkFailed("bench error");
}

// --- addListener ordering: listeners before reporters ---

TEST_F(MultiReporterTest_789, AddListenerAndReporter_FatalErrorCallsBoth_789) {
    auto [mockListener1, ptrL1] = createMock();
    auto [mockReporter1, ptrR1] = createMock();
    auto [mockListener2, ptrL2] = createMock();

    {
        ::testing::InSequence seq;
        // Listeners should be called before reporters (since listeners are inserted first)
        EXPECT_CALL(*mockListener1, fatalErrorEncountered(_)).Times(1);
        EXPECT_CALL(*mockListener2, fatalErrorEncountered(_)).Times(1);
        EXPECT_CALL(*mockReporter1, fatalErrorEncountered(_)).Times(1);
    }

    multiReporter.addListener(std::move(ptrL1));
    multiReporter.addReporter(std::move(ptrR1));
    multiReporter.addListener(std::move(ptrL2));

    multiReporter.fatalErrorEncountered("ordered error");
}

// --- Multiple calls ---

TEST_F(MultiReporterTest_789, FatalErrorEncountered_CalledMultipleTimes_789) {
    auto [mock, ptr] = createMock();
    EXPECT_CALL(*mock, fatalErrorEncountered(_)).Times(3);
    multiReporter.addReporter(std::move(ptr));

    multiReporter.fatalErrorEncountered("error1");
    multiReporter.fatalErrorEncountered("error2");
    multiReporter.fatalErrorEncountered("error3");
}

// --- skipTest tests ---

TEST_F(MultiReporterTest_789, SkipTest_NoReporters_DoesNotCrash_789) {
    // Cannot easily create a TestCaseInfo, but we test the no-reporter case
    // This test validates that with no reporters, skipTest doesn't crash.
    // Since we can't easily construct TestCaseInfo, we skip this if it won't compile.
    // Instead, test with a mock added.
    auto [mock, ptr] = createMock();
    EXPECT_CALL(*mock, skipTest(_)).Times(1);
    multiReporter.addReporter(std::move(ptr));

    // We need a TestCaseInfo - this depends on the Catch2 API
    // Use a minimal construction if possible
    TestCaseInfo info("", {"test", "tag"}, {"file.cpp", 1});
    multiReporter.skipTest(info);
}

// --- Mixed listeners and reporters for various events ---

TEST_F(MultiReporterTest_789, NoMatchingTestCases_ListenerAndReporter_789) {
    auto [mockL, ptrL] = createMock();
    auto [mockR, ptrR] = createMock();

    EXPECT_CALL(*mockL, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mockR, noMatchingTestCases(_)).Times(1);

    multiReporter.addListener(std::move(ptrL));
    multiReporter.addReporter(std::move(ptrR));

    multiReporter.noMatchingTestCases("spec");
}

// --- Boundary: adding many reporters ---

TEST_F(MultiReporterTest_789, FatalErrorEncountered_ManyReporters_789) {
    std::vector<MockEventListener*> mocks;
    for (int i = 0; i < 10; ++i) {
        auto [mock, ptr] = createMock();
        EXPECT_CALL(*mock, fatalErrorEncountered(_)).Times(1);
        mocks.push_back(mock);
        multiReporter.addReporter(std::move(ptr));
    }
    multiReporter.fatalErrorEncountered("mass error");
}

// --- Boundary: single listener, no reporters ---

TEST_F(MultiReporterTest_789, FatalErrorEncountered_SingleListener_789) {
    auto [mock, ptr] = createMock();
    EXPECT_CALL(*mock, fatalErrorEncountered(_)).Times(1);
    multiReporter.addListener(std::move(ptr));
    multiReporter.fatalErrorEncountered("listener error");
}
