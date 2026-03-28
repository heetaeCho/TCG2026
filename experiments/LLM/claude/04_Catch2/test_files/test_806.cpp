#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/benchmark/catch_estimate.hpp"
#include "catch2/benchmark/catch_outlier_classification.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;

// Mock IEventListener for testing
class MockEventListener : public IEventListener {
public:
    MockEventListener() : IEventListener(nullptr) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo&), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo&), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats&), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats&), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats&), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>&), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>&), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>&), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>&), (override));
};

class MultiReporterTest_806 : public ::testing::Test {
protected:
    void SetUp() override {
        multiReporter = Detail::make_unique<MultiReporter>(nullptr);
    }

    Detail::unique_ptr<MultiReporter> multiReporter;
};

// Test: listReporters is forwarded to all added reporters
TEST_F(MultiReporterTest_806, ListReportersForwardsToAllReporters_806) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    std::vector<ReporterDescription> descriptions;

    EXPECT_CALL(*mock1, listReporters(::testing::Ref(descriptions))).Times(1);
    EXPECT_CALL(*mock2, listReporters(::testing::Ref(descriptions))).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->listReporters(descriptions);
}

// Test: listReporters with no reporters does nothing (no crash)
TEST_F(MultiReporterTest_806, ListReportersWithNoReporters_806) {
    std::vector<ReporterDescription> descriptions;
    EXPECT_NO_THROW(multiReporter->listReporters(descriptions));
}

// Test: noMatchingTestCases is forwarded to all reporters
TEST_F(MultiReporterTest_806, NoMatchingTestCasesForwardsToAll_806) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->noMatchingTestCases("someSpec"_catch_sr);
}

// Test: fatalErrorEncountered is forwarded to all reporters
TEST_F(MultiReporterTest_806, FatalErrorEncounteredForwardsToAll_806) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->fatalErrorEncountered("fatal error"_catch_sr);
}

// Test: reportInvalidTestSpec forwarded
TEST_F(MultiReporterTest_806, ReportInvalidTestSpecForwardsToAll_806) {
    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, reportInvalidTestSpec(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));

    multiReporter->reportInvalidTestSpec("invalidArg"_catch_sr);
}

// Test: benchmarkPreparing forwarded
TEST_F(MultiReporterTest_806, BenchmarkPreparingForwardsToAll_806) {
    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));

    multiReporter->benchmarkPreparing("benchName"_catch_sr);
}

// Test: benchmarkFailed forwarded
TEST_F(MultiReporterTest_806, BenchmarkFailedForwardsToAll_806) {
    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));

    multiReporter->benchmarkFailed("error"_catch_sr);
}

// Test: addListener places listeners before reporters
TEST_F(MultiReporterTest_806, AddListenerAndReporterBothReceiveEvents_806) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*reporter, noMatchingTestCases(_)).Times(1);

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter));

    multiReporter->noMatchingTestCases("spec"_catch_sr);
}

// Test: Single reporter receives listReporters
TEST_F(MultiReporterTest_806, SingleReporterReceivesListReporters_806) {
    auto* mock1 = new MockEventListener();

    std::vector<ReporterDescription> descriptions;

    EXPECT_CALL(*mock1, listReporters(::testing::Ref(descriptions))).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));

    multiReporter->listReporters(descriptions);
}

// Test: listListeners forwarded
TEST_F(MultiReporterTest_806, ListListenersForwardsToAll_806) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    std::vector<ListenerDescription> descriptions;

    EXPECT_CALL(*mock1, listListeners(::testing::Ref(descriptions))).Times(1);
    EXPECT_CALL(*mock2, listListeners(::testing::Ref(descriptions))).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->listListeners(descriptions);
}

// Test: listTests forwarded
TEST_F(MultiReporterTest_806, ListTestsForwardsToAll_806) {
    auto* mock1 = new MockEventListener();

    std::vector<TestCaseHandle> tests;

    EXPECT_CALL(*mock1, listTests(::testing::Ref(tests))).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));

    multiReporter->listTests(tests);
}

// Test: listTags forwarded
TEST_F(MultiReporterTest_806, ListTagsForwardsToAll_806) {
    auto* mock1 = new MockEventListener();

    std::vector<TagInfo> tags;

    EXPECT_CALL(*mock1, listTags(::testing::Ref(tags))).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));

    multiReporter->listTags(tags);
}

