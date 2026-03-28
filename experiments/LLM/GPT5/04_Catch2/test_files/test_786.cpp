// File: tests/reporter/MultiReporter_addListener_786_tests.cpp
#include <gtest/gtest.h>
#include <catch2/reporters/catch_reporter_multi.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>

using namespace Catch;

// A minimal concrete IEventListener that records observable calls via a shared log.
// It implements all interface methods to avoid relying on GoogleMock for heavy signatures.
class RecordingListener final : public IEventListener {
public:
    explicit RecordingListener(std::vector<std::string>& log, std::string id)
        : m_log(&log), m_id(std::move(id)) {}

    // Observable event we assert on in tests
    void testRunStarting(const TestRunInfo& tri) override {
        (void)tri; // we don't depend on contents; only that the call happened
        m_log->push_back(m_id);
    }

    // Remaining interface methods: provided as no-ops to satisfy the interface.
    void noMatchingTestCases(StringRef) override {}
    void fatalErrorEncountered(StringRef) override {}
    void reportInvalidTestSpec(StringRef) override {}

    void benchmarkPreparing(StringRef) override {}
    void benchmarkStarting(const BenchmarkInfo&) override {}
    void benchmarkEnded(const BenchmarkStats<>&) override {}
    void benchmarkFailed(StringRef) override {}

    void testCaseStarting(const TestCaseInfo&) override {}
    void testCasePartialStarting(const TestCaseInfo&, uint64_t) override {}
    void sectionStarting(const SectionInfo&) override {}
    void assertionStarting(const AssertionInfo&) override {}
    void assertionEnded(const AssertionStats&) override {}
    void sectionEnded(const SectionStats&) override {}
    void testCasePartialEnded(const TestCaseStats&, uint64_t) override {}
    void testCaseEnded(const TestCaseStats&) override {}
    void testRunEnded(const TestRunStats&) override {}
    void skipTest(const TestCaseInfo&) override {}

    void listReporters(const std::vector<ReporterDescription>&) override {}
    void listListeners(const std::vector<ListenerDescription>&) override {}
    void listTests(const std::vector<TestCaseHandle>&) override {}
    void listTags(const std::vector<TagInfo>&) override {}

private:
    std::vector<std::string>* m_log;
    std::string m_id;
};

// -----------------------------
// Tests for addListener (TEST_ID: 786)
// -----------------------------

// Verifies that a single listener added via addListener receives forwarded events.
TEST(MultiReporterAddListener_786, SingleListenerReceivesEvent_786) {
    MultiReporter mr;

    std::vector<std::string> calls;
    auto* l1_raw = new RecordingListener(calls, "L1");
    IEventListenerPtr l1{ l1_raw };

    mr.addListener(std::move(l1));

    // Trigger an observable event through the public interface
    TestRunInfo tri{ "dummy-run" };
    mr.testRunStarting(tri);

    ASSERT_EQ(calls.size(), 1u);
    EXPECT_EQ(calls[0], "L1");
}

// Verifies that multiple listeners added via addListener are all notified.
// (We assert only on delivery, not internal state.)
TEST(MultiReporterAddListener_786, MultipleListenersAllReceiveEvent_786) {
    MultiReporter mr;

    std::vector<std::string> calls;
    IEventListenerPtr l1{ new RecordingListener(calls, "L1") };
    IEventListenerPtr l2{ new RecordingListener(calls, "L2") };

    mr.addListener(std::move(l1));
    mr.addListener(std::move(l2));

    TestRunInfo tri{ "multi" };
    mr.testRunStarting(tri);

    ASSERT_EQ(calls.size(), 2u);
    // Registration order should be observable via call order for forwarded events
    EXPECT_EQ(calls[0], "L1");
    EXPECT_EQ(calls[1], "L2");
}

// Verifies insertion behavior that is observable through call order relative to reporters.
// Scenario:
//   1) addReporter(RA)
//   2) addListener(L1)
//   3) addReporter(RB)
//   4) addListener(L2)
// When an event is forwarded, expected order (observable):
//   L1, L2, RA, RB
TEST(MultiReporterAddListener_786, ListenersPlacedBeforeReportersAndPreserveRegistrationOrder_786) {
    MultiReporter mr;

    std::vector<std::string> calls;

    // "Reporters" and "Listeners" are both IEventListener; observable difference
    // is *how* they are added to MultiReporter.
    IEventListenerPtr rA{ new RecordingListener(calls, "RA") };
    mr.addReporter(std::move(rA)); // reporter added first

    IEventListenerPtr l1{ new RecordingListener(calls, "L1") };
    mr.addListener(std::move(l1)); // listener should be placed before existing reporters

    IEventListenerPtr rB{ new RecordingListener(calls, "RB") };
    mr.addReporter(std::move(rB)); // another reporter appended

    IEventListenerPtr l2{ new RecordingListener(calls, "L2") };
    mr.addListener(std::move(l2)); // next listener goes after previous listeners, still before reporters

    TestRunInfo tri{ "order-check" };
    mr.testRunStarting(tri);

    // We expect that listeners (in their registration order) are called before reporters (in their registration order).
    std::vector<std::string> expected{ "L1", "L2", "RA", "RB" };
    ASSERT_EQ(calls.size(), expected.size());
    EXPECT_EQ(calls, expected);
}
