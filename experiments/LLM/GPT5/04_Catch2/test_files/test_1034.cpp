// File: tests/trackerbase_close_1034_tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/internal/catch_test_case_tracker.hpp>

using ::testing::StrictMock;
using ::testing::InSequence;
using ::testing::Invoke;
using ::testing::Exactly;

namespace Catch { namespace TestCaseTracking {

// ---------- Test doubles (collaborators) ----------

// Minimal fake TrackerContext that lets us:
//  - expose/override current tracker
//  - observe that completeCycle() was called
class FakeTrackerContext : public TrackerContext {
public:
    FakeTrackerContext() : current_(nullptr), completeCalled_(false) {}

    // Expose setters for tests
    void forceSetCurrent(ITracker* t) { current_ = t; }

    // Public observers
    bool completeCalled() const { return completeCalled_; }

    // Shim the required interface that TrackerBase::close() uses
    ITracker& currentTracker() {
        // In production this is non-null; keep same contract in tests.
        // We keep it simple and assume tests set this before use.
        return *current_;
    }

    void completeCycle() {
        completeCalled_ = true;
    }

private:
    ITracker* current_;
    bool completeCalled_;
};

// Concrete TrackerBase we can construct
class ConcreteTracker : public TrackerBase {
public:
    ConcreteTracker(NameAndLocation&& nl, TrackerContext& ctx, ITracker* parent = nullptr)
        : TrackerBase(CATCH_MOVE(nl), ctx, parent) {}
};

// A strict mock over ITracker so we can verify `close()` calls on "other" trackers.
class MockTracker : public ITracker {
public:
    MockTracker(NameAndLocation&& nl, ITracker* parent = nullptr)
        : ITracker(CATCH_MOVE(nl), parent) {}

    // We only need to mock the interactions exercised by TrackerBase::close() loop.
    MOCK_METHOD(void, close, (), (override));
    // Default virtuals (not used here) fall back to ITracker's implementation.
};

// Helper to build a simple NameAndLocation for constructing trackers.
static inline NameAndLocation makeNL(const char* name = "t") {
    // SourceLineInfo is commonly available inside Catch2; use a benign value.
    return NameAndLocation{name, SourceLineInfo{__FILE__, static_cast<std::size_t>(__LINE__)}};
}

}} // namespace Catch::TestCaseTracking

using namespace Catch::TestCaseTracking;

// ---------------- Test fixture ----------------
class TrackerBaseCloseTest_1034 : public ::testing::Test {
protected:
    FakeTrackerContext ctx_;
    // We’ll build the SUT (ConcreteTracker) in each test as needed.
};

// ---------------------- Tests ----------------------

// Normal operation: when currentTracker() is already `this`,
// close() should finish cleanly and call completeCycle().
// Also: open() places tracker into a valid running state through the public API,
// so we do not touch internal state.
TEST_F(TrackerBaseCloseTest_1034, Close_WhenAlreadyCurrent_CallsCompleteCycle_1034) {
    ConcreteTracker sut(makeNL("sut"), ctx_);
    sut.open();                      // public API; establishes running state
    ctx_.forceSetCurrent(&sut);      // collaborator behavior

    sut.close();

    EXPECT_TRUE(ctx_.completeCalled());
    // Optionally, verify a successful completion is observable via public API
    // (depends on Catch2's ITracker contract).
    EXPECT_TRUE(sut.isSuccessfullyCompleted());
}

// Interaction verification: If some *other* tracker is current,
// close() should repeatedly call that tracker's close() until `this` becomes current.
// Here it takes exactly one step.
TEST_F(TrackerBaseCloseTest_1034, Close_UnwindsOnceByClosingCurrentTracker_1034) {
    ConcreteTracker sut(makeNL("sut"), ctx_);
    sut.open();

    StrictMock<MockTracker> other(makeNL("other"));
    // Initially, "other" is current
    ctx_.forceSetCurrent(&other);

    {
        InSequence s;
        EXPECT_CALL(other, close())
            .WillOnce(Invoke([&](){
                // After closing "other", context now points to sut
                ctx_.forceSetCurrent(&sut);
            }));
    }

    sut.close();

    EXPECT_TRUE(ctx_.completeCalled());
    EXPECT_TRUE(sut.isSuccessfullyCompleted());
}

// Interaction verification: multi-step unwind.
// currentTracker() starts at other1 -> close() moves to other2 -> close() moves to sut.
// We verify both others are closed in order, then completeCycle() is called.
TEST_F(TrackerBaseCloseTest_1034, Close_UnwindsMultipleLevels_1034) {
    ConcreteTracker sut(makeNL("sut"), ctx_);
    sut.open();

    StrictMock<MockTracker> other1(makeNL("other1"));
    StrictMock<MockTracker> other2(makeNL("other2"));

    // Start with other1 as "current"
    ctx_.forceSetCurrent(&other1);

    {
        InSequence seq;
        EXPECT_CALL(other1, close())
            .WillOnce(Invoke([&](){
                // Step 1: move to other2
                ctx_.forceSetCurrent(&other2);
            }));
        EXPECT_CALL(other2, close())
            .WillOnce(Invoke([&](){
                // Step 2: now move to sut
                ctx_.forceSetCurrent(&sut);
            }));
    }

    sut.close();

    EXPECT_TRUE(ctx_.completeCalled());
    EXPECT_TRUE(sut.isSuccessfullyCompleted());
}

// Boundary/edge case observable via public API:
// If the tracker is marked as needing another run via the *public* API,
// close() should not mark it as successfully completed (per interface contract).
// We still expect completeCycle() to be called.
TEST_F(TrackerBaseCloseTest_1034, Close_WhenNeedsAnotherRun_DoesNotReportSuccess_ButCompletesCycle_1034) {
    ConcreteTracker sut(makeNL("sut"), ctx_);
    sut.open();
    ctx_.forceSetCurrent(&sut);

    // Public method to express "needs another run" (no private access)
    sut.markAsNeedingAnotherRun();

    sut.close();

    EXPECT_TRUE(ctx_.completeCalled());
    EXPECT_FALSE(sut.isSuccessfullyCompleted());
}
