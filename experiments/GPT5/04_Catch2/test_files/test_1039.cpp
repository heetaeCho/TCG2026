// File: tests/section_tracker_tryopen_1039_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Use the real headers from your codebase.
// These includes are indicative; adjust paths if your tree differs.
#include "catch2/internal/catch_test_case_tracker.hpp"

using ::testing::_;
using ::testing::Exactly;
using ::testing::Return;

using namespace Catch::TestCaseTracking;

// ---- Test double: only to observe external interactions (public virtuals) ----
// We DO NOT simulate internal state transitions; we only stub public queries and
// observe calls to public/virtual methods as allowed by the constraints.
class TestableSectionTracker_1039 : public SectionTracker {
public:
    using SectionTracker::SectionTracker;

    // Public, virtual in the interface — safe to mock for observable behavior
    MOCK_METHOD(bool, isComplete, (), (const, override));
    MOCK_METHOD(void, open, (), (override));
};

// A lightweight helper to construct a SectionTracker. The concrete types below
// are part of the public interface; we just provide minimal values.
// (No internal behavior is relied upon.)
static TestableSectionTracker_1039 makeTracker_1039(TrackerContext& ctx) {
    NameAndLocation nl{"tryOpen target", SourceLineInfo{"<test>", 1}};
    // Parent can be nullptr – we are testing the unit in isolation.
    return TestableSectionTracker_1039(std::move(nl), ctx, /*parent*/nullptr);
}

// -----------------------------------------------------------------------------

// TEST_ID: 1039
TEST(SectionTracker_TryOpen_1039, OpensWhenNotComplete_1039) {
    TrackerContext ctx;
    auto tracker = makeTracker_1039(ctx);

    EXPECT_CALL(tracker, isComplete())
        .Times(Exactly(1))
        .WillOnce(Return(false));
    EXPECT_CALL(tracker, open())
        .Times(Exactly(1));

    tracker.tryOpen();
}

// TEST_ID: 1039
TEST(SectionTracker_TryOpen_1039, DoesNotOpenWhenAlreadyComplete_1039) {
    TrackerContext ctx;
    auto tracker = makeTracker_1039(ctx);

    EXPECT_CALL(tracker, isComplete())
        .Times(Exactly(1))
        .WillOnce(Return(true));
    EXPECT_CALL(tracker, open())
        .Times(Exactly(0));

    tracker.tryOpen();
}

// TEST_ID: 1039
TEST(SectionTracker_TryOpen_1039, MultipleCallsOnlyOpenIfNotComplete_1039) {
    TrackerContext ctx;
    auto tracker = makeTracker_1039(ctx);

    // 1st call => not complete => should open
    // 2nd call => complete => should not open
    ::testing::InSequence seq;
    EXPECT_CALL(tracker, isComplete())
        .WillOnce(Return(false));
    EXPECT_CALL(tracker, open())
        .Times(Exactly(1));
    EXPECT_CALL(tracker, isComplete())
        .WillOnce(Return(true));
    EXPECT_CALL(tracker, open())
        .Times(Exactly(0));

    tracker.tryOpen();  // triggers open()
    tracker.tryOpen();  // should be a no-op w.r.t open()
}
