// File: tests/Reporter/MultiReporter_testRunStarting_795.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_test_run_info.hpp"
#include "catch2/internal/catch_stringref.hpp"

using ::testing::_;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::Truly;

namespace Catch {

// Simple mock that overrides only what we need.
// Note: IEventListener provides default (non-pure) virtuals, so we only mock the one we verify.
struct MockListener : IEventListener {
    explicit MockListener(const IConfig* cfg = nullptr) : IEventListener(cfg) {}
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo&), (override));
};

} // namespace Catch

// Test fixture that constructs MultiReporter with a null config pointer.
// We don't rely on any internal state; we only use public methods to add listeners/reporters.
class MultiReporterTest_795 : public ::testing::Test {
protected:
    // Assuming MultiReporter has a ctor that accepts IConfig const* (as per Catch2 style).
    Catch::MultiReporter multi_{ /*config*/ nullptr };

    // Helper to create & move unique ptrs while keeping a raw pointer for expectations.
    template <typename MockT>
    static std::pair<MockT*, Catch::IEventListenerPtr> makeOwned(MockT* raw) {
        return {raw, Catch::IEventListenerPtr(raw)};
    }
};

// 1) No reporters/listeners: calling testRunStarting should be a no-op (no crashes).
TEST_F(MultiReporterTest_795, NoReporters_NoCrash_795) {
    Catch::TestRunInfo info{ Catch::StringRef("empty-run") };
    // Just ensure it does not throw/crash.
    multi_.testRunStarting(info);
    SUCCEED();
}

// 2) Single reporter: the call is forwarded exactly once with the same run name.
TEST_F(MultiReporterTest_795, SingleReporter_ForwardedExactlyOnce_795) {
    auto [mockPtr, ptr] = makeOwned(new NiceMock<Catch::MockListener>());
    EXPECT_CALL(*mockPtr, testRunStarting(Truly([](const Catch::TestRunInfo& tri) {
        return tri.name == Catch::StringRef("suite-A");
    }))).Times(1);

    multi_.addReporter(std::move(ptr));

    Catch::TestRunInfo info{ Catch::StringRef("suite-A") };
    multi_.testRunStarting(info);
}

// 3) Two reporters: both receive the call; verify call order matches insertion order.
TEST_F(MultiReporterTest_795, MultipleReporters_BothCalledInInsertionOrder_795) {
    auto [mock1, p1] = makeOwned(new StrictMock<Catch::MockListener>());
    auto [mock2, p2] = makeOwned(new StrictMock<Catch::MockListener>());

    {
        InSequence seq;
        EXPECT_CALL(*mock1, testRunStarting(_)).Times(1);
        EXPECT_CALL(*mock2, testRunStarting(_)).Times(1);
    }

    multi_.addReporter(std::move(p1)); // inserted first
    multi_.addReporter(std::move(p2)); // inserted second

    Catch::TestRunInfo info{ Catch::StringRef("ordered-run") };
    multi_.testRunStarting(info);
}

// 4) Mixing listener & reporter: both are notified (we do not assert cross-type order).
TEST_F(MultiReporterTest_795, ListenerAndReporter_BothReceiveNotification_795) {
    auto [listenerMock, lp] = makeOwned(new NiceMock<Catch::MockListener>());
    auto [reporterMock, rp] = makeOwned(new NiceMock<Catch::MockListener>());

    EXPECT_CALL(*listenerMock, testRunStarting(_)).Times(1);
    EXPECT_CALL(*reporterMock, testRunStarting(_)).Times(1);

    multi_.addListener(std::move(lp));
    multi_.addReporter(std::move(rp));

    Catch::TestRunInfo info{ Catch::StringRef("mix-run") };
    multi_.testRunStarting(info);
}

// 5) Boundary: empty test run name should still propagate to children.
TEST_F(MultiReporterTest_795, PropagatesEmptyRunName_795) {
    auto [mockPtr, ptr] = makeOwned(new NiceMock<Catch::MockListener>());
    EXPECT_CALL(*mockPtr, testRunStarting(Truly([](const Catch::TestRunInfo& tri) {
        return tri.name.size() == 0;
    }))).Times(1);

    multi_.addReporter(std::move(ptr));

    Catch::TestRunInfo info{ Catch::StringRef("") };
    multi_.testRunStarting(info);
}

// 6) Boundary: non-ASCII run name should be forwarded intact.
TEST_F(MultiReporterTest_795, PropagatesUnicodeRunName_795) {
    auto [mockPtr, ptr] = makeOwned(new NiceMock<Catch::MockListener>());
    EXPECT_CALL(*mockPtr, testRunStarting(Truly([](const Catch::TestRunInfo& tri) {
        return tri.name == Catch::StringRef("테스트런");
    }))).Times(1);

    multi_.addReporter(std::move(ptr));

    Catch::TestRunInfo info{ Catch::StringRef("테스트런") };
    multi_.testRunStarting(info);
}
