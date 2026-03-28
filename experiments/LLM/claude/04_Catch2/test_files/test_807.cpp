#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"
#include "catch2/benchmark/catch_estimate.hpp"
#include "catch2/benchmark/catch_outlier_classification.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;

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

class MultiReporterTest_807 : public ::testing::Test {
protected:
    void SetUp() override {
        multiReporter = Detail::make_unique<MultiReporter>(nullptr);
    }

    Detail::unique_ptr<MultiReporter> multiReporter;
};

// Helper to create a mock and return both the raw pointer and a unique_ptr
std::pair<MockEventListener*, Detail::unique_ptr<IEventListener>> createMockListener() {
    auto* raw = new MockEventListener();
    Detail::unique_ptr<IEventListener> ptr(raw);
    return {raw, std::move(ptr)};
}

TEST_F(MultiReporterTest_807, NoReporters_NoMatchingTestCases_807) {
    // Should not crash when no reporters are added
    EXPECT_NO_THROW(multiReporter->noMatchingTestCases("spec"_catch_sr));
}

TEST_F(MultiReporterTest_807, SingleReporter_NoMatchingTestCases_807) {
    auto [mock, ptr] = createMockListener();
    EXPECT_CALL(*mock, noMatchingTestCases(_)).Times(1);
    multiReporter->addReporter(std::move(ptr));
    multiReporter->noMatchingTestCases("unmatchedSpec"_catch_sr);
}

TEST_F(MultiReporterTest_807, MultipleReporters_NoMatchingTestCases_807) {
    auto [mock1, ptr1] = createMockListener();
    auto [mock2, ptr2] = createMockListener();
    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));
    multiReporter->noMatchingTestCases("spec"_catch_sr);
}

TEST_F(MultiReporterTest_807, FatalErrorEncountered_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    auto [mock2, ptr2] = createMockListener();
    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));
    multiReporter->fatalErrorEncountered("fatal error"_catch_sr);
}

TEST_F(MultiReporterTest_807, ReportInvalidTestSpec_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    auto [mock2, ptr2] = createMockListener();
    EXPECT_CALL(*mock1, reportInvalidTestSpec(_)).Times(1);
    EXPECT_CALL(*mock2, reportInvalidTestSpec(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));
    multiReporter->reportInvalidTestSpec("invalid"_catch_sr);
}

TEST_F(MultiReporterTest_807, BenchmarkPreparing_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->benchmarkPreparing("bench"_catch_sr);
}

TEST_F(MultiReporterTest_807, BenchmarkFailed_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->benchmarkFailed("error"_catch_sr);
}

TEST_F(MultiReporterTest_807, TestRunStarting_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    auto [mock2, ptr2] = createMockListener();
    EXPECT_CALL(*mock1, testRunStarting(_)).Times(1);
    EXPECT_CALL(*mock2, testRunStarting(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));
    TestRunInfo runInfo("test_group");
    multiReporter->testRunStarting(runInfo);
}

