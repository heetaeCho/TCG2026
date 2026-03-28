// File: tests/Reporter/MultiReporter_testRunEnded_804.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

// Catch2 public headers for the interface under test
#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

using ::testing::Ref;
using ::testing::StrictMock;

namespace {

// Minimal mock of IEventListener for verifying observable interactions.
// We only mock testRunEnded because other methods have default implementations.
class MockEventListener_804 : public Catch::IEventListener {
public:
    explicit MockEventListener_804(const Catch::IConfig* config = nullptr)
        : Catch::IEventListener(config) {}

    MOCK_METHOD(void, testRunEnded, (const Catch::TestRunStats&), (override));
};

// Helper to build a dummy TestRunStats purely through the public interface.
// We do NOT depend on any private state or behavior.
inline Catch::TestRunStats makeStats_804(bool aborting = false) {
    Catch::TestRunInfo runInfo{"dummy-run"};
    Catch::Totals totals{}; // default constructed totals
    return Catch::TestRunStats{runInfo, totals, aborting};
}

} // namespace

// --- Tests ---

// [Boundary] No reporters/listeners added: calling testRunEnded should be safe (no crash/throw).
TEST(MultiReporterTest_804, NoReporters_NoThrow_804) {
    Catch::MultiReporter mr{nullptr};
    auto stats = makeStats_804(false);

    EXPECT_NO_THROW(mr.testRunEnded(stats));
}

// [Normal] Single listener added via addListener: call is forwarded exactly once with the same reference.
TEST(MultiReporterTest_804, ForwardsToSingleListener_804) {
    Catch::MultiReporter mr{nullptr};

    // Create strict mock and transfer ownership via Catch's IEventListenerPtr
    auto* raw = new StrictMock<MockEventListener_804>{nullptr};
    Catch::IEventListenerPtr listener{raw};

    auto stats = makeStats_804(false);

    // Expect exactly one call and verify the exact same object reference is forwarded
    EXPECT_CALL(*raw, testRunEnded(Ref(stats))).Times(1);

    mr.addListener(std::move(listener));
    mr.testRunEnded(stats);
}

// [Normal] Single reporter added via addReporter: call is forwarded exactly once with the same reference.
TEST(MultiReporterTest_804, ForwardsToSingleReporter_804) {
    Catch::MultiReporter mr{nullptr};

    auto* raw = new StrictMock<MockEventListener_804>{nullptr};
    Catch::IEventListenerPtr reporter{raw};

    auto stats = makeStats_804(true); // any value; content is not inspected by MultiReporter

    EXPECT_CALL(*raw, testRunEnded(Ref(stats))).Times(1);

    mr.addReporter(std::move(reporter));
    mr.testRunEnded(stats);
}

// [Normal] Multiple reporter-likes (listener + reporter): both receive the call exactly once.
// We do NOT assert on ordering (not part of the documented interface).
TEST(MultiReporterTest_804, ForwardsToAllReporterLikes_804) {
    Catch::MultiReporter mr{nullptr};

    auto* raw1 = new StrictMock<MockEventListener_804>{nullptr};
    auto* raw2 = new StrictMock<MockEventListener_804>{nullptr};

    Catch::IEventListenerPtr listener{raw1};
    Catch::IEventListenerPtr reporter{raw2};

    auto stats = makeStats_804(false);

    EXPECT_CALL(*raw1, testRunEnded(Ref(stats))).Times(1);
    EXPECT_CALL(*raw2, testRunEnded(Ref(stats))).Times(1);

    mr.addListener(std::move(listener));
    mr.addReporter(std::move(reporter));

    mr.testRunEnded(stats);
}

// [Repetition] Calling testRunEnded multiple times forwards each time to all registered reporter-likes.
TEST(MultiReporterTest_804, MultipleInvocations_AreForwarded_804) {
    Catch::MultiReporter mr{nullptr};

    auto* raw = new StrictMock<MockEventListener_804>{nullptr};
    Catch::IEventListenerPtr listener{raw};

    auto stats = makeStats_804(false);

    EXPECT_CALL(*raw, testRunEnded(Ref(stats))).Times(2);

    mr.addListener(std::move(listener));

    mr.testRunEnded(stats);
    mr.testRunEnded(stats);
}
