#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::InSequence;

namespace {

class MockEventListener : public IEventListener {
public:
    MockEventListener() : IEventListener( Catch::IConfig::empty() ) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo&), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo&), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo&), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats&), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats&), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats&), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>&), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>&), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>&), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>&), (override));
};

class MultiReporterTest_786 : public ::testing::Test {
protected:
    void SetUp() override {
        multiReporter = Detail::make_unique<MultiReporter>( Catch::IConfig::empty() );
    }

    Detail::unique_ptr<MultiReporter> multiReporter;
};

} // anonymous namespace

// Test adding a single reporter and forwarding noMatchingTestCases
TEST_F(MultiReporterTest_786, NoMatchingTestCasesForwardedToReporter_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, noMatchingTestCases(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter->noMatchingTestCases("some spec"_catch_sr);
}

// Test adding a single listener and forwarding noMatchingTestCases
TEST_F(MultiReporterTest_786, NoMatchingTestCasesForwardedToListener_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, noMatchingTestCases(_)).Times(1);

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(mock));
    multiReporter->noMatchingTestCases("some spec"_catch_sr);
}

// Test that events are forwarded to multiple reporters
TEST_F(MultiReporterTest_786, EventForwardedToMultipleReporters_786) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));
    multiReporter->noMatchingTestCases("test"_catch_sr);
}

// Test that events are forwarded to both listeners and reporters
TEST_F(MultiReporterTest_786, EventForwardedToListenersAndReporters_786) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();
    EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*reporter, noMatchingTestCases(_)).Times(1);

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter));
    multiReporter->noMatchingTestCases("test"_catch_sr);
}

// Test listeners are called before reporters (ordering)
TEST_F(MultiReporterTest_786, ListenersCalledBeforeReporters_786) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    {
        InSequence seq;
        EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(1);
        EXPECT_CALL(*reporter, noMatchingTestCases(_)).Times(1);
    }

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter));
    multiReporter->noMatchingTestCases("test"_catch_sr);
}

// Test listener added after reporter still comes first
TEST_F(MultiReporterTest_786, ListenerAddedAfterReporterStillFirst_786) {
    auto* reporter = new MockEventListener();
    auto* listener = new MockEventListener();

    {
        InSequence seq;
        EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(1);
        EXPECT_CALL(*reporter, noMatchingTestCases(_)).Times(1);
    }

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter));
    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter->noMatchingTestCases("test"_catch_sr);
}

