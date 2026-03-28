// File: optional_assign_move_tests_405.cpp
#include <gtest/gtest.h>
#include <stdexcept>
#include <utility>

// Include the class under test
#include "Catch2/src/catch2/internal/catch_optional.hpp"

using Catch::Optional;

// -------------------------
// Helper types for testing
// -------------------------

// Move-only tracker that lets us observe lifetime & move semantics externally.
struct MoveOnlyTracker {
    static int live_count;
    static int last_destroyed_value;

    int value;
    bool moved_from;

    static void ResetStatics() {
        live_count = 0;
        last_destroyed_value = -777777;
    }

    explicit MoveOnlyTracker(int v) : value(v), moved_from(false) {
        ++live_count;
    }

    // Move-only (no copies)
    MoveOnlyTracker(MoveOnlyTracker&& other) noexcept
        : value(other.value), moved_from(false) {
        other.moved_from = true;
        ++live_count;
    }
    MoveOnlyTracker(const MoveOnlyTracker&) = delete;
    MoveOnlyTracker& operator=(const MoveOnlyTracker&) = delete;
    MoveOnlyTracker& operator=(MoveOnlyTracker&&) = delete;

    ~MoveOnlyTracker() {
        last_destroyed_value = value;
        --live_count;
    }
};
int MoveOnlyTracker::live_count = 0;
int MoveOnlyTracker::last_destroyed_value = -777777;

// Type whose move-ctor throws. Copy-ctor is allowed so we can
// create a non-empty Optional first without triggering the throwing move.
struct ThrowOnMove {
    int tag = 0;

    ThrowOnMove() = default;
    explicit ThrowOnMove(int t) : tag(t) {}

    // Copy allowed (non-throwing), used to construct initial Optional via lvalue.
    ThrowOnMove(const ThrowOnMove&) = default;

    // Move throws to exercise exception path in operator=(T&&)
    ThrowOnMove(ThrowOnMove&&) {
        throw std::runtime_error("move-ctor boom");
    }
};

// -------------------------
// Test fixture
// -------------------------
class OptionalAssignMoveTest_405 : public ::testing::Test {
protected:
    void SetUp() override {
        MoveOnlyTracker::ResetStatics();
    }
};

// ---------------------------------------------------------
// Tests
// ---------------------------------------------------------

// Normal: assign rvalue into empty Optional
TEST_F(OptionalAssignMoveTest_405, AssignIntoEmptyCreatesValue_405) {
    Optional<MoveOnlyTracker> opt;  // empty
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(static_cast<bool>(opt));

    opt = MoveOnlyTracker(7);  // rvalue

    EXPECT_TRUE(opt.some());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ((*opt).value, 7);
    // Exactly one live instance remains in the Optional after the temporary dies.
    EXPECT_EQ(MoveOnlyTracker::live_count, 1);
}

// Normal: assigning a new rvalue over an existing value destroys the old one
TEST_F(OptionalAssignMoveTest_405, AssignOverExistingDestroysOldThenStoresNew_405) {
    Optional<MoveOnlyTracker> opt;
    opt = MoveOnlyTracker(1);
    ASSERT_TRUE(opt.some());
    ASSERT_EQ((*opt).value, 1);

    MoveOnlyTracker::last_destroyed_value = -1;
    opt = MoveOnlyTracker(2);  // overwrite with new rvalue

    EXPECT_TRUE(opt.some());
    EXPECT_EQ((*opt).value, 2);
    // Old value must have been destroyed at some point (observable via helper).
    EXPECT_EQ(MoveOnlyTracker::last_destroyed_value, 1);
    // Only the contained value remains alive.
    EXPECT_EQ(MoveOnlyTracker::live_count, 1);
}

// Boundary-ish: assign from an lvalue that we std::move (moved-from state observable)
TEST_F(OptionalAssignMoveTest_405, AssignFromMovedLvalueMarksSourceMoved_405) {
    Optional<MoveOnlyTracker> opt;
    MoveOnlyTracker src(42);
    EXPECT_FALSE(src.moved_from);

    opt = std::move(src);

    EXPECT_TRUE(opt.some());
    EXPECT_EQ((*opt).value, 42);
    // Source was moved-from (observable external state of helper type).
    EXPECT_TRUE(src.moved_from);
    EXPECT_EQ(MoveOnlyTracker::live_count, 1);
}

// API contract: operator=(T&&) returns Optional& (chaining / identity)
TEST_F(OptionalAssignMoveTest_405, AssignmentReturnsSelfReference_405) {
    Optional<MoveOnlyTracker> opt;
    Optional<MoveOnlyTracker>* ret_ptr = &(opt = MoveOnlyTracker(3));
    EXPECT_EQ(ret_ptr, &opt);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ((*opt).value, 3);
    EXPECT_EQ(MoveOnlyTracker::live_count, 1);
}

// Exceptional path: if T’s move-ctor throws, the exception propagates and
// (per the provided operator= code calling reset() first) the Optional ends up empty.
TEST_F(OptionalAssignMoveTest_405, ExceptionDuringMoveLeavesOptionalEmpty_405) {
    // Prepare a non-empty Optional<ThrowOnMove> using a copy (non-throwing)
    ThrowOnMove seed(11);
    Optional<ThrowOnMove> opt(seed);
    ASSERT_TRUE(opt.some());

    // Now assign from an rvalue that will throw on move
    EXPECT_THROW((opt = ThrowOnMove(22)), std::runtime_error);

    // Observable post-condition: Optional is empty (because reset() happens before construction)
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(static_cast<bool>(opt));
}