TEST_F(MultiReporterTest_807, TestRunEnded_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, testRunEnded(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    Totals totals;
    TestRunStats runStats(TestRunInfo("test_group"), totals, false);
    multiReporter->testRunEnded(runStats);
}

TEST_F(MultiReporterTest_807, ListListeners_NoReporters_807) {
    std::vector<ListenerDescription> descriptions;
    EXPECT_NO_THROW(multiReporter->listListeners(descriptions));
}

TEST_F(MultiReporterTest_807, ListListeners_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    auto [mock2, ptr2] = createMockListener();
    EXPECT_CALL(*mock1, listListeners(_)).Times(1);
    EXPECT_CALL(*mock2, listListeners(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));
    std::vector<ListenerDescription> descriptions;
    multiReporter->listListeners(descriptions);
}

TEST_F(MultiReporterTest_807, ListReporters_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    auto [mock2, ptr2] = createMockListener();
    EXPECT_CALL(*mock1, listReporters(_)).Times(1);
    EXPECT_CALL(*mock2, listReporters(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));
    std::vector<ReporterDescription> descriptions;
    multiReporter->listReporters(descriptions);
}

TEST_F(MultiReporterTest_807, ListTests_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, listTests(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    std::vector<TestCaseHandle> tests;
    multiReporter->listTests(tests);
}

TEST_F(MultiReporterTest_807, ListTags_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, listTags(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    std::vector<TagInfo> tags;
    multiReporter->listTags(tags);
}

TEST_F(MultiReporterTest_807, AddListener_ForwardsEventsToListener_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    multiReporter->addListener(std::move(ptr1));
    multiReporter->noMatchingTestCases("spec"_catch_sr);
}

TEST_F(MultiReporterTest_807, ListenerAndReporter_BothReceiveEvents_807) {
    auto [mockListener, listenerPtr] = createMockListener();
    auto [mockReporter, reporterPtr] = createMockListener();
    EXPECT_CALL(*mockListener, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mockReporter, noMatchingTestCases(_)).Times(1);
    multiReporter->addListener(std::move(listenerPtr));
    multiReporter->addReporter(std::move(reporterPtr));
    multiReporter->noMatchingTestCases("spec"_catch_sr);
}

TEST_F(MultiReporterTest_807, SkipTest_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    auto [mock2, ptr2] = createMockListener();
    EXPECT_CALL(*mock1, skipTest(_)).Times(1);
    EXPECT_CALL(*mock2, skipTest(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->addReporter(std::move(ptr2));
    
    auto info = makeTestCaseInfo("", {"test", "[tag]"}, {});
    multiReporter->skipTest(*info);
}

TEST_F(MultiReporterTest_807, TestCaseStarting_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, testCaseStarting(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    auto info = makeTestCaseInfo("", {"test", "[tag]"}, {});
    multiReporter->testCaseStarting(*info);
}

TEST_F(MultiReporterTest_807, TestCaseEnded_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, testCaseEnded(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    auto info = makeTestCaseInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(*info, totals, "", "", false);
    multiReporter->testCaseEnded(stats);
}

TEST_F(MultiReporterTest_807, SectionStarting_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, sectionStarting(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    SectionInfo sectionInfo("", "section_name");
    multiReporter->sectionStarting(sectionInfo);
}

TEST_F(MultiReporterTest_807, SectionEnded_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, sectionEnded(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    Counts assertions;
    SectionInfo sectionInfo("", "section_name");
    SectionStats sectionStats(sectionInfo, assertions, 0.0, false);
    multiReporter->sectionEnded(sectionStats);
}

TEST_F(MultiReporterTest_807, AssertionStarting_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, assertionStarting(_)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    AssertionInfo assertionInfo("", {""_catch_sr, 0}, ""_catch_sr, ResultDisposition::Normal);
    multiReporter->assertionStarting(assertionInfo);
}

TEST_F(MultiReporterTest_807, TestCasePartialStarting_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, testCasePartialStarting(_, 42)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    auto info = makeTestCaseInfo("", {"test", "[tag]"}, {});
    multiReporter->testCasePartialStarting(*info, 42);
}

TEST_F(MultiReporterTest_807, TestCasePartialEnded_ForwardedToAll_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, testCasePartialEnded(_, 7)).Times(1);
    multiReporter->addReporter(std::move(ptr1));
    auto info = makeTestCaseInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(*info, totals, "", "", false);
    multiReporter->testCasePartialEnded(stats, 7);
}

TEST_F(MultiReporterTest_807, MultipleListenersAndReporters_AllReceiveEvents_807) {
    auto [mockL1, ptrL1] = createMockListener();
    auto [mockL2, ptrL2] = createMockListener();
    auto [mockR1, ptrR1] = createMockListener();
    auto [mockR2, ptrR2] = createMockListener();

    EXPECT_CALL(*mockL1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mockL2, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mockR1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mockR2, fatalErrorEncountered(_)).Times(1);

    multiReporter->addListener(std::move(ptrL1));
    multiReporter->addListener(std::move(ptrL2));
    multiReporter->addReporter(std::move(ptrR1));
    multiReporter->addReporter(std::move(ptrR2));

    multiReporter->fatalErrorEncountered("fatal"_catch_sr);
}

TEST_F(MultiReporterTest_807, NoReporters_AllMethodsSafe_807) {
    // All forwarding methods should be safe to call with no reporters
    EXPECT_NO_THROW(multiReporter->noMatchingTestCases("spec"_catch_sr));
    EXPECT_NO_THROW(multiReporter->fatalErrorEncountered("err"_catch_sr));
    EXPECT_NO_THROW(multiReporter->reportInvalidTestSpec("arg"_catch_sr));
    EXPECT_NO_THROW(multiReporter->benchmarkPreparing("name"_catch_sr));
    EXPECT_NO_THROW(multiReporter->benchmarkFailed("err"_catch_sr));

    std::vector<ListenerDescription> ld;
    EXPECT_NO_THROW(multiReporter->listListeners(ld));
    std::vector<ReporterDescription> rd;
    EXPECT_NO_THROW(multiReporter->listReporters(rd));
    std::vector<TestCaseHandle> tc;
    EXPECT_NO_THROW(multiReporter->listTests(tc));
    std::vector<TagInfo> ti;
    EXPECT_NO_THROW(multiReporter->listTags(ti));
}

TEST_F(MultiReporterTest_807, CalledMultipleTimes_ForwardedEachTime_807) {
    auto [mock1, ptr1] = createMockListener();
    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(3);
    multiReporter->addReporter(std::move(ptr1));
    multiReporter->noMatchingTestCases("a"_catch_sr);
    multiReporter->noMatchingTestCases("b"_catch_sr);
    multiReporter->noMatchingTestCases("c"_catch_sr);
}