// Test fatalErrorEncountered forwarding
TEST_F(MultiReporterTest_786, FatalErrorEncounteredForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, fatalErrorEncountered(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter->fatalErrorEncountered("fatal"_catch_sr);
}

// Test reportInvalidTestSpec forwarding
TEST_F(MultiReporterTest_786, ReportInvalidTestSpecForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, reportInvalidTestSpec(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter->reportInvalidTestSpec("bad spec"_catch_sr);
}

// Test benchmarkPreparing forwarding
TEST_F(MultiReporterTest_786, BenchmarkPreparingForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkPreparing(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter->benchmarkPreparing("bench"_catch_sr);
}

// Test benchmarkFailed forwarding
TEST_F(MultiReporterTest_786, BenchmarkFailedForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkFailed(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter->benchmarkFailed("bench error"_catch_sr);
}

// Test testRunStarting forwarding
TEST_F(MultiReporterTest_786, TestRunStartingForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testRunStarting(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    TestRunInfo runInfo("test run");
    multiReporter->testRunStarting(runInfo);
}

// Test testCaseStarting forwarding
TEST_F(MultiReporterTest_786, TestCaseStartingForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testCaseStarting(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));

    auto testInfo = Catch::makeTestCaseInfo(
        ""_catch_sr, {"test case", "[tag]"}, {""_catch_sr, 0});
    multiReporter->testCaseStarting(*testInfo);
}

// Test skipTest forwarding
TEST_F(MultiReporterTest_786, SkipTestForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, skipTest(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));

    auto testInfo = Catch::makeTestCaseInfo(
        ""_catch_sr, {"test case", "[tag]"}, {""_catch_sr, 0});
    multiReporter->skipTest(*testInfo);
}

// Test sectionStarting forwarding
TEST_F(MultiReporterTest_786, SectionStartingForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, sectionStarting(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    SectionInfo sectionInfo(""_catch_sr, "section name"_catch_sr);
    multiReporter->sectionStarting(sectionInfo);
}

// Test assertionStarting forwarding
TEST_F(MultiReporterTest_786, AssertionStartingForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, assertionStarting(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    AssertionInfo info{"", {""_catch_sr, 0}, ""_catch_sr, ResultDisposition::Normal};
    multiReporter->assertionStarting(info);
}

// Test no reporters - calling methods should not crash
TEST_F(MultiReporterTest_786, NoReportersDoesNotCrash_786) {
    EXPECT_NO_THROW(multiReporter->noMatchingTestCases("test"_catch_sr));
    EXPECT_NO_THROW(multiReporter->fatalErrorEncountered("error"_catch_sr));
    EXPECT_NO_THROW(multiReporter->reportInvalidTestSpec("spec"_catch_sr));
    EXPECT_NO_THROW(multiReporter->benchmarkPreparing("bench"_catch_sr));
    EXPECT_NO_THROW(multiReporter->benchmarkFailed("err"_catch_sr));
}

// Test multiple listeners ordering
TEST_F(MultiReporterTest_786, MultipleListenersOrdering_786) {
    auto* listener1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter = new MockEventListener();

    {
        InSequence seq;
        EXPECT_CALL(*listener1, fatalErrorEncountered(_)).Times(1);
        EXPECT_CALL(*listener2, fatalErrorEncountered(_)).Times(1);
        EXPECT_CALL(*reporter, fatalErrorEncountered(_)).Times(1);
    }

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener1));
    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener2));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter));
    multiReporter->fatalErrorEncountered("fatal"_catch_sr);
}

// Test listReporters forwarding
TEST_F(MultiReporterTest_786, ListReportersForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, listReporters(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    std::vector<ReporterDescription> descriptions;
    multiReporter->listReporters(descriptions);
}

// Test listListeners forwarding
TEST_F(MultiReporterTest_786, ListListenersForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, listListeners(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    std::vector<ListenerDescription> descriptions;
    multiReporter->listListeners(descriptions);
}

// Test listTests forwarding
TEST_F(MultiReporterTest_786, ListTestsForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, listTests(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    std::vector<TestCaseHandle> tests;
    multiReporter->listTests(tests);
}

// Test listTags forwarding
TEST_F(MultiReporterTest_786, ListTagsForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, listTags(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    std::vector<TagInfo> tags;
    multiReporter->listTags(tags);
}

// Test testCasePartialStarting forwarding
TEST_F(MultiReporterTest_786, TestCasePartialStartingForwarded_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testCasePartialStarting(_, 42)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    auto testInfo = Catch::makeTestCaseInfo(
        ""_catch_sr, {"test case", "[tag]"}, {""_catch_sr, 0});
    multiReporter->testCasePartialStarting(*testInfo, 42);
}

// Test event forwarded multiple times
TEST_F(MultiReporterTest_786, MultipleEventCalls_786) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkPreparing(_)).Times(3);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter->benchmarkPreparing("a"_catch_sr);
    multiReporter->benchmarkPreparing("b"_catch_sr);
    multiReporter->benchmarkPreparing("c"_catch_sr);
}

// Test interleaved listener and reporter additions maintain correct order
TEST_F(MultiReporterTest_786, InterleavedAdditionsCorrectOrder_786) {
    auto* reporter1 = new MockEventListener();
    auto* listener1 = new MockEventListener();
    auto* reporter2 = new MockEventListener();
    auto* listener2 = new MockEventListener();

    {
        InSequence seq;
        EXPECT_CALL(*listener1, reportInvalidTestSpec(_)).Times(1);
        EXPECT_CALL(*listener2, reportInvalidTestSpec(_)).Times(1);
        EXPECT_CALL(*reporter1, reportInvalidTestSpec(_)).Times(1);
        EXPECT_CALL(*reporter2, reportInvalidTestSpec(_)).Times(1);
    }

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter1));
    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter2));
    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener2));
    multiReporter->reportInvalidTestSpec("bad"_catch_sr);
}