// Test: skipTest forwarded
TEST_F(MultiReporterTest_806, SkipTestForwardsToAll_806) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, skipTest(_)).Times(1);
    EXPECT_CALL(*mock2, skipTest(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    auto fakeTestCaseInfo = Catch::makeTestCaseInfo(
        ""_catch_sr, {"test", "[tag]"}, {""_catch_sr, 0});
    multiReporter->skipTest(*fakeTestCaseInfo);
}

// Test: Multiple listeners all receive events
TEST_F(MultiReporterTest_806, MultipleListenersReceiveEvents_806) {
    auto* listener1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter1 = new MockEventListener();

    EXPECT_CALL(*listener1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*listener2, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*reporter1, fatalErrorEncountered(_)).Times(1);

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener1));
    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener2));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter1));

    multiReporter->fatalErrorEncountered("fatal"_catch_sr);
}

// Test: No reporters - calling various methods does not crash
TEST_F(MultiReporterTest_806, NoReportersNoMatchingTestCasesNoCrash_806) {
    EXPECT_NO_THROW(multiReporter->noMatchingTestCases("spec"_catch_sr));
}

TEST_F(MultiReporterTest_806, NoReportersFatalErrorNoCrash_806) {
    EXPECT_NO_THROW(multiReporter->fatalErrorEncountered("error"_catch_sr));
}

TEST_F(MultiReporterTest_806, NoReportersReportInvalidTestSpecNoCrash_806) {
    EXPECT_NO_THROW(multiReporter->reportInvalidTestSpec("arg"_catch_sr));
}

TEST_F(MultiReporterTest_806, NoReportersBenchmarkPreparingNoCrash_806) {
    EXPECT_NO_THROW(multiReporter->benchmarkPreparing("name"_catch_sr));
}

TEST_F(MultiReporterTest_806, NoReportersBenchmarkFailedNoCrash_806) {
    EXPECT_NO_THROW(multiReporter->benchmarkFailed("error"_catch_sr));
}

TEST_F(MultiReporterTest_806, NoReportersListListenersNoCrash_806) {
    std::vector<ListenerDescription> descriptions;
    EXPECT_NO_THROW(multiReporter->listListeners(descriptions));
}

TEST_F(MultiReporterTest_806, NoReportersListTestsNoCrash_806) {
    std::vector<TestCaseHandle> tests;
    EXPECT_NO_THROW(multiReporter->listTests(tests));
}

TEST_F(MultiReporterTest_806, NoReportersListTagsNoCrash_806) {
    std::vector<TagInfo> tags;
    EXPECT_NO_THROW(multiReporter->listTags(tags));
}

// Test: Events called multiple times are forwarded each time
TEST_F(MultiReporterTest_806, MultipleCallsForwardedMultipleTimes_806) {
    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(3);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));

    multiReporter->noMatchingTestCases("spec1"_catch_sr);
    multiReporter->noMatchingTestCases("spec2"_catch_sr);
    multiReporter->noMatchingTestCases("spec3"_catch_sr);
}

// Test: assertionStarting forwarded
TEST_F(MultiReporterTest_806, AssertionStartingForwardsToAll_806) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, assertionStarting(_)).Times(1);
    EXPECT_CALL(*mock2, assertionStarting(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    AssertionInfo info{"", {"", 0}, "", ResultDisposition::Normal};
    multiReporter->assertionStarting(info);
}

// Test: sectionStarting forwarded
TEST_F(MultiReporterTest_806, SectionStartingForwardsToAll_806) {
    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, sectionStarting(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));

    SectionInfo sectionInfo{""_catch_sr, "section"};
    multiReporter->sectionStarting(sectionInfo);
}

// Test: Listeners added before reporters still receive events in order
TEST_F(MultiReporterTest_806, ListenersBeforeReportersOrder_806) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    {
        ::testing::InSequence seq;
        EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(1);
        EXPECT_CALL(*reporter, noMatchingTestCases(_)).Times(1);
    }

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter));

    multiReporter->noMatchingTestCases("test"_catch_sr);
}
