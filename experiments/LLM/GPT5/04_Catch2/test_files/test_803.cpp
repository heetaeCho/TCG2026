// File: tests/Reporter/MultiReporter_testCaseEnded_803.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

// NOTE:
// - We only verify externally observable behavior: that MultiReporter forwards
//   testCaseEnded(...) to each registered reporter/listener.
// - We never touch private state or infer internal logic.
// - We use Google Mock strictly to observe external collaborator interactions.

using ::testing::_;
using ::testing::Ref;
using ::testing::InSequence;
using ::testing::AnyNumber;

namespace {

// Minimal mock of IEventListener that only cares about testCaseEnded
struct MockListener : Catch::IEventListener {
    // IEventListener requires a config pointer; MultiReporter uses it internally.
    // For forwarding tests it's fine to pass nullptr.
    explicit MockListener() : Catch::IEventListener(/*config*/nullptr) {}

    MOCK_METHOD(void, testCaseEnded,
                (Catch::TestCaseStats const&),
                (override));
};

// Helper: create a trivially valid TestCaseStats we can pass by const&.
// We avoid depending on internal fields; the forwarding only needs a reference.
static Catch::TestCaseStats makeDummyStats() {
    // These types/ctors come from Catch2. If your local Catch2 version
    // needs different construction, adjust this block only.
    Catch::Totals totals{}; // usually default-constructible

    // Create a minimal TestCaseInfo. Prefer the simplest available ctor in your tree.
    // For many v2/v3 builds, default construction works; otherwise use whatever
    // TestCaseInfo factory/ctor you already use across your test suite.
    Catch::TestCaseInfo dummyInfo{};

    return Catch::TestCaseStats(
        dummyInfo,
        totals,
        std::string{},   // stdOut
        std::string{},   // stdErr
        /*aborting*/false
    );
}

// Convenience to wrap a raw pointer mock into Catch's unique_ptr alias.
// In Catch2 it is typically `using IEventListenerPtr = Detail::unique_ptr<IEventListener>;`.
static Catch::IEventListenerPtr take(Catch::IEventListener* p) {
    return Catch::IEventListenerPtr(p);
}

} // namespace

// --- Tests ------------------------------------------------------------------

// Normal operation: single listener receives exactly one forwarded call with the
// exact same TestCaseStats reference.
TEST(MultiReporterTest_803, ForwardsToSingleListener_803) {
    Catch::MultiReporter mr(/*config*/nullptr);

    auto* l = new MockListener();
    Catch::IEventListenerPtr lp = take(l);
    EXPECT_CALL(*l, testCaseEnded(_)).Times(1);

    mr.addListener(std::move(lp)); // black-box API

    auto stats = makeDummyStats();
    EXPECT_CALL(*l, testCaseEnded(Ref(stats))).Times(1); // same object identity

    mr.testCaseEnded(stats);
}

// Normal operation: multiple listeners all receive the call.
// We do not rely on internal state, only verify each collaborator is invoked once.
TEST(MultiReporterTest_803, ForwardsToAllListeners_803) {
    Catch::MultiReporter mr(/*config*/nullptr);

    auto* l1 = new MockListener();
    auto* l2 = new MockListener();
    auto* l3 = new MockListener();

    mr.addListener(take(l1));
    mr.addListener(take(l2));
    mr.addListener(take(l3));

    auto stats = makeDummyStats();
    EXPECT_CALL(*l1, testCaseEnded(Ref(stats))).Times(1);
    EXPECT_CALL(*l2, testCaseEnded(Ref(stats))).Times(1);
    EXPECT_CALL(*l3, testCaseEnded(Ref(stats))).Times(1);

    mr.testCaseEnded(stats);
}

// Boundary condition: no listeners added. The call should be a no-op (no crash).
// We can't "observe" silence directly, but reaching the end of the test is success.
TEST(MultiReporterTest_803, NoListenersNoCrash_803) {
    Catch::MultiReporter mr(/*config*/nullptr);
    auto stats = makeDummyStats();
    // Should not throw/terminate
    mr.testCaseEnded(stats);
    SUCCEED();
}

// (Optional, still observable) Mixed registration: reporters and listeners all get called.
// If your MultiReporter does not distinguish in forwarding between "reporter" and "listener",
// this remains a pure external-behavior test.
TEST(MultiReporterTest_803, ReporterAndListenerBothReceiveForward_803) {
    Catch::MultiReporter mr(/*config*/nullptr);

    auto* listener = new MockListener();
    auto* reporter = new MockListener(); // still IEventListener per public API

    mr.addListener(take(listener));
    mr.addReporter(take(reporter));

    auto stats = makeDummyStats();
    EXPECT_CALL(*listener, testCaseEnded(Ref(stats))).Times(1);
    EXPECT_CALL(*reporter, testCaseEnded(Ref(stats))).Times(1);

    mr.testCaseEnded(stats);
}

// (Optional) Order verification: if your project REQUIRES stable insertion order,
// you can keep this test; otherwise, remove it to avoid over-specifying behavior.
TEST(MultiReporterTest_803, ForwardsInRegistrationOrder_803) {
    Catch::MultiReporter mr(/*config*/nullptr);

    auto* first  = new MockListener();
    auto* second = new MockListener();

    mr.addListener(take(first));
    mr.addListener(take(second));

    auto stats = makeDummyStats();
    InSequence seq; // enforce call order on mocks
    EXPECT_CALL(*first,  testCaseEnded(Ref(stats))).Times(1);
    EXPECT_CALL(*second, testCaseEnded(Ref(stats))).Times(1);

    mr.testCaseEnded(stats);
}
